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

## Pre-refactor batches G6-B3 then G6-B1 — APPLIED (with one half reverted)

Steps 3 and 4 of `prerefactor_plan.md` §3: **G6-B3** (string heads the plan
classified as having no canonical-tree site) then **G6-B1** (log-argument string
literals). Neither is class T — withdrawing the backing object necessarily
changes the image — so the gate is the flash/RAM delta plus the behavioural
oracle, not a byte-identical `zephyr.bin`.

**Headline honesty note, stated first because it changes what the batch is.**
G6-B1's canonical-tree half was applied, **measured to break the parity proof,
and reverted**. `tools/cfg_verify.py` compares the ordered call trace *including
the recorded argument values*, and a logging call's format-string pointer is one
of those arguments. Replacing the original-image `.rodata` address with a
string-literal pointer therefore turns a PASSing canonical function into a
FAILing one. This was measured, not assumed (§5). The image half of G6-B1 — the
part that retires the pins and shrinks flash — is applied and gated; the
canonical corpus is back to byte-for-byte what it was.

### 0. Headline result

| | G6-B3 | G6-B1 | cumulative |
|---|---:|---:|---:|
| candidates applied | **796** of 857 | **548** of 554 | **1,344** |
| reference sites inlined (as delivered) | **2,842** | **5,938** | **8,780** |
| numeric `PROVIDE` pins retired | **796** | **548** | **1,344** |
| rodata objects withdrawn | 796 (27,318 B declared) | 548 (19,650 B declared) | 1,344 (**46,968 B**) |
| app FLASH | 952,332 → **950,220 B** (**−2,112 B**) | 950,220 → **948,764 B** (**−1,456 B**) | **−3,568 B** |
| app `.text` | 947,364 → 945,260 | 945,260 → 943,804 | −3,560 B |
| app `.data` / `.bss` | 4,951 / 249,251 — **Δ 0** | **Δ 0** | **Δ 0** |
| app RAM | 253,765 B — **Δ 0** | **Δ 0** | **Δ 0** |
| net FLASH / RAM | untouched | untouched | **225,581 / 63,380 — Δ 0, `zephyr.bin` byte-identical to baseline** |

**Both batches shrink the image; neither moves one byte of RAM.** App went from
96.93 % to **96.56 %** of its 982,528 B partition — headroom 30,196 → **33,764 B**.
`recon/symbols/g1_app_globals.ld` went from **2,593 `PROVIDE(rodata_…)` lines
(2,392 numeric)** to **1,249 (1,046 numeric)**: **56 % of the numeric pin
population retired**, and every one of them converted from a silent
original-image-address resurrection hazard (`rodata_decode_report.md` §10) into
a link error.

RAM **layout** is identical too, not just the total: `nm -n` over every
`0x2…`-addressed symbol diffs to **0 lines** against the baseline ELF in both
batch builds. That is what keeps the oracle's probe addresses
(`G1_CTX_FE8=0x20040F38`, `G1_CTX_105A=0x20040FAA`, `G1_SCREEN_ID=0x20040025`,
`$rtinfo_pc=0x00015b8c`) valid for the ELFs actually booted.

Baseline, built first from the working tree as found:

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-b0-app
recon/application/build_cohesive.sh net /private/tmp/g1-b0-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

It measured **952,332 / 253,765** app and **225,581 / 63,380** net — 16 B of app
flash above the 952,316 the previous batch recorded, which is the concurrent
sensor-parity work, not this pass.

**Attribution boundary.** A final verification build of the tree as left
measures **948,828 B**, i.e. **+64 B** above this pass's 948,764. That 64 B is
*not* this pass: while these batches ran, the concurrent P4 bring-up wired
`recon/data/rodata_0x88570.c` (the SAADC `struct adc_channel_cfg`, iteration 38)
into `recon/application/app/CMakeLists.txt` and
`recon/generated/app_verified_data_sources.cmake` — 50,583 → 50,647 byte-exact
data input bytes, exactly 64. The figures above are measured on
`/private/tmp/g1-b3-app` and `/private/tmp/g1-b1-app`, built before that landed.

---

### 1. The transaction, and three live corrections to the plan

Every candidate was applied as the **single transaction** `prerefactor_plan.md`
§3.2 rule 5 demands, plus a fourth part the rule does not name but the link
requires:

1. every reference site becomes a C string literal,
2. the backing object is deleted from `g1_app_string_rodata.c` /
   `recon/application/rodata/g1_app_rodata_0N.c`,
3. the `PROVIDE(rodata_X = 0x…)` line is deleted from `g1_app_globals.ld`,
4. **the now-dangling `extern const unsigned char rodata_X[];` declaration is
   deleted from `recon/symbols/g1_app_symbols.h` and
   `recon/readable_sources/app/include/g1_app_symbols.h`** (1,344 and 1,313).

Nothing was renamed and no `rodata_*` object **filename** was touched — only
object *bodies*, each an independent C declaration in its own
`.rodata.rodata_<hex>` section.

#### 1.1 Correction — G6-B3's defining claim is false live

The plan defines G6-B3 as *"string heads with no canonical-tree site …
**no canonical body changes, so no parity re-proof is owed**"*. Re-derived live
(comments and string bodies masked, every hex spelling accepted):

> **All 857 G6-B3 addresses have canonical-tree sites — 1,527 of them.**

The plan's scan missed them because the canonical trees spell the reference as a
raw hex integer, not as `rodata_<hex>`, and its canonical pass evidently matched
only the short spelling. The two app parity trees have themselves diverged in
*form*: `recon/app/src/FUN_000536b8.c` carries
`printk(0x00099cbdu, 0x000f2eb8u, …)` while `recon/verified/src/FUN_000536b8.c`
still carries the raw Ghidra `FUN_0007e2fa(0x99cbd,0xf2eb8,…)`.

It does not change what G6-B3 must do to the image — the canonical trees are
never linked, only `recon/symbolized/{app,net}` is compiled — but the batch's
"no parity obligation" property holds **only because G6-B3 was deliberately
applied to the symbol-spelling trees and left every canonical raw-hex site
alone.** Those 1,527 sites are deferred, not silently claimed.

#### 1.2 Correction — `.inc` files are compiled sources, and the first link proved it

The first G6-B3 link failed:

```
ld.bfd: app/libapp.a(ble_process_put_req.c.obj): in function `ble_put_op9_dispatch':
  recon/symbolized/app/ble_process_put_ops_09_10.inc:1419: undefined reference to `rodata_9b8fd'
```

`recon/symbolized/app/*.inc` and `recon/readable_sources/app/include/*.inc`
(20 files) are `#include`d into real translation units and contain reference
sites, but every literal scan in this repository — and the first version of this
batch's substituter — enumerates `*.c` and `*.h` only. Two sites in
`ble_process_put_ops_01_08.inc` were missed.

Worth recording twice over. The failure mode is **exactly** what
`rodata_decode_report.md` §10 asks for: deleting the pin converted a silent
original-image-address corruption into a hard link error. And **any future G6/G7
batch must enumerate `.inc`**, or it will withdraw an object that is still
referenced.

#### 1.3 Correction — the harness DOES compare call arguments (see §5)

`prerefactor_plan.md` §2.4 says the harness is "blind to dropped register/stack
arguments", and §1.3 promises G6-B1 is re-provable by re-running it. Measured,
the trace it compares contains the argument **values** of stubbed callees, so a
format-string pointer change is fully visible. G6-B1's canonical half is
therefore **not** re-provable, and was reverted.

---

### 2. G6-B3 — 796 of 857 candidates

#### 2.1 Evidence re-derived before any edit

Every candidate was re-verified against the shipped image through
`tools/extract.py` — never by naive VA arithmetic — before it was allowed in:

