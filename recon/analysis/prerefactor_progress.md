# Pre-refactor batch application progress

Companion to `recon/analysis/prerefactor_plan.md` (which is analysis only). This
file records batches that were actually **applied** to the corpus, in the order
§3 of the plan prescribes, with the measurement that gated each one.

**Nothing here is committed.** No `tools/` logic, no `armemul`, no build file,
no linker script and nothing under `recon/emulator/**` was modified by this
pass. The only new files are three headers under `recon/headers/`.

---

## Pre-refactor batch G7-B1 + G6-B4

Applied in plan order: **G7-B1** (header extraction of duplicated definitions,
clusters C03/C04/C05) then **G6-B4** (evidence-backed hardware-register names).
Both are **class T** in the taxonomy of `production_refactor_plan.md`:
provably codegen-neutral, gated on a byte-identical `zephyr.bin`.

### 0. Headline result

| | app | net |
|---|---|---|
| `zephyr.bin` vs pre-batch baseline | **byte-identical (`cmp` silent)** | **byte-identical (`cmp` silent)** |
| FLASH | 952,316 B / 982,528 B = **96.93 %** — **Δ 0 B** | 225,581 B / 226 KB = **97.48 %** — **Δ 0 B** |
| RAM | 253,765 B / 440 KB = 56.32 % — **Δ 0 B** | 63,380 B / 64 KB = 96.71 % — **Δ 0 B** |
| `nm -u` undefined | **0** | **0** |
| duplicate global definitions | **0** | **0** |
| ELF symbol table vs baseline | **identical, all 9,139 entries** (address, type, name) | identical |
| compiler warnings | 1,798 → **1,798** (no new diagnostics) | 1,066 → **1,066** |

Both batches were budgeted at 0 B and both landed at exactly 0 B. Because the
image is byte-identical the behavioural oracle is unchanged **by construction**;
it was nevertheless re-run end-to-end as confirmation (§5).

Baselines were built first, from the working tree as found, and the resulting
`zephyr.bin` of each core kept as the comparison artifact:

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-b0-app
recon/application/build_cohesive.sh net /private/tmp/g1-b0-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

The baseline reproduced `production_refactor_plan.md` §1.3 exactly (952,316 /
253,765 app, 225,581 / 63,380 net), so the plan's flash figures are current.

---

### 1. G7-B1 — header extraction

#### 1.1 The gate the plan demands, and what it found

The plan's gate is *"diff every copy before collapsing; if any copy differs it
is a separate function and must keep its own name."* That diff was run over all
nine trees and it **fails for the majority of copies**. This is the most
important finding of the batch.

**743 helper definitions** were extracted and normalised (comments stripped,
whitespace collapsed). Raw grouping gives **49 distinct (name, body) variants**.
Applying a *sound* type-equivalence normalisation — on arm-zephyr-eabi `unsigned`,
`unsigned int`, `uint`, `u32` and `uint32_t` all denote one type, `int`/`i32`/
`int32_t` likewise, and `&1u` is `&1` in unsigned context, so substituting one
spelling for another cannot change codegen — still leaves **43 distinct
families**, and only **10 of the 22 helper names have a single family**.

The disagreements are load-bearing, not cosmetic:

