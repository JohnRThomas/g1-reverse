# G8 — production-grade refactor: architecture plan

**Status: ANALYSIS AND PLANNING ONLY.** Nothing in the corpus, the build, the
linker scripts, `tools/` or `recon/emulator/**` was modified by this pass, and
nothing was committed. Two deliverables were written:

| file | contents |
|---|---|
| this file | target layout, mapping rule, consolidation sequence, gate ladder, batch order, flash accounting, non-goals |
| `recon/ownership/refactor_module_map.json` | 2,115 app + 945 net rows: ownership, target module, target path, evidence tier, confidence |

This plan is the successor to `recon/analysis/prerefactor_plan.md` (G6 inline
literals, G7 dedupe) and assumes G6/G7 land first — several G8 batches depend on
them and say so. It does **not** re-derive anything G6/G7 already decided.

**Snapshot caveat.** A parity bring-up (P4/G4) is running concurrently and owns
`recon/symbolized/**`, `recon/application/**` and `recon/emulator/**`. Every
count below is a snapshot at commit `6aa09be0` / working tree of 2026-07-26.
Re-run the reproducer scripts before applying a batch.

---

## 0. What "production-grade" has to mean here, and what it cannot mean

This codebase has a property no ordinary refactor target has: **its correctness
is defined by a binary it must keep matching.** Three consequences shape
everything below.

1. **The parity corpus cannot become the production tree.** `tools/cfg_verify.py`,
   `tools/recon_kit.py`, `tools/net_recon_kit.py`, `tools/reverify.py` and
   `recon/emulator/scripts/check_thread_create_stack_args.py` all resolve a
   function by `os.path.join(<flat srcdir>, <name> + ".c")` with
   `srcdir ∈ {recon/app/src, recon/net/src, recon/verified/src}`. Moving a file
   out of those flat directories breaks the proof chain outright. **`recon/app/src`
   and `recon/net/src` stay flat, stay address-headed, and stay the parity
   corpus. The production tree is generated *from* them.**
2. **Beauty that changes codegen is a regression.** The image is at 96.93 %
   (app) and 97.48 % (net) of its partition. A refactor that grows `.text` by
   1 % on app is fine; the same on net does not link.
3. **The refactor's real payoff is not aesthetic.** The three highest-value
   outcomes are: eliminating the nine-tree drift that has already shipped bugs;
   retiring the `FUN_`/`rodata_<hex>` namespace so a human can navigate; and
   converting the 676 verified struct layouts and 585 named globals from
   analysis artifacts into actual types the compiler checks. Directory structure
   is the vehicle, not the goal.

---

## 1. Baseline — the measured state this plan starts from

### 1.1 Corpus and trees

| tree | `.c` | role | writer |
|---|---:|---|---|
| `recon/app/src` | 2,141 | **canonical app parity corpus** (`recon_kit.RECON_SRC`) | `recon_kit.prove()` |
| `recon/net/src` | 1,177 | **canonical net parity corpus** | `net_recon_kit.prove()` |
| `recon/verified/src` | 2,138 | app mirror; `reverify.py` legacy `sweep`/`check` modes read *this*, not `app/src` | `cp` by hand |
| `recon/app/src_sym`, `recon/verified/src_sym` | 1,059 each | **dead** — last commit 2026-07-11 (`5c489985`) | nobody |
| `recon/named` | 2,140 | app, human filenames + names, raw addresses | `tools/apply_names.py` |
| `recon/net/named` | 1,124 | net equivalent | `tools/apply_names.py` |
| `recon/symbolized/app` | 2,141 | **what the app build compiles** (1,609 retained) | `tools/symbolize.py --write` *and hand edits* |
| `recon/symbolized/net` | 1,155 | **what the net build compiles** (923 retained) | same |
| `recon/readable_sources/app/{g1,library}` | 1,156 + 959 | presentation copy, split by ownership | `tools/build_readable_sources.py` |
| `recon/application/src` | 1,156 | **symlinks** into `recon/named` — a view, not a copy | `tools/build_app_source_view.py` |
| `recon/data` / `recon/net/data` | 993 / 6 | byte-verified rodata tables | generators |
| `recon/application/rodata` | 8 app + 8 net | decoded `.rodata` batches (G5) | `gen_app_rodata_sources.py` |

The trees are a **pipeline**, not five independent copies:

```
recon/{app,net}/src  --apply_names.py-->  recon/{named,net/named}
                     --symbolize.py-->    recon/symbolized/{app,net}   <-- THE BUILD
                     --build_readable_sources.py--> recon/readable_sources/app/{g1,library}
                     --build_app_source_view.py-->  recon/application/src (symlinks)
```

**The drift is real and it is bounded.** Measured today:

| divergence | count | files |
|---|---:|---|
| symbolized app files whose last commit is *newer* than their `recon/named` counterpart (edited downstream, never pushed back) | **37** | `main.c`, `DashBoard_Reflash.c`, `power_down_panel.c`, `gpio_*`, `device_reg3_init_config.c`, … |
| canonical app files missing from `recon/verified/src` | 3 | `FUN_0007c86c.c`, `aging_mode_thread.c`, `master_display_thread.c` |
| symbolized app files with no `recon/named` counterpart | 1 | `FUN_0007c86c.c` |
| symbolized app files with no `readable_sources` counterpart | 29 | — |
| symbolized net files with no `recon/net/named` counterpart | 31 | — |

37 + 3 + 1 + 29 + 31 = **101 files** is the entire reconciliation debt. That is
a one-session job, not a rewrite — but it must be paid *before* consolidation,
because a generator re-run silently discards downstream hand edits.

### 1.2 Build

- App: `recon/application/app/CMakeLists.txt`, no globs. 1,609 symbolized +
  993 verified-data + 6 rodata batches + ~20 hand `src/*.c` + 2 raw canonical.
- Net: `recon/application/net/CMakeLists.txt`, 923 symbolized + 32 report-only +
  ~40 explicit + 6 data, with a **path-keyed regex filter** excluding 17
  symbolized `FUN_0102….c` in favour of canonical copies.
- Source lists are generated by `tools/gen_retained_sources.py` from
  `recon/ownership/adoption_manifest.json`. It is **rename-safe by design**
  (keys on the VA in the in-file `identity:` header, cross-checked against the
  name catalog) but **not move-safe** (`os.listdir` + `basename`, single
  relative prefix).
- `recon/application/build_cohesive.sh app|net <dir>` is the only supported
  build entry (`west build -p always`, `PYTHONSAFEPATH=1`, pinned `~/ncs251`).

### 1.3 Flash and RAM — the hard constraint

| | app (`g1-i36b-app`) | net (`g1-i30e-net`) |
|---|---:|---:|
| FLASH used | **952,316 B** | **225,581 B** |
| partition | 982,528 B (Partition Manager, no `pm_static.yml`) | 231,424 B modeled (DT 260 KiB − 0x8800); **real device 227,328 B** |
| % | **96.93 %** | 97.48 % modeled / **99.23 % real** |
| headroom | **30,212 B** | **5,843 B modeled / 1,747 B real** |
| RAM | 253,765 B / 440 KB | 63,380 B / 65,536 B = 96.71 % |
| gc-sections | on, but neutered for rodata (§1.4) | forced off by default; measured builds pass `-DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF` |
| LTO | none | none |

Several in-tree documents quote stale flash figures — `net/FLASH_DIVERGENCE.md`
(227,961 B), `library_displacement_report.md` (99.02 %), `prerefactor_plan.md`
§5 (921,576 B app / 225,073 B net). **The numbers above are the current ones.**

### 1.4 Three build mechanisms that couple correctness to filenames

These are the single biggest technical obstacle to a file-layout refactor and
must be neutralised first (Batch 0).

1. **`recon/application/app/g1_verified_rodata_keep.ld`**

   ```
   KEEP(*rodata_*.c.obj(".rodata.rodata_*"))
   KEEP(*rodata_*.c.obj(".rodata.litpool_*"))
   ```

   The outer pattern matches the **object filename**. It deliberately catches
   the 993 `recon/data/rodata_0x*.c` objects and *accidentally* catches
   `g1_app_rodata_01.c.obj … _07.c.obj` (they contain the substring `rodata_0`),
   which is why `rodata_decode_report.md` §10 measured that `--gc-sections`
   drops nothing. It does **not** match `g1_app_string_rodata.c.obj`,
   `g1_app_font_rodata.c.obj`, `g1_app_localized_rodata.c.obj`,
   `g1_app_fade_mask_rodata.c.obj`, `g1_app_glyph_bitmap_rodata.c.obj`.
   Renaming any file across that boundary changes flash occupancy silently, in
   either direction. Moving to a subdirectory is safe (`*` absorbs the path);
   **renaming is not.**

2. **`tools/gen_retained_sources.py`** — flat `os.listdir`, emits
   `"${CMAKE_CURRENT_LIST_DIR}/<one-prefix>/<basename>"`. A file moved into a
   subdirectory simply vanishes from the build; you find out at `nm -u`.

