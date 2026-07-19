# G1 Firmware Reconstruction — Accomplishments and Current State

**Status date:** 2026-07-19  
**Repository checkpoint:** `119584cc` (`main`)  
**Target:** Even Realities G1 firmware, Nordic nRF5340 CPUAPP + CPUNET  
**Pinned build environment:** NCS 2.5.1, Zephyr 3.4.99, GCC 12.2, newlib-nano, Cortex-M33 hard-float, `-Os`

## Executive summary

The shipped dual-core firmware has been converted into a complete function-level C recovery corpus. Every current CPUAPP and CPUNET reconstruction has an authoritative control-flow-directed semantic parity result: **3,257 PASS, 0 unresolved**. The repository also contains readable naming, persistent address back-mapping, recovered data objects, ownership decisions for stock libraries, cohesive NCS integration projects, product-root wiring, and section-level binary comparison tooling.

This is not yet the final byte-layout-equivalent firmware build. CPUAPP links far enough to produce ELF/firmware section comparisons. CPUNET has zero undefined-symbol diagnostics but still exceeds its flash region by **633 bytes**, so it does not yet produce the final ELF. Final initialization/root cohesion, layout convergence, type reconciliation, and image comparison remain.

## Quantitative snapshot

| Area | Current result |
|---|---:|
| CPUAPP reconstructed functions | 2,115 / 2,115 |
| CPUAPP authoritative CFG parity | 2,115 PASS, 0 FAIL, 0 unresolved |
| CPUNET reconstructed functions | 1,142 / 1,142 |
| CPUNET authoritative CFG parity | 1,142 PASS, 0 FAIL, 0 unresolved |
| Total semantically verified functions | 3,257 |
| CPUAPP readable-name files | 1,546 |
| CPUAPP names still represented as `FUN_*` | 569 |
| Recovered CPUAPP data source objects | 993 |
| Current fixed byte-exact CPUAPP rodata sections | 81 sections / 15,694 bytes |
| MMIO-referencing functions inventoried | 212 |
| Functions with ordered MMIO read tracing | 104 |
| Upstream ownership decisions | 515 CPUAPP + 611 CPUNET |
| G1-only CPUAPP source view | 1,338 included; 777 library bodies excluded |
| Deferred reconstructions | 0 |
| Byte-blob fallback files | 0 |
| CPUNET normal-GC link residue | 0 undefined symbols; 633-byte flash overflow |

## Accomplishments

### 1. Complete dual-core function recovery

- Recovered the complete current CPUAPP corpus into `recon/app/src/`.
- Recovered the complete current CPUNET corpus into `recon/net/src/`.
- Preserved the two cores as separate address spaces and source domains; no invalid cross-core struct or function sharing is assumed.
- Retained the original virtual address and raw `FUN_*` identity for every renamed function.
- Split Ghidra-inflated functions where trailing data had been incorrectly folded into the function extent.
- Recovered late-discovered address-taken callbacks and product roots that were absent from the original direct-call worklists.

### 2. Sound semantic verification pipeline

- Built a Unicorn Cortex-M33 differential harness that compares reconstructed code against the original firmware.
- The comparison covers ABI return values, ordered non-stack writes, call order/count, and fault parity.
- Fixed the original random-input blind spot for small enum, switch, opcode, and flag arguments.
- Added CFG-directed test generation for comparisons, conditional branches, `cbz`/`cbnz`, and `tbb`/`tbh` switch tables.
- Made `tools/cfg_verify.py` the authoritative function acceptance gate.
- Re-swept the entire active corpus after the harness correction and reconstructed every discovered false proof.
- Current authoritative overlays report:
  - CPUAPP: 2,115 PASS, no source drift, fully covered.
  - CPUNET: 1,142 PASS, no source drift, fully covered.
- Added proof receipts and source/tool hashes so later edits fail closed instead of silently inheriting an obsolete PASS.

Evidence:

- `recon/analysis/cfg_sweep_app_recheck_overlay.json`
- `recon/analysis/cfg_sweep_net_current_overlay.json`
- `tools/cfg_verify.py`
- `tools/parity/emu.py`

### 3. MMIO and hardware-side-effect verification

- Audited functions that touch fixed peripheral or shared-memory addresses.
- Added ordered MMIO-read tracing where a function's result or write trace depends on volatile read order.
- Inventoried 212 MMIO-reference functions across both cores.
- Established ordered read traces for 104 functions and canonical targeted coverage for 89 high-priority cases.

Evidence: `recon/catalogs/mmio_parity_coverage_inventory.json`.

### 4. Recovered data, literal pools, and fixed-address objects

