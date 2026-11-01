# Parasite Eve II — native PC port

A native port of *Parasite Eve II* (PlayStation, USA release) built from the
matching decompilation of the original game code and
[PsyZ](https://github.com/khasinski/parasite-eve-psyz), a drop-in replacement
for the PlayStation runtime library (Psy-Q) on top of SDL3.

> **Status: pre-alpha, work in progress.** Nothing is playable yet. The port is
> modelled on [parasite-eve-pc](https://github.com/khasinski/parasite-eve-pc),
> our port of the first game.

You need **your own copy of the game**. This repository contains no game data:
the port reads your North American CUE/BIN disc images at runtime (both discs,
with automatic switching).

## Approach

- The original game code is compiled natively with a host C11 compiler and
  linked against PsyZ. This is neither an emulator nor a static recompiler.
- The port is one-way: byte-matching the PS1 binaries is not a goal. Compiler
  workarounds from the decompilation (register pins, scheduling barriers,
  declaration order for the linker) are removed as the code is repaired.
- Game data is loaded from the disc images at runtime. Disc records (32-bit
  offsets and addresses) are decoded into host structures; pointers are never
  stored in 32-bit fields.
- Overlays are linked statically with explicit state and reset.

See [docs/PORT_PLAN.md](docs/PORT_PLAN.md) for the phases.

## Acknowledgements

This port would not exist without the work of others:

- **[GabeRealB/parasite-eve-2-decomp](https://github.com/GabeRealB/parasite-eve-2-decomp)**
  — the matching decompilation of *Parasite Eve II* that all game code in this
  repository comes from, together with its documentation of the game's formats
  and systems and its asset tooling (`tools/peassets`). This repository started
  as a copy of that project and keeps its history; the decompilation is
  released under CC0. Its original README and project notes are kept in
  [docs/decomp/](docs/decomp/).
- **[PsyZ](https://github.com/Xeeynamo/psyz)** by Xeeynamo, and our
  [fork](https://github.com/khasinski/parasite-eve-psyz), which provide the
  PSY-Q compatible runtime. PsyZ builds on the
  [sotn-decomp](https://github.com/Xeeynamo/sotn-decomp) PSY-Q work and
  [Sozud's PSY-Q decomp](https://github.com/sozud/psy-q-decomp).
- **[parasite-eve-pc](https://github.com/khasinski/parasite-eve-pc)** — the
  port of the first game, whose architecture and conventions this project
  follows.

*Parasite Eve* is a trademark of Square Enix. This is an unofficial fan project
and is not affiliated with or endorsed by Square Enix.

## Building

Not yet buildable. The build will use CMake and the PsyZ submodule:

```sh
git submodule update --init third_party/psyz
git -C third_party/psyz submodule update --init external/SDL
```

## License

Project code is released under [CC0 1.0](LICENSE), as the decompilation it is
derived from. Game assets and the game's copyrighted content are not included
and remain the property of their owners. PsyZ and its dependencies carry their
own licenses (see `third_party/psyz`).
