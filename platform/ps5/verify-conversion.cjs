// Adapted from the owner PE1 native metadata verification route. Static only.
const fs = require('fs'), crypto = require('crypto'), path = require('path');
if (process.argv.length !== 5) throw Error('Usage: node verify-conversion.cjs <input-ELF> <conversion-directory> <output-json>');
const [input, dir, output] = process.argv.slice(2).map(x => path.resolve(x));
const check = (v, m) => { if (!v) throw Error(m); };
function load(file) {
    const b = fs.readFileSync(file), u = o => Number(b.readBigUInt64LE(o)), ph = [];
    for (let i = 0; i < b.readUInt16LE(56); i++) {
        const o = u(32) + i * b.readUInt16LE(54);
        ph.push({ type: b.readUInt32LE(o), offset: u(o + 8), address: u(o + 16), filesz: u(o + 32), memsz: u(o + 40) });
    }
    const at = a => { const p = ph.find(p => p.type === 1 && a >= p.address && a < p.address + p.filesz); check(p, 'Unmapped metadata ' + a); return p.offset + a - p.address; };
    const d = ph.find(p => p.type === 2), tags = new Map();
    for (let o = d.offset; o < d.offset + d.filesz; o += 16) {
        const t = u(o); if (!t) break; const a = tags.get(t) || []; a.push(b.readBigUInt64LE(o + 8)); tags.set(t, a);
    }
    const val = t => Number((tags.get(t) || [0n])[0]);
    const str = o => { const a = at(val(5)) + o; return b.toString('utf8', a, b.indexOf(0, a)); };
    return { b, ph, at, tags, val, str };
}
const a = load(input), b = load(path.join(dir, 'eboot.elf'));
const rel = e => { const start = e.at(e.val(7)); return Array.from({ length: e.val(8) / 24 }, (_, i) => e.b.subarray(start + i * 24, start + i * 24 + 24).toString('hex')); };
const old = rel(a), remaining = new Map();
for (const r of rel(b)) remaining.set(r, (remaining.get(r) || 0) + 1);
for (const r of old) { check(remaining.get(r) > 0, 'Lost/changed source relocation'); remaining.set(r, remaining.get(r) - 1); }
const added = [...remaining.entries()].flatMap(([r, count]) => Array(count).fill(r));
check(added.length === 8, 'Expected exactly eight process-parameter relocations');
const parameters = b.ph.find(p => p.type === 0x61000001); check(parameters, 'Missing process parameters');
for (const r of added) { const v = Buffer.from(r, 'hex'); check(v.readBigUInt64LE(8) === 8n && Number(v.readBigUInt64LE(0)) >= parameters.address, 'Invalid added relocation'); }
for (const tag of [12, 13, 25, 26, 27, 28, 32, 33]) check(a.val(tag) === b.val(tag), 'Changed init/fini pointer/size ' + tag);
const imports = JSON.parse(fs.readFileSync(path.join(dir, 'imports.json'), 'utf8')).Imports;
const symbolCount = imports.length + 1;
check(b.val(0x6100003f) === symbolCount * 24, 'Converted symbol table size mismatch');
const modules = (b.tags.get(0x61000045) || []).map(v => ({ id: Number(v >> 48n), name: b.str(Number(v & 0xffffffffn)) }));
const libs = (b.tags.get(0x61000049) || []).map(v => ({ id: Number(v >> 48n), name: b.str(Number(v & 0xffffffffn)) }));
const needed = a.tags.get(1).map(v => a.str(Number(v)).replace(/\.sprx$/, '.prx'));
check(JSON.stringify(needed) === JSON.stringify(b.tags.get(1).map(v => b.str(Number(v)))), 'Module order changed');
const alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-';
const decode = s => [...s].reduce((n, c) => n * 64 + alphabet.indexOf(c), 0);
const salt = Buffer.from('518d64a635ded8c1e6b039b1c3e55230', 'hex');
for (let i = 1; i < symbolCount; i++) {
    const oldAt = a.at(a.val(6)) + i * 24, newAt = b.at(b.val(6)) + i * 24;
    const name = a.str(a.b.readUInt32LE(oldAt)), parts = b.str(b.b.readUInt32LE(newAt)).split('#');
    const h = crypto.createHash('sha1').update(name).update(salt).digest();
    const nid = Buffer.from(h.subarray(0, 8)).reverse().toString('base64').replace(/=+$/, '').replaceAll('/', '-');
    check(parts[0] === nid, 'NID mismatch ' + name);
    const provider = imports.find(x => x.Symbol === name);
    check(modules.find(x => x.id === decode(parts[2]))?.name === provider.Module.replace(/\.sprx$|\.prx$/, ''), 'Provider mismatch ' + name);
    check(libs.some(x => x.id === decode(parts[1])), 'Missing import library ' + name);
    check(a.b.subarray(oldAt + 4, oldAt + 24).equals(b.b.subarray(newAt + 4, newAt + 24)), 'Changed import attributes ' + name);
}
const sha = value => crypto.createHash('sha256').update(value).digest('hex');
fs.writeFileSync(output, JSON.stringify({ passed: true, inputSHA256: sha(a.b), outputSHA256: sha(b.b), sourceRelocations: old.length,
    addedProcessParameterRelocations: added.length, allSourceRelocationsByteIdentical: true,
    constructorsAndFinalizersPreserved: true, importNidsAndProvidersVerified: imports.length, neededOrder: needed, runtime: false }, null, 2) + '\n');
console.log('Source relocations, constructor metadata and import NIDs/providers verified.');
