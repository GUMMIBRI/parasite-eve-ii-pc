# PE2 PS5 PsyZ backend source patch

This patch records source from the selected test17 PS5 backend relative to khasinski/parasite-eve-psyz commit 512780a18a2d205e06f8193b95519470132a3435. It is a review artifact, not applied to this repository's PsyZ submodule, which remains pinned at ff5457d8bfcf636c6e12941a71ee66c065a3e01f. Apply to a clean checkout of the stated base with git apply --index after reviewing the result.

The PsyZ baseline LICENSE identifies psyz/src/platform and psyz/src/psyz as MPL-2.0 and psyz/include as unlicensed. Existing unlicensed include files, plus a new include file without an explicit license, are deliberately excluded. New include files carrying explicit MPL-2.0 or MIT markings are included. This patch therefore is not a complete buildable backend: changes to include/malloc.h and include/psyz/{gpu,gte,overlay_sdl3,video}.h and the new fsr1.h remain absent pending rights and integration review. AMD FSR source retains its included MIT notice; xxHash and miniz retain their embedded notices. Generated SPIR-V headers represent shaders, not original game data. The patch includes no game image, game assets, personal data, executables or private SDK modules.

No PS5 build or runtime validation was performed for this export. Local source can continue to change; the file is a captured snapshot.
