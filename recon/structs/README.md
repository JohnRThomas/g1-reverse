# CPUAPP struct recovery

Recovered in-memory struct layouts for the G1 CPUAPP, derived from Ghidra
(stable source) and named/reviewed by a two-wave agent flow, then mechanistically
verified. **JSON-only** — no reconstructed source was edited.

## Pipeline

1. **`struct_extract.py`** — parse Ghidra's exported decompilation
   (`recon/catalogs/app_funcs.json.gz`) into per-base-object access footprints
   (param / global / stack; offset + size + read/write). → `footprints_app.json`
2. **`struct_cluster.py`** — union-find over call-argument flow unifies pointer
   params describing the same object into canonical clusters. → `clusters_app.json`
3. **`build_struct_bundles.py`** — mechanical candidate layout (fields at observed
   offsets, gap-clamped widths, explicit padding) + library hint per cluster;
   684 sharded evidence bundles. → `bundles/`
4. **Wave 1** (`struct_collect.wf.js`, 20 Sonnet / medium) — name each struct and
   its fields, refine types, flag library vs original. → `proposals_sonnet.json`
5. **`merge_struct_proposals.py`** — group by *distinctive* footprint (>=4 fields)
   into review groups; trivial layouts stay separate. → `review/`, `mgroup_shard_*`
6. **Wave 2** (`struct_merge.wf.js`, 10 Opus / high) — dedup genuine duplicates,
   split coincidental footprint collisions, sanity-review, and verify library
   struct offsets against the pinned NCS 2.5.1 headers (`~/ncs251`). → merged
7. **`verify_structs.py`** — mechanistic gate:
   - **D1** every field maps to a real Ghidra access; width ≥ observed; size ≥ last byte.
   - **D2** compile-time offset/size proof: each field placed at its exact byte
     offset with `_Static_assert(offsetof==)`, compiled by the toolchain
     (byte-slot normalized — pure layout arithmetic, type-name agnostic).
8. **`assemble_struct_catalog.py`** / **`finalize_structs.py`** — combine + coverage.

## Result

- **676 structs**, all D1+D2 verified, **684/684 clusters covered** (1 mechanical
  fallback where an agent dropped a cluster).
- **299 library** (60 with offsets verified against real headers) / **377 G1-original**.
- 56 unions/overlaps flagged, 70 arrays.
- **Fields named**: a follow-up 20-opus deep code sweep over
  `recon/readable_sources/app` named the `field_0x*` placeholders from real usage
  — **1008 → 96 remaining** (912 named, 280 retyped, 53 struct renames). The 96
  left are agent-marked undeterminable. Machinery: `build_field_bundles.py`,
  `field_name.wf.js`, `merge_field_names.py`.

## Files

| File | Contents |
|---|---|
| `footprints_app.json` | ground-truth per-base access sets (Ghidra) |
| `clusters_app.json` | unified clusters + call-edge provenance |
| `proposals_sonnet.json` | raw Wave-1 proposals |
| `merge_groups.json`, `mgroup_shard_*.json`, `review/` | Wave-2 inputs |
| `merged_app.json` | deduped/reviewed structs (pre-verify) |
| `struct_verification_report.json` | per-struct D1/D2 pass + warnings |
| **`struct_catalog_app.json`** | **final verified catalog** |
| `struct_library_app.json` / `struct_original_app.json` | library vs G1 split |
| `struct_coverage_app.json` | coverage audit |

## Not done here (by design)

Applying structs into reconstructed sources is a separate, `cfg_verify`-gated pass
(alignment padding could perturb codegen; every rewrite must re-prove parity).
This task ends at a verified JSON catalog. Library offsets not yet mechanically
confirmed (239 of 299) are agent-identified; a later D3 can compile probe TUs
against the real headers to promote them.