| divergence | copies | why it must not be collapsed |
|---|---:|---|
| `getBasePriority(void){return 0;}` | 6 | a **stub**, not the CMSIS read. Collapsing injects real `MRS BASEPRI` into functions that do not have it in the shipped image. |
| `setBasePriority(int p){(void)p;}` | 6 | same, for `MSR BASEPRI`. |
| `isCurrentModePrivileged(void){return 1;}` | 6 | same, for `MRS CONTROL`. |
| `InstructionSynchronizationBarrier` via `__atomic_signal_fence(__ATOMIC_SEQ_CST)` | 6 | compiler-only barrier, **emits no instruction**; the dominant form emits a real `isb`. |
| `InstructionSynchronizationBarrier` with an empty body | 3 | as above. |
| `static inline __attribute__((always_inline))` spellings of `isb`, `isb_`, `rd_basepri`, `wr_basepri`, `wr_basepri_max`, `getBasePriority`, `setBasePriority`, `isCurrentModePrivileged`, `readIPSR` | 5+5+5+3+3+3 | exactly the `-Os` hazard the plan names: `always_inline` vs `inline` changes whether a call is emitted, which changes the call trace the parity harness compares. |
| `CARRY4` via `__builtin_add_overflow` | 6 | semantically equal but **not assumed** codegen-equal. |
| `SBORROW4` via `__builtin_sub_overflow`, and a `static`-not-`inline` variant | 3 + 3 | as above. |
| `getBasePriority` / `rd_basepri` returning `int` vs `unsigned` | 12 + 5 | a real **return-type** change visible to every consumer. |

So a single shared header cannot host these names for the whole corpus without
changing generated code. The batch was therefore scoped to the provable subset.

#### 1.2 What was created

Three new headers in `recon/headers/` (per plan §3.2 rule 6 — never in
`recon/symbols/`, which is generated):

| header | hosts | contents |
|---|---:|---|
| `g1_cmsis_shim.h` | 14 helpers | the dominant CMSIS-wrapper family (C03) |
| `g1_ghidra_ops.h` | 7 helpers | the dominant `CARRY`/`SCARRY`/`SBORROW` family (C04) |
| `g1_nrf_regs.h` | 34 macros | G6-B4, see §2 |

`readIPSR` is **deliberately absent** from `g1_cmsis_shim.h`: its two families
are an exact 3/3 split between the `always_inline` and the plain spelling, so
there is no dominant variant to host. Each header carries its codegen contract
and the list of families it must not absorb, in-file.

**Include-path finding.** One include spelling resolves on every path that
matters, so the corpus needs no build-file change and no `tools/` change:

```c
#include "../../headers/g1_cmsis_shim.h"
```

* from `recon/symbolized/{app,net}/*.c` and `recon/{app,net}/src/*.c` it resolves
  by GCC's own-directory rule;
* from the **parity harness**, which copies the source into a fresh
  `tempfile.mkdtemp()` TU and so has no own-directory, it resolves through
  `tools/parity/recon.py`'s existing `-I recon/app/src` / `-I recon/net/src`,
  because GCC concatenates the `-I` directory with the quoted path:
  `recon/app/src/../../headers/…` **is** `recon/headers/…`. Verified by compiling
  a probe TU with the harness's exact flag set.

This matters because `recon/headers` is on the **app** build's include path but
**not** the net build's, and `tools/` may not be edited. The relative spelling
sidesteps both constraints.

**Per-tree depth.** The relative path is *not* uniform across trees, and per plan
§3.2 rule 4 it must not be copied verbatim between them. `recon/{app,net}/src`,
`recon/verified/src`, `recon/symbolized/{app,net}` and `recon/net/named` all sit
three levels below the repo root, so `../../headers/…` is correct; `recon/named`
needs `../headers/…` and `recon/readable_sources/app/{g1,library}` need
`../../../headers/…`. All **309** inserted includes were verified to resolve from
their own file's directory (`0` unresolved).

#### 1.3 C05 — the absolute host-path `#include` (the portability defect)

`#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"`
→ `#include <cmsis_gcc.h>`. `CMSIS/Core/Include` is already on the include path
of **both** cores' builds and of the parity harness, so this resolves the same
file a portable way.

**354 files in 9 trees**, every occurrence outside the symlink view:

| tree | files |
|---|---:|
| `recon/app/src` | 45 |
| `recon/verified/src` | 45 |
| `recon/symbolized/app` | 45 |
| `recon/named` | 45 |
| `recon/net/src` | 43 |
| `recon/symbolized/net` | 43 |
| `recon/net/named` | 43 |
| `recon/readable_sources/app/library` | 30 |
| `recon/readable_sources/app/g1` | 15 |
| **total** | **354** |