| check | result (app + net, 857 candidates) |
|---|---|
| the emitted object's bytes equal `app_update.bin` at the pin VA | **857 / 857 match, 0 differ** |
| the byte *before* the VA is NUL, so the VA is a string **head** | **857 / 857** |
| the object is **exactly** one NUL-terminated string (`len == strlen+1`) | 835 pass, **22 fail — deferred** |
| the object is **> 4 B** (the §10 stub hazard) | **857 / 857 — zero short objects** |

**The §10 stub hazard is not live in G6-B3 or G6-B1.** The plan's 60 app + 4 net
`short_object_review` candidates are all in **G6-A**, not in either batch here.
Nothing was inlined against an object of ≤ 4 B; the same check on G6-B1 returned
554 / 554. No object had to be re-derived on suspicion, and none was trusted
without the byte compare above.

#### 2.2 What was substituted

Only the symbol spelling `((unsigned long)&rodata_X) /*=0x…*/` (plus the one
`(uint32_t)(uintptr_t)&rodata_X` variant in `recon/symbolized/net`) was
rewritten, to `((unsigned long)"…")`. The `(unsigned long)` cast is kept
deliberately: with C10's 384 distinct logging prototypes still in the corpus,
preserving the exact argument type at every site is the only way the
substitution cannot change how the argument is passed. The `/*=0x…*/`
provenance comment is **kept**, and the per-file `*  rodata_X  @ 0x…` header
lines are annotated `[INLINED -- G6 literal batch]` rather than deleted, so every
literal remains traceable to its original VA.

| tree | files with substitutions |
|---|---:|
| `recon/symbolized/app` (**build tree**) | 253 `.c` + 1 `.inc` |
| `recon/readable_sources/app/g1` | 193 |
| `recon/readable_sources/app/library` | 50 |
| `recon/readable_sources/app/include` | 1 `.inc` |
| `recon/named` | 7 |
| **total** | **505 files, 2,842 sites** |

`recon/application/src` is a symlink view into `recon/named` and inherits the
change; it was never written to directly. `recon/app/src_sym` and
`recon/verified/src_sym` hold no symbol-spelling site for this batch.

Non-ASCII strings (Chinese UI text, German/French localisations) are emitted as
**octal escapes**, with a `" "` concatenation break inserted whenever an octal
escape is followed by an octal digit, so the bytes are exact regardless of the
compiler's source/exec charset; `?` is escaped `\?` so no trigraph can form.
**17 non-ASCII strings were inlined and all 17 appear byte-for-byte in the
linked `zephyr.bin`** — e.g. `"Keine Daten ausgew\303\244hlt"` and
`"\345\276\256\344\277\241"` (微信).

#### 2.3 Deferred from G6-B3, with the reason

| deferred | count | reason |
|---|---:|---|
| **all 49 net candidates** | 49 | **There is no net rodata object to withdraw.** `nm` on the net ELF reports **0** `rodata_*` symbols defined as objects and **142 absolute**: `recon/application/rodata/g1_net_rodata_0*.c` is not wired into `recon/application/net/CMakeLists.txt`. The transaction has no "withdraw" half on net, so inlining is pure growth (≤ 692 B over the 26 candidates with a live reference) on a core the brief freezes. Inlining them *would* be a correctness fix — those references currently resolve to absolute original-image addresses — but it cannot be paid for. **Highest-value net follow-up: wire the net rodata objects first, and this becomes a shrinking transaction.** |
| string **pools** — one object spanning several strings | 11 app, 11 net | Withdrawing the object deletes bytes other pins address: `rodata_f304a` is a 147 B object whose first string is 28 B; `rodata_f2963` 226 B / 60 B; `rodata_a7fae` 105 B / 53 B; also `f3157`, `f327f`, `f3324`, `f4346`, `f540e`, `f0be7`, `f4eb1`, `f1105`. Splitting a pool is a region-shape change, not a literal inline. |
| `rodata_f541c` | 1 | No object of its own — it is the interior of the `rodata_f540e` pool (`"parent->frags"` is 14 B, `0xf540e + 14 = 0xf541c`) and its pin is already non-numeric. |
| the 1,527 **canonical-tree** raw-hex sites (§1.1) | 1,527 | Editing them makes G6-B3 a re-proof event, and §5 shows that re-proof cannot pass. Left as raw hex. |

---

### 3. G6-B1 — 548 of 554 candidates, image half applied

#### 3.1 The symbol half (this is what changes the image, and it stands)

Identical mechanism to G6-B3:

| tree | files with substitutions |
|---|---:|
| `recon/symbolized/app` (**build tree**) | 424 |
| `recon/readable_sources/app/g1` | 220 |
| `recon/readable_sources/app/library` | 202 |
| `recon/named` | 2 |
| **total** | **848 files, 3,977 sites** |

Deferred: the same **6 pool objects** — `rodata_f0661` (49 B object / 32 B
string), `f2201` (212/47), `f402a` (79/39), `f4b44` (154/29), `f52c0` (147/20),
`f6acd` (51/30). 548 of 554 applied, 548 pins retired.

#### 3.2 The canonical half — applied, measured, reverted

In `recon/{app,verified}/src`, `recon/named` and the two `_src_sym` snapshots the
site is a **raw hex integer**, which carries no evidence of what it is. A site
was rewritten only if the identifier owning the enclosing argument list is a
variadic logging entry point read out of the corpus, not assumed:
`FUN_0007e2fa(unsigned int, ...)` (its canonical body is `va_start` →
`FUN_0004b1cc(fmt,args)` → `va_end`), `FUN_00019c70` (the symbolizer's own header
records `debug_print <= FUN_00019c70 @ 0x00019c70`), `FUN_0007dda4(uintptr_t
format, ...)`, `DEBUG_PRINT`, `debug_print`, `log_message`, `printk`,
`assert_log`, `dmic_log`, `TASK_LOG`.

That produced 1,967 sites in 416 files of `recon/app/src`, 1,966 in 415 of
`recon/verified/src`, 1,961 in 414 of `recon/named`, and 241 in 115 files of each
`_src_sym`. **100 sites were refused and left as raw hex:**

| refused context | sites | reason |
|---|---:|---|
| `UINT32_C(…)` / `UINT64_C(…)` argument | **42** | `UINT32_C(c)` is `c ## U`; substituting there is a hard preprocessing error — the same defect G6-B4 hit (§2.4 above). The substituter now enforces the plan's "exclude token-pasting contexts" rule for strings as well as integers. |
| `<none>` — parenthesised expression, no callee | 33 | no evidence the value is consumed as a string |
| `<stmt>` — assignment / initialiser | 16 | as above; a stored pointer may be compared |
| `fatal` / `nrfx_assert_report` / `FUN_0007e2ec` / `assert_post_action` | 3 / 3 / 2 / 1 | not read off a prologue; each needs a per-site disassembly read. The `assert_post_action` site passes the *assert format* as argument 0, which is not what that function takes — suspicious, so left alone. |

**Then §5 happened, and all of `recon/app/src`, `recon/verified/src`,
`recon/app/src_sym` and `recon/verified/src_sym` were restored byte-for-byte.**
`grep -rl '((unsigned long)"'` returns **0 files** in each of those four trees,
and `git diff --stat` over them shows only the **18 files a concurrent agent
edited** (the `FUN_00024f40` / `FUN_00025528` / `FUN_00062644` / `FUN_0007c8fa` /
`FUN_0007c8e8` / `FUN_0007fe72` dropped-argument fixes), which the restore was
written to detect and skip: a file was reverted **only** if re-applying this
batch's substitution to the backup reproduced the current file exactly. 428
files failed that test and were left untouched.

`recon/named` **keeps** its 1,961 inlined sites (422 files). It is the *readable*
mirror — not compiled into either image, not read by `recon_kit`, `cfg_verify`,
`reverify` or `check_thread_create_stack_args`, all of which resolve
`recon/{app,net}/src` or `recon/verified/src`. Keeping it inlined is the owner's
readability goal at zero parity cost. Caveat for whoever runs it next:
`tools/apply_names.py` regenerates `recon/named` from the canonical tree and
would overwrite this.

