# Optional font presentation providers

Original game font data remains in the user's game assets. No game glyph images or resource bindings are included here.

Plex uses the existing IBM Plex Sans provider. Retro uses the exact retained Chakra Petch Bold provider from PE1 Build17; Atkinson uses the exact retained Atkinson Hyperlegible Regular provider from PE1 Build17. These font programs retain their SIL Open Font License1.1, copyright and notices in OFL-IBMPlex.txt, OFL-ChakraPetch.txt and OFL-AtkinsonHyperlegible.txt. New renderer routing is MPL2.0; no font license is replaced.

PE1 provider mapping source: game-src/src/main/render/dialogue_alpha.c::PeFont_TrueTypeData, MIT. Only the provider mapping is adapted; PE2 retains its own metric, source-bound run admission, lifetime token and renderer rules.

Atkinson upstream receipt retained from PE1: google/fonts commit eb20e9cf19d97cf579fa3867d729d4222d6c59e1, ofl/atkinsonhyperlegible/AtkinsonHyperlegible-Regular.ttf, 54348 bytes, SHA256 7fb917c89019896d0b52ee84b7cbb3304c18cb90b19a62f5e32712bd23e97669.