3. **`tools/full_link.py`** — `glob.glob(recon/symbolized/<core>/*.c)`, same
   flat assumption; plus it is **fail-closed on undefined-symbol-name drift**
   against `recon/catalogs/app_full_link_unknown_audit.json` and
   `net_link_function_residue.json` (exact set equality → `RuntimeError`).

Two further filename couplings: `set_source_files_properties(... discovery_callback.c
... COMPILE_OPTIONS "-std=gnu99")` in the app CMake (CMake does **not** error if
the path stops existing — the flag silently disappears and the TU fails to
compile), and the net `list(FILTER ... REGEX "/FUN_0102(a4c8|…)\\.c$")`
exclusion, which turns into a duplicate-symbol link error if those 17 files are
renamed.

### 1.5 Ownership — the natural first axis

| app | count |
|---|---:|
| catalogued CPUAPP functions | 2,115 |
| **product (G1-owned)**, after overlaying the live `adoption_manifest.json` | **1,101** |
| library, still reconstructed and compiled into the image | **482** (57,874 Ghidra-declared bytes) |
| displaced to real SDK (manifest `exclude_reconstruction`) | **532** |

2,141 symbolized files − 1,609 retained = 532: the exclusion set exactly.

⚠️ `recon/application/application_sources.json` still reports 1,156 product /
959 library. It records `adoption_manifest.json` sha `5122cb4d…`; the live file
differs, and 55 addresses that now carry a manifest exclusion are still marked
`included_g1_application`. **Regenerate it (`tools/build_app_source_view.py`)
as step 1 of Batch 1.** The map JSON already applies the overlay and reports
1,101.

**Net is ~100 % stock.** `recon/ownership/net_function_ownership.json`:
452/452 `sdk_library`, `genuine_firmware_owner_missing_c: 0`, and the report
states "zero newly discovered product-owned net-core functions requiring
readable C". 325 addresses are owned by the SDC archive, 158 by Zephyr kernel,
49 by NCS `nrf/`. The identifiable G1 net surface is **~30 functions**: the 15
`G1_PRODUCT_ENDPOINT_SOURCES`, 4 `G1_ESB_UPLINK_WORKER_SOURCES`, 5
`G1_TIMESLOT_OWNER_SOURCES`, the ESB clock-callback closure, `g1_cpunet_main`
(`FUN_0102a720`) and `g1_ipc_rpmsg_register_ept`. **Net gets an ownership
layout, not a subsystem layout.**

### 1.6 Naming and typing assets

| | app | net |
|---|---:|---:|
| catalogued addresses | 2,534 | 1,309 |
| human-named | **2,466 (97.3 %)** | **266 (20.3 %)** |
| still `FUN_xxxxxxxx` **in the build tree** | 4 / 1,609 (0.2 %) | **747 / 923 (80.9 %)** |
| names tagged medium/low confidence | 372 of 2,466 | none tagged |
| globals declared in `g1_<core>_symbols.h` | 3,387 | 462 |
| …with a real name | 585 (17.3 %) — RAM 549/740, rodata 36/2,647 | 177 (38.3 %) |
| verified struct layouts | **676**, all `verified:true`, 2,921 fields, **97 offset-only placeholders in 32 structs**, covering **826 of 2,115 functions (39 %)** | **none — no net struct catalog exists** |

The app naming job is essentially done; **the net naming job is the largest
single unit of remaining human work in G8** (747 files).

### 1.7 Gates that must survive

| gate | reads | current |
|---|---|---|
| `tools/cfg_verify.py <core> <FUNC>` | flat `recon/{app,net}/src/<name>.c`, first line `@ 0xADDR` | authoritative per-function verifier |
| `tools/reverify.py sweeplist <core> <i> 8` | SHA-256 inventory digest of the whole flat corpus | **any rename/move invalidates every lane receipt** |
| `tools/recon_kit.prove` / `net_recon_kit.prove` | saves to `<RECON_SRC>/<name>.c` | filename derived from function name |
| `tools/full_link.py <core>` | flat symbolized glob + audit JSONs | 0 unknown, fail-closed on drift |
| `tools/gen_retained_sources.py --check` | manifest + symbolized identity headers | must be clean |
| `check_ram_pin_collisions.py <elf> [--core net]` | `.ld` pins vs linked ELF | app 0/0, bound 624/0; net 0/0 |
| `check_net_raw_literals.py <elf>` | `compile_commands.json`, re-preprocesses every TU | 0/0/0 |
| `check_thread_create_stack_args.py --trials 120` | **hard-coded list of 10 source basenames** | 10/10 |
| `recon/application/verify_net_stock_data_window.py <elf>` | shipped image vs linked `.data` | PROVEN |
| display/sensor oracle (`capture_display_sensor_oracle.sh` + `build_display_sensor_oracle.py`) | Renode capture, ~2 min + ~20 s | G-1 **PASS** (p2 navigation byte-identical, 1,098 == 1,098 px), G-2 **PASS** (p1_boot byte-identical, 656 == 656 px), G-3 FAIL (SPI repeats), D-1 peak 2,895 lit / 2,659 exact vs oracle 2,923 |
| unit tests | 159 `tools/test_*.py`, `unittest`, **no runner, no CI** | run via `python -m unittest discover -s tools -p 'test_*.py'` |

**The single most dangerous property of the whole system**, and the one that
governs the rename batches: in `tools/parity/recon.py`, callee *identity* is
checked through `LAST_DIRECT_TARGET_MAP`, built from (a) the `FUN_xxxxxxxx`
name pattern, (b) an in-source `/* FUN_xxxxxxxx */` back-map comment, (c) the
name catalogs and `g1_<core>_aliases.ld`. If a renamed callee resolves to no
VA, the entry is simply **absent** and the identity check for that callee is
**skipped**. A rename does not fail the gate — it silently weakens it. Every
rename batch below therefore carries a mandatory *coverage* assertion, not just
a pass assertion.

---

## 2. Target layout

Two Zephyr applications under one root, replacing `recon/application/{app,net}`
once Batch 6 completes. Directory names are the contract; file names are
`<recovered_function_name>.c` (one function per file initially — see §2.3).

```
g1/
  CMakeLists.txt                 # dispatches to app/ or net/ (keeps build_cohesive.sh's two modes)
  boards/                        # g1_board.overlay, app.overlay, pins_gpio.md, pins_buses.md
  include/g1/                    # the ONLY public header namespace
    types.h                      # <- recon/headers/g1_types.h
    device_info.h                # the shared device_info_t + accessors (826-function struct hub)
    log.h                        # G7-C10: ONE prototype per logging entry point (ABI-critical)
    mmio.h                       # G7-C02: G1_R8/R16/R32/RS16 volatile accessors, per width
    assert.h                     # G7-C01 __ASSERT expansion
    cmsis_shim.h, ghidra_ops.h   # G7-C03/C04 — transitional, delete when the last user goes
    display.h esb.h ble.h ipc.h audio.h storage.h sensors.h notify.h ui.h analytics.h
                                 # <- recon/modules/<m>/<m>.h, minus the [shared-infra] entries
    structs/                     # generated from recon/structs/struct_catalog_app.json
  app/
    CMakeLists.txt  prj.conf  Kconfig
    src/
      main.c
      core/          142  boot/init graph, threads, work-mode, power, device_info, wiring
      common/          3  cross-cutting utilities (fan-in >= 40 from product code)
      display/        89  panel, brightness, framebuffer blit, screen state machine
      gui/            57  glyph/bitmap/UTF drawing into the canvas
      ui/                 thin per-screen feature code
        dashboard/    26   navigation/ 5   teleprompt/ 2   translate/ 8
        quicknote/    11   onboarding/ 13
      notify/         99  ANCS + notification pipeline
      ble/            99  GATT/ATT/conn/pairing transport
      esb/            24  L<->R master/slave sync
      ipc/            47  OpenAMP/RPMsg/msgq to the net core
      audio/         137  PDM/DMIC capture, LC3 integration, voice
      sensors/
        imu/          22   power/ 42 (battery, PMIC, ALS)   input/ 30 (touch, keys)
      storage/        86  flash, NVS, settings, persistence
      analytics/      14
      UNSORTED/      145  ** explicit quarantine — see §2.2 **
      lib/           482  recovered stock not yet displaced, foldered by manifest component
      rodata/        993 + 8  byte-exact data — FILENAMES FROZEN (§1.4)
  net/
    CMakeLists.txt  prj.conf  app.overlay
    src/
      core/            1  g1_cpunet_main
      esb_sync/       24  product endpoints + uplink worker + clock-callback closure
      timeslot/        5
      stock/         915  recovered SDC/MPSL/Zephyr/OpenAMP residue, not yet displaced
      rodata/          6
```

App module sizes are from `refactor_module_map.json`; `(sdk)` 532 rows have no
target path (they are already displaced and are not compiled).

### 2.1 The rule that produced the mapping

Deterministic, five layers, most-trusted first. Reproduce with the script
archived in `refactor_module_map.json.generator`; inputs are sha256-pinned in
the JSON.