---

### 4. Gate ladder

| gate | G6-B3 | G6-B1 | final tree |
|---|---|---|---|
| `gen_retained_sources.py --check` | **clean** | **clean** | **clean** |
| app build | **exit 0** | **exit 0** | **exit 0** |
| net build (`-DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON`) | untouched | untouched | **exit 0, `zephyr.bin` byte-identical to baseline** |
| `nm -u` undefined | **0** | **0** | **0 app / 0 net** |
| duplicate global definitions | **0** | **0** | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` | **0 occurrences** | **0** | **0 / 0** |
| weak-symbol or numeric-root hacks | none | none | none |
| compiler warnings | 1,798 → **1,798** | **1,798** | 1,798 app / 1,066 net — **unchanged** |
| FLASH | **−2,112 B** | **−1,456 B** | see §0 attribution |
| RAM (total **and** `nm` layout) | **Δ 0 / 0 diff lines** | **Δ 0 / 0 diff lines** | **Δ 0** |
| `.rodata` read back out of the ELF PT_LOAD and byte-compared with `app_update.bin` | **1,875 match / 14 mismatch** | **1,422 / 14** | — |
| `check_ram_pin_collisions.py` app | 0 inside a live object, 0 escaped (624 bound OK) | same | **0 / 0** |
| `check_ram_pin_collisions.py --core net` | — | — | **0 / 0** (170 bound OK) |
| `check_net_raw_literals.py` | — | — | **0 / 0**, 0 TUs failed to preprocess |
| `check_thread_create_stack_args.py` | **10/10** | — | **10/10 PASS** |
| `verify_net_stock_data_window.py` | — | — | **PROVEN** (256/349 equal, 93 flash pointers, **0 differing for any other reason**, 0 non-stock sections) |

The 14 `.rodata` mismatches are **identical to the baseline's 14** and are
pre-existing and documented: the eight localized-string pointer tables
`rodata_8a3e0…8ab18`, `rodata_87d58`, and the five `rodata_0x27cc0`-class
records — the "byte-exact **modulo relocation**" class of
`rodata_decode_report.md` §4. The match count falls 2,558 → 1,875 → 1,422
exactly as the 683 + 453 class-`R` objects are withdrawn; **no object that
survived changed a byte.**

**`tools/full_link.py app` FAILS, and it failed before this pass.** It stops at
`COMPILE_FAIL recon/symbolized/app/spawn_display_thread.c` — `#include
<zephyr/kernel.h>` is not on `full_link.py`'s bare-metal include path — and then
reports UNKNOWN-audit drift naming `rodata_8a3e0…8ab18`, `rodata_9890c`,
`98e3c`, `98fbc`, `98fe8`, `aae20`, `bb220`, `d753a`, `e123a`, `e5f62`,
`a8ea0`, plus `imu_fusion_init`, `sqrtf_hw`, `update_cache` and others. **None
of those symbols is in either batch's applied set** (checked: intersection is
empty) and `spawn_display_thread.c` is untouched by this pass (`git diff` empty).
The gate is stale with respect to the P4 bring-up, not broken by G6. Recorded,
not worked around; the real link is the cohesive build, which passes with
`nm -u` 0.

---

### 5. The measurement that reverted G6-B1's canonical half

The plan asks for `recon_kit.prove` + `cfg_verify` on every canonical file
G6-B1 touches. Run on the edited corpus, `cfg_verify` **fails**, and the reason
is structural rather than a mistake in the edit.

```
main FAIL cases=48
detail=[(3,'prefix',500,500,(125, ('C',68,629247,0,'S','F','T',None),
                                  ('C',68, 96414,0,'S','F','T',None))), …]