- Recovered 993 CPUAPP data/rodata C objects in `recon/data/`.
- Preserved exact firmware bytes rather than attempting to infer large tables semantically.
- Added placement and comparison machinery for fixed-address data.
- The current fixed-rodata build has 81 byte-exact non-executable sections totaling 15,694 bytes.
- Added explicit ownership handling for data split from inflated functions.

Evidence:

- `recon/catalogs/app_fixed_verified_rodata.json`
- `recon/analysis/app_fixed_rodata_section_comparison.json`

### 5. Readable naming with durable back-mapping

- Created human-readable CPUAPP sources in `recon/named/`.
- Assigned readable filenames to 1,546 of 2,115 CPUAPP functions.
- Preserved the raw name and address in every readable source header.
- Created address-to-function, function-to-address, global-name, alias, and linker symbol catalogs.
- Replaced raw absolute references with readable symbols in generated symbolized trees while retaining `/*=0xADDRESS*/` provenance.
- Built comment/string-aware symbol substitution to avoid corrupting source literals and annotations.
- Kept 569 unresolved names as `FUN_*`; their semantics are recovered, but their best human names are not yet proven.

Key catalogs:

- `recon/catalogs/function_names_app.json`
- `recon/catalogs/function_names_net.json`
- `recon/catalogs/address_names_app.json`
- `recon/catalogs/address_names_net.json`
- `recon/symbols/`

### 6. Stock-library identification and adoption

- Identified the pinned firmware environment and matched stock code against the actual NCS, Zephyr, nrfx, toolchain, and archive versions.
- Built machine-readable ownership records rather than deleting suspected library code by name alone.
- CPUAPP ownership manifest: 515 entries, including 500 approved upstream substitutions and 15 reconstruction retentions.
- CPUNET ownership manifest: 611 entries, including 244 approved upstream substitutions and 367 retained reconstructions.
- Identified and handled LC3, cJSON, newlib/libm, libgcc, Zephyr kernel/host code, nrfx/HAL, TinyCrypt, CC312/Oberon, OpenAMP/rpmsg, and other SDK components.
- Kept SDC matches report-only: no automatic SDC removal is authorized without per-address machine-verifiable ownership.
- Preserved collision reports for cases where the correct version/configuration or selected link owner was ambiguous.

Evidence:

- `recon/ownership/adoption_manifest.json`
- `recon/catalogs/upstream_library_provenance.json`
- `recon/catalogs/lc3_ownership_app.json`
- `recon/ownership/net_sdc_archive_ownership.json`

### 7. G1-only application source view

- Created `recon/application/src/` as the product-facing CPUAPP source directory.
- Included 1,338 currently attributed G1 application functions.
- Excluded 777 identified compiler, libc, Zephyr/NCS, LC3, cJSON, Bluetooth-host, crypto, and other library bodies.
- Kept `app_codec_lc3_test.c` because it is G1 integration code that calls the stock LC3 implementation.
- Used relative symlinks into `recon/named/` so readable source fixes have one canonical owner.
- Added a complete per-function manifest with address, raw symbol, readable name, inclusion decision, and exclusion reason.
- Added deterministic regeneration and regression checks.
- Ambiguous unnamed functions remain included rather than being discarded without ownership evidence.

Evidence:

- `recon/application/application_sources.json`
- `tools/build_app_source_view.py`
- `tools/test_app_source_view.py`

### 8. Cohesive NCS/Zephyr integration projects

- Created CPUAPP and CPUNET integration projects under `recon/application/app/` and `recon/application/net/`.
- Added pinned project configuration, CMake integration, board overlay, linker fragments, recovered globals, and Zephyr kernel-object definitions.
- Added a reproducible build wrapper in `recon/application/build_cohesive.sh`.
- Implemented fail-closed retain-all probes to expose duplicate and undefined owners that normal garbage collection could hide.
- Implemented normal-GC product-link mode for physical flash-fit work.
- Made fixed CPUAPP placement opt-in so normal builds remain useful while exact layout work proceeds independently.

### 9. Product roots and callback wiring

- Recovered and wired CPUAPP DMIC/LC3 capture behavior and direct callback edges.
- Inventoried CPUAPP address-taken roots.
- Recovered and wired CPUNET production roots, IPC endpoint callbacks, RPMsg receive paths, ESB event handling, MPSL signal handling, timeslot workers, HCI RPMsg receive dispatch, and HCI worker threads.
- The most recent CPUNET callback closure added 11 sources, updated 6 existing sources, and produced 17 CFG passes covering 376 directed checks.
- CPUNET product integration now reports zero undefined-symbol diagnostics.

Evidence:

- `recon/ownership/app_address_taken_roots.json`
- `recon/ownership/net_current_callback_recovery.json`
- `recon/ownership/net_product_root_wiring.json`