| layer | rule | app rows | trust |
|---|---|---:|---|
| **L0** | ownership: `application_sources.json` overlaid with `adoption_manifest.json` `exclude_reconstruction` → `product` / `library` / `displaced_to_sdk` | 2,115 | high — evidence-backed per address |
| **L1** | product function with ≥ 40 in-edges from other product functions → `common` | 3 | high |
| **L2** | name declared in exactly one `recon/modules/<m>/<m>.h`, not `[shared-infra]`, **and** L3 agrees or is silent | 161 | high — hand-curated |
| **L3** | ordered regex over the recovered readable name, specific → generic | 443 (+29 overriding L2) | medium-high |
| **L4** | majority module among refgraph callers ∪ callees already assigned, excluding `common` | 320 | **medium — must be confirmed** |
| **L5** | nothing fired | **145** | none — quarantine |

**Cleanly mapped: 636 of 1,101 product functions (L1+L2+L3, 58 %).
Needs confirmation: 320 (L4, 29 %). Needs judgement: 145 (L5, 13 %).**

Within L4, 241/320 assignments were unanimous among their neighbours, 285 were
≥ 2/3, and 20 were below half. The 20 sub-half rows are the review shortlist.

Boundary quality, measured as intra-module call fraction (product↔product edges,
`common` excluded from both ends):

| module | funcs | cohesion | verdict |
|---|---:|---:|---|
| ipc_core | 47 | 0.98 | real module |
| audio | 137 | 0.75 | real module |
| storage (flash_store) | 86 | 0.73 | real module |
| battery | 42 | 0.76 | real module |
| gui_text | 57 | 0.65 | real module |
| notify (ancs) | 99 | 0.64 | real module |
| ble_proto | 99 | 0.64 | real module |
| display | 89 | 0.62 | real module |
| analytics | 14 | 0.63 | real module |
| system/core | 142 | 0.55 | catch-all; see §2.2 |
| esb_sync | 24 | 0.55 | small but coherent |
| touch_key | 30 | 0.37 | thin — mostly calls gui/display |
| onboarding | 13 | 0.32 | **screen, not module** |
| imu_motion | 22 | 0.25 | thin — mostly calls gui/audio |
| dashboard | 26 | 0.17 | **screen, not module** |
| translate | 8 | 0.11 | **screen** |
| navigation | 5 | 0.10 | **screen** |
| quicknote | 11 | 0.04 | **screen** |
| teleprompt | 2 | 0.04 | **screen** |

This is why the layout puts the six low-cohesion features under `src/ui/` rather
than giving each a peer directory: they are ~70 files of screen logic whose real
work happens in `gui/` and `display/`. Grouping them under one `ui/` parent with
one `include/g1/ui.h` is honest about that; six sibling directories would not be.

### 2.2 What the classifier got wrong, and how to settle it

Three findings the executing pass must not inherit blindly.

**(a) The `recon/modules/*.h` "public API" lists are the refgraph *api set* —
functions the module calls as well as functions it owns.** `imu_motion.h` says
so in its own prose: *"the refgraph 'api' set for this topic group is dominated
by shared GUI-canvas primitives … they logically belong to a gui/display
layer."* That is why L3 overrides L2 on disagreement (29 rows). **Settle by:**
one pass over the 20 module headers splitting each declaration list into
`owns:` and `uses:`; the prose already states the answer for `display.h`,
`imu_motion.h` and `misc.h`.

**(b) A handful of utilities dominate the cross-module graph and are not module
members.** `debug_print` (262 in-edges), `get_device_info` (181),
`memset_bytes` (130) alone accounted for ~400 of the cross-module edges in the
first pass. Before the fan-in rule they dragged `ancs_notify`'s apparent
cohesion to 0.64 while making it look like a sink for every other module.
Median cohesion rose from 0.49 to 0.63 once they were lifted into `common`.
`get_timestamp`, `safe_memcpy_checked`, `send_event` and `device_info_*_get*`
sit just below the threshold and are candidates for `common` on review.

**(c) The 145-row L5 residual is not "hard product code" — 87 of it is
unrecognised SDK.** The list contains `dtoa_r`, `strtod`, `strtol_r`, `multadd`,
`d2b_decompose`, `swhatbuf_r`, `sys_heap_free`, `sys_heap_aligned_alloc`,
`arch_swap`, `bt_acl_data_recv`, `bt_id_save`, `bt_pub_key_gen`, `bt_crypto_g2`,
`adc_channel_config`, `saadc_start_read`, `clock_control_nrf_on`, `mpu_*`,
`nrf_rtc_timer_chan_free`, `net_pkt_skip`, the `cbor_*` family and the `log_msg_*`
family. That is a direct consequence of `application_sources.json`'s stated
policy *"ambiguous unclassified functions remain application candidates"*.
**Settle by:** running the residual list through
`tools/build_app_high_fanin_sdk_ownership.py` / `lib_sigmatch2.py` against the
pinned NCS build before assigning a module; expect ≈ 87 to move to `lib/` or
straight to the adoption manifest. The remaining ≈ 58 split into (i) generic
utilities for `common/` (`clz32`, `ctz32_normalize_inplace`,
`hex_nibble_from_ascii`, `hex4_to_uint`, `u32_to_bytes_le_array`,
`bytes_to_u32le_array`, `growbuf_ensure_capacity`, `dynbuf_push_byte_grow`,
`linked_node_at_index`, `subtract_32`) and (ii) **a genuinely new subsystem the
current 20 modules do not have**: `packet_transport_write_frame`,
`packet_transport_send_byte`, `pt_queue_get_free_slot`,
`framed_serial_receive_parser`, `transport_state_update`,
`transport_parameters_{read,write}`, `transport_send_type2_via_ops`,
`transport_notify_callback`. That looks like a framed serial/packet transport.
**Settle by:** reading the log literals in those eight bodies; if they name a
production-test or UART path, create `app/src/transport/`, otherwise fold into
`ble/`. Do **not** guess.

**(d) The call graph itself is incomplete.**
`recon/catalogs/refgraph_app.json.gz` is a 2026-07-16 snapshot with 2,391 nodes
for 2,534 catalogued functions. **52 product functions have no node at all**,
and **156 have a node but zero recorded callers** — the dispatch-table and
work-handler entry points, which are exactly the ones a topic classifier most
needs edges for. Several of the transport functions above are in that set.
**Settle by:** re-running `tools/ghidra_refgraph.py` and, for indirect targets,
using `recon/catalogs/app_address_taken_roots.json` (which already records who
takes each address) as a synthetic caller edge. Until then, no L4 assignment on
a zero-caller function should be trusted.

### 2.3 One function per file, or merge?

Keep one function per file for the whole of G8. Reasons: `cfg_verify` resolves
by `<name>.c`; `recon_kit.prove` writes `<name>.c`; `symbolize.py` hard-asserts
`basename == public_name + ".c"`; `generated_identity.py` enforces
`(core, entry_address)` ownership per generated source. Merging N functions into
`display_panel.c` breaks all four at once for no measurable benefit — the build
already has no glob and CMake does not care about file count. **Merging is a
post-G8 question, and only for functions that are already `static` to one
module.** The 121 symbolized files that today contain more than one top-level
definition are pre-existing static-helper groupings and stay as they are.

---

## 3. Naming and typing

### 3.1 Retiring `FUN_xxxxxxxx`

App is done (4 of 1,609 retained files). **Net is the work: 747 of 923.**

The mechanism already exists and must be used rather than replaced: the durable
map `recon/catalogs/function_names_net.json` (`by_address` →
`{raw_name, name, aliases, human}`), plus `tools/apply_names.py`,
`tools/merge_name_proposals.py` and `tools/validate_name_maps.py`. Rules:

1. **Add, never replace.** A rename adds the new spelling to `name` and pushes
   the old one into `aliases`. `cfg_verify._resolve_source_path` and
   `recon.py::_semantic_name_map` both consult `aliases`, so the proof chain and
   the callee-identity map survive the rename. Dropping the alias is what
   silently weakens the gate.
2. **The rename lands in the same commit as the catalog update**, or
   `symbolize.py` raises `readable filename/identity mismatch`,
   `build_readable_sources.py` raises `source absent from function name map`,
   and `gen_retained_sources.py --check` reports stale.
3. **No name may become ambiguous.** `_semantic_name_map` drops any name that
   maps to more than one VA — silently. Add a gate assertion (§5.3).
4. **Net naming evidence is thin and must be sourced, not invented.** The
   available sources, in order: the SDC/MPSL archive symbol tables already
   indexed by `recon/ownership/net_sdc_archive_ownership.json` (325 addresses,
   218 exact+unique); `net_function_ownership.json` (452 rows, 435 by ordered
   opcode match against `~/ncs251/netref_build`); the Zephyr kernel/`nrf` subsys
   matches in the adoption manifest (158 + 49). Between them **604 of 1,247 net
   functions already have an upstream identity** — those are mechanical renames
   with a byte-match receipt, not judgement calls. The remaining ~643 unnamed
   reconstructions should stay `FUN_` until an upstream match or a log literal
   names them. **Do not synthesise plausible names for net stock code.**