```

Call #125 is a logging call. `629247` is `0x99A7F` — an original-image `.rodata`
address; `96414` is the pointer our recompiled TU passes to its own
`.rodata.str1.1` copy. **The trace `emu.compare` checks includes the argument
values of stubbed callees**, so replacing a format-string address with a literal
is a first-class trace difference.

Controlled, both directions, same command:

| function | canonical file inlined | canonical file restored |
|---|---|---|
| `main` | **FAIL** (27 mismatches) | **PASS** cases=48 |
| `FUN_00019718` | **FAIL** | **PASS** |
| `FUN_00021a40` | **FAIL** | **PASS** |
| `FUN_00031fd8` | **FAIL** | **PASS** |
| `opt3007_chip_init` | **FAIL** | **PASS** |
| `flash_settings_read`, `proxy_thread_handler` | PASS | PASS |

A 12-function probe on the restored corpus — `main`, `FUN_00019718`,
`FUN_00021a40`, `flash_settings_read`, `FUN_00031fd8`, `proxy_thread_handler`,
`opt3007_chip_init`, `FUN_000536b8`, `FUN_00048e28`, `process_for_new_task`,
`FUN_00019b54`, `FUN_00025290` — returns **12 / 12 PASS**.

**The rule this establishes, which the plan did not know:**

> A `.rodata` address that reaches a **call argument** cannot be inlined in
> `recon/{app,net}/src` or `recon/verified/src` while parity is proven against
> the original image, because the proof compares that argument's value. String
> inlining in the parity corpus is only possible after the harness is taught to
> treat a `.rodata` pointer argument as an equivalence class — which is a
> `tools/` change, and `tools/` is out of scope for this pass.

That makes **G6-B2** (623 candidates, 614 pins) and the canonical halves of
G6-B1/B3 blocked on the same prerequisite, and it is the single most useful
thing this pass learned. Because the reverted half touched no canonical body in
the tree as left, **no canonical function owes a re-proof and none was left in a
FAILing state.**

---

### 6. Behavioural oracle — the acceptance bar, held

Run end-to-end on the ELFs each batch actually produced, following
`our_boot_bringup.md` §37 — `mkfifo` stdin pipe, `G1_HOOKS=0`,
`$rtinfo_pc=0x00015b8c` (confirmed by `nm` on both ELFs),
`G1_CTX_FE8=0x20040F38`, `G1_CTX_105A=0x20040FAA`, `G1_SCREEN_ID=0x20040025`,
net `/private/tmp/g1-b0-net`.

| stimulus / phase | expected | G6-B3 (`g1-b3-app`) | G6-B1 (`g1-b1-app`) |
|---|---|---|---|
| DASHBOARD `p2_render` (`G1_ATT_WRITE=""`) | `19b1f24a…`, 2,923 px, (78,211)–(564,338) | **`19b1f24a…` 2,923 == 2,923, bbox exact — PASS** | **identical — PASS** |
| DASHBOARD `p1_boot` | `0c5cc90b…`, 0 px | **`0c5cc90b…` 0 == 0 — PASS** | **identical — PASS** |
| NAVIGATION `p2_render` (`G1_ATT_WRITE` unset) | `b26c73b3…`, 1,098 px, (34,266)–(497,287) | **`b26c73b3…` 1,098 == 1,098 — PASS** | **identical — PASS** |
| NAVIGATION `p1_boot` | `1d617c65…`, 656 px, (178,267)–(449,287) | **`1d617c65…` 656 == 656 — PASS** | **identical — PASS** |

`cmp`-ed against the committed goldens, not only compared by hash: dashboard
`p2_render` vs `golden_framebuffer_dashboard_p2_render.raw`, navigation
`p2_render` vs `golden_framebuffer_p2_render.raw`, navigation `p1_boot` vs
`golden_framebuffer_p1_boot.raw` — **no difference**, in both batches.

Supporting counters also held in both: dashboard `spim_a` 9,246 transactions,
navigation `spim_a` 235, `spim_b` 0, `pdm0` 2, `gpiote0` 25 / `gpiote1` 0 —
every one identical to iteration 37. `saadc` reads 668 in this pass's runs
against iteration 37's 95; that is the concurrent iteration-38 SAADC work
visible in the shared `recon/` tree, not a change these batches made — they
touch no sensor path, and all four framebuffers are byte-identical either way.

**All four framebuffers byte-identical. The acceptance bar is held.**

---

### 7. Constraint compliance

| constraint | status |
|---|---|
| keep-symbolic is absolute | **held** — every candidate is `class: string_literal`. No `ADDR_*_THUMB`, ptr_table/ptr_record, device pointer, RAM/`.text` address or section boundary touched. The substituter additionally refuses any symbol appearing on the RHS of **any** `PROVIDE` in **any** `.ld` in the tree, or in any hand-written `recon/application/**/src` source — the rule that protects `g1_bt_adv_objects.c`'s `rodata_9ac7c`. **0 of the 1,344 was blocked by it, i.e. none was load-bearing for the linker.** |
| each string batch is ONE transaction | **held** — literal + object + pin + declaration in the same edit, gated on a build that must not grow |
| flash must not grow | **held, and it shrank** — −2,112 B then −1,456 B, **−3,568 B**; RAM Δ 0 |
| net effectively frozen | **held — net was not touched at all**; `zephyr.bin` byte-identical to baseline; its 49 candidates deferred (§2.3) |
| no renames; no `rodata_*` object filename touched | **held** — no file added, removed, moved or renamed in any tree; only object *bodies* deleted |
| `recon/{app,net}/src` flat and address-keyed | **held** — and, after §5, byte-for-byte unchanged |
| no `tools/` logic edited | **held** |
| no `recon/board/**`, no `recon/application/*/prj.conf`, no `recon/emulator/**`, no `armemul`, no build file | **held** — the `recon/application/app/CMakeLists.txt` and `recon/generated/app_verified_data_sources.cmake` changes in the tree are the concurrent agent's iteration 38 (§0) |
| nothing committed | **held** |

Both generated families that lost objects carry an in-file note saying so and
why a regeneration reproduces them without those lines: `gen_app_string_rodata.py`
and `gen_app_rodata_sources.py` both select a symbol **only if it still carries a
numeric `PROVIDE` pin**, and the pin is gone. The withdrawal is therefore
regeneration-stable — the same mechanism iterations 31/33/35 used for
`rodata_8ac2c`, `rodata_8ad40` and `rodata_9890c`. `g1_app_string_rodata.c` is
down from 1,787 to **562** emitted string objects.

---

### 8. Trees reconciled

| tree | G6-B3 | G6-B1 | left carrying inlined literals |
|---|---|---|---:|
| `recon/symbolized/app` (**build**) | 253 `.c` + 1 `.inc` | 424 | **605 files** |
| `recon/symbolized/net` (**build**) | deferred (§2.3) | n/a | 0 |
| `recon/readable_sources/app/g1` | 193 | 220 | 370 |
| `recon/readable_sources/app/library` | 50 | 202 | 223 |
| `recon/readable_sources/app/include` | 1 `.inc` | — | 1 |
| `recon/named` | 7 (symbol form) | 2 (symbol) + 414 (raw hex) | 422 |
| `recon/net/named` | deferred | n/a | 0 |
| `recon/app/src`, `recon/verified/src` (**parity corpus**) | untouched by design | applied then **reverted** (§5) | **0** |
| `recon/app/src_sym`, `recon/verified/src_sym` | no site | applied then **reverted** | **0** |
| `recon/application/src` | symlink view into `recon/named` — inherits, never written directly | | |

---

### 9. Deferred, in one list

| deferred | count | reason |
|---|---:|---|
| G6-B3 net, all of it | 49 candidates / 49 pins | no net rodata object exists to withdraw; net is frozen (§2.3). Unblocks by wiring `recon/application/rodata/g1_net_rodata_0*.c`. |
| string-pool objects | 11 app (B3) + 11 net (B3) + 6 app (B1) | withdrawing the object deletes bytes other pins address; splitting a pool is a region-shape change |
| `rodata_f541c` | 1 | pool interior, pin already non-numeric |
| canonical-tree inlining, **all batches** | 1,527 (B3) + 1,967 (B1, reverted) | §5 — the parity harness compares the call argument; blocked on a `tools/` change that is out of scope |
| `UINT32_C()` / `UINT64_C()` argument sites | 42 | token pasting (§3.2) |
| `<none>` / `<stmt>` / `fatal` / `nrfx_assert_report` / `FUN_0007e2ec` / `assert_post_action` sites | 58 | not provably a string consumer; needs a per-site disassembly read |
| G6-B2, B5, B6, G6-A, G6-X | — | out of this pass by plan order; **G6-B2 is additionally blocked by §5** |
| `full_link.py` UNKNOWN-audit drift | — | pre-existing, unrelated to G6 (§4) |

---

## Pre-refactor batch G7-B2 — one declaration per logging entry point

Cluster **G7-C10** of `recon/analysis/prerefactor_plan.md`, applied after
G7-B1 and G6-B3/B1. The plan calls this batch *"not really a dedupe — it is a
latent ABI bug"*, and the measurement below confirms that reading: the
consolidation is what made six reconstructions stop compiling, and every one
of them was a real defect.

**Nothing here is committed.** No `tools/` logic, no `armemul`, no build file,
no linker script and nothing under `recon/emulator/**` or `recon/board/**` was
modified. The only new file is `recon/headers/g1_log.h`.

### 0. Headline result

| | app | net |
|---|---|---|
| declarations consolidated | **2,398** in **1,661 files** (4 trees) | **22** in **22 files** (2 trees) |
| distinct signature spellings retired | 245 | 11 |
| **real ABI defects found and fixed** | **6 files / 15 call sites** | 0 |
| `zephyr.bin` vs pre-batch baseline | differs — **only** where the six defects were fixed and where a wrong prototype had been changing codegen (§4) | **byte-identical (`cmp` silent)** |
| FLASH | 948,812 B / 982,528 B = 96.57 % — **Δ −16 B** | 225,581 B / 226 KB = 97.48 % — **Δ 0 B** |
| RAM | 253,765 B / 440 KB = 56.32 % — **Δ 0 B** | 63,380 B / 64 KB = 96.71 % — **Δ 0 B** |
| per-object comparison | **3,407 / 3,430 byte-identical** | **1,168 / 1,170 byte-identical** |
| the four acceptance framebuffers | **all four byte-identical** (§6) | — |

The two net objects that differ are `open_amp/remoteproc_virtio.c.obj` and
`lib__posix/uname.c.obj` — stock SDK units this batch does not touch, and the
linked `zephyr.bin` is byte-identical, so the difference is not in loaded
content.

Baselines were built first, from the working tree as found at `914f61b0`
(clean except for an untracked `.xapk`), and each `zephyr.bin` kept:

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-b2-base-app
recon/application/build_cohesive.sh net /private/tmp/g1-b2-base-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

The baseline reproduced the brief's figures exactly: app 948,828 B FLASH /
253,765 B RAM, net 225,581 / 63,380.

---

### 1. Ground truth, per symbol, from the shipped disassembly

The plan names four entry points. **There are three**, on the application
core, plus one on the net core. `DEBUG_PRINT` is Ghidra's name for the *same
address* as `log_message`, and `recon/symbolized/app/log_message.c` already
binds it as an `__asm__` alias:

| symbol | address | sink | authoritative declaration |
|---|---|---|---|
| `debug_print` | `FUN_00019c70` @ `0x00019c70` | ring buffer via `vsnprintf_impl` | `void debug_print(uintptr_t format, ...)` |
| `log_message` | `FUN_0007dda4` @ `0x0007dda4` | console via `vprintf` | `void log_message(uintptr_t format, ...)` |
| `DEBUG_PRINT` | **== `0x0007dda4`** | same function | alias of `log_message` |
| `printk` (app) | `FUN_0007e2fa` @ `0x0007e2fa` | console via `vprintf` | `void printk(uintptr_t format, ...)` |
| `printk` (net) | `FUN_01039722` @ `0x01039722` | console | `void printk(uintptr_t format, ...)` |

#### 1.1 Evidence for `...` and for exactly ONE fixed parameter

All three application entries open with the AAPCS variadic register-save
prologue and then take the `va_list` from the **second** saved word:

```
00019c70  push {r0, r1, r2, r3}       0007dda4  push {r0, r1, r2, r3}
00019c72  push {r4, r5, r6, lr}       0007dda6  push {r0, r1, r2, lr}
00019c74  sub  sp, #0xd0              0007dda8  add  r1, sp, #0x10
00019c76  add  r5, sp, #0xe0          0007ddaa  ldr  r0, [r1], #4   <- fixed arg
00019c78  ldr  r6, [r5], #4  <- fixed arg, va_list = r5 afterwards

0007e2fa  push {r0, r1, r2, r3} / push {r0, r1, r2, lr}
0007e300  ldr  r0, [r1], #4     <- fixed arg, va_list = r1 afterwards
```

The **post-increment load** is decisive: the callee reads exactly one word out
of the r0..r3 save area and starts the `va_list` at the next word. One fixed
parameter, in r0, then `...`. No VFP register is touched anywhere in any of
the three prologues, which is what the variadic ABI requires and what a
non-variadic hard-float declaration would have violated.

This agrees with, and is independent of, the evidence already recorded in
`tools/cfg_verify.py`: `REVIEWED_CALL_ARITIES_BY_FORMAT` keys every reviewed
arity by `(callee, format)` — e.g. `(0x7dda4, 0xa25d9) -> 2`,
`(0x19c70, 0xa25d9) -> 3` — which is only meaningful for a variadic callee
whose argument count is a property of the format string.

#### 1.2 Evidence for `void`

Every `bl`/`b.w` in `app_update.bin` that targets one of the three addresses
was disassembled — **2,526 sites** (990 `log_message`/`DEBUG_PRINT`, 829
`debug_print`, 707 `printk`; 56 of them tail calls) — and the instructions
after each call examined for a read of r0 before a write. **Not one site reads
it.** The ten sites that mention r0 at all execute `eors r0, r0`, which is a
write. The corpus spellings `int`, `uint32_t`, `uint64_t`, `long long`,
`uintptr_t` and `unsigned int` were all decompiler noise from r0/r1 being live
scratch across a `void` call — and §3 shows that noise had become six real
defects.

#### 1.3 Evidence that the shipped firmware really does pass floats here

`fuel_gauge_update` @ `0x10c14` converts three floats with `__aeabi_f2d`
(`FUN_0000d848`) and hands the results to `debug_print` in **core** register
pairs and on the stack:

```
00010c14  vmov  r0, s21          00010c2a  vmov  r0, s20
00010c18  bl    #0xd848          00010c30  bl    #0xd848
...                              00010c3a  strd  r0, r1, [sp, #8]
00010c36  mov   r2, r6           00010c3e  strd  r8, sb, [sp]
00010c48  mov   r3, r7           00010c4e  bl    #0x19c70
```

r2:r3 carries the first `double`, `[sp+0]` and `[sp+8]` the other two. That is
the variadic convention. A non-variadic declaration in that translation unit
would have placed them in `s0..s15` instead, which is exactly the hazard the
plan flagged.

#### 1.4 Why the fixed parameter is spelled `uintptr_t` and not `const char *`

In the shipped firmware r0 holds a pointer to a format string. `uintptr_t` on
arm-zephyr-eabi in this build is `unsigned long`: the same 32-bit value in the
same register, so the declaration is ABI-identical. The reason for choosing it
is measured, not aesthetic — after batch G6-B1 the corpus universally spells
format addresses as integer expressions (`((unsigned long)"...")`,
`DAT_000241a8`, `0x000a6a28u`), and a probe compile with `const char *`
produced, for a single five-argument `printk` call, **four** diagnostics: one
`-Wint-conversion` for the format plus one `-Wformat` per variadic argument,
because the SDK prototype carries `__printf_like(1, 2)`. Corpus-wide that is
roughly 2,500 + 1,500 diagnostics and **zero** instruction changes.
Re-spelling the call sites is a separate, purely textual batch.

#### 1.5 `printk` is Zephyr's, and the header defers to it

Both link maps show `printk` resolving to stock
`zephyr/libzephyr.a(printk.c.obj)`, not to the reconstructions in
`recon/symbolized/{app,net}/printk.c` — the adoption manifest displaces both.
`<zephyr/sys/printk.h>` therefore declares the linked function as
`extern __printf_like(1, 2) void printk(const char *fmt, ...)`, and two
different declarations of one symbol in one translation unit is a **hard
error** (verified by probe: `error: conflicting types for 'printk'`).
`g1_log.h` guards its own `printk` declaration on
`#ifndef ZEPHYR_INCLUDE_SYS_PRINTK_H_`, and the transformer always emits the
include **after every other `#include` in the file** (verified: 0 files have
an `#include` following it), so where the SDK header is in scope the SDK wins.

---

### 2. What was created and what was replaced

`recon/headers/g1_log.h` is the single declaration site. Its body is four
lines; the rest of the file is the evidence of §1, written down where the next
editor will see it.

```c
void log_message(uintptr_t format, ...);   /* 0x0007dda4 */
void DEBUG_PRINT(uintptr_t format, ...);   /* the same address, Ghidra's name */
void debug_print(uintptr_t format, ...);   /* 0x00019c70 */
#ifndef ZEPHYR_INCLUDE_SYS_PRINTK_H_
void printk(uintptr_t format, ...);        /* 0x0007e2fa app / 0x01039722 net */
#endif
```

The transformer deletes whole `extern` **statements** (parsing the declarator
list so a statement that also declares a non-logging symbol is refused rather
than mangled) and inserts

```c
#include "../../headers/g1_log.h"
```

after the last `#include` of the file. It refuses, and records as deferred, any
file that (a) `#define`s one of the four names to something else, (b) contains
a call with **zero** arguments — which cannot compile against a prototype with
one fixed parameter — or (c) mixes logging and non-logging declarators in one
statement.