### 10. CPUNET size-convergence work

- Reduced the normal-GC CPUNET image from a 761-byte overflow to 633 bytes.
- Tightened eight recovered functions without changing proven behavior.
- Reduced production object code by 124 bytes and the whole image by 128 bytes.
- Preserved all proven product roots and configuration; no region growth, padding trick, archive substitution, or automatic SDC deletion was used.
- Refreshed the authoritative CFG overlay after every size-changing source edit.

Evidence: `recon/analysis/net_size_convergence_receipt.json`.

### 11. Binary and section comparison gates

- Added MCUBoot-aware firmware parsing and coordinate-space normalization.
- Added section-by-section comparisons for vectors, executable code, rodata, data, and generated fixed-address sections.
- Added overlap and out-of-range detection.
- Produced CPUAPP default, DMIC-enabled, and fixed-rodata comparison reports.
- Produced CPUNET comparison diagnostics for intermediate link states.
- Established that semantic parity and byte-identical code generation are separate gates: CFG parity is complete, while final linked layout and section convergence remain active work.

Evidence:

- `recon/analysis/app_binary_section_comparison.json`
- `recon/analysis/app_dmic_default_section_comparison.json`
- `recon/analysis/app_fixed_rodata_section_comparison.json`
- `recon/analysis/net_binary_section_comparison.json`

### 12. Reproducibility and repository durability

- Regenerated and persisted the function classifications, function inventories, reference graphs, reference database, symbol maps, and global maps.
- Backed volatile scratch catalogs up under `recon/catalogs/`.
- Added hashes to proof and ownership receipts.
- Kept reconstruction output, readable views, symbolized views, integration projects, data objects, and ownership evidence separated by purpose.
- Reached zero files in both `recon/deferred/` and `recon/blobs/`; no current function depends on a last-resort byte blob.

## What remains

The function-reconstruction phase is complete, but the end goal is not yet complete. Remaining work is:

1. Remove the final 633-byte CPUNET flash overflow through semantics-preserving codegen/layout convergence or precisely proven upstream ownership.
2. Refresh the CPUNET symbolized/generated source view for all 1,142 current canonical functions.
3. Complete CPUAPP and CPUNET production initialization/root cohesion, including all address-taken registrations and generated Zephyr objects.
4. Reconcile remaining structs, types, globals, linker aliases, and source-unit ownership so the cohesive projects use ordinary readable declarations instead of reconstruction-era fixed-address scaffolding where possible.
5. Continue naming the 569 CPUAPP `FUN_*` functions and reclassify any newly proven stock-library bodies out of the G1-only source view.
6. Produce flash-fitting final ELFs for both cores.
7. Compare final `.text`, `.rodata`, `.data`, vectors, and section maps against the shipped images and explain every remaining difference.
8. Keep SDC reconstruction/adoption conservative until each removal has a per-address machine-readable proof.

## Primary working locations

| Purpose | Path |
|---|---|
| G1-only readable CPUAPP view | `recon/application/src/` |
| Canonical CPUAPP reconstructions | `recon/app/src/` |
| Canonical CPUNET reconstructions | `recon/net/src/` |
| Full readable CPUAPP corpus | `recon/named/` |
| Symbolized generated sources | `recon/symbolized/` |
| Recovered data | `recon/data/` |
| Ownership and adoption decisions | `recon/ownership/` |
| Persistent catalogs | `recon/catalogs/` |
| Cohesive NCS projects | `recon/application/app/`, `recon/application/net/` |
| Binary/CFG analysis reports | `recon/analysis/` |
| Reconstruction and verification tools | `tools/` |

## Recent milestone commits

- `119584cc` — tighten CPUAPP libc exclusions
- `27062d48` — add G1-only CPUAPP source view
- `d8f9f60f` — refresh CPUNET size-tightening CFG overlay
- `3b8faccc` — record CPUNET size convergence
- `144e82d9` — tighten three CPUNET recovered functions
- `2ebf5e43` — tighten four CPUNET kernel reconstructions
- `127c0f4c` — tighten CPUNET radio owner initialization
- `c0fe95af` — wire cohesive CPUNET product owners
- `bec91810` — make cohesive CPUAPP fixed placement opt-in
- `64a6715a` — inventory CPUAPP address-taken roots

## Completion definition

The project is complete only when both cores build as one cohesive NCS 2.5.1 firmware project, all required roots and objects are linked, no unexplained raw address or unresolved owner remains, CPUNET fits its real flash region, and the resulting sections are compared against the shipped images with every mismatch either eliminated or explicitly justified. Function-level semantic recovery has reached that standard; whole-image integration and layout have not yet done so.