5. `misc`-suffixed and address-suffixed spellings on app (46
   `<name>_<hex>`, 37 `_N` dedupe suffixes, 15 `thunk_*`, 16 `g1_recon_*`) are
   deliberate disambiguators for real distinct symbols. They stay until the
   function they disambiguate is displaced. Do not "clean" them.
6. 372 of the 2,466 app human names are tagged medium- or low-confidence. Those
   are the ones a reviewer should re-derive from log literals during the module
   sweep; a wrong name in a header is worse than `FUN_`.

### 3.2 Retiring `rodata_<hex>` and `g_<hex>`

`g1_app_symbols.h` declares 3,387 globals of which **585 (17.3 %) have a real
name**; the 2,611 `rodata_<hex>` externs are the bulk. **G6 already retires
2,024 of the 2,625 numeric pins by inlining string literals** — that work is
scoped in `prerefactor_plan.md` §1.5 and must not be duplicated here. G8 inherits
whatever G6 leaves and names only what has evidence:

- RAM globals are the tractable half: 549 of 740 already named. The 191
  remaining `g_<hex>` should be named from their accessors' log strings and from
  `recon/structs/struct_catalog_app.json` `kind:global` (68 layouts).
- The 36 named rodata externs are LC3 tables and handler lists. The rest are
  data whose *meaning* is not recovered; `rodata_decode_report.md` §4 records
  that element width is proven for exactly two regions. **Naming the rest is
  invention. They keep the address spelling.**

### 3.3 Introducing real types

`recon/structs/struct_catalog_app.json`: **676 layouts, all `verified:true`**
(D1 access proof + D2 `_Static_assert(offsetof)` compile proof),
2,921 fields of which 2,824 (96.7 %) are named, 97 offset-only placeholders in
32 structs, covering **826 of 2,115 functions (39 %)**. 299 are library shapes
(only 60 verified against real NCS headers), 377 are G1-original. Confidence:
505 low / 128 medium / 43 high.

Application rules:

1. **Generate, don't hand-write.** Emit `include/g1/structs/<struct>.h` from the
   catalog, each with its `_Static_assert(sizeof(...) == N)` and per-field
   `_Static_assert(offsetof(...) == 0xNN)`. Those asserts are the type system's
   own parity gate; they must be in the shipped header, not in a test.
2. **Apply per function, gated by `cfg_verify`, never in bulk.**
   `recon/structs/README.md` already defers application to a separate gated
   pass for exactly this reason. Replacing `*(int *)(p + 0x10)` with `p->field`
   changes nothing *if* the type width and signedness are identical — and
   changes codegen if they are not. AGENTS.md methodology step 1 makes width and
   signedness load-bearing.
3. **The 299 library structs are the wrong place to start.** Only 60 are
   verified against real headers; using the other 239 imprints an agent's guess
   into a header. Start with the 377 G1-original structs, and within those with
   the 43 high-confidence ones.
4. **The 97 offset-only fields stay `field_0xNN`.** Renaming them is invention.
5. **`device_info_t` first.** It is the hub the module headers all reference and
   it is what makes `display/`, `ui/` and `sensors/` legible. It is also the
   riskiest single header: a wrong field width there touches hundreds of files.
   It gets its own batch (§5, Batch 7a) and its own before/after `.o` byte
   comparison.
6. **Net has no struct catalog.** Do not fabricate one; the net core is stock,
   and its types come from NCS headers when a function is displaced.

---

## 4. Tree consolidation

### 4.1 Target end state

```
recon/app/src, recon/net/src        canonical parity corpus — FLAT, address-headed, unchanged
        |
        |  (generators, one direction only, all with --check)
        v
g1/{app,net}/src/<subsystem>/...    the production tree — GENERATED, never hand-edited
```

Everything else is deleted or becomes a generated view:

| tree | fate |
|---|---|
| `recon/app/src_sym`, `recon/verified/src_sym` | **delete** — dead since 2026-07-11, 2,118 files |
| `recon/verified/src` | **delete after repointing** `reverify.py`'s legacy `sweep`/`check` `core_ctx()` at `recon/app/src`. It exists only because those two modes read it. |
| `recon/named`, `recon/net/named` | keep as an *intermediate* of the generator pipeline, or fold into `symbolize.py`. Not a place anyone edits. |
| `recon/symbolized/{app,net}` | becomes the generator's staging output; the production tree is materialised from it. **Stops being hand-edited (§4.3).** |
| `recon/readable_sources/app/{g1,library}` | **delete** — 2,115 real copies that duplicate `symbolized` + `application_sources.json`. `build_readable_sources.py` already `rmtree`s and rebuilds, so it is regenerable on demand. |
| `recon/application/src` | keep — it is 1,156 symlinks, costs nothing, and `--check` verifies it |
| `recon/modules/*.h` | **promote** to `include/g1/*.h` after the owns/uses split (§2.2a) |
| `recon/data`, `recon/net/data`, `recon/application/rodata` | move under `g1/{app,net}/src/rodata/` **with filenames unchanged** (§1.4) |

Nine trees → **two hand-edited roots** (`recon/{app,net}/src`) plus one generated
production tree plus one symlink view.

### 4.2 Sequence

The order matters because each step removes a way for the next to go wrong.

1. **Reconcile the 101-file debt** (§1.1). For each of the 37 downstream-edited
   symbolized files, diff against `recon/named`, decide whether the edit is a
   symbolization artifact (keep, it will regenerate) or a real semantic fix
   (port back to `recon/app/src`, re-prove with `cfg_verify`, then regenerate).
   Same for the 3 missing `verified/src` files and the 31 net orphans. **Output:
   a receipt JSON listing every file and its disposition.** Nothing else in this
   plan may start before this lands.
2. **Regenerate `application_sources.json`** against the live manifest
   (`build_app_source_view.py`, then `--check`). Product count should land at
   ~1,101.
3. **Delete the two dead `src_sym` trees.** Zero build effect; confirm with a
   byte-identical rebuild.
4. **Repoint `reverify.py` legacy modes, then delete `recon/verified/src`.**
   Re-run the full 8×2 `sweeplist` sweep afterwards — the inventory digest
   changes and every lane receipt is discarded fail-closed anyway.
5. **Prove the generators are byte-faithful.** Run `apply_names.py`,
   `symbolize.py --write`, `build_readable_sources.py`,
   `build_app_source_view.py --check` on a clean checkout and diff the outputs
   against the committed trees. **Any file that does not round-trip is drift
   that step 1 missed.** (`build_symbol_map.py` must run first — the scratchpad
   `symbol_map.json` / `symbol_map_net.json` that `symbolize.py` and
   `gen_linker.py` need are **currently missing**; see §4.4.)
6. **Delete `recon/readable_sources`** once step 5 shows it round-trips.
7. **Materialise `g1/`** from the symbolized trees via the new directory-aware
   generator (Batch 6). Keep `recon/application/{app,net}` alive in parallel for
   one iteration and require both builds to produce byte-identical `zephyr.bin`
   before retiring the old one.

### 4.3 Making the production tree unhand-editable — the actual fix for drift

Today the build tree is downstream of the parity tree *and* is where people fix
bugs, because a symbolization-level fix has nowhere else to live. Deleting trees
does not fix that; it just makes the next drift harder to see.

**Proposal: an explicit override layer with a completeness gate.**

- `recon/overlay/{app,net}/<name>.c` — reviewed, hand-authored replacements for
  a generated file. Each carries the same `identity:` header plus a
  `overlay-reason:` line.
- The generator prefers an overlay file over its generated output and records
  the substitution in `recon/generated/<core>_overlay_manifest.json`.
- A new gate, `tools/check_generated_tree.py --core app`, regenerates into a
  temp dir and asserts that every file in the production tree is either
  byte-identical to the generated output or listed in the overlay manifest.
  **Exit 1 on any unexplained difference.**

That converts "someone edited the build tree and nobody noticed" — which is the
bug class the owner reported — into a listed, reviewable set that CI fails on.
It costs one script and one JSON.

### 4.4 Two infrastructure repairs that block everything

1. **The hard-coded dead scratchpad.** `cfg_verify.py:27`, `parity/recon.py:22`,
   `reverify.py:18`, `recon_kit.py:23`, `net_recon_kit.py:12`,
   `build_symbol_map.py`, `gen_linker.py` and `symbolize.py` all embed
   `SCR = "/private/tmp/claude-501/.../bf259b2e-.../scratchpad"`. `app_funcs.json`,
   `classified.json` and `net_funcs.json` still exist there; **`symbol_map.json`
   and `symbol_map_net.json` do not**, so `symbolize.py` and `gen_linker.py`
   cannot run at all right now. Make `SCR` an env var with a repo-relative
   default (`recon/generated/cache/`) and commit the inputs the generators need.
   Until this is fixed the consolidation in §4.2 step 5 is impossible.