`recon/application/src` is a **symlink view** into `recon/named` (1,155 symlinks
+ 1 real file); it was skipped so the substitution is not applied twice, and it
inherits the change through the symlinks. `recon/app/src_sym` and
`recon/verified/src_sym` contained **zero** occurrences, so the dead-snapshot
question (plan §3.2 rule 3) does not arise for this batch.

Pre-flight proof: 8 representative TUs across both cores compiled before and
after; after `--strip-debug --remove-section=.comment` the objects are
**byte-identical** (only DWARF, which records the source path, differed).

#### 1.4 C03/C04 — collapsing the duplicated definitions

Applied to the two **build** trees, which is where the change reaches the image
and where the `cmp` gate is therefore meaningful:

| tree | files converted | duplicate definitions removed |
|---|---:|---:|
| `recon/symbolized/app` | 13 | 82 |
| `recon/symbolized/net` | 12 | 47 |
| **total** | **25** | **129** |

Converted app files: `SettingStoreHandler.c`, `ble_conn_set_state.c`,
`check_work_mode.c`, `cjson_print_value.c`, `hci_vs_init.c`,
`k_queue_insert_and_wake.c`, `l2cap_recv.c`, `net_buf_slist_get.c`,
`poll_signal_event_locked.c`, `resource_manger_get.c`, `uarte_nrfx_isr.c`,
`ui_DashBoard_task.c`, `z_work_submit_to_queue.c`.

Converted net files: `FUN_01008940.c`, `FUN_0101ad38.c`, `FUN_010237b0.c`,
`FUN_0102cd8c.c`, `FUN_0102cf00.c`, `FUN_01033660.c`, `FUN_01035d18.c`,
`FUN_01036660.c`, `clear_event_registrations.c`, `onoff_request.c`,
`register_events.c`, `z_impl_k_msgq_put.c`.

A file is converted only if **every** helper it defines is type-canonically
identical to the header's definition; otherwise the whole file is left alone.
The removed block is replaced by the `#include` at the exact position of the
first removed definition, so declaration order is preserved.

Per-TU proof, before the full link: for each converted file that is a retained
TU, the pre-edit and post-edit objects were compiled with the build's own
recorded command and compared after `--strip-debug`: **13 of 13 byte-identical,
0 differing.** The other 12 files are not retained in either build (they are in
the 532-file displacement set), so they cannot affect the image at all.

#### 1.5 Deferred from G7-B1, with the reason

| deferred | count | reason |
|---|---:|---|
| `recon/symbolized/app` files with a divergent copy | 2 — `k_msgq_get.c`, `k_msgq_put.c` | `rd_basepri` / `wr_basepri` / `wr_basepri_max` / `isb` are the `always_inline` family; collapsing changes `-Os` inlining and hence the harness's call trace |
| `recon/symbolized/net` files with a divergent copy | 11 — `FUN_01020054.c`, `FUN_01023ea8.c`, `FUN_01036410.c`, `FUN_01036774.c`, `FUN_0103721c.c`, `FUN_010375b8.c`, `FUN_010378c4.c`, `FUN_01037e10.c`, `FUN_0103814c.c`, `z_impl_k_poll_signal_raise.c`, `z_impl_k_timer_start.c` | stub family, `__atomic_signal_fence` barrier, `__builtin_*_overflow`, differing return types, and `readIPSR` (no dominant variant) |
| C03/C04 in the **canonical** trees (`recon/{app,net}/src`) and their `verified`/`named`/`readable` mirrors | — | see below |
| the 20 absolute-path `#include`s of `liblc3` private headers (`bits.h`, `sns.h`, `spec.h`, `tables.h`, 5 each) | 20 | `modules/lib/liblc3/src` is **not** on any TU's include path — only `liblc3/include` is, and the private `src` dir is added to the `liblc3` target, not to `app`. Converting them to `<bits.h>` would not compile. Fixing this needs an include-directory addition to `recon/application/app/CMakeLists.txt`, which plan §4 puts out of scope. |
| 17 documentation artifacts still quoting the absolute CMSIS path | 17 | `recon/naming_bundles/FUN_*.md` (16 historical naming snapshots) and `recon/ownership/code_dedupe_plan.json` (the authority record of the defect). Not compiled; changing the plan JSON would destroy the evidence it exists to carry. |

