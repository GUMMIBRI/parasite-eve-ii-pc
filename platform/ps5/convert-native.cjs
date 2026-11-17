// PE2 adaptation of GUMMIBRI/parasite-eve-ps5's native conversion checks.
// Source recipe/tool digests are recorded with the result. Static tools only.
const fs = require('fs'), path = require('path'), cp = require('child_process'), crypto = require('crypto');
if (process.argv.length < 6 || process.argv.length > 7) throw Error('Usage: node convert-native.cjs <PE2-build-output> <public-prefix> <native-tool> <audit-recipe-directory> [attempt-name]');
const [build, base, tool, recipe] = process.argv.slice(2, 6).map(x => path.resolve(x));
const attempt = process.argv[6] || 'converted';
if (!/^[a-zA-Z0-9-]+$/.test(attempt)) throw Error('Attempt name must be a single directory component');
const project = path.resolve(__dirname, '../../..');
if (!build.toLowerCase().startsWith((project + path.sep).toLowerCase())) throw Error('Build must be inside isolated PE2 project');
const out = path.join(build, attempt), llvm = path.join(base, 'deps/llvm/bin');
const stubs = path.join(base, 'deps/ps5-payload-sdk/target/lib');
const sha = f => crypto.createHash('sha256').update(fs.readFileSync(f)).digest('hex');
const record = f => ({ path: f, sha256: sha(f), bytes: fs.statSync(f).size });
const save = (name, value) => fs.writeFileSync(path.join(out, name), JSON.stringify(value, null, 2) + '\n');
function assert(ok, message) { if (!ok) throw Error(message); }
assert(sha(tool) === '78fdfec756c6e7fa132bd2fbf6eeaea753d9b01349d09a8993bba76eed77fd84', 'Reviewed converter digest mismatch');
assert(!fs.existsSync(path.join(out, 'eboot.elf')), 'Fresh conversion directory required');
fs.mkdirSync(path.join(out, 'recipe'), { recursive: true });
const recipes = ['audit-application-imports.ps1', 'audit-application-runtime.ps1', 'inspect-executable.ps1'].map(name => {
    const file = path.join(recipe, name); fs.copyFileSync(file, path.join(out, 'recipe', name)); return record(file);
});
const commands = [];
function run(exe, args, name) {
    commands.push({ exe, args });
    const r = cp.spawnSync(exe, args, { encoding: 'utf8', windowsHide: true, maxBuffer: 256 * 1024 * 1024 });
    fs.writeFileSync(path.join(out, name), (r.stdout || '') + (r.stderr || ''));
    save('COMMANDS.json', commands);
    assert(r.status === 0, name + ': exit ' + r.status); return r.stdout;
}
function elf(file) {
    const b = fs.readFileSync(file), u = o => Number(b.readBigUInt64LE(o));
    assert(b.length >= 64 && b.readUInt32LE(0) === 0x464c457f && b[4] === 2 && b[5] === 1 && b.readUInt16LE(18) === 62, 'Require ELF64 x86-64');
    const ph = [], sh = [];
    for (let i = 0; i < b.readUInt16LE(56); i++) {
        const o = u(32) + i * b.readUInt16LE(54);
        ph.push({ type: b.readUInt32LE(o), flags: b.readUInt32LE(o + 4), offset: u(o + 8), address: u(o + 16), filesz: u(o + 32), memsz: u(o + 40), align: u(o + 48) });
    }
    for (let i = 0; i < b.readUInt16LE(60); i++) {
        const o = u(40) + i * b.readUInt16LE(58);
        sh.push({ nameAt: b.readUInt32LE(o), type: b.readUInt32LE(o + 4), flags: u(o + 8), address: u(o + 16), offset: u(o + 24), size: u(o + 32), link: b.readUInt32LE(o + 40), align: u(o + 48) });
    }
    const names = sh[b.readUInt16LE(62)];
    if (names) for (const s of sh) { const a = names.offset + s.nameAt; s.name = b.toString('utf8', a, b.indexOf(0, a)); }
    return { b, ph, sh, type: b.readUInt16LE(16), entry: u(24) };
}
const input = path.join(build, 'game/parasite-eve-ii-ps5.elf'), e = elf(input), section = n => e.sh.find(s => s.name === n);
assert(e.type === 3 && e.entry > 0 && section('.text')?.address === 0, 'Require native PIE entry and zero-based text');
assert(!e.ph.some(p => p.type === 7) && !e.sh.some(s => s.flags & 0x400), 'Native TLS requires separate loader review');
for (const p of e.ph.filter(p => p.type === 1)) assert(p.filesz <= p.memsz && p.offset + p.filesz <= e.b.length && p.align === 0x4000 && p.offset % p.align === p.address % p.align, 'Invalid native LOAD');
const dyn = section('.dynsym'); assert(dyn, 'Missing dynamic symbols');
for (let o = dyn.offset + 24; o < dyn.offset + dyn.size; o += 24) assert(e.b.readUInt16LE(o + 6) === 0, 'Converter cannot publish exports');
const assets = section('.data.rel.ro.peassets'); assert(assets && assets.size > 0 && assets.size % 32 === 0 && assets.address % 8 === 0, 'PE2 asset registry missing/misaligned');
const retained = e.sh.filter(s => /^\.(got(?:\.plt)?|data\.rel\.ro.*|preinit_array.*|init_array.*|fini_array.*)$/.test(s.name));
const end = Math.max(...retained.map(s => s.address + s.size));
assert(section('.dynamic').address > end, 'No metadata room after retained registry/RELRO');
const relocationTypes = {};
for (const s of e.sh.filter(s => s.type === 4)) for (let o = s.offset; o < s.offset + s.size; o += 24) {
    const type = e.b.readUInt32LE(o + 8); relocationTypes[type] = (relocationTypes[type] || 0) + 1;
    assert([1, 6, 7, 8].includes(type), 'Unreviewed relocation type ' + type);
}
const nm = run(path.join(llvm, 'llvm-nm.exe'), ['-n', input], 'symbols.txt');
assert(!/\b(__crt_start|payload_get_args|kernel_init)\b/.test(nm) && /\b_start\r?$/m.test(nm), 'Wrong application entry/runtime');
run('pwsh', ['-NoProfile', '-File', path.join(out, 'recipe/audit-application-imports.ps1'), '-Elf', input, '-StubDirectory', stubs, '-ReadElf', path.join(llvm, 'llvm-readelf.exe'), '-Output', path.join(out, 'imports.json')], 'imports.log');
run('pwsh', ['-NoProfile', '-File', path.join(out, 'recipe/audit-application-runtime.ps1'), '-Elf', input, '-ImportAudit', path.join(out, 'imports.json'), '-LlvmBin', llvm, '-Output', path.join(out, 'runtime.json')], 'runtime.log');
save('PREFLIGHT.json', { passed: true, input: record(input), assets: { address: assets.address, bytes: assets.size, records: assets.size / 32 }, lastRetainedByte: end, relocationTypes, recipes });
const converted = path.join(out, 'eboot.elf');
run(tool, ['link', '--in', input, '--out', converted, '--stub-dir', stubs, '--file-name', 'eboot.elf'], 'link.log');
const c = elf(converted), comparisons = [];
assert(c.type === 0xfe10 && c.entry === e.entry, 'Converted type/entry mismatch');
for (const s of e.sh.filter(s => (s.flags & 2) && s.size && s.type !== 8 && !/^\.(dynstr|dynsym|dynamic|hash|gnu\.hash|rela\.)/.test(s.name))) {
    const p = c.ph.find(p => p.type === 1 && s.address >= p.address && s.address + s.size <= p.address + p.filesz);
    assert(p, 'Unmapped retained section ' + s.name);
    const at = p.offset + s.address - p.address;
    assert(e.b.subarray(s.offset, s.offset + s.size).equals(c.b.subarray(at, at + s.size)), 'Changed bytes: ' + s.name);
    comparisons.push({ name: s.name, address: s.address, bytes: s.size, identical: true });
}
assert(comparisons.some(s => s.name === '.data.rel.ro.peassets'), 'PE2 registry not explicitly verified');
for (const s of e.sh.filter(s => (s.flags & 2) && s.type === 8 && s.size)) {
    const p = c.ph.find(p => p.type === 1 && s.address >= p.address && s.address + s.size <= p.address + p.memsz);
    assert(p && s.address >= p.address + p.filesz, 'BSS not preserved: ' + s.name);
}
for (const p of c.ph.filter(p => p.type === 1)) assert(p.filesz <= p.memsz && p.offset + p.filesz <= c.b.length && p.offset % 0x4000 === p.address % 0x4000, 'Converted LOAD bounds/alignment');
save('RETAINED-SECTIONS.json', { passed: true, entryPreserved: true, bssPreserved: true, comparisons, programHeaders: c.ph });
run('pwsh', ['-NoProfile', '-File', path.join(out, 'recipe/inspect-executable.ps1'), '-Path', converted, '-RequireApplicationElf'], 'shape.json');
const self = path.join(out, 'eboot.bin');
run(tool, ['self', '--sign', '--in', converted, '--out', self], 'sign.log');
const inspection = run(tool, ['self', '--inspect', '--file', self], 'self-inspect.log');
assert(/^integrity:\s*valid\s*$/m.test(inspection), 'SELF integrity invalid');
save('RESULT.json', { input: record(input), converted: record(converted), self: record(self), converter: record(tool), sdkConversion: true, selfIntegrity: true, runtime: false, consoleValidated: false });
console.log('PE2 native conversion/retention/import/runtime-shape/SELF checks passed; no console execution.');
