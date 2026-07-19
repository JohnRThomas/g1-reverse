# Session coordination — active file locks

> Purpose: two Claude sessions work this repo in the same dir. Before editing a
> path listed here as **HELD**, ping the other session or pick different files.

## DONE by session A (struct-recovery wave) — 2026-07-19 (landed, committed)

**Task:** recovered CPUAPP in-memory struct layouts from Ghidra footprints,
named via 20-sonnet + 10-opus flow, mechanistically verified, emitted JSON.
**Complete — no locks remain.**

Result: 676 structs (all D1+D2 verified), 684/684 clusters covered; 299 library
(60 offset-verified vs pinned headers) / 377 G1-original. Deliverables in
`recon/structs/` (final: `struct_catalog_app.json`). JSON-only — no source,
name-map, or net files touched.

Files this session owns (now committed):

- `recon/structs/**` — footprints, clusters, bundles, proposals, catalogs (this session owns the whole dir)
- `tools/struct_extract.py`, `tools/struct_cluster.py`, `tools/build_struct_bundles.py`,
  `tools/struct_collect.wf.js`, `tools/struct_merge.wf.js`, `tools/verify_structs.py`,
  `tools/merge_struct_proposals.py` (new)

JSON-only output — this task does NOT edit any reconstructed source, name maps, or
net files. CPUNET, parity/CFG tooling, ownership manifests remain free.

---

## DONE by session A (naming wave) — 2026-07-19 (landed, committed)

**Task:** named the 563 unnamed CPUAPP `FUN_*` functions via a 20-agent resumable
Workflow, then merged accepted names. **Complete — no locks remain.**

Result: CPUAPP human names 1875 → 2438; only 70 `FUN_*` left (thunks/aliases
without a reconstructed body). App `validate_name_maps.py` clean.

Files this session touched (now committed, safe to build on):

- `recon/naming_bundles/**` — evidence bundles, GUIDE, proposals (new)
- `tools/build_name_bundles.py`, `tools/merge_name_proposals.py`, `tools/name_wave.wf.js` (new)
- `recon/catalogs/function_name_overrides.json` (+563 app entries),
  `recon/catalogs/function_names_app.json`, `recon/named/*.c`, `recon/symbolized/app/*`,
  `recon/symbols/g1_app_symbols.h` (regenerated for app only)

**Deliberately NOT touched:** all CPUNET (`recon/net/**`, `function_names_net.json`
was reverted after the shared builder incidentally rewrote it), parity/CFG tooling,
ownership manifests. Net readable-tree validator errors seen during this run are
pre-existing CPUNET work owned by the other session, not caused here.