**Why C03/C04 was not applied to the canonical trees.** It is *technically*
possible — §1.2 shows the include resolves through the harness's `-I` flags — but
it converts a compile-only change into a **re-proof event**: plan §3.1 requires
`recon_kit.prove` + `cfg_verify` on every canonical file touched, and the
duplication in the canonical corpus is partly *structural*, since the harness
compiles each file as a standalone TU. Doing it correctly is a separate,
separately-gated batch. It is recorded here as the immediate follow-up, together
with the working include recipe, rather than half-done.

---

### 2. G6-B4 — hardware register names

#### 2.1 Evidence check first

All **58** candidates were re-verified against the SDK headers shipped with
NCS 2.5.1, per-core, before any edit:

* app candidates against `modules/hal/nordic/nrfx/mdk/nrf5340_application.h`
  (141 `NRF_*_BASE` macros parsed),
* net candidates against `nrf5340_network.h` (41 macros),
* the 9 SCS addresses against the CMSIS Cortex-M33 System Control Space map.

**58 / 58 verify; 0 unverified.** (A first pass reported 18 mismatches; that was
a bug in the check itself — a single dict merged both cores' headers, and the
app value won for every shared macro name. Re-running per-core cleared all 18.
Worth recording because it is the same trap the header below guards against.)

#### 2.2 Why the names carry a `G1_` prefix

The two cores' MDK headers give the **same macro name different values** —
`NRF_IPC_NS_BASE` is `0x4002a000` in `nrf5340_application.h` but `0x41012000` in
`nrf5340_network.h`; `NRF_P0_NS_BASE` is `0x40842500` vs `0x418c0500`. A shared
header reusing the SDK spelling would be wrong for one core and would shadow the
real SDK macro wherever the MDK header is genuinely on the include path.
`recon/headers/g1_nrf_regs.h` therefore defines **`G1_`-prefixed** macros
(9 SCS + 9 app bases + 16 net bases = 34), and asserts at generation time that
the app and net sections share no macro name.

Each macro expands to the **same token** the source used, so the substitution is
codegen-neutral by construction rather than by optimiser luck. A base+offset
site expands to `(G1_NRF_X_BASE + 0xoff)`, whose type and value are identical to
the folded literal on this ABI (every base is `< INT_MAX` and so `int`, as is
every folded sum; the SCS addresses are `> INT_MAX` and are substituted whole).

#### 2.3 What was substituted

Comment bodies and string literals are masked before matching, so a provenance
comment such as `/* raw backmap: 0xe000ed00 + 0x28 */` is never rewritten.

| tree | files | — |
|---|---:|---|
| `recon/net/src` | 75 | canonical net |
| `recon/net/named` | 75 | |
| `recon/symbolized/net` | 44 | **build tree** |
| `recon/app/src` | 20 | canonical app |
| `recon/verified/src` | 20 | |
| `recon/named` | 20 | |
| `recon/symbolized/app` | 14 | **build tree** |
| `recon/readable_sources/app/library` | 11 | |
| `recon/readable_sources/app/g1` | 3 | |
| **total** | **282 files** | **662 sites** |

All 34 macros are used; the heaviest are `G1_NRF_RADIO_NS_BASE` (80 sites),
`G1_NRF_DPPIC_NS_BASE` and `G1_NRF_TIMER0_NS_BASE` (45 each),
`G1_NRF_PDM0_S_BASE` (42), `(G1_NRF_GPIOTE0_S_BASE + 0x510)` (40),
`G1_SCB_CPUID` (29), `G1_NVIC_ISER0` (27).

The plan predicted 232 reference sites over the canonical trees; the live scan
finds 662 over nine trees (241 canonical). The plan's own snapshot caveat
applies — its numeric-literal census recorded only the canonical trees.