| tree | files | declarations removed | still carrying a local declaration |
|---|---:|---:|---:|
| `recon/symbolized/app` (**build**) | 557 + 3 definition files | **806** | 45 files / 87 decls |
| `recon/symbolized/net` (**build**) | 11 + 1 definition file | **11** | 0 |
| `recon/named` | 558 | **808** | 44 / 85 |
| `recon/net/named` | 11 | **11** | 0 |
| `recon/readable_sources/app/g1` | 343 | **577** | 42 / 82 |
| `recon/readable_sources/app/library` | 203 | **207** | 4 / 7 |
| **total** | **1,683 files** | **2,420** | 135 files / 261 decls |

The four **definition** files were also pointed at the header so that the
corpus has one type, not two: `recon/symbolized/app/{log_message,debug_print,
printk}.c` and `recon/symbolized/net/printk.c`. `log_message` was defined
`void log_message(const char *format, ...)` while 355 of its declarations said
otherwise; it and the net `printk` now take `uintptr_t` and cast once when
forwarding to `vprintf` / `FUN_0103a2a6`. `debug_print.c` and the two
`printk.c` were already `unsigned int`, which is the same type. All four
objects are byte-identical to baseline afterwards (`printk.c` on both cores is
displaced by the SDK and not compiled at all — §1.5).

---

### 3. The six real ABI defects — the payoff

These are not style. Each one is a translation unit that compiled, linked and
shipped in our image while doing something the shipped firmware does not do,
and **each was found because the authoritative declaration refused to compile
it**. Five of the six were invisible to `cfg_verify`, which returns PASS on
the defective canonical bodies.

