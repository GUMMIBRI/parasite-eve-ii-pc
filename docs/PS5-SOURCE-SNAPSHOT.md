# PS5 native source snapshot

This branch records an in-progress source snapshot of the PE2 PS5 host: native storage, UI, font providers, optional HD and interpolation adapters, effects support, and conversion tooling. Font programs retain the included SIL Open Font License notices; native component notices remain in platform/ps5/notices and the existing project notices.

This snapshot is not a complete buildable candidate. Its originating test17 tree contains additional changes to existing game/decompilation files and to a separately maintained PsyZ native backend; those changes and private game data are not supplied here. The existing public PsyZ submodule pin and compatibility patch are earlier than the backend used by this snapshot. Do not interpret this branch as an executable release, a reproducible build, or proof of gameplay. Integration requires a reviewed, distributable backend, compatible game-side changes, and the external toolchain and runtime dependencies specified by the PS5 recipe.

The shadow capture implementation identifies its PE1 planar-shadow source as MIT; the projection helper retains its MPL-2.0 notice. No original disc image, game asset, personal save, build output or private artwork is included in this source update.