#### 2.4 A real defect the gate caught: `UINT32_C()` token pasting

The first application broke three net TUs:

```
error: pasting ")" and "U" does not give a valid preprocessing token
   return UINT32_C((G1_NRF_TIMER0_NS_BASE + 0x140)) + channel * 4;
```

`UINT32_C(c)` is `c ## U`. A literal inside it is **token-pasted** with a `U`
suffix, so substituting a parenthesised expression is a hard preprocessing error
and substituting a bare macro name pastes onto the *name*. The substituter now
refuses any site whose enclosing context is a `U?INT{8,16,32,64,MAX,PTR}_C(`
macro argument. **50 sites across 29 files stay as raw hex** for this reason —
listed in the batch record; the largest groups are `recon/{net/src,net/named,
symbolized/net}/FUN_010250d0.c` (3 each), `.../FUN_010231c8.c` and
`recon/net/named/sdc_conn_window_admit.c` (3 each), and
`recon/{app/src,verified/src,named,symbolized/app,readable_sources/app/library}`
`FUN_000507d4.c` / `z_arm_fault.c` (1 each).

This is exactly the class the plan warns scripted edits produce, and it was
caught by the per-object gate rather than by the link.

#### 2.5 Per-TU proof

After the exclusion, every touched file that is a retained TU was compiled
before and after with the build's own recorded command and compared after
`--strip-debug --remove-section=.comment`:

**40 of 40 retained TUs byte-identical; 0 differing; 0 compile failures.**
242 of the 282 touched files are not retained TUs and so cannot affect the image.

#### 2.6 Deferred from G6-B4

| deferred | count | reason |
|---|---:|---|
| sites inside `UINT*_C()` | 50 in 29 files | token pasting, §2.4. Renaming them needs the surrounding `UINT32_C` removed, which is a source-shape change, not a literal substitution. |
| the other 2,633 G6 candidates | — | out of this batch by plan order (B1/B2/B3 strings, B5 errno, B6 float bits, G6-A ambiguous, G6-X keep-symbolic) |

Consistent with the plan, G6-B4 retires **0** linker pins and withdraws **0**
rodata objects, so the §1.6 flash hazard does not apply to it.

---

### 3. Constraint compliance

| constraint | status |
|---|---|
| flash/RAM must not move | **held — 0 B on both cores**, `cmp` byte-identical |
| `recon/{app,net}/src` stay flat and address-keyed | **held** — no file moved, added or removed in any tree |
| no renames | **held** — no function, file or symbol renamed; `LAST_DIRECT_TARGET_MAP` identity checks cannot silently drop out |
| `rodata_*` object filenames untouched | **held** — no `recon/data/**`, `recon/application/rodata/**` or `g1_*_rodata*.c` file touched |
| keep-symbolic absolute | **held** — the batch inlines no address at all; G6-B4 only *names* fixed peripheral/architectural registers, and `g1_nrf_regs.h` states the exclusion explicitly. No `ADDR_*_THUMB`, ptr_table/ptr_record, device pointer, RAM/`.text` address or section boundary was touched |
| no `tools/` logic edited | **held** (see §6 for a concurrent-modification observation) |
| no build files, linker scripts, `recon/emulator/**` or `armemul` edited | **held** |
| nothing committed | **held** |

---

### 4. Gate ladder

