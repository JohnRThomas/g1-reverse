# Session coordination — active file locks

> Purpose: two Claude sessions work this repo in the same dir. Before editing a
> path listed here as **HELD**, ping the other session or pick different files.

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