2. **No test runner, no CI.** 159 `tools/test_*.py`, no `pytest.ini`, no
   `Makefile`, no script that runs them. Add
   `tools/run_all_gates.sh` that runs `python -m unittest discover -s tools -p
   'test_*.py'` plus the six binary gates of §1.7, and make it the definition of
   "green". A refactor of this size without one runnable command is not
   reviewable. **Do not move `tools/*.py` into packages** — 159 tests, every
   `recon/**` importer, `reverify.py`'s `subprocess([... BASE + "/tools/cfg_verify.py" ...])`
   and ~8 hard-coded `sys.path.insert(0, ".../tools")` sites all assume the flat
   layout. That is a separate, later, low-value refactor.

---

## 5. How parity is preserved

### 5.1 Three classes of change, three different obligations

| class | example | obligation |
|---|---|---|
| **T — textual/structural, provably codegen-neutral** | move a file; rename a symbol; extract a `static inline` verbatim into a header | **byte-identical `.o`**: rebuild and `cmp` every affected object file, then `cmp` `zephyr.bin`. If the bytes differ at all, it was not a T change. |
| **S — semantic-preserving but codegen-visible** | struct typing, MMIO macro per width, unified logging prototype | `recon_kit.prove` **and** `tools/cfg_verify.py <core> <FUNC>` per touched canonical function; plus a disassembly read if argument passing or stack layout is involved |
| **B — behavioural** | displacing a function to the SDK; changing a thread's stack args | the full gate ladder including the display/sensor oracle |

**The refactor is designed so that the overwhelming majority of it is class T.**
Moving 1,101 files and renaming 747 net functions should not change one byte of
the image. If it does, the move was not what you thought it was.

### 5.2 The gate ladder

Run in this order; stop at the first failure.

```sh
cd /Users/freedomcoder/Projects/G1disasm2
V=PYTHONSAFEPATH=1\ .venv/bin/python

# L0 — static consistency (seconds)
$V tools/gen_retained_sources.py --check
$V tools/build_app_source_view.py --check
$V tools/check_generated_tree.py --core app --core net      # NEW, §4.3
$V -m unittest discover -s tools -p 'test_*.py'

# L1 — per-function parity, only for touched canonical bodies (minutes)
$V tools/cfg_verify.py app  <FUNC>          # per function
$V tools/cfg_verify.py net  <FUNC>
# whole-corpus, only when the inventory changed (hours, free on compute):
for i in 0 1 2 3 4 5 6 7; do $V tools/reverify.py sweeplist app $i 8; done
for i in 0 1 2 3 4 5 6 7; do $V tools/reverify.py sweeplist net $i 8; done

# L2 — link-level (minutes)
$V tools/full_link.py app && $V tools/full_link.py net       # 0 UNKNOWN, no audit drift
recon/application/build_cohesive.sh app /private/tmp/g1-<tag>-app
recon/application/build_cohesive.sh net /private/tmp/g1-<tag>-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
#   assert: nm -u == 0, 0 duplicate globals, no --allow-multiple-definition

# L3 — image-level
cmp <new>/zephyr/zephyr.bin <baseline>/zephyr/zephyr.bin     # class-T batches: MUST be identical
arm-zephyr-eabi-size <new>/zephyr/zephyr.elf                 # record FLASH/RAM every time

# L4 — the four defect gates
$V recon/emulator/scripts/check_ram_pin_collisions.py            <app-elf>
$V recon/emulator/scripts/check_ram_pin_collisions.py --core net <net-elf>
$V recon/emulator/scripts/check_net_raw_literals.py              <net-elf>
$V recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
$V recon/application/verify_net_stock_data_window.py             <net-elf>

# L5 — behavioural oracle (~2 min Renode + ~20 s analysis), class B and end-of-batch only
#   navigation: default G1_ATT_WRITE;  dashboard: G1_ATT_WRITE=""
#   (full invocation: recon/emulator/reports/our_boot_bringup.md, iteration 36)
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_<tag>
$V recon/emulator/scripts/build_display_sensor_oracle.py /private/tmp/g1_ours_<tag> /private/tmp/g1_rep_<tag>
#   assert: G-2 p1_boot sha == 1d617c65a688f10e… , 656 == 656 lit px, 0 differing rows
#           G-1 p2_render sha == b26c73b37d441fc8… , 1,098 == 1,098 lit px
#           D-1 dashboard peak >= 2,895 lit / 2,659 exact, bbox (78,211)-(564,338)
```

### 5.3 Keeping a renamed or moved function provable

Five invariants. Each gets an assertion in `tools/check_generated_tree.py` or a
new `tools/check_identity_integrity.py`.

1. **Identity is the address, and it is written in the file.** Every generated
   source carries `identity: <RAW> @ 0x<VA>` in its header, and
   `gen_retained_sources.py` cross-checks it against the name catalog.
   *Assertion: every `.c` under `g1/**/src/**` has a parseable identity header,
   and the (core, VA) set is exactly the retained set.*
2. **A rename is an alias addition.** *Assertion: for every function, the old
   spelling appears in `function_names_<core>.json` `aliases`; no name maps to
   more than one VA (`_semantic_name_map` drops ambiguous names silently, which
   is the failure this catches).*
3. **Callee-identity coverage must not regress.** Before and after any rename
   batch, run `cfg_verify` on a fixed sample and compare
   `len(recon.LAST_DIRECT_TARGET_MAP)` per function. *Assertion: the map is
   never smaller after than before.* This is the only defence against the
   silent-weakening mode in §1.7.
4. **The canonical corpus stays flat.** *Assertion: `recon/{app,net}/src`
   contain no subdirectories and every `.c` basename equals its function name or
   a recorded alias.*
5. **The inventory digest is recomputed deliberately.** Any change to the flat
   corpus invalidates every `reverify_<core>_L*.json` lane receipt. *Assertion:
   a batch that touches the corpus schedules a full 8×2 re-sweep in the same
   PR.* Compute is free on the agent budget; skipping it is not.

---

## 6. Batch sequence, gates and flash accounting

Ordered safest-first. Each batch is independently revertible (one commit, one
receipt JSON). "Flash" is the expected delta on the app image unless stated.

| # | batch | class | scope | gates | flash |
|---|---|---|---|---|---|
| **0** | **Build-machinery de-coupling.** Replace `KEEP(*rodata_*.c.obj(...))` with a generated explicit KEEP list, emitted by `gen_app_rodata_sources.py`, naming exactly the objects matched today. Make `gen_retained_sources.py` and `full_link.py` use `os.walk` + `relpath`. Fix the dead-scratchpad path (§4.4). | T | 3 tools, 1 `.ld`, 2 CMake | L0–L4, **`cmp zephyr.bin` must be identical** | **0 B — this is the whole point of the batch.** If it is not 0, the old KEEP was retaining or dropping something nobody knew about; find out before proceeding. |
| **1** | **Reconciliation.** §4.2 steps 1–2: 37 + 3 + 1 + 29 + 31 files, regenerate `application_sources.json`. | S (a few) | ≤ 101 files | L0–L4, `cfg_verify` on any body ported back | ~0; any real semantic fix is a normal parity change |
| **2** | **Dead-tree deletion.** `app/src_sym`, `verified/src_sym`; repoint `reverify.py` legacy modes; delete `verified/src`. | T | 5,256 files removed, 1 tool | L0–L2 + full 8×2 sweep | 0 B (nothing compiled) |
| **3** | **Generator round-trip proof + `readable_sources` deletion.** §4.2 steps 5–6. Add `check_generated_tree.py` and the overlay mechanism (§4.3). | T | 1 new tool, 2,115 files removed | L0, byte-diff of regenerated vs committed | 0 B |
| **4** | **Test runner + gate script** (`tools/run_all_gates.sh`), CI-able. | — | 1 script | it *is* the gate | 0 B |
| **5** | **Net renaming, tranche 1: the 604 upstream-identified functions.** Mechanical, each with a byte-match receipt from `net_sdc_archive_ownership.json` / `net_function_ownership.json` / the adoption manifest. Aliases added, never replaced. | T | ~604 net files + catalogs | L0–L4 + **§5.3 invariant 3 coverage assertion** + full net sweep | **0 B** (symbol names do not occupy flash) — verify with `cmp zephyr.bin` |
| **6** | **The move.** Materialise `g1/{app,net}/src/<subsystem>/…` per `refactor_module_map.json`; keep `recon/application/{app,net}` building in parallel for one iteration. Rodata filenames frozen. | T | 1,101 + 482 + 945 files | L0–L4, **both builds must emit byte-identical `zephyr.bin`**, then L5 oracle once | **0 B** |
| **7a** | **`device_info_t` header.** Generate `include/g1/device_info.h` from the catalog with `_Static_assert`s; apply to the ~40 densest accessors only. | S | ~40 app files | `prove` + `cfg_verify` per file; `.o` `cmp` where the types are provably identical; L5 oracle | target 0 B; **budget +2 KB, abort above that** |
| **7b** | **Remaining G1-original structs**, high-confidence first (43), then medium (128). Library structs and the 97 offset-only fields excluded. | S | ~200–400 app files, batched by struct | as 7a, per struct | target 0 B; measure per struct |
| **8** | **Module headers.** Promote `recon/modules/*.h` → `include/g1/*.h` after the owns/uses split; every non-`static` function gets exactly one prototype; module-internal functions become `static`. | S | all app product files | L0–L4; `nm` diff must show the expected set of symbols losing global binding | **likely a small shrink** — `static` + `-Os` lets GCC inline and drop wrappers. Measure; a large shrink means a function got dropped that should not have. |
| **9** | **Library residue displacement, app.** The 482 recovered stock functions still compiled (57,874 Ghidra-declared bytes). Bluetooth host is 217 of the 666 known candidates and goes last, unit by unit (`l2cap.c → id.c → adv.c → conn.c → hci_core.c → smp.c → att.c → gatt.c`). Honour the 27 `keep_reconstructed` exceptions. | B | per unit | full ladder incl. L5 **after every unit** | **the only batch with a real win, and it is smaller than it looks.** 93 rows applied so far gave **−3,516 B**. `library_displacement_report.md` §6 measures the *remaining non-BT live headroom at 15 rows / 1,068 B* — everything else is already gc'd out. The BT-host 217 rows are unmeasured. **Do not budget a saving; measure one.** |
| **10** | **Library residue displacement, net.** 33 candidates, zero applied. | B | per row | full ladder | net duplication residual is **2,329 B**; but 57 of the 666 candidates *pull new archive members in* (`lib_a-dtoa.o` 3,308 B, `lib_a-nano-vfprintf_float.o` 1,422 B). **Measure FLASH after every single row.** Net has 1,747 B of real headroom. |
| **11** | **Net renaming, tranche 2** and the `UNSORTED/` quarantine drain (§2.2c/d), as evidence arrives. | T/S | ongoing | per item | 0 B |