| gate | result |
|---|---|
| `gen_retained_sources.py --check` | **clean** — "retained source lists are current", before and after both batches |
| app build | **exit 0**, 3,068 targets |
| net build (`-DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON`) | **exit 0** |
| `nm -u` undefined | **0 / 0** |
| duplicate global definitions | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` / weak-symbol hacks | **0 occurrences** in either build log |
| **class-T `cmp` of `zephyr.bin`** | **byte-identical, both cores, after G7-B1 and again after G6-B4** |
| ELF symbol table | **identical to baseline**, all 9,139 entries |
| compiler warnings | **unchanged** (1,798 app / 1,066 net) |
| `check_ram_pin_collisions.py` app | **0 raw-literal pins inside a live object, 0 escaped binds** (624 bound pins OK) |
| `check_ram_pin_collisions.py --core net` | **0 / 0** (170 bound pins OK) |
| `check_net_raw_literals.py` | **0 / 0** — 983 TUs preprocessed, 0 failures, 0 distinct raw literals |
| `check_thread_create_stack_args.py` | **10/10 PASS** |
| `verify_net_stock_data_window.py` | **PROVEN** — 256/349 words equal, 93 differing are all flash pointers, **0 differing for any other reason**, 0 non-stock input sections |
| `cfg_verify` on every canonical function G6-B4 touched | **95/95 PASS** (20 app + 75 net) |
| new-header includes resolving from their own directory | **309/309**, 0 unresolved |

---

### 5. Behavioural oracle

`zephyr.bin` is byte-identical and the ELF symbol table is identical, so the
oracle is unchanged **by construction**. It was re-run once end-to-end as
confirmation, on the ELFs actually produced by this batch
(`/private/tmp/g1-b4-app`, `/private/tmp/g1-b4-net`), following the *Regenerate*
recipe of `our_boot_bringup.md` §37 — `mkfifo` stdin pipe, `G1_HOOKS=0`,
`$rtinfo_pc=0x00015b8c` (confirmed to be `runtime_info_sync` at exactly that
address in the ELF booted), `G1_CTX_FE8=0x20040F38`, `G1_CTX_105A=0x20040FAA`,
`G1_SCREEN_ID=0x20040025`.

| stimulus / phase | expected sha256 | measured sha256 | lit px | bbox | verdict |
|---|---|---|---|---|---|
| DASHBOARD `p2_render` (`G1_ATT_WRITE=""`) | `19b1f24a…` | `19b1f24a09f97a8d85f1572ac865c8fc61fe6d542af18247a5bcceeb7651b513` | **2,923 == 2,923** | (78,211)–(564,338) | **PASS** |
| DASHBOARD `p1_boot` | `0c5cc90b…` | `0c5cc90b079d0d9c1ded1376357d23a9782a704a83e01731f50ccd162e246492` | **0 == 0** | — | **PASS** |
| NAVIGATION `p2_render` (`G1_ATT_WRITE` unset) | `b26c73b3…` | `b26c73b37d441fc8a6732c02e6d889a719677ec4c9ad2adc2d48f28deedb8131` | **1,098 == 1,098** | (34,266)–(497,287) | **PASS** |
| NAVIGATION `p1_boot` | `1d617c65…` | `1d617c65a688f10eefe139741b680164f09adcd960b18c3ec9ad1f0fb193b953` | **656 == 656** | (178,267)–(449,287) | **PASS** |

**All four framebuffers match §37.6/§37.7 exactly**, on sha256, lit-pixel count
and bounding box on all four edges. The raws were additionally `cmp`-ed against
the committed goldens, not only compared by hash:

```
cmp <dash p2_render>.raw recon/emulator/reports/golden_framebuffer_dashboard_p2_render.raw  -> no difference
cmp <nav  p2_render>.raw recon/emulator/reports/golden_framebuffer_p2_render.raw            -> no difference
cmp <nav  p1_boot>.raw   recon/emulator/reports/golden_framebuffer_p1_boot.raw              -> no difference
```

Supporting counters also held: dashboard `spim_a` `p1_boot` stream sha
`f91505ab8dc0dd27…` (the §37.7 D-3 PASS value), `spim_b` 0 transactions both
phases, `pdm0` 2 accesses, `gpiote0` 25 / `gpiote1` 0, `saadc` 95 — every one
identical to iteration 37, including the known-failing `saadc` value, i.e. the
batch changed nothing in either direction.

**No regression. The acceptance bar is held.**

---

### 6. Observation: `tools/` changed underneath this session

`tools/cfg_verify.py` and `tools/parity/emu.py` carry **uncommitted
modifications that this pass did not make** (+480 lines, adding hard-float
`s0..s15` argument-coverage derivation — the follow-up named in
`our_boot_bringup.md` §37.13). Their mtimes (17:40:50 and 17:42:27) fall inside
this session's window and *after* its last source edit (17:37:09), and they were
not present in the `git status` taken at session start.

This is **not** a side effect of running the verifier: neither
`tools/cfg_verify.py` nor `tools/parity/emu.py` contains a single write-mode
`open()`, so executing them cannot rewrite them. The edits came from another
writer.

Recorded rather than acted on: the brief forbids editing `tools/`, and this pass
did not. The consequence to note is that the `cfg_verify` sweep of §7 ran
against a verifier that was itself being modified concurrently, so its results
should be read as indicative, not as a frozen measurement.

Separately, `HEAD` moved from `6aa09be0` (the commit named in this session's
starting snapshot) to `f334bd84 G4 iter-37`, which committed the
`recon/emulator/reports/**` and `recon/application/src/lsm6dso_init_chip.c`
changes that the snapshot showed as dirty. The baseline build was taken after
that and reproduced `production_refactor_plan.md` §1.3 byte-for-byte
(952,316 / 253,765 app, 225,581 / 63,380 net), so the tree this batch started
from was the intended one.

---

### 7. `cfg_verify` on the canonical functions G6-B4 touched

G7-B1 touched no canonical file, so it owes no re-proof. G6-B4 touched **20
canonical app + 75 canonical net** functions, and the plan asks for `cfg_verify`
on those "because the substitution is done by a script and scripts mis-edit" —
which §2.4 vindicates.

**Result: 95 / 95 PASS — 20 app + 75 net, zero failures, zero errors.**
Case coverage was non-trivial on many: e.g. `FUN_0005f654` `cases=12`,
`FUN_000635a4` `cases=3 sel={0:[0,1,2]}`, `FUN_00061310` `cases=4
sel={3:[0,1]}`.

Note that the strongest evidence for these 95 functions is not the harness but
the per-object comparison of §2.5 plus the byte-identical image: the substituted
token is the same token, so the compiler's output is unchanged, which the
`--strip-debug` object compare and the two `cmp`s both confirm directly.
`our_boot_bringup.md` §37.13 independently records that `cfg_verify` can return
the same `PASS` on a broken and a fixed source when the arguments arrive in VFP
registers, so a green sweep here is corroboration, not proof.

---

### 8. Trees reconciled

| tree | C05 | C03/C04 | G6-B4 |
|---|---|---|---|
| `recon/app/src` (canonical app) | 45 | deferred §1.5 | 20 |
| `recon/verified/src` | 45 | deferred | 20 |
| `recon/symbolized/app` (**build**) | 45 | 13 | 14 |
| `recon/named` | 45 | deferred | 20 |
| `recon/readable_sources/app/g1` | 15 | deferred | 3 |
| `recon/readable_sources/app/library` | 30 | deferred | 11 |
| `recon/net/src` (canonical net) | 43 | deferred | 75 |
| `recon/symbolized/net` (**build**) | 43 | 12 | 44 |
| `recon/net/named` | 43 | deferred | 75 |
| `recon/application/src` | symlink view — inherits from `recon/named`, never edited directly | | |
| `recon/app/src_sym`, `recon/verified/src_sym` | **0 occurrences of anything in either batch** | | |

Pre-existing drift **not** touched by this pass, and deliberately so: the 37
symbolized app files edited downstream of `recon/named`, the 3 canonical files
missing from `recon/verified/src` (`FUN_0007c86c.c`, `aging_mode_thread.c`,
`master_display_thread.c`), the 1 orphan, and the 29 + 31 missing counterparts.
The plan lists regenerating over the 37 unpushed hand edits as a top risk; no
generator was run, and every edit here was applied surgically per file, so no
hand edit was overwritten. `symbolize.py` and `gen_linker.py` remain unrunnable
(dead scratchpad path, missing `symbol_map.json`) and were not needed.