The common root: `log_message`/`debug_print` return **nothing**, so r0 and r1
after a call hold the sink's scratch. Ghidra saw them live, invented a 32- or
64-bit return value, and the reconstructions then *fed that invented value back
in as an argument*. The same class produced surplus arguments: the format
strings were never consulted, so r1..r3 residue was written down as arguments
that the format has no specifier for.

| # | file | sites | what was wrong | evidence |
|---|---|---:|---|---|
| 1 | `get_lux_info` (`FUN_00010fc8` @ 0x10fc8) | 4 | `uint64_t debug_state = log_message(fmt, ctx, slot, size)` and then `debug_state >> 32` passed as argument 2 of the next call; two more calls carried a stale 4th argument | `0xa6a28` = `"###…join in get_lux_info\n"` and `0xa6a61` = `"get_lux_info para is NULL\n"` have **no specifiers**; 0x10fce and 0x10fda load **only r0**. `0xa6a7c` = `"%s(): curve_lux:0x%x\n\n"` has two, so three arguments; 0x11086..0x1108c loads exactly r0/r1/r2 and the r3 that was being passed is the `g_log_use_alt_sink` value the branch itself loaded |
| 2 | `set_imu_thread_delay` @ 0x25d8c | 2 | declared `int` and `return`ed the logging call; also passed a 4th argument | fall-through 0x25db0 is a bare `bx lr` with r0 untouched; both logging exits are TAIL calls `b.w 0x19c70` / `b.w 0x7dda4`. `0x9f721` = `"%s(): %d(ms)\n"` — two specifiers, three arguments |
| 3 | `send_data_in_ble_chunks` (`FUN_0003384c` @ 0x3384c) | 2 | declared `uint32_t` and `return`ed the logging call — while **both** call sites already declared it `extern void send_data_in_ble_chunks(void *)` | 0x338d4 pops straight to pc with the incoming NULL still in r0; the other three exits are tail calls `b.w 0x19c70`, `b.w 0x7dda4`, `b.w 0x33730`. The four-argument shape here is CORRECT (`0xa7bf5` has three specifiers) and was left alone |
| 4 | `exit_dashboard_burial_point` @ 0x4aab0 | 2 | `r0v = log_message(...)` where `r0v` is the value the function returns | every exit is `add sp,#0xc; pop {r4,r5,pc}` at 0x4ab0a with r0 left as the last callee's scratch, and the sole caller (`ui_DashBoard_task.c:649`) discards it. The five-argument shape is CORRECT and was left alone |
| 5 | `test_mode_apply_base_status_cmd` (`FUN_00031dd8` @ 0x31dd8) | 3 | `uint64_t debug_result = log_message(fmt, …)` fed back as argument 2 of the two later calls, plus stale 3rd/4th arguments on all three | `0xa715d`, `0xa7173`, `0xa672f` are **all** argument-free formats; 0x31dde, 0x31dea and 0x31e00 load **only r0** |
| 6 | `reflash_fb_data_to_lcd_ex` (`FUN_000473c8` @ 0x473c8) | 2 | `uVar3 = (unsigned)((u64)log_message(...) >> 32)` — modelling r1 after a `void` call | 0x474fe / 0x47516 load only r0/r1 (the format has one specifier) and 0x47502 immediately reloads r0 from `[sp,#0x20]`, so nothing the sink leaves is read |