### 6.1 Flash accounting summary

- **Batches 0–6 and 11 are budgeted at exactly 0 B and are gated on
  `cmp zephyr.bin` being identical.** Roughly 90 % of the refactor's file churn
  lives there. This is the plan's main safety property: the parts that touch the
  most files cannot change the image, and the gate proves it rather than hoping.
- **Batch 7 (typing) is the one that can grow the image.** Budget +2 KB total
  against the app's 30,212 B headroom; abort a sub-batch that exceeds it. Do
  **not** run Batch 7 on net (no struct catalog, 1,747 B of real headroom).
- **Batch 8 should shrink slightly**; an unexpected large shrink is a bug.
- **Batches 9–10 are the only sources of a real saving, and the measured
  evidence says it is modest**: −3,516 B achieved so far, ~1,068 B of non-BT
  live headroom left, BT-host unmeasured, and displacement can be net-negative
  because it pulls archive members in.
- **G6 (literal inlining) is the big flash event, and it belongs to the
  pre-refactor plan, not here.** 66,243 B of app strings + 3,753 B net are at
  stake and `prerefactor_plan.md` §1.6 already specifies the
  inline→withdraw-object→delete-PROVIDE transaction. G8 must not start Batch 7
  until G6's string batches have landed and the flash number has been re-taken.
- **Net ordering rule:** never run two flash-affecting batches on net without a
  build in between. At 1,747 B of real headroom, one 2 KB regression is the
  difference between a shippable image and one that does not fit the device.

### 6.2 What each batch produces as evidence

One JSON receipt per batch under `recon/ownership/g8_batch_<n>_receipt.json`:
files touched, gate results (all of L0–L5 that ran), `FLASH`/`RAM` before and
after, `zephyr.bin` sha256 before and after, and for class-T batches the
assertion that they are equal. A batch without a receipt is not landed.

---

## 7. Non-goals — what must NOT be cleaned up

1. **The canonical parity corpus layout.** `recon/{app,net}/src` stay flat,
   `FUN_`/name-keyed, with the `@ 0xADDR` first-line header. Five tools resolve
   through it. It is not ugly; it is the index.
2. **Byte-exact data.** The 993 `recon/data/rodata_0x*.c`, the 6 net ones and
   the 16 decoded batch files keep their **exact filenames** (§1.4), their
   `__asm__("rodata_<hex>")` object names, their `unsigned char []` typing and
   their contents. `rodata_decode_report.md` §4 proves element width for exactly
   two regions; typing the others as arrays is invention. No reformatting, no
   renaming, no re-splitting.
3. **The `__asm__`-alias mechanism.** All three uses stay:
   `extern const unsigned char __g1_fp_FUN_xxxxxxxx[] __asm__("real_symbol")`
   for relocation-correct function-pointer rebinding (95 uses in
   `g1_app_symbols.h`, 13 in net); `extern T f(...) __asm__("FUN_xxxxxxxx")` for
   call-identity aliasing inside symbolized TUs (41 sites); and
   `const char g1_ro_99e71[44] __asm__("rodata_99e71")` for data-object naming.
   The untyped `unsigned char[]` spelling is *deliberate* — it is what stops the
   extern colliding with the real definition's signature. Do not "fix" it to a
   function pointer type.
4. **Anything that must stay relocatable.** The 127 `ADDR_*_THUMB` symbols (258
   sites), the `ptr_table`/`ptr_record` regions, the `struct device` /
   `init_entry` neighbourhoods, RAM and `.text` addresses. `prerefactor_plan.md`
   §1.4 is the authority; G8 inherits it unchanged.
5. **Deliberate ABI shapes.** Variadic vs non-variadic logging prototypes on a
   hard-float build (G7-C10) is an ABI decision to be *made once from the
   disassembly*, not a style question. `int` vs `unsigned int` volatile accesses
   are not interchangeable. Narrow-ABI net functions and the reviewed stack
   arities in `cfg_verify.REVIEWED_TARGET_CALL_STACK_ARITIES` are load-bearing.
6. **SDK-displaced units.** The 532 app + 312 net manifest exclusions are not
   ours. They keep their reconstruction file on disk (deliberately — the
   manifest is *not* a glob) and they get no target path, no rename, no header,
   no struct typing.
7. **The 27 `keep_reconstructed` functions** that look stock but are Even
   modifications — including the 8 `bt_conn_*` notify/ref helpers. A blanket
   "displace everything named `bt_*`" rule is wrong and the report says so.
8. **`tools/*.py` packaging.** Flat by necessity (§4.4).
9. **The 121 multi-definition symbolized files, the 46 address-suffixed names,
   the 37 `_N` dedupe suffixes, the 16 `g1_recon_*` and 15 `thunk_*` spellings.**
   Each disambiguates a real distinct symbol.
10. **`recon/emulator/**`, `armemul`, and the golden artifacts.** The oracle
    defines correctness; refactoring the thing that measures you is how you stop
    being able to measure.
11. **Merging functions into larger translation units** (§2.3).
12. **Naming the 2,217 evidence-free scalars, the 97 offset-only struct fields,
    or the ~643 unmatched net functions.** Carried over from
    `prerefactor_plan.md` §4 and restated because G8 is exactly the phase where
    the temptation peaks.

---

## 8. Where the evidence is thin, and how to settle it

