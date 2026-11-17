# PS5 native source snapshot

This branch records an in-progress source snapshot of the PE2 PS5 host and selected game-side integration changes: native storage, UI, font providers, optional HD and interpolation adapters, effects support and conversion tooling. Font programs retain the included SIL Open Font License notices; native component notices remain in platform/ps5/notices and the existing project notices.

The accompanying patches/psyz source patch captures the licensed portions of the separately maintained native backend against the documented public PsyZ revision. The PsyZ baseline classifies existing include headers as unlicensed; their modifications and one new header lacking explicit licensing are excluded from that patch. The public PsyZ submodule pin remains earlier than the backend used by this snapshot. These missing interfaces, the separately applied backend patch, and external toolchain and runtime dependencies mean this source is not a reproducible build or executable release. It is not proof of gameplay.

The shadow capture implementation identifies its PE1 planar-shadow source as MIT; the projection helper retains its MPL-2.0 notice. No original disc image, original extracted game asset, personal save, build output or private artwork is included in this source update.