That is **6 files and 15 call sites** (the table's counts). Every fix was
verified the way the brief demands — by compiling the single translation unit
and reading the emitted instructions against the shipped disassembly, not by
trusting a green harness:

* `get_lux_info` — the corrected body emits
  `stmdb / mov r4,r2 / ldr r0,[pc] / mov r5,r3 / bl / cbz / cbnz / ldr r0,[pc] /
  bl / mov.w r0,#-1 / ldmia.w` and a tail
  `ldr r3,[pc] / mov r2,r0 / ldr r3,[r3] / str r0,[r4,#32] / cmp r3,#2 / ble /
  ldr r3,[pc] / ldr r1,[pc] / ldr r3,[r3] / ldr r0,[pc] / cbnz / bl / … / bl` —
  **instruction-for-instruction** the shipped 0x10fc8..0x10fe4 and
  0x1107a..0x110a0, with only the cbz/cbnz polarity and the two sinks exchanged
  (identical semantics; GCC picks the layout).
* `set_imu_thread_delay` — instruction-for-instruction the shipped
  0x25d8c..0x25db2, including the trailing `nop`.
* `send_data_in_ble_chunks` — all four exits reproduce the shipped shape:
  `add sp,#0x28 / ldmia.w sp!,{…,lr} / b.w <sink>` twice, the same to
  `send_notification_app_whitelist`, and `ldmia.w sp!,{…,pc}` for the NULL path.
* `test_mode_apply_base_status_cmd` — instruction-identical prologue to the
  shipped 0x31dd8..0x31df6.
* `exit_dashboard_burial_point` and `reflash_fb_data_to_lcd_ex` — same call
  order, same argument registers (`r0,r1,r2,r3,[sp]` / `r0,r1`), same branch
  structure and epilogue as the shipped bodies.

**Objects, measured against the pre-batch baseline:** `set_imu_thread_delay`
and `send_data_in_ble_chunks` are **byte-identical** — dropping the stale r3
and the `return` changed nothing, because r3 already held that value and the
tail call survives. The other four shrink: `get_lux_info` −12 B,
`test_mode_apply_base_status_cmd` −12 B, `exit_dashboard_burial_point` −4 B,
`reflash_fb_data_to_lcd_ex` −4 B.

#### 3.1 One canonical body could not be re-proven, and is left divergent

The six fixes were also applied to the canonical parity tree
(`recon/app/src` + `recon/verified/src`) and re-proven:

| canonical function | `cfg_verify` after the fix |
|---|---|
| `FUN_00010fc8` (`get_lux_info`) | **PASS** `cases=4 sel={2:[0,1], 3:[0,1]}` |
| `FUN_0003384c` (`send_data_in_ble_chunks`) | **PASS** `cases=2 sel={0:[0,1]}` |
| `FUN_000473c8` (`reflash_fb_data_to_lcd_ex`) | **PASS** `cases=5` |
| `set_imu_thread_delay` | **PASS** `cases=0` |
| `exit_dashboard_burial_point` | **PASS** `cases=0` |
| `FUN_00031dd8` (`test_mode_apply_base_status_cmd`) | **FAIL**, 42 mismatches — **reverted** |

`FUN_00031dd8`'s failure is instructive and is recorded rather than worked
around. The harness compares **four** arguments at each of these calls
(`call_arities_used: [4, 4]` in the trace) even though all three formats are
argument-free, and the mismatch is entirely in argument 4:

```
original  ('C', 1, ('RO', b'warning: not test mode,disable setting\n'), …, 536977139)
candidate ('C', 1, ('RO', b'warning: not test mode,disable setting\n'), …, 536976896)
```

`536977139` is `0x20019EF3`, the `g_test_mode_flag` address the shipped code had
just loaded into r3 for its own `ldrb`. It is dead scratch at the call, not an
argument — exactly what `REVIEWED_CALL_ARITIES_BY_FORMAT` exists to record, and
adding an entry for `("app", 0x00031dd8)` is a `tools/` change, which this pass
is forbidden to make. **The canonical body therefore keeps its defect and the
build tree carries the fix**, and this divergence is listed in §9. The evidence
that the build tree is the correct one is the disassembly, not the harness: the
three formats have no conversion specifiers and the image loads only r0.

This is the mirror image of the hazard the brief names. Here the harness is
**red on correct code**, for the same reason it is elsewhere green on broken
code: it compares register residue it cannot distinguish from arguments.

---

### 4. Per-object measurement — which translation units the declaration changed

Every `.c.obj` of both builds was `--strip-debug`-ed and `cmp`-ed against its
baseline counterpart.

| core | objects | byte-identical | differing |
|---|---:|---:|---:|
| app | 3,430 | **3,407** | 23 |
| net | 1,170 | **1,168** | 2 |

The **net** pair — `open_amp/remoteproc_virtio.c.obj` and
`lib__posix/uname.c.obj` — are stock SDK units this batch does not touch, and
the linked net `zephyr.bin` is byte-identical, so whatever differs in them is
not loaded content. The **same two** objects also differ on the app side, which
confirms they are build non-determinism rather than a consequence of the batch.

Of the 23 app objects: **6** are the defect fixes of §3, **1** is the generated
`isr_tables.c.obj` (it follows the link layout), **2** are the stock pair just
named, and the remaining **14** changed for the reason this batch exists — they
had been compiling against a wrong prototype:

| object | Δ text | previous local declaration | what changed |
|---|---:|---|---|
| `app_event_manager_process_events` | **−20 B** | `void printk(int,int,int,int)` | **instruction stream identical**; the literal pool loses 5 words, because the format/argument expressions no longer round-trip through `int` |
| `master_process_audio_fw_load_req` | +4 B | `int log_message(const char*, const char*, ...)` (**two** fixed parameters) | register/stack-slot allocation and one `cmp` operand order |
| `is_ext_flash_burned` | 0 | 4 fixed `int` | scheduling |
| `spec_ble_command_hook` | 0 | 4 fixed | scheduling |
| `arch_irq_priority_set` | 0 | 5 fixed | a `str`/`ldr` pair swapped |
| `k_msgq_put`, `k_msgq_get`, `gatt_notify`, `adc_nfc_init`, `adc_nfc_run`, `jbd_panel_resume`, `ble_privacy_id_remove`, `bt_ancs_data_source_handler`, `bt_att_chan_create_pdu`, `main`, `reflash_fb_data_to_lcd` | 0 | 2–5 fixed parameters | 2–8 lines of scheduling / literal-pool ordering |

None of the 14 changes an executed operation; they are the compiler's freedom
under a corrected prototype. The whole-image effect is **−16 B**.

**1,589 of the 1,609 retained app translation units and all 944 retained net
ones are byte-identical objects** — i.e. for the overwhelming majority the
consolidation is provably codegen-neutral, and the batch's risk is concentrated
in a list of 20 objects small enough to read one by one, which is what §3 and
this table do.

---

### 5. Gate ladder

| gate | result |
|---|---|
| `gen_retained_sources.py --check` | **clean** — "retained source lists are current" |
| app build | **exit 0**, 3,070 targets |
| net build (`-DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON`) | **exit 0** |
| `nm -u` undefined | **0 / 0** |
| duplicate global definitions | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` / weak-symbol hack | **0 occurrences** in either log (the only `weak` hits are the stock `main_weak.c` filename) |
| numeric-root hacks added | **0** — no linker script touched |
| `check_ram_pin_collisions.py` app | **0 escaped binds, 0 unknown inside a live object** (624 bound pins OK) |
| `check_ram_pin_collisions.py --core net` | **0 / 0** (170 bound pins OK) |
| `check_net_raw_literals.py` | **0 / 0** — 0 TUs failed to preprocess, 0 distinct raw literals |
| `check_thread_create_stack_args.py` | **10 / 10 PASS** |
| `verify_net_stock_data_window.py` | **PROVEN** — 256/349 words equal, 93 differing all flash pointers, **0 differing for any other reason**, 0 non-stock input sections |
| `cfg_verify` on every canonical body this batch changed | **5 / 5 PASS**; the sixth (`FUN_00031dd8`) FAILed and was reverted — §3.1 |
| net `zephyr.bin` `cmp` vs baseline | **byte-identical** |
| app FLASH | 948,812 / 982,528 = 96.57 % — **Δ −16 B**, ~32.9 KB headroom |
| app RAM | 253,765 / 440 KB = 56.32 % — **Δ 0 B** |
| compiler warnings | app 1,798 → **1,887** (+89), net 1,066 → **1,066** (Δ 0) |

The +89 app diagnostics are all one kind: `-Wint-conversion, passing argument 1`
— 44 `log_message`, 41 `debug_print`, 4 `printk`. They are the call sites that
hand a *pointer* expression (`(const void *)…`, `void *`, a bare `rodata_*`
array) to the `uintptr_t` format parameter, and they were silent before only
because each such file declared its own pointer-typed prototype. **No
instruction changes with them**; re-spelling those 89 first arguments is
mechanical and is left for the same textual batch as §1.4. This is two orders
of magnitude cheaper than the ~4,000 diagnostics a `const char *` header would
have produced.

---

### 6. Behavioural oracle — the acceptance bar

Re-run end to end on **the ELFs this batch produced**
(`/private/tmp/g1-b2-app`, `/private/tmp/g1-b2-net`), following
`our_boot_bringup.md` §37/§38: `mkfifo` stdin pipe, `G1_HOOKS=0`,
`$rtinfo_pc=0x00015b8c`, and `G1_CTX_*`/`G1_SCREEN_ID` **taken from the ELF
booted** — `nm` gives `_end = 0x2003ff45` in this build exactly as in
iteration 38, so `G1_CTX_FE8=0x20040F38`, `G1_CTX_105A=0x20040FAA`,
`G1_SCREEN_ID=0x20040025`. The net ELF used is this batch's own, and its
`zephyr.bin` `cmp`s byte-identical to `g1-i30e-net`.

| stimulus / phase | expected sha256 | measured sha256 | lit px | bbox | verdict |
|---|---|---|---|---|---|
| DASHBOARD `p2_render` (`G1_ATT_WRITE=""`) | `19b1f24a…` | `19b1f24a09f97a8d85f1572ac865c8fc61fe6d542af18247a5bcceeb7651b513` | **2,923 == 2,923** | (78,211)–(564,338) | **PASS** |
| DASHBOARD `p1_boot` | `0c5cc90b…` | `0c5cc90b079d0d9c1ded1376357d23a9782a704a83e01731f50ccd162e246492` | **0 == 0** | — | **PASS** |
| NAVIGATION `p2_render` (`G1_ATT_WRITE` unset) | `b26c73b3…` | `b26c73b37d441fc8a6732c02e6d889a719677ec4c9ad2adc2d48f28deedb8131` | **1,098 == 1,098** | (34,266)–(497,287) | **PASS** |
| NAVIGATION `p1_boot` | `1d617c65…` | `1d617c65a688f10eefe139741b680164f09adcd960b18c3ec9ad1f0fb193b953` | **656 == 656** | (178,267)–(449,287) | **PASS** |

The raws were additionally `cmp`-ed against the committed goldens, not only
compared by hash:

```
cmp <dash p2_render>.raw recon/emulator/reports/golden_framebuffer_dashboard_p2_render.raw -> no difference
cmp <nav  p2_render>.raw recon/emulator/reports/golden_framebuffer_p2_render.raw           -> no difference
cmp <nav  p1_boot>.raw   recon/emulator/reports/golden_framebuffer_p1_boot.raw             -> no difference
```

Supporting counters held: dashboard `spim_a` `p1_boot` stream sha
`f91505ab8dc0dd271eb4d43a3f6c12605247c0e01eb9e14463f64f8e37a5a52e` (the §37.7
D-3 PASS value) over 34 transactions, `spim_b` 0 transactions in both phases.

**All four framebuffers byte-identical. The acceptance bar is held**, and
unlike G7-B1 it is held across a **−16 B image change**, so this is a
measurement rather than a tautology.

---

### 7. Constraint compliance

| constraint | status |
|---|---|
| `recon/{app,net}/src` stay flat and address-keyed | **held** — no file moved, added or removed in any tree; the five surviving canonical edits are in place under their existing names |
| no renames | **held** — no function, file or symbol renamed |
| flash budget | **held and improved** — app −16 B (96.57 %, ~32.9 KB headroom), net Δ 0 B |
| RAM | **held** — Δ 0 B on both cores |
| no `tools/` logic edited | **held** — and §3.1 records one place where a `tools/` change *would* have been the right fix and was not made |
| no `recon/board/**` edited | **held** |
| no build file, linker script, `recon/emulator/**` or `armemul` edited | **held** — `recon/emulator/**` was only *read* and *executed*; the capture output went to `/private/tmp` |
| nothing committed | **held** |
| `--allow-multiple-definition` / weak-symbol / numeric-root hacks | **none** |

---

### 8. Trees reconciled

| tree | role | declarations consolidated | defect fixes propagated |
|---|---|---:|---:|
| `recon/symbolized/app` | **build** | 806 (+3 definition files) | 6 |
| `recon/symbolized/net` | **build** | 11 (+1 definition file) | — |
| `recon/named` | readable app mirror | 808 | 6 |
| `recon/net/named` | readable net mirror | 11 | — |
| `recon/readable_sources/app/g1` | readable split | 577 | 5 (no `set_imu_thread_delay` copy exists) |
| `recon/readable_sources/app/library` | readable split | 207 | — |
| `recon/app/src` | **canonical parity** | deferred (§9) | **5** of 6 — `FUN_00031dd8` reverted (§3.1) |
| `recon/verified/src` | canonical mirror | deferred | **5**, copied from `recon/app/src` so the two are identical for those files |
| `recon/app/src_sym`, `recon/verified/src_sym` | older symbolized snapshots | deferred | none — no copy of any of the six functions carries the defect in a compiled path |
| `recon/net/src` | canonical net (28 files are **compiled**) | 0 declarations exist | — |
| `recon/application/src` | readable app tree | deferred (1 declaration) | — |

The `recon/net/src` files that the net build compiles were checked
individually: **none** of the 28 declares any of the four symbols, so the batch
neither needed nor made a change there. `recon/symbolized/net/FUN_0102afbc.c`
does carry `extern void printk(int, ...)` next to a `#include
<zephyr/kernel.h>` — a declaration that would not compile — but that file is
**not** in the retained list; the compiled copy is `recon/net/src/FUN_0102afbc.c`
and it has no such declaration. Recorded, not acted on.

---

### 9. Deferred, in one list, with reasons

| deferred | count | reason |
|---|---:|---|
| **zero-argument call sites** | **140 sites / 45 files** in the build tree (1,071 sites across all nine trees) | `debug_print()` / `log_message()` / `printk()` with **no arguments at all** cannot compile against a prototype with one fixed parameter, so those files keep their local declarations. They are a **real defect class, quantified here for the first time**: the shipped image loads r0 (and often r1, r2) before every one of these `bl`s — e.g. `handle_attitude_trigger` @ 0xfec0 hoists `ldr r1,[pc]` and `ldr r0,[pc]` *above* the `cbz` and then calls either sink, so both take the same two arguments. Our build emits `bl` with r0 undefined. Fixing them is mechanical (give each the arguments its paired sibling call carries, which also lets GCC hoist the setup exactly as the image does) but it is 140 call sites each needing its own format-string check, and it changes codegen at every one — a batch of its own, not a rider on this one. |
| **canonical parity trees** (`recon/app/src`, `recon/verified/src`, `recon/app/src_sym`, `recon/verified/src_sym`, `recon/application/src`) — 1,435 declarations | 1,435 | `tools/parity/recon.py` builds a **temporary translation unit** and its `CFLAGS` carry only `-I…/recon/app/src` and `-I…/recon/net/src`; a `#include "../../headers/g1_log.h"` written relative to the source directory does not resolve from there, and adding `recon/headers` to that include path is a `tools/` change. The same `CFLAGS` also pin `-std=gnu11` specifically to *preserve* the firmware-era rule that `f()` is unprototyped — which is what the 1,071 zero-argument canonical call sites rely on. The six defect **bodies** were still fixed and re-proven individually (§3.1); only the declaration consolidation is deferred. |
| **`FUN_00031dd8` canonical body** | 1 | `cfg_verify` FAILs on the corrected body because it compares four arguments at an argument-free format (§3.1). Needs a `REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x00031dd8)]` entry — a `tools/` change. |
| files that `#define` a logging name to something else | 8 (`hci_set_ad.c` → `z_log_msg_runtime_create`, plus 7 raw-`FUN_` redirects in the older `*_sym` snapshots) | the name is not this symbol there |
| mixed-declarator `extern` statements | 2 | one `extern` statement declaring both a logging and a non-logging function; the transformer refuses rather than rewrites |
| re-spelling the format argument as `const char *` | ~2,500 sites + the 89 pointer-typed ones that now warn | §1.4 / §5 — purely textual, zero instruction change, but it must be done *with* the `-Wformat` fallout of the SDK's `__printf_like(1, 2)` in view |
| `DEBUG_PRINT` as a live spelling in the build tree | — | no build-tree file calls or declares it; the header declares it for the canonical trees' benefit and `recon/symbolized/app/log_message.c` still supplies the `__asm__` alias |

---

### 10. Honest summary

The plan predicted this batch would find a latent ABI bug and it did, but not
in the shape predicted. **No call site was passing a floating-point argument
under the wrong convention** — the corpus scan found ten translation units that
mention `float`/`double` at all near a logging declaration, six of them with a
non-variadic prototype, and per-site inspection showed none of the six actually
hands a float to a logging entry. The one place in the whole image where floats
*do* reach one of these sinks, `fuel_gauge_update` @ 0x10c14, already had a
variadic declaration.

What the wrong prototypes were actually doing was **inventing return values and
arguments**: 15 call sites across 6 files, all of them consequences of
`log_message`/`debug_print` being declared to return data when the shipped
functions return nothing. Four of the six files are invisible to `cfg_verify`,
and one of them (§3.1) is a body the verifier actively rejects *after* it was
corrected. The declaration change also moved codegen in 14 further translation
units, all provably semantics-neutral, and the net effect on the image is
−16 B with all four acceptance framebuffers byte-identical.

The batch is **not** complete: 45 build-tree files and the five canonical trees
still carry their own declarations, for the two structural reasons in §9. Both
unblock the same way — the zero-argument sites need a dedicated per-site batch,
and the canonical trees need one line in `tools/parity/recon.py`'s include path.

---

### 11. Observation: `tools/` changed underneath this session again

As in G7-B1 §6, `tools/` carries **uncommitted modifications this pass did not
make** — 41 modified files including `tools/cfg_verify.py` (mtime 22:10:31),
`tools/parity/emu.py` and `tools/parity/recon.py` (22:00:21), plus three new
files (`tools/g1_paths.py`, `tools/run_tests.py`,
`tools/audit_negative_controls.py`) and three new
`recon/analysis/harness_unblock*` artifacts. The session-start `git status` was
clean apart from an untracked `.xapk`, and this pass never opened any file
under `tools/` for writing. Recorded, not acted on.

Two consequences were checked rather than assumed:

1. **The §9 deferral rationale is still true at the end of the session.**
   `grep -c "recon/headers" tools/parity/recon.py` = **0**; its `CFLAGS` still
   carry only `-I…/recon/app/src` and `-I…/recon/net/src`, so a header include
   written relative to a canonical source directory still cannot resolve in the
   temporary parity TU.
2. **Every `cfg_verify` result in §3.1 was re-measured after the last observed
   `tools/` mtime** and is unchanged: `FUN_00010fc8` PASS `cases=4`,
   `FUN_0003384c` PASS `cases=2`, `FUN_000473c8` PASS `cases=5`,
   `set_imu_thread_delay` PASS `cases=0`, `exit_dashboard_burial_point` PASS
   `cases=0`. The corrected `FUN_00031dd8` still **FAILs** with the same 42
   mismatches, and the reverted (still-defective) body still **PASSes** — the
   two outcomes side by side, under the newest verifier, are the cleanest
   statement of why a green harness is not evidence for an ABI change.