| # | thin spot | how to settle |
|---|---|---|
| 1 | **320 L4 graph assignments (29 % of product code)** rest on first-hop majority. 241 unanimous, 20 below half. | Re-run `tools/ghidra_refgraph.py`; add address-taken edges from `app_address_taken_roots.json`; review the 20 sub-half rows by hand. Do the six lowest-cohesion `ui/` features last — their members are mostly correct by name anyway. |
| 2 | **145 L5 residual**, of which ~87 look like unrecognised SDK. | `lib_sigmatch2.py` / `build_app_high_fanin_sdk_ownership.py` against the pinned NCS build. Expect most to leave `UNSORTED/` for `lib/`. |
| 3 | **The `transport_*` / `packet_transport_*` / `framed_serial_*` cluster (8 functions)** matches no existing module. | Read the log literals in those bodies. New `app/src/transport/` if they name a serial/production-test path; otherwise fold into `ble/`. |
| 4 | **`recon/modules/*.h` mixes owned and used symbols.** | Split each header into `owns:` / `uses:`; the prose in `display.h`, `imu_motion.h` and `misc.h` already gives the answer for the known cases. |
| 5 | **52 product functions have no refgraph node; 156 have no recorded caller.** | Re-export the refgraph; treat dispatch-table targets via address-taken roots. Until then their module assignment is a guess and they belong in `UNSORTED/`. |
| 6 | **`system`/`core` at 142 functions and 0.55 cohesion is still a catch-all.** | After batches 1–3 re-run the classifier; split into `core/boot`, `core/threads`, `core/power`, `core/device_info` only if the sub-cluster cohesion supports it. Do not split on vibes. |
| 7 | **Net module boundaries beyond the ~30 curated G1 functions.** | There are none to find — `net_function_ownership.json` says 452/452 stock and zero missing product functions. `net/src/stock/` is the honest answer; sub-foldering it by manifest component is cosmetic and optional. |
| 8 | **App library-displacement saving is unmeasured** (only net's 2,329 B duplication is). | Parse the kept-sections part of the app `zephyr.map` and diff recovered vs archive-provided symbols, exactly as `library_displacement_report.md` §6 did for non-BT. Produce a number *before* budgeting one. |
| 9 | **505 of 676 structs are low-confidence.** | Only the 43 high + 128 medium are in scope for Batch 7. The 505 low stay analysis artifacts. |

---

## 9. Risks, ranked

1. **Silent gate weakening on rename (§1.7, §5.3 invariant 3).** A callee
   renamed without an alias vanishes from `LAST_DIRECT_TARGET_MAP` and its
   identity check is skipped — the harness still says PASS. This is the only
   risk in the plan whose failure mode is invisible, and it is concentrated in
   Batch 5 (604 net renames). Mitigation: the coverage assertion, mandatory.
2. **The `KEEP(*rodata_*.c.obj)` filename coupling (§1.4).** Renaming a rodata
   file across the `rodata_0`-substring boundary either drops byte-verified
   tables (which then resolve through an inert `PROVIDE` to an original-image
   address holding unrelated bytes — the `fortify_chk_fail` / font-directory bug
   class) or KEEPs ~1,793 string objects that are currently gc-able, into an
   image with 30,212 B of headroom. Mitigation: Batch 0, before anything moves.
3. **Net flash.** 1,747 B of real headroom, 96.71 % RAM, and displacement can
   *increase* size by pulling archive members. One careless batch makes the
   image unshippable. Mitigation: one flash-affecting change at a time,
   `arm-zephyr-eabi-size` after each.
4. **Regenerating over unpushed hand edits.** Batch 3 runs the generators for
   real; the 37 downstream-edited files are exactly what a regeneration
   destroys. Mitigation: Batch 1 must complete and produce its receipt first;
   the overlay mechanism (§4.3) is what stops it recurring.
5. **Struct typing changing widths.** `*(int *)(p+0x10)` → `p->field` where
   `field` is `uint32_t` changes every downstream comparison and shift, and the
   harness is blind to some of it. Mitigation: high-confidence G1-original
   structs only, per-function `cfg_verify`, `.o` `cmp` wherever the types are
   provably identical.
6. **The oracle is the only behavioural check, it is ~2.5 min, and two of its
   criteria are currently failing** (G-3 SPI repeats; D-1 dashboard 2,895/2,923).
   A refactor that moves those numbers is hard to attribute if a batch changed
   many files. Mitigation: run L5 at every batch boundary, not only at the end,
   and record the exact hashes in the receipt.
7. **Ambiguity collisions in the name catalog.** `_semantic_name_map` drops any
   name with two VAs, silently. 6 conflicts already exist on app. A renaming
   pass that creates more degrades the harness without failing anything.
   Mitigation: §5.3 invariant 2.
8. **Scope creep into `recon/emulator/**` and `armemul`.** Off limits (§7.10).
9. **Concurrency.** Two agents are editing the source trees and
   `recon/emulator/**` right now. Batch 1 in particular cannot run against a
   moving tree. Mitigation: G8 starts only when the P4/G4 bring-up declares a
   stable point, and Batch 0 re-measures flash on that exact build.

---

## 10. Ordering against the owner's roadmap

```
G6 inline small literals        prerefactor_plan.md §1   -> retires 2,024 pins, frees up to 66 KB app
G7 dedupe / inline+macro        prerefactor_plan.md §2   -> fixes the C10 logging-ABI defect
G5 rodata decode                DONE
--------------------------------------------------------------------------------
G8 Batch 0-4    infrastructure  no source churn, no flash change      <- START HERE
G8 Batch 5      net renaming    0 B, 604 receipted renames
G8 Batch 6      the move        0 B, ~2,500 files
G8 Batch 7-8    types + headers the only codegen-visible structural work
G8 Batch 9-10   displacement    the flash win, measured not budgeted
G8 Batch 11     residual drain  as evidence arrives
```

Batches 0–4 have no dependency on G6/G7 and can start immediately once the
bring-up settles — they are pure infrastructure and they are what makes the rest
safe. **Batch 7 must wait for G6**, because inlining string literals moves
66 KB around and there is no point typing structs against a flash number that is
about to change.

---

## Appendix A — the mapping generator, verbatim

Read-only. Writes `recon/ownership/refactor_module_map.json` and nothing else.
Run with `PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python`.
The output JSON pins the sha256 of every input, so a stale run is detectable.

```python
"""Generate recon/ownership/refactor_module_map.json.

Rule (documented in recon/analysis/production_refactor_plan.md Sec 3):
  L0 ownership : recon/application/application_sources.json (app) overlaid with
                 recon/ownership/adoption_manifest.json exclusions -> product | library | displaced
  L1 fan-in    : product functions with >=40 in-edges from other product functions -> "common"
  L2 curated   : name declared (non [shared-infra]) in exactly one recon/modules/<m>/<m>.h
                 AND the lexical rule agrees or is silent -> that module
  L3 lexical   : ordered regex over the recovered readable name (specific -> generic)
  L4 graph     : majority module among refgraph callers+callees already assigned (not "common")
  L5 residual  : unassigned -> needs_judgement
Net: no topic axis exists (core is ~100% stock).  Grouping comes from the
explicit source groups already declared in recon/application/net/CMakeLists.txt
plus adoption-manifest ownership.
"""
import json,re,gzip,collections,glob,os,hashlib,datetime
B='/Users/freedomcoder/Projects/G1disasm2/'
OUT=B+'recon/ownership/refactor_module_map.json'
def sha(p):
    return hashlib.sha256(open(p,'rb').read()).hexdigest()

TOPICS=[
 ("teleprompt", r"teleprompt|tpm_"),
 ("quicknote",  r"quicknote|quick_note"),
 ("navigation", r"navigat|\bnav_|panoramic|overview_map"),
 ("translate",  r"translat|language|\blang_"),
 ("onboarding", r"onboard"),
 ("analytics",  r"burial|buried|analytic|point_record|record_info"),
 ("dashboard",  r"dashboard|\bdash_"),
 ("ancs_notify",r"ancs|whitelist|message_come|msg_expir|notification"),
 ("imu_motion", r"\bimu|attitude|anti_shake|fusion|accel|gyro|lsm6|bmi2|head_?up|motion|spline"),
 ("touch_key",  r"touch|key_event|keypress|button|click|gesture|sw0|\bkey_"),
 ("battery",    r"battery|fuel|charge|soc_|glassbox|opt300|\blux|ambient"),
 ("audio",      r"audio|dmic|\bpdm|mic_|voice|whisper|lc3|record_|codec"),
 ("gui_text",   r"gui_|utf|font|bitmap|wordwrap|glyph|truncate|text_width|draw_|\bdraw\b|canvas"),
 ("display",    r"display|panel|jbd|jdb|raster|projector|brightness|screen|lcd|reflash"),
 ("esb_sync",   r"\besb|_to_slave|slave_|master_|sync_"),
 ("ble_proto",  r"\bble|gatt|\batt_|l2cap|conn_|pairing|bond|\bsmp|advertis|\bhci"),
 ("ipc_core",   r"\bipc|rpmsg|\bept|mbox|msgq|openamp|virtqueue"),
 ("flash_store",r"flash|\bnvs|settings|sett_|storage|persist|burn|read_usr|save_"),
 ("system",     r"system|power|\bboot|\bdfu|reset|reboot|watchdog|work_mode|device_info|aging|\bmain\b|thread|init"),
]
NOT_ANCS=re.compile(r"^(ble|sys|clock_event|context_release_and|transport)_notify|_notify_(callback|packet)$|notify_config_change")
DIR={
 'common':'app/src/common','system':'app/src/core','display':'app/src/display','gui_text':'app/src/gui',
 'dashboard':'app/src/ui/dashboard','navigation':'app/src/ui/navigation','teleprompt':'app/src/ui/teleprompt',
 'translate':'app/src/ui/translate','quicknote':'app/src/ui/quicknote','onboarding':'app/src/ui/onboarding',
 'ancs_notify':'app/src/notify','ble_proto':'app/src/ble','esb_sync':'app/src/esb','ipc_core':'app/src/ipc',
 'audio':'app/src/audio','imu_motion':'app/src/sensors/imu','battery':'app/src/sensors/power',
 'touch_key':'app/src/sensors/input','flash_store':'app/src/storage','analytics':'app/src/analytics',
 'needs_judgement':'app/src/UNSORTED',
}
def lexical(n):
    low=n.lower()
    for t,p in TOPICS:
        if re.search(p,low):
            if t=='ancs_notify' and NOT_ANCS.search(low): continue
            return t
    return None

appsrc=json.load(open(B+'recon/application/application_sources.json'))
funcs=appsrc['functions']
manifest=json.load(open(B+'recon/ownership/adoption_manifest.json'))
excl_app={int(e['va'],16) if isinstance(e['va'],str) else e['va']:e
          for e in manifest['cores']['app']['entries'] if e.get('exclude_reconstruction')}
excl_net={int(e['va'],16) if isinstance(e['va'],str) else e['va']:e
          for e in manifest['cores']['net']['entries'] if e.get('exclude_reconstruction')}
rg=json.load(gzip.open(B+'recon/catalogs/refgraph_app.json.gz'))['functions']
graph={int(k,16):v for k,v in rg.items()}
names_app=json.load(open(B+'recon/catalogs/function_names_app.json'))['by_address']
names_net=json.load(open(B+'recon/catalogs/function_names_net.json'))['by_address']
retained_app=set(re.findall(r'symbolized/app/([^"]+)\.c"',open(B+'recon/generated/app_retained_sources.cmake').read()))
retained_net=set(re.findall(r'symbolized/net/([^"]+)\.c"',open(B+'recon/generated/net_retained_sources.cmake').read()))

# --- L0 ownership -----------------------------------------------------------
rec={}
for f in funcs:
    a=int(f['address'],16)
    own='library' if f['status']!='included_g1_application' else 'product'
    if a in excl_app:
        own='displaced_to_sdk'
    rec[a]={'address':f['address'],'raw_symbol':f['raw_symbol'],'name':f['readable_name'],
            'ownership':own,'exclusion_reasons':f['reasons'],
            'in_build':f['readable_name'] in retained_app}
    if a in excl_app:
        rec[a]['sdk_component']=excl_app[a].get('component')
        rec[a]['sdk_symbol']=excl_app[a].get('upstream_symbol')
prod={a for a,r in rec.items() if r['ownership']=='product'}
# --- L1 fan-in --------------------------------------------------------------
indeg=collections.Counter()
for a in prod:
    for c in graph.get(a,{}).get('calls',[]):
        x=int(c,16)
        if x in prod: indeg[x]+=1
FANIN=40
assign={}; tier={}
for a in prod:
    if indeg[a]>=FANIN: assign[a]='common'; tier[a]=['L1-fanin',indeg[a]]
# --- L2/L3 ------------------------------------------------------------------
curated=collections.defaultdict(set)
for h in sorted(glob.glob(B+'recon/modules/*/*.h')):
    mod=os.path.basename(os.path.dirname(h))
    if mod=='misc': continue
    for line in open(h):
        if '[shared-infra]' in line: continue
        m=re.match(r'\s*(?:extern\s+)?[A-Za-z_][\w \*]*?\b([A-Za-z_]\w*)\s*\([^;]*\)\s*;',line)
        if m and m.group(1) not in ('if','for','while','switch','sizeof','return'):
            curated[m.group(1)].add(mod)
for a in sorted(prod):
    if a in assign: continue
    n=rec[a]['name']; lx=lexical(n); cu=curated.get(n)
    if cu and len(cu)==1:
        m=next(iter(cu))
        if lx is None or lx==m: assign[a]=m; tier[a]=['L2-curated',1.0]; continue
        assign[a]=lx; tier[a]=['L3-lexical-overrides-curated:'+m,1.0]; continue
    if lx: assign[a]=lx; tier[a]=['L3-lexical',1.0]; continue
    if cu and len(cu)>1:
        assign[a]=sorted(cu)[0]; tier[a]=['L2-curated-ambiguous:'+'|'.join(sorted(cu)),0.5]
# --- L4 graph ---------------------------------------------------------------
for it in range(8):
    new=0
    for a in sorted(prod):
        if a in assign: continue
        nb=collections.Counter()
        for c in graph.get(a,{}).get('calls',[])+graph.get(a,{}).get('callers',[]):
            x=int(c,16)
            if x in assign and assign[x]!='common': nb[assign[x]]+=1
        if nb:
            t,k=nb.most_common(1)[0]
            assign[a]=t; tier[a]=['L4-graph',round(k/sum(nb.values()),2)]; new+=1
    if not new: break
for a in prod:
    if a not in assign: assign[a]='needs_judgement'; tier[a]=['L5-residual',0.0]
for a,r in rec.items():
    if r['ownership']=='product':
        r['module']=assign[a]; r['evidence']=tier[a]
        r['target_path']=DIR[assign[a]]+'/'+r['name']+'.c'
    elif r['ownership']=='displaced_to_sdk':
        r['module']='(sdk)'; r['evidence']=['L0-manifest',1.0]; r['target_path']=None
    else:
        comp=(excl_app.get(a) or {}).get('component')
        r['module']='lib'
        r['evidence']=['L0-appsourceview',1.0]
        r['target_path']='app/src/lib/'+(comp or 'unclassified')+'/'+r['name']+'.c'

# --- NET --------------------------------------------------------------------
netcm=open(B+'recon/application/net/CMakeLists.txt').read()
def grab(var):
    m=re.search(r'set\('+var+r'(.*?)\n\)',netcm,re.S)
    if not m: return []
    return re.findall(r'/([A-Za-z0-9_]+)\.c"',m.group(1))
netgroups={
 'net/src/esb_sync':grab('G1_PRODUCT_ENDPOINT_SOURCES')+grab('G1_ESB_UPLINK_WORKER_SOURCES')
                    +grab('G1_ESB_CLOCK_CALLBACK_CLOSURE_SOURCES'),
 'net/src/timeslot':grab('G1_TIMESLOT_OWNER_SOURCES'),
}
netrec={}
for path,members in netgroups.items():
    for stem in members:
        netrec[stem]={'stem':stem,'ownership':'product','module':os.path.basename(path),
                      'target_path':path+'/'+stem+'.c','evidence':['net-CMake-curated',1.0]}
for stem in sorted(retained_net):
    if stem in netrec: continue
    netrec[stem]={'stem':stem,'ownership':'stock_recovered','module':'stock',
                  'target_path':'net/src/stock/'+stem+'.c','evidence':['net-default-stock',1.0]}
for extra in ('g1_cpunet_main','g1_ipc_rpmsg_register_ept'):
    netrec.setdefault(extra,{'stem':extra,'ownership':'product','module':'core',
                             'target_path':'net/src/core/'+extra+'.c','evidence':['net_esb_boot_root/named',1.0]})

summary={
 'app':{
   'total_catalogued_functions':len(rec),
   'ownership':dict(collections.Counter(r['ownership'] for r in rec.values())),
   'module_sizes':dict(collections.Counter(r['module'] for r in rec.values())),
   'evidence_tiers':dict(collections.Counter(r['evidence'][0].split(':')[0] for r in rec.values() if r['ownership']=='product')),
   'in_build':sum(1 for r in rec.values() if r['in_build']),
 },
 'net':{
   'records':len(netrec),
   'ownership':dict(collections.Counter(r['ownership'] for r in netrec.values())),
   'module_sizes':dict(collections.Counter(r['module'] for r in netrec.values())),
 },
}
doc={
 'schema':1,
 'generated':'2026-07-26',
 'generator':'recon/analysis/production_refactor_plan.md Sec 3 rule; script archived in the plan',
 'purpose':'Advisory file->subsystem mapping for the production refactor. NOT a proof artifact. '
           'Every row must be confirmed by the executing pass; rows with evidence tier L4/L5 are '
           'explicitly unconfirmed.',
 'caveats':[
   'application_sources.json is stale against adoption_manifest.json (recorded input sha 5122cb4d, '
   'live sha differs); 55 addresses now manifest-excluded are still included_g1_application in the '
   'view. Regenerate with tools/build_app_source_view.py before trusting the product count.',
   'recon/catalogs/refgraph_app.json.gz is a 2026-07-16 snapshot: 2,391 nodes for 2,534 catalogued '
   'functions; 52 product functions have no node and 156 have zero recorded callers (indirect/'
   'dispatch-table entry points). L4 assignments for those are unsupported.',
   'The recon/modules/*.h public-API lists are the refgraph "api" set, i.e. functions the module '
   'CALLS as well as functions it owns. L2 is therefore overridden by L3 when the two disagree; '
   '29 app functions took that path.',
   'Net has no topic axis: recon/ownership/net_function_ownership.json reports 452/452 sdk_library '
   'and zero product-owned net functions needing readable C. Net grouping is ownership-only.',
 ],
 'inputs':{p:sha(B+p) for p in [
   'recon/application/application_sources.json',
   'recon/ownership/adoption_manifest.json',
   'recon/catalogs/refgraph_app.json.gz',
   'recon/catalogs/function_names_app.json',
   'recon/catalogs/function_names_net.json',
   'recon/generated/app_retained_sources.cmake',
   'recon/generated/net_retained_sources.cmake',
   'recon/application/net/CMakeLists.txt',
 ]},
 'directory_map':DIR,
 'summary':summary,
 'app':[rec[a] for a in sorted(rec)],
 'net':[netrec[k] for k in sorted(netrec)],
}
json.dump(doc,open(OUT,'w'),indent=1)
print(json.dumps(summary,indent=1))
print('wrote',OUT, os.path.getsize(OUT),'bytes')
```

### A.1 Reproducing the cohesion measurement

The per-module intra-call fractions in §2.1 come from the same inputs: for every
product function `a` with module `m(a)`, count edges `a -> b` where `b` is also
assigned, excluding any edge with `common` at either end; cohesion is
`|{a->b : m(b)==m(a)}| / |{a->b}|`. The `common` exclusion is load-bearing —
without it `debug_print`, `get_device_info` and `memset_bytes` contribute ~400
spurious cross-module edges and every module looks incoherent.
