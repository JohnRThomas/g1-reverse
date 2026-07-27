# `recon/refactor/` — the staged, mechanical refactor pipeline

This directory turns the recovered G1 firmware sources into production-grade C
**one numbered, independently-verifiable stage at a time**. It is a build
pipeline, not a place anyone edits code.

```
stage_00  =  verbatim snapshot of the COMPILABLE input set
stage_N   =  transformer_N(stage_N-1)          for N >= 1
```

---

## The contract

**C1 — the canonical trees are evidence and are never transformed.**
`recon/app/src`, `recon/net/src`, `recon/verified/src` and their `*_sym`
siblings, plus `recon/data`, `recon/net/data`, `recon/emulator` and `tools`, are
byte-verified, flat, address-keyed evidence. Roughly 40 tools and 50 test files
resolve a function inside them as `os.path.join(<flat dir>, name + ".c")` —
`cfg_verify`, `reverify`, `global_evidence`, `recon_kit`,
`check_thread_create_stack_args`, and the whole `test_*_adoption` /
`test_*_namespace` corpus. Restructuring there silently changes what the entire
test corpus MEANS.

This is enforced *structurally*, not by convention: every write in this pipeline
goes through `guard.check_write(path, stage_dir)`, which refuses (a) any path
inside a protected tree and (b) any path outside the stage's own directory.
`test_guard.py` proves both refusals.

Genuine reconstruction **defect fixes** to the canonical trees are legitimate and
are made concurrently by a different agent. This pipeline never fights them: it
consumes their output and reports a stage as *stale* when they land.

**C2 — the pipeline operates on the COMPILABLE sources only.**
The tree that compiles is `recon/symbolized/{app,net}`, and the authority for
*which* of its files compile is `recon/generated/{app,net}_retained_sources.cmake`
(1,615 app / 923 net, encoding 677 + 312 manifest exclusions), **never a
directory glob**. `input_set.py` derives the set from those lists, plus:

* the `.inc` **and `.h`** fragments the sources `#include`, as a transitive
  closure resolved the way the compiler resolves them — relative to the
  including file first, then along `INCLUDE_SEARCH_DIRS` (the `-I` directories
  the two CMakeLists actually pass). *Stage 03 added the `.h` half and the
  `-I` resolution; stage 02 §5.3 had found two wrong declarations in
  `ble_process_put_common.h` that were invisible to the pipeline because only
  relative `.inc` includes were enumerated. A declaration is compiled content
  exactly as much as a definition is.*
* the hand-written integration TUs in `recon/application/{app,net}/src`;
* the generated `recon/application/rodata/*.c`;
* the pin/declaration artifacts
  `recon/symbols/g1_{app,net}_{globals.ld,symbols.h}` that a
  withdraw-transaction has to edit in the same breath as an inline;
* the **build machinery** a STRUCTURAL transaction has to edit in the same
  breath as a move (C6): `recon/generated/{app,net}_retained_sources.cmake` and
  `recon/application/{app,net}/CMakeLists.txt`. *Added by stage 03. The app
  CMakeLists is in the set because it names
  `symbolized/app/discovery_callback.c` by path to give it `-std=gnu99`, and
  **CMake does not error when a `set_source_files_properties` path stops
  existing** — the flag silently disappears and the TU then fails under strict
  C99.*

Total: **2,629** transformable, 36 quarantined-protected.

From stage 04 on, one stage output may be derived from MANY manifest inputs (a
merged translation unit). `Stage.emit` therefore takes `extra_sources` and
records `additional_sources`, and `staleness()` checks every one of them — a
staleness mechanism that watched only the first member would report "current"
while an upstream defect fix sat unnoticed inside member 7.

A transformer may also emit **generated artifacts** that are outputs rather
than inputs (stage 02's `recon/headers/g1_dedupe.h`, stage 03's 16 module
headers). They are deliberately absent from `MANIFEST["files"]` — staleness
would otherwise hunt for a source that never existed — so `driver.materialize`
carries them forward explicitly: any *real* file in stage N−1's tree that its
manifest does not list is inherited verbatim and recorded as
`inherited_generated_outputs`. *Added by stage 03, after a compile failure: the
defect only appears at the third stage in a chain, so stages 01 and 02 could
not have exposed it.*

Build inputs that live inside a protected tree (the app CMakeLists compiles 2
sources out of `recon/app/src`, the net CMakeLists 34 out of `recon/net/src`)
are carried **by reference** and reported as `quarantined_protected`.

**C2b — a transformer's EVIDENCE is an input, and staleness watches it.**
`sdk_declared_symbols.json` and `link_referenced_symbols.json` are measurements
a transformer consults to decide what it may do. They live inside the pipeline,
so `input_set` never lists them — and before `stagelib.EVIDENCE_INPUTS` existed,
`driver.py status` reported a stage as **current** after its evidence had been
regenerated underneath it. Measured when it was added: correcting the SDK
evidence moved stage 03's harvest (218 → 215 hoists, 267 → 300 refusals) while
`status` went on reporting stages 03, 04 and 05 as current. `materialize` now
records the evidence hashes in every MANIFEST and `staleness()` checks them.

**C3 — one directory per step.** `stage_NN_<slug>/` holding `MANIFEST.json`,
`PARITY_MAP.json`, an optional `QUARANTINE.json`, and `tree/`.

**C4 — `stage_N = transformer(stage_N-1)`, reproducible, zero hand-edits.**
The stage tree is derived mechanically from sources that already compile.
**Therefore a compile failure in a stage tree is proof the transformer is wrong,
not a task to hand-fix.** Never hand-patch a stage tree. One hand-edit destroys
reproducibility, which is exactly what lets a stage be regenerated when the
concurrent parity agent lands a defect fix upstream.

First-try compile status is a **measurement**, not a checkbox: how many files
compiled clean on the first regeneration after each transformer change, how many
rounds the transformer needed, and what the compiler said. Every failure is
triaged into exactly one of two buckets and the split is reported:

* **(a) transformer bug** — fix the transformer, regenerate;
* **(b) latent defect in the original reconstruction that the compiler just
  exposed.** This bucket is real and valuable. In the G7-B2 batch the *predicted*
  float-ABI defect turned out not to exist at all, but 15 call sites across 6
  files were inventing return values and arguments — caught for exactly one
  reason: an authoritative declaration refused to compile them. The compiler
  finds what the parity harness structurally cannot see. Look for this
  deliberately.

**C5 — automate everything; zero manual edits at any scale.**
If you are about to make the same edit twice by hand, write the transformer.
Residue that genuinely cannot be automated is **quarantined**, listed in
`QUARANTINE.json` with its reason, and left untransformed. An honest smaller
fully-mechanical stage beats a larger one contaminated by manual edits.

**C6 — renaming is gated by a real link, and regenerates its dependants.**
Two specific hazards for any future rename stage:
`KEEP(*rodata_*.c.obj(".rodata.rodata_*"))` in
`recon/application/app/g1_verified_rodata_keep.ld` ties flash occupancy to
**filenames** — renaming a `rodata_*` file silently changes what survives
`--gc-sections`; and commit `183f8787` was a 563-function rename wave that never
regenerated downstream artifacts and left the cohesive build unlinkable for many
commits while the README still claimed it built. A rename stage MUST regenerate
the generated `.cmake`/`.ld` lists, alias and gc-root files, and MUST be gated by
an actual link.

**C7 — THE ACCEPTANCE BAR.**
The refactored firmware is **not** constrained by `cfg_verify` or per-function
positional parity. It is proven by **observable side-effect equivalence with the
SHIPPED binaries**: every peripheral bus transaction (SPI display; TWIM/I2C for
IMU, PMIC, ambient light, NFC; QSPI; PDM; ADC), radio traffic (BLE
advertising/connection/GATT-NUS, ESB L<->R sync), pixel-exact framebuffers, GPIO
and MMIO writes, sensor interpretation results, and ordering.

The reference is always the shipped binaries. Comparing against our own previous
build proves only that we changed nothing — a tautology.

Consequently **refactoring may be genuinely aggressive**: cohesive modules
grouping many functions per file, real headers and types, inlining, macro
substitution, dead-parameter removal, changed calling conventions between our own
internal functions. None of it is observable from outside the chip. Do NOT
contort later stages to preserve flat one-function-per-file address keying.

`cfg_verify` and `tools.parity` are demoted to **diagnostics** — how you localise
a cause once side-effect equivalence fails. `PARITY_MAP.json` exists for exactly
that traceability, and `driver.py check-addresses A B` asserts the SET of
original addresses is identical between consecutive stages (an address that gains
or loses an entry means a transformation dropped or duplicated a function). It is
a debugging aid and an integrity check, **not** the thing being proven.

**C7b — EVERY STAGE DECLARES A CODEGEN CLASS, AND THE CLASS IS CHECKED.**
Added after the Stage 04 R7 gate, which learned from nine Renode captures
something a `size -A` could have predicted. Three independent measurements in
this project now agree: **+60 B**, **+16 B** and **−16 B** of `.text` each
re-phased the boot path enough to break byte-equality of a peripheral bus
stream. The third is the decisive one, because it points the other way:
**shrinking the image is not safe either.**

So `driver.STAGES` carries a fifth field:

| class | meaning | gate |
|---|---|---|
| `byte-identical` | the linked image must be byte-identical to the input stage's | `cmp zephyr.bin` |
| `size-neutral` | the image may differ, but every allocatable section size is unchanged | the section table |
| `size-changing` | sections move; **an oracle run is REQUIRED** and may not be inferred, argued or borrowed from a previous stage | Renode |

`materialize` records the class and `"oracle_required"` in the MANIFEST, so the
obligation travels with the stage rather than living in a report.
`driver.py size-gate N BASE_BUILD STAGE_BUILD` measures the class the stage
ACTUALLY achieved, writes `SIZE_GATE.json` into the stage directory, and exits
non-zero when the stage came out **worse** than it declared. Coming out better
passes and is reported.

The classifier keys on **`SHF_ALLOC` in the ELF section header**, never on a
list of section names. Its first version compared `(".text", ".rodata", ...)`
and reported a stage whose `.text` had moved 80 bytes as `size-neutral` with
every delta `+0` — because the G1 Zephyr link names them `text`, `rodata`,
`datas`, `bss`, `noinit`, with no leading dot, plus 20 further allocatable
areas. A gate keyed on a name list is a gate that silently passes.
`test_size_gate.py` pins all of this (25 tests); the suite is **139/139**.

**C7c — a rule keyed on a hand-maintained list of NAMES is a rule that silently
stops covering what it was written for.** This has now happened four times, and
the list is kept here because the fifth is coming:

* the first size gate compared `(".text", ".rodata", …)` and passed a stage whose
  `.text` had moved 80 bytes, because this link names them without a leading dot
  (C7b above) — fixed by keying on `SHF_ALLOC`;
* stage 03's declaration scanner anchored a `;` at end of line and could not see
  `extern void memset_bytes(void *, int, size_t);  /* memset */`;
* `sdk_symbols.py`'s `-aux-info` parser did the same and dropped **every**
  `static inline` the SDK declares — 410 identifiers, reported for two passes as
  a GCC limitation;
* stage 07's pinned-symbol rule listed **three** linker fragments out of
  **eighteen**, and the link failed on
  `PROVIDE(prepare_new_task = wait_touch_key_release_or_timeout)`.

The repair is always the same shape: **discover, or key on a structural property,
never on a list of names.**

**C8 — the one genuinely risky transformation class.**
Inlining and macro substitution are invisible from outside the chip in almost
every case, but anything that **reorders or coalesces volatile MMIO accesses**,
or changes the number or order of bus transactions, IS directly observable.
Every stage must enumerate which of its transformations could be observable that
way and give those a conservative default. Stage 01's enumeration is in its
transform docstring and in `recon/analysis/staged_refactor_stage01.md`.

---

## Stage ordering

Most-mechanical / least-risky first, so that if side-effect equivalence later
breaks we learn WHICH stage broke it. A big-bang restructure verifiable only at
the end gives a pass/fail with no diagnostic value.

| stage | what | why here |
|---|---|---|
| 00 | verbatim snapshot | identity transform; proves the build mechanism |
| 01 | literal inlining | value-preserving substitution in argument position; no control flow, no MMIO, no layout. **Declared class corrected 2026-07-27 `byte-identical` -> `size-changing`:** its first-ever `size-gate` measured `text` -4 B / `rodata` -124 B, which is what withdrawing 100 backing objects worth 3,997 B does. See the consolidated verdict below. |
| 02 | **block dedupe (LANDED)** — volatile-accessor spelling normalisation (one type only), plus the `G1_NORETURN_CALL` / `G1_LOG_ROUTE` / `G1_ASSERT_FAIL` macros and the log-prototype convergence residue. Stage 03's `__ASSERT` / noreturn extraction was folded in here because it is the same class of token-identical statement macro. | textual, codegen-identical; gate is a byte-identical `.o`, and it held: both cores' `zephyr.bin` byte-identical to stage 01, 4,594/4,598 objects byte-identical. Report: `recon/analysis/staged_refactor_stage02.md` |
| 03 | **module structure (LANDED, app core only)** — the `input_set.py` `.h`-fragment fix stage 02 filed as blocking, plus the first STRUCTURAL transform: 1,621 app sources moved into 22 cohesive module directories (build lists regenerated in the same transaction, list order preserved exactly), and 99 module-wide type-identical `extern` declarations hoisted into 16 generated module headers. Net untouched and therefore byte-identical by construction. | file layout + declaration siting only; gate is a byte-identical `zephyr.bin`, and it held on both cores. **Harvest: 1,014 symbol/module type disagreements, 446 of them against the symbol's own definition, 175 about arity.** Report: `recon/analysis/staged_refactor_stage03.md` |
| 03b (partly done, upstream) | **repair the declaration disagreements** in the CANONICAL trees (stage 03 `DEFECTS.json`). The parity agent's type-disagreement pass took the census from 1,014 to **833** (measured by re-running stage 03's own agreement test at HEAD `50929c5d`). | blocking prerequisite for a *blanket* cohesive-TU merge; still the single thing standing between stage 04's 695 translation units and 243. R1 means this work is the parity agent's, not the pipeline's. |
| 04 | **scoped cohesive-TU merge, app core only — DEFAULT IS NOW SUB-BATCH `B`** — maximal ORDER-PRESERVING runs of consecutive retained sources inside one module that provably cannot collide. Seven refusal rules (`type`, `dupdef`, `static`, `typedef`, `macro`, `asmname`, `tag`/`enumconst`, `includes`); quoted repository headers are *read* and folded rather than refused. `A` and `B` now **partition** the clean runs and the R7 gate below charged 100 % of the damage to `A`, so `B` is the default: **1,615 → 700 TUs, 249 merged units, 1,164 files absorbed.** | **the first stage that CANNOT be gated on `cmp zephyr.bin`.** Declared codegen class **`size-changing`**, measured `.text` **−76 B** for `B` alone (−12 B for `A`, −88 B for `AB`) — so **an oracle run is REQUIRED and has NOT been done for `B`**. Reports: `recon/analysis/staged_refactor_stage04.md` (the original AB build), `recon/analysis/stage04_r7_validation.md` (the gate), `recon/analysis/staged_refactor_stage05.md` (the rework). |
| 05 | **cohesive composition, app core only** — turns stage 04's concatenated units into composed ones: one include block per unit (repeats of *provably idempotent* headers withdrawn, never moved — 2,423 → 850 directives, worst unit 49 → 6), one declaration site per symbol per unit (146 duplicates withdrawn), one-line member banners, every `identity:` banner preserved byte for byte. Sub-batch `S` (internal linkage for TU-private symbols: 241 candidates) is opt-in and **not applied**. | declared `size-neutral`, **measured `byte-identical` — `zephyr.bin` `cmp`-identical to stage 04's, 956,276 B.** Needs no oracle of its own; inherits stage 04's unproven status. Report: `recon/analysis/staged_refactor_stage05.md` |
| 06 | **composition depth (LANDED)** — module-private declaration demotion (a generated module-header declaration whose users have collapsed to ONE merged unit moves into that unit, at the include point) and include hoisting (a late `#include` moves to the unit's first block only when no preprocessor directive intervenes AND no identifier in the code it jumps over is a macro of that header, per the measured evidence; a header with no name-level macro evidence is refused). | declared `byte-identical`, **measured `byte-identical` — `cmp`-identical `zephyr.bin`, 956,276 B.** 251 of 285 late includes hoisted; units at exactly one include block **21 → 112**; 4 of 215 module-header declarations demoted (211 genuinely still have ≥2 users). Report: `recon/analysis/staged_refactor_stage06.md` |
| 07 | **internal linkage (BUILT, NOT PROVEN)** — `static` for TU-private symbols, decided by **link evidence** (`recon/refactor/link_evidence.py`: `nm --undefined-only` over all 66 inputs of the app link, archives scanned whole) rather than by a source-text scan. The source scan was wrong on **58 of its 240 candidates**. 137 applied. | declared `size-changing`, measured `size-changing`, `.text` **−276 B**. **Gated by a real link (C6), which caught two hazards no `nm` evidence can see: a `PROVIDE()` in one of the 18 linker fragments the rule had listed 3 of, and 112 `-Wl,--undefined=` gc-roots reached through a `foreach(… IN LISTS …)`.** Side-finding: 120 recovered functions are now provably dead. **Oracle REQUIRED, not run.** |
| 08 | **call-order reordering (LANDED AS A MEASURED NO-OP)** — stable topological sort of a merged unit's member blocks, callee before caller. | declared `size-changing` on principle. Result: **0 units reordered.** The 249 merged units contain **11 internal call edges in total**, all already callee-before-caller; stage 08's tree is byte-for-byte stage 07's. The finding is that stage 04 merges by link-order adjacency, which is nearly orthogonal to call structure. |
| 09 | **call cohesion (BUILT, NOT PROVEN)** — group translation units that CALL ONE ANOTHER inside a module, instead of stage 04's runs of link-order-adjacent sources. First-fit greedy, a call edge required, `t04.conflicts`'s seven rules unchanged and evaluated against every member already in the group. Sub-batch `M` (the no-adjacency ceiling) is opt-in and not the default. | declared `size-changing` / `oracle_required`. **742 → 659 TUs, 55 merged units, 138 absorbed; call edges inside a unit 11 → 85.** Compiles first try after one transformer round; **the link failure it hits is stage 08's own** (see the gate record). **Oracle REQUIRED, not run.** Report: `recon/analysis/staged_refactor_stage09.md` |
| 10 (was 09, was 06) | MMIO accessor macros per width, with a signedness audit | **stage that can change codegen** by value; C8 applies. Stage 02 already reduced 84 accessor spellings to 52, which is the prerequisite. |
| 11 (was 10) | net renaming from upstream-identified symbols | 0 B, gated by a real link (C6) |
| 12 (was 11) | struct typing | the stage that can grow the image; budget it |

---

## Commands

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

$V recon/refactor/driver.py input-set            # what the pipeline may transform
$V recon/refactor/driver.py materialize 0        # snapshot
$V recon/refactor/driver.py materialize 1        # stage 01 = transformer(stage 00)
$V recon/refactor/driver.py status               # staleness, per stage
$V recon/refactor/driver.py check-addresses 0 1  # address-set integrity; exit 1 on drift
$V -m unittest discover -s recon/refactor -p 'test_*.py'

# build a stage exactly as the repo builds -- no build-file edit anywhere
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-stage01-app
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh \
    net /private/tmp/g1-stage01-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

## Staleness and repair

A stage is **stale iff an input's content hash differs from the hash recorded in
its `MANIFEST.json`.** `driver.py status` reports which inputs moved. The repair
is always `driver.py materialize N` — regenerate, then re-run the gates. It is
never a hand patch, and a stage tree is never edited in place.

Because the concurrent parity agent edits `recon/symbolized/**`,
`recon/application/**` and `recon/symbols/**` continuously, expect stage 00 to go
stale routinely. That is the mechanism working, not a problem.

## How a stage is built

`tree/` is a **complete buildable repository root**: transformed files are real
files, everything else the build needs is a relative symlink back into the
repository, and `.venv` is symlinked so `build_cohesive.sh` finds it. No build
file, linker script or `tools/` module is edited to build a stage.

`driver.FORCE_REAL_DIRS` lists ten directories that must be *real* directories in
a stage tree because a relative `..` traversal starts inside them
(`recon/generated/*.cmake` spells its sources `${CMAKE_CURRENT_LIST_DIR}/../symbolized/...`,
and the symbolized sources `#include "../../headers/g1_log.h"`). If one of those
were a symlink, the OS's *physical* `..` resolution would escape the stage tree
and silently compile the LIVE repository — a silent-wrong failure. The mechanism
is validated by building stage 00 and `cmp`-ing its `zephyr.bin` against the
in-tree build.

---

## R7 GATE RECORD — the behavioural validation, run 2026-07-27

Stages 01 and 02 had never been run against the emulator oracle; the pipeline
had no behavioural evidence at all. It now does. Full working:
`recon/analysis/staged_refactor_r7_validation.md`.

**Inputs.** HEAD `a2f3303d` ("P4 iter-40"), working tree clean. Stage 00 was
**stale** (12 inputs moved by iterations 39/40 — 10 symbolized sources plus
`g1_app_globals.ld` / `g1_app_symbols.h`); stages 00 → 01 → 02 were
**regenerated**, never patched, in **zero** transformer rounds. Transformation
output was unchanged (100 candidates / 178 sites; 3,116 + 45 + 266 + 135 + 2
sites over 714 files); only `file_count` 2,612 → 2,619,
`retained_sources.app` 1,609 → 1,615 and
`A_volatile_spelling.total_accessor_sites_seen` 6,069 → 6,078 moved. The nine
new accessor sites are all already canonically spelled, hence 0 new rewrites.
`check-addresses 0 1` and `1 2`: identical, **2,567** addresses (was 2,561; +6
= iteration 40's six recovered WLC NDEF ops).

**What was compared, against what.** Seven Renode captures via
`recon/emulator/scripts/capture_display_sensor_oracle.sh`, both screens, three
way: the **shipped-firmware oracles**
(`display_sensor_oracle.json`, `display_sensor_oracle_dashboard.json`) — the
real R7 bar — the **current in-tree build**, and the **Stage 02 build**. The
in-tree app image is `cmp`-identical to `g1-i40d-app`; the net image is
`cmp`-identical to `g1-i30e-net` and to the Stage 02 net image, so one net
binary was booted in every run.

**Result.**

| | verdict |
|---|---|
| **dashboard `p2_render` framebuffer** | `19b1f24a09f97a8d…`, 2,923 lit px — **PASS**, 153,600 B byte-identical to the in-tree build |
| **dashboard `p1_boot` framebuffer** | `0c5cc90b079d0d9c…` all-zero — **PASS** |
| **navigation `p2_render` framebuffer** | `b26c73b37d441fc8…`, 1,098 lit px — **PASS** |
| **navigation `p1_boot` framebuffer** | `1d617c65a688f10e…`, 656 lit px — **PASS** |
| D-3, D-5, D-6, D-7, G-6, S-ESB, S-MIC, S-KEYS, S-PMIC, S-NFC, S-ALS, dashboard S-IMU `p1_boot` | **PASS**, Stage 02 stream-identical to the in-tree build |
| every remaining NE (`spim_a` navigation = **G-3**, `saadc` stream sha, `twim1`/`twim2` `p2_render`) | **pre-existing gap** — the in-tree build differs from the shipped oracle in exactly the same way, byte for byte |
| **refactor regressions** | **NONE** |

**Why "none" is defensible rather than convenient.** Stage 02's `zephyr.bin` is
`cmp`-identical to Stage 01's on **both** cores, its ELF symbol table diffs to
0 lines, and 3,130 of 3,132 objects are byte-identical (the 2 are the known
`remoteproc_virtio` / `uname` stock churn units). Against the in-tree build,
disassembling both linked ELFs end to end gives 179,900 vs 179,899 entries whose
**only** histogram difference is one `.word` — a literal-pool data word.
Sections: `.text` −4 B, `.rodata` −120 B, `.text` base unchanged at `0x0000c358`.
There is no instruction Stage 02 executes differently.

**One apparent regression was investigated and disproved.** Navigation
`twim2 p1_boot` (LSM6DSO, S-IMU) was EQ vs shipped on the in-tree build and NE
on Stage 02, at identical 1,089 transactions, differing only in where one
4-transaction poll pair sat relative to a periodic ODR-reconfiguration block.
Double-running both images showed **each image produces both outcomes**: in-tree
EQ then NE, Stage 02 NE then **EQ**; the same in-tree image also gave OPT3001
`p1_boot` 33 then 35. That stream is **bistable for our rebuilt images under the
navigation stimulus**, contradicting `display_sensor_parity.md` §2.1 (which
measured determinism on the *shipped* images), and it retro-corrects
`our_boot_bringup.md` §40.13 item 5. Treat navigation `twim2 p1_boot` and the
merged/OPT3001 `twim1 p1_boot` as multi-run criteria until the capture is made
reproducible. Dashboard streams, both cores' framebuffers, `spim_a`, `saadc`,
`pdm0`, `gpiote*`, nPM1300 and both ST25DV ports were stable across every run.

**Non-emulator ladder, all re-run at these inputs:** app/net builds exit 0 first
try; app FLASH 954,912 B (97.19 %, Δ −136 B vs the in-tree 955,048 B); `.text`
Δ −124 B; RAM Δ 0 and RAM layout 0 diff lines; net frozen at 225,581 B /
63,380 B with a byte-identical image; `nm -u` 0/0; duplicate globals 0/0;
warnings 1,887 app / 1,066 net (Δ 0); `.rodata` vs `app_update.bin` 1,325 match
/ 14 mismatch (the same 14, name for name; the in-tree build is 1,424 / 14 — the
−99 is the withdrawn objects that were live in the link);
`check_ram_pin_collisions` app 627 bound / 0 / 0 and net 170 / 0 / 0;
`check_net_raw_literals` 983 TUs 0/0/0/0/0; `verify_net_stock_data_window`
**PROVEN** (93 differing words all flash pointers, 0 otherwise, 0 non-stock
sections); `check_thread_create_stack_args --trials 120` 10/10;
`gen_retained_sources.py --check` current; `test_guard`/refactor suite 7/7.

### Reproducing the R7 gate

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py materialize 0 && $V recon/refactor/driver.py materialize 1 \
  && $V recon/refactor/driver.py materialize 2
./recon/application/build_cohesive.sh                                            app /private/tmp/g1-r7-base-app
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   app /private/tmp/g1-r7-s2-app

# probe values MUST be re-read from the ELF actually booted:
#   arm-zephyr-eabi-nm zephyr.elf | grep -wE 'runtime_info_sync|_end'
#   device ctx = align16(_end);  +0xd5 / +0xfe8 / +0x105a
printf '$rtinfo_pc=0x00015bc8\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-r7/ours-paired.resc

# one capture (dashboard = G1_ATT_WRITE=""; navigation = leave it unset).
# The mkfifo writer is required: Renode's ConsoleIOSource aborts without stdin.
bash -c 'F=$(mktemp -u); mkfifo $F; sleep 100000 > $F & W=$!
G1_ATT_WRITE="" G1_RESC=/private/tmp/g1-r7/ours-paired.resc \
G1_APP_ELF=/private/tmp/g1-r7-s2-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-r7-base-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_r7_s2_dash < $F
kill $W; rm -f $F'
$V recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_r7_s2_dash /private/tmp/g1-r7/rep-s2_dash

# three-way diff (shipped vs in-tree vs stage): /private/tmp/g1-r7/cmp3.py in the
# pass's scratch, reproduced in recon/analysis/staged_refactor_r7_validation.md
```

**Run every navigation capture at least twice.** A single-run EQ/NE on
navigation `twim2 p1_boot` or `twim1 p1_boot` is not evidence.
*(**Superseded by the Stage 04 gate record below.** That instruction was written
from UNSEEDED double-runs. With `emulation SetSeed` pinned — which
`capture_display_sensor_oracle.sh` now does by default — run 1 and run 2 of the
same image give a byte-identical regenerated oracle directory, measured on four
images. Still run twice as a cheap determinism check, but a single seeded run on
these two streams **is** evidence.)*

**`$rtinfo_pc` must be re-read from the ELF actually booted.** Stage 04 moves
`runtime_info_sync` from `0x00015c04` to `0x0001632c`; the value hard-coded in
every earlier recipe is wrong for that image. `_end` is unchanged
(`0x2003ff45`), so the three RAM probe addresses carry over.

**Timing note on that record.** All Stage 02 builds and all six our-build
captures completed by 04:15:48; the concurrent parity agent landed a ~1,800-file
batch at 04:19:48 which moved **75** pipeline inputs and made stage 00 stale
again. Nothing in the record was measured against a moving input, but the stages
must be regenerated before the next measurement. The R7 verdict above stands for
the inputs it names (HEAD `a2f3303d`, clean tree); re-running it after that batch
is the next stage's first job, not a repair of this one.

---

## R7 GATE RECORD — STAGE 04, run 2026-07-27

Stage 04 is the first stage whose image cannot be gated on `cmp zephyr.bin`, and
its own report (`recon/analysis/staged_refactor_stage04.md` §7.3) stated plainly
that the oracle was REQUIRED and had not been run. It has now been run. Full
working: **`recon/analysis/stage04_r7_validation.md`**.

**Inputs.** HEAD `3b8242fa` ("refactor Stage 04"), working tree clean except an
unrelated untracked `.xapk`. `driver.py status`: stages **00–04 all current**
(2,629 inputs unchanged, 0 changed) — nothing needed regenerating. Stage 99 left
stale (the retired diagnostic probe). `check-addresses` 0-1, 1-2, 2-3, 3-4 all
identical at **2,567** addresses; refactor suite **58/58**. Materialising
sub-batch A and then restoring AB reproduced `MANIFEST.json` sha `d0e66ecd…`
byte-identically.

**Three images, and each has its OWN `$rtinfo_pc`** — the stage-04 report knew
about two of the three:

| image | FLASH | `runtime_info_sync` | `_end` |
|---|---:|---|---|
| in-tree HEAD (`cmp`-identical to iteration 42's `g1-i42d-app`) | 956,480 B | `0x00015c04` | `0x2003ff45` |
| stage 04 **sub-batch A** | 956,340 B | **`0x00015c0c`** | `0x2003ff45` |
| stage 04 **sub-batch AB** (`cmp`-identical to the stage report's `g1-s4-app`) | 956,244 B | `0x0001632c` | `0x2003ff45` |

**Nine seeded captures** (`G1_SEED=305419896`), three images × {navigation ×2,
dashboard}, against the seeded shipped oracles, compared three ways per C7:
stage vs shipped (the bar) and in-tree vs shipped (to separate pre-existing gaps
from refactor damage).

### Result — **STAGE 04 FAILS R7 ON BOTH SUB-BATCHES**

| | verdict |
|---|---|
| **all four acceptance framebuffers, both sub-batches** | **PASS** — `1d617c65…` / `b26c73b3…` / all-zero / `19b1f24a…`, `cmp` exit 0, 153,600 B each. Twelve of twelve across the three images. |
| `SCREEN_ID` `0x0A`/`0x06`, `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02` | **PASS** on every image |
| navigation `spim_a` whole run 3,645; `twim1 p2_render` 599 with all four per-device streams; `JBD_FRAMECOUNTER_P2` `0x0D61`; every dashboard criterion iteration 42 made byte-exact | **HOLD** |
| **navigation `twim1 p1_boot`** 371 → **373** (OPT3001 33 → **35**, its sha, the merged-bus sha) | **REGRESSION** |
| **navigation `twim2 p1_boot`** 1,089 → 1,089 but `7ed8ddcd0c0d420d…` → **`03537cda890a2b7d…`** (and `regprog`) | **REGRESSION** |
| `counters/RADIO_TX` `0x232` → `0x233` (A) / `0x234` (AB), both stimuli | **REGRESSION** |
| every other NE (dashboard `spim_a p2_render`, nPM1300 −14, `ESB_*` +1, `spim_a` p1/p2 split, `JBD_FRAMECOUNTER_P1`, `VC_DATA_EVENTS`) | **pre-existing** — the in-tree build differs from shipped identically or in the same direction; stage 04 makes none of them worse |

**The eight regressions are IDENTICAL between sub-batch A and sub-batch AB.**
Comparing AB against A gives **0 regressions and 2 improvements** (`twim2
p2_render` becomes byte-equal to shipped on both stimuli). So sub-batch B — 271
further merged units, 1,087 more files, a further −96 B of `.text` — introduces
nothing, and **100 % of the damage is sub-batch A**, whose entire codegen delta
is **−16 B and two functions** (`k_uptime_get_3` 28 → 4 B, `__ieee754_pow`
2,480 → 2,488 B). The R8 "no `volatile` in any member" argument that made A the
low-risk half is not refuted — the failure is not a volatile reordering — it is
simply irrelevant, because the mechanism is linked size, not access ordering.

**Both regressions are re-phasings, decoded transaction by transaction.**
OPT3001: the first 33 transactions are identical and in order, the poll *period*
is unchanged to 30 ns, but the train's phase moves **−100.7 ms** and one extra
poll fits inside the 6 s window. LSM6DSO: one 4-transaction poll pair rotates
from index 99 to the tail of an otherwise identical 1,089-transaction stream.
Content-identical, order-different — and C7 gates order.

### Two corrections to the R7 gate record above

1. **The navigation "bistability" is withdrawn.** That record instructs treating
   navigation `twim2 p1_boot` and `twim1 p1_boot` as multi-run criteria because
   "each image produces both outcomes". Measured here with the seed pinned, run 1
   vs run 2 of the *same* image gives a **byte-identical regenerated oracle
   directory** — for the shipped image, the in-tree build, sub-batch A and
   sub-batch AB alike. The bistability was the unseeded net-core RNG (iteration
   41's finding), not a property of the stream. A single **seeded** run is
   evidence now, and a difference on these streams can no longer be excused.
2. Consequently the record's "one apparent regression was investigated and
   disproved" paragraph rested on unseeded double-runs. Its Stage 02 conclusion
   is not overturned by anything measured here — Stage 02's image is
   `cmp`-identical to Stage 01's on both cores — but the reasoning it used is no
   longer available to a later stage.

### ACTED ON, 2026-07-27 — the stage was reworked, not bisected

`recon/analysis/staged_refactor_stage05.md` reworked stage 04 on this evidence
**as a transformer change and a regeneration**, never a hand-edit: `A` and `B`
now partition the clean runs and **`B` is the default**. Measured at HEAD
`ff99f0c6` after regeneration (653 inputs had moved), `.text` is **−12 B for A,
−76 B for B, −88 B for AB** — additive to the byte — so **a B-only stage is NOT
size-neutral and the oracle is still REQUIRED**. B carries 918 of the 1,019 TU
reduction (90 % of the yield) for a tenth of the units. The `volatile` token
turned out to partition *shape*, not risk: this corpus models every global as a
`volatile` pointer, so the files WITHOUT the token are the pure computational
leaves and forwarding thunks — exactly the ones whose merging collapses a
28-byte thunk into a 4-byte tail branch. See also **C7b**, which turns
size-neutrality into a declared, checked stage property so the next such finding
costs a build rather than nine Renode captures.

### Original recommendation (superseded above for the A/B decision, still binding on everything else)

**Do not land stage 04 in this form**, and do not bisect sub-batch A looking for
a bad unit: there is no bad unit, the mechanism is the linked size of the boot
path, and any merge that changes it will reproduce this. Either fix the boot-path
timing gap first (our build is +3.45 ms / +6.4 ms late to the first bus
transaction; `stage04_r7_validation.md` §4.3 shows the +3.45 ms half is *not*
codegen-carried), or re-baseline these two `p1_boot` streams deliberately, with
the decoded diffs as the record of what was given up. Not by widening a
tolerance.

### Reproducing the Stage 04 R7 gate

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py status                       # expect 00-04 current
./recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-base-app
G1_STAGE04_BATCH=A $V recon/refactor/driver.py materialize 4
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-A-app
$V recon/refactor/driver.py materialize 4                # back to AB
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-AB-app

# $rtinfo_pc PER IMAGE -- there are THREE different values, re-read every one:
#   arm-zephyr-eabi-nm zephyr.elf | grep -wE 'runtime_info_sync|_end'
# capture: /private/tmp/g1-s4r7/cap.sh <tag> <build-dir> <rtinfo_pc> <nav|dash>
#   ALWAYS seeded (the script defaults G1_SEED=305419896); navigation twice.
$V recon/emulator/scripts/build_display_sensor_oracle.py                    <cap> <rep>   # navigation
$V recon/emulator/scripts/build_display_sensor_oracle.py --screen=dashboard <cap> <rep>   # dashboard
$V /private/tmp/g1-s4r7/cmp3.py <shipped.json> <base.json> <stage.json> LABEL
```

**`build_display_sensor_oracle.py` now takes `--screen=dashboard`** (default
`navigation`), so the dashboard oracle can be regenerated without hand-merging.
The navigation path is a measured strict no-op: pre- and post-change scripts run
over the same capture produce `diff -r`-identical report directories.

### Stage 04 gate side-finding: `DEFECTS.json` is a defect list, not just a merge blocker

Chasing the dashboard `spim_a p2_render` gap during the Stage 04 gate produced a
result that changes how the stage-03 census should be read. The gap is 2,958
missing SPI pixel windows caused by **one missing argument**:
`recon/symbolized/app/errno_wrapped_tick_call.c` calls
`rate_limited_elapsed_seconds_tick(param_2, 0)` where the shipped image passes
three arguments (`movs r2,#0` at `0x7d1ec` is absent from our codegen), so the
callee takes its RESET-ONLY arm and the only `*param_1 += elapsed_seconds` in
the image never runs. Our device clock is frozen at the 2024-01-01 epoch for the
entire run, `notify_display_mode` therefore never fires after boot, and
`DashBoard_Reflash` is called with `param_3 == 1` **4** times against the shipped
**11** (measured with a Renode PC hook on both images).

**That defect is already in
`recon/refactor/stage_03_module_structure/DEFECTS.json`**, as
`declaration_disagrees_with_definition` on `rate_limited_elapsed_seconds_tick`
with both prototypes spelled out. It was filed as one of the 833 merge blockers
"worth 452 translation units" and has sat unactioned since stage 03. The `type`
refusal rule correctly kept those two files out of one TU — which is exactly why
the compiler was never allowed to see the contradiction.

Read the census accordingly: the `arity_differs` and
`declaration_disagrees_with_definition`-against-own-definition entries are
candidate **firmware defects** that the parity harness structurally cannot see
(it constrains the function body, not the argument registers at an outgoing
`bl`; the defective file's banner still reads `parity: 300/300 trials, PROVEN`).
Repairing them arity-first was already README stage-03b work for merge yield; it
should be re-prioritised as a defect hunt. Full working and the falsifiable
prediction for the fix: `recon/analysis/stage04_r7_validation.md` §8.

---

## R7 GATE RECORD — STAGE 04 SUB-BATCH **B** (and STAGE 05), run 2026-07-27

The record above ends by making `B` the default on the evidence that 100 % of
sub-batch A's damage was A's and that AB-against-A gave 0 regressions, while
recording that **a B-only image had never been booted** and that its `.text`
delta (−76 B) is five to six times the A delta that broke eight fields. It has
now been booted. Full working: **`recon/analysis/stage04b_r7_validation.md`**.

**Inputs.** HEAD `fc11c2c8` ("P4 iter-43: the frozen-clock fix lands"), working
tree clean except the unrelated untracked `.xapk`. `driver.py status`: stage 00
**stale** on **3** inputs — iteration 43 §43.13's four `memcpy`-length repairs in
`clear_timeout_message.c`, `confirm_message.c`,
`post_notification_cmd_process.c`. Stages 00 → 05 were **regenerated, never
patched**, and **every transformer output is unchanged field for field**: 249
merged units absorbing 1,164 files, 1,573 duplicate includes withdrawn, 146
duplicate declarations, 218 hoists, 19 module headers.
`DEFECTS.json` 930 → **940**. `check-addresses` 0-1 … 4-5 all identical at
**2,567**; refactor suite **105/105**; stages 04 and 05 both byte-idempotent
(manifest *and* whole tree).

One consequence of iteration 43 is worth naming: `errno_wrapped_tick_call.c` and
`rate_limited_elapsed_seconds_tick.c` are now in **one** merged unit
(`ble/g1_ble_12.c`). The stage-04 `type` refusal rule had kept them apart, which
is precisely why the compiler was never allowed to see the contradiction that
froze the device clock. Repairing the declaration lapsed the refusal.

**Four images**, all built with the repository's own entry point:

| image | FLASH | `text` | `runtime_info_sync` |
|---|---:|---:|---|
| in-tree HEAD (`cmp`-identical to iteration 43's `g1-i43b-app`) | 956,480 B | 492,692 | `0x00015c04` |
| stage 03 | 956,356 B | 492,688 | `0x00015c04` |
| **stage 04 sub-batch B** | **956,276 B** | **492,612** | **`0x00016c14`** |
| **stage 05** (`cmp`-identical to stage 04's `zephyr.bin`) | 956,276 B | 492,612 | `0x00016c14` |

**`$rtinfo_pc` is `0x00016c14` for stage 04-B — a FIFTH distinct value.**
`size-gate 4` measured `size-changing` as declared, `text` **−76 B**, everything
else Δ 0; `size-gate 5` measured **`byte-identical`**, so the stage-04 capture
covers stage 05 exactly — re-verified after regeneration rather than assumed.

**Six seeded captures** (`G1_SEED=305419896`), `$rtinfo_pc` re-read per image:
stage 04-B nav ×2 + dash, in-tree base nav + dash, and **stage 03 nav** (new —
it is what brackets the threshold). Run 1 vs run 2 of stage 04-B navigation gave
a `diff -r`-identical regenerated oracle directory.

**A correction that had to be made first: the committed navigation shipped
oracle is STALE.** `recon/emulator/reports/display_sensor_oracle.json` differs
from a regeneration of the seeded shipped capture in **8 of 69 fields**
(`RADIO_TX` `0x230` vs `0x232`, `VC_DATA_EVENTS`, `twim1 p1_boot`/`p2_render`
sha, the `saadc` pointer canonicalisation, and three fields it does not carry at
all). Comparing against it would have scored two of the failures below as
pre-existing gaps. The **dashboard** oracle is current (0 of 69). Everything
below is measured against the seeded regeneration. *The navigation oracle was
deliberately NOT regenerated in this pass — see the report's §6 item 4.*

### Result — **STAGE 04 SUB-BATCH B FAILS R7, ON THE SAME EIGHT FIELDS AS A**

| | verdict |
|---|---|
| **all four acceptance framebuffers, both stimuli** | **PASS** — `1d617c65…` 656 px / `b26c73b3…` 1,098 px / `0c5cc90b…` all-zero / `19b1f24a…` 2,923 px, `cmp` exit 0, 153,600 B each |
| `SCREEN_ID` `0x0A`/`0x06`, `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02` | **PASS** on every image |
| navigation `spim_a` whole run 3,645; `twim1 p2_render` 599 with all four per-device streams; `JBD_FRAMECOUNTER_P2` `0x0D61`; every dashboard number iteration 43 moved (`spim_a p2_render` 12,289, `JBD_FRAMECOUNTER_P2` `0x2EA3`, `twim1 p2_render` 584 / nPM1300 514 — bit-identical between base and stage) | **HOLD** |
| **navigation `twim1 p1_boot`** 371 → **373** (OPT3001 33 → **35**, its sha, the merged-bus sha) | **REGRESSION** |
| **navigation `twim2 p1_boot`** 1,089 → 1,089 but `7ed8ddcd0c0d420d…` → **`03537cda890a2b7d…`** (and `regprog`) | **REGRESSION** |
| **`counters/RADIO_TX`** `0x232` → **`0x234`** navigation, **`0x235`** dashboard | **REGRESSION** |
| `twim2 p2_render` NE → byte-equal with shipped on both stimuli | improvement, reported not celebrated — same phase mechanism landing right |
| every other NE | **pre-existing** — identical on base and stage, or moved toward shipped |

**Every failing hash is byte-for-byte the value sub-batch A produced.** Not the
same kind of failure — the same failure. AB-against-A had measured B's
*incremental* effect on top of an A that had already moved the thread; B on its
own moves it identically.

### The mechanism, and why it retires two earlier recommendations

The OPT3001 poll train's first steady-state poll, from `twim1.p1.trace` ticks:

| image | `text` Δ vs in-tree | poll #13 | polls in `p1_boot` | whole-run |
|---|---:|---|---:|---:|
| shipped | — | 4.295530 s | 17 (33 tx) | 113 |
| in-tree base | 0 | 4.304170 s | 17 (33) | 113 |
| **stage 03** | **−4** | **4.304200 s** | 17 (33) | 113 |
| stage 04 A | −16 | 4.203950 s | **18 (35)** | 115 |
| **stage 04 B** | **−80** | **4.203650 s** | **18 (35)** | **115** |
| stage 04 AB | −92 | 4.203460 s | **18 (35)** | 115 |

**There are exactly two slots, 100.5 ms apart.** Three images spanning −16 B to
−92 B land in the earlier one within **0.5 ms of each other**; stage 03 at −4 B
stays in the base slot within 0.03 ms. The `twim2` regression is the *same*
100.51 ms step of a periodic ODR-reconfiguration block (only 18 of 1,089
canonical lines differ, all between indices 967 and 984; whole-run LSM6DSO is
**2,289 on shipped and on every one of our images**). **The displacement is
quantised, not proportional to linked size.**

And the margin: the OPT3001 period is 350.31 ms, `p1_boot` ends at 6.000 s, so
the in-tree build is **55.6 ms** from gaining an 18th poll — and **the shipped
firmware itself is only 46.8 ms from it**, 0.78 % of the phase.

> **The step (100.5 ms) is larger than the margin (55.6 ms). There is no landing
> between the two slots.**

1. **A size-compensating measure is refuted, not merely unattractive.** No pad
   size lands between the slots; the only compensation that works is
   byte-identity, which for a merge stage means not merging.
2. **The A/AB record's recommendation 1 — "fix the boot-path timing gap first" —
   is also refuted.** The gap is 3.45 ms and the step is 100.5 ms, a factor of
   29; closing the whole gap moves the train under 4 % of one step. Iteration 43
   showed the converse: a **+2 B** relink that moved 1,000 text symbols left all
   69 navigation fields bit-identical.

So the live options are the A/AB record's option 2 (re-baseline these streams
deliberately, with the decoded diffs as the record of what was given up), or a
phase-tolerant criterion published **together with the class of defect it would
stop catching** (a wrong sleep constant / dropped tick / priority inversion is
exactly a 100 ms-class phase move). **Neither was taken in this pass and no
tolerance was widened.** `"oracle_required": true` in stage 04's manifest is
**not** discharged: the oracle ran and the stage failed it.

### Stage 05

`zephyr.bin` `cmp`-identical to stage 04-B's at **956,276 B**, `size-gate 5`
`byte-identical`, all sections Δ 0. Its composition work costs nothing
observable and it **inherits stage 04's failure exactly**.

### Two transient integrity failures — cause: a SECOND WRITER in this directory

* `materialize 4` once produced a tree **missing merged-unit files its own
  manifest listed** — `"parity_rows": 2473` instead of 2,567 — and `materialize
  5` died on the first missing file. It did not reproduce. `check-addresses 3 4`
  would have caught it; `materialize` does not run that check itself, so a
  last-in-chain stage would have been built and captured 94 functions short in
  silence.
* The first stage-04 `build_cohesive.sh` failed with `discovery_callback.c`
  compiled at **`-std=c99`** — the exact C2 hazard — although `CMakeLists.txt`
  is sha-identical across the stage 03/04/05 trees and carries the correct
  post-stage-03 path, the source is sha-identical across all three, and stages
  03 and 05 built it clean minutes either side. A clean rebuild of the same tree
  gave exit 0.

**Both are explained, and the explanation is a gap in the contract.** `ls -lT`
shows `transforms/t03_module_structure.py` rewritten at **11:56:15**, inside my
stage-03/stage-04 build window — the failing build was the one running at that
instant — with `stagelib.py`, `sdk_symbols.py`, `driver.py` and the new stages
06–08 landing 12:03–12:22. **A second agent was editing this pipeline while it
ran.** C1 protects the canonical trees *from* the pipeline; nothing protects the
pipeline *from* a second writer, and the two failure modes it produced were a
tree silently 94 functions short and a compile error that reads exactly like a
transformer bug.

Two consequences worth carrying forward:

* **C4's "a compile failure in a stage tree is proof the transformer is wrong"
  holds only when nobody else is writing the transformer.** Check `git status`
  and file mtimes, and rebuild once from a clean build directory, before
  invoking it.
* **`materialize` should assert its own `parity_rows` against
  `check-addresses`.** The 2,473-vs-2,567 corruption surfaced only because the
  *next* stage crashed on it.

Everything this record reports was re-verified afterwards: stages 4 and 5
re-materialised **byte-identically** (manifest and whole tree), and stages 03
and 04 were **rebuilt from the post-edit trees with `cmp`-identical
`zephyr.bin`** — so the captured images are exactly what the trees produce.

### Reproducing

See `recon/analysis/stage04b_r7_validation.md` §8. The one thing that will bite:
**the shipped navigation reference must be regenerated from
`/private/tmp/g1_ship_seed_q1`, not read from the committed
`display_sensor_oracle.json`.**

---

## R7 GATE RECORD — THE PHASE-TOLERANT CRITERION, and stages 01-07 re-run, 2026-07-27

The record above left stage 04 failing on eight navigation fields that are
**content-identical and order-identical within each poll train**, and named two
live options. The owner chose the **phase-tolerant criterion**, explicitly in
preference to re-baselining the two `p1_boot` streams, on the ground that it
**keeps both streams gated** rather than exempting them. It is now implemented,
its bound is derived from measurement, and stages 01-07 are re-run against it.
Full working: **`recon/analysis/phase_tolerant_criterion.md`**.

**Inputs.** HEAD `3d3ee155`, working tree clean except the unrelated untracked
`.xapk`. `driver.py status`: stages **00-08 all current** at the start. Stage
trees as materialised by the stage04b pass (11:48-12:26). *The concurrent parity
agent moved **104** inputs at 13:02:49 — after every build in this record
completed (12:55:23 … 13:01:46). Stage 00 is stale again; regenerate before the
next measurement.*

**Three images cover stages 01-07** — measured with `cmp`, not assumed:

| image | FLASH | `text` Δ vs in-tree | `runtime_info_sync` |
|---|---:|---:|---|
| in-tree base | 956,480 B | 0 | `0x00015c04` |
| **stage 01 = 02 = 03** (`cmp`-identical) | 956,356 B | −4 | `0x00015c04` |
| **stage 04-B = 05 = 06** (`cmp`-identical) | 956,276 B | −80 | `0x00016c14` |
| **stage 07** | **955,996 B** | **−356** | `0x00016c14` (the *same* fifth value, not a sixth) |

`size-gate 6` measured **byte-identical** as declared; `size-gate 7` measured
`size-changing`, `text` **−276 B**, `rodata` **−8 B**, `oracle_required` true.
Only stage 07 needed new Renode runs: three seeded captures (nav ×2, dash),
`diff -r`-identical between the two navigation runs.

### The criterion

`recon/emulator/scripts/phase_tolerant_compare.py`, fed by an **additive**
`peripherals/<bus>/whole_run_trains` block that
`build_display_sensor_oracle.py` now writes. **No pre-existing oracle field
changed value** — proved by regenerating the dashboard oracle and diffing:
`CHANGED: 0`, `ADDED: 444`, all 444 in the new block.

* **burst** — consecutive transactions on one `(bus, device)` at most
  `BURST_GAP_NS = 5 ms` apart. The gap distribution is bimodal and the
  separation is **asserted per capture** (`gap_separation.separated`), because
  the valley is only ~1 ms wide on `spim_a` and `twim1` npm1300.
* **train** — bursts sharing one **register-programme** key: every *write*
  payload verbatim, every *read* reduced to `(register, payload length)`.
  A write payload is the firmware talking; a read payload is the model talking.
  Keying on full content instead put `npm1300` bursts in different trains as its
  charger-state register stepped, and produced `δ = −3,706 ms` on a
  population-equal train **between shipped and our accepted base**.
* **P1** the set of train keys must be identical — a changed register, write
  payload, read length or burst shape fails.
* **P2** per-train burst populations must be equal, or differ only by bursts the
  20 s observation wall clipped, checked by extrapolating **the train's own
  measured median period** across the wall. This is the count effect handled by
  construction, not by a widened tolerance.
* **P3** `|starts_ns[i] ours − shipped| ≤ Δ`, on bursts whose correspondence is
  unambiguous (`|δ_i|` below half the local period; above that the measurement
  does not exist and is reported as such, with content and population still
  gated).
* **P4** cadence is gated **through** P3: a period error `e` accumulates to
  `|δ| > Δ` after `⌈Δ/e⌉` bursts — on the 45-burst OPT3001 train that is a
  **0.94 %** period error.
* **P5** an order inversion between two bursts more than Δ apart in the shipped
  run fails. Ordering is enforced through time, not through index.
* **P0** (added after it fired) a train that appears only in ours and whose key
  *begins* with another train's key is a **shared-bus burst merge** — a
  criterion artifact — and is named as such rather than counted as content.

### The bound, derived before any stage was compared

> Δ = the maximum `|δ|` over **phase-measurable** trains between the **shipped
> firmware** and **our in-tree build**, over both stimuli and every traced bus.

**Δ = 145.440 ms.** It comes from four navigation display-animation trains of
22-transaction pixel-window bursts with a **2,265.1 ms** minimum period, so the
correspondence is forced, not chosen:

```
shipped 5.620470  7.885550  10.150620  12.588180
ours    5.583150  7.848230  10.113330  12.442740
delta    -37.320   -37.320    -37.290   -145.440 ms
```

Three cycles in lock-step, then one **−108.15 ms slip**. The justification for
treating that as not-a-difference is the strongest in the project: on this very
stream whole-run `spim_a` is **3,645 == 3,645** and **all four framebuffers are
byte-identical to the goldens**. A 145 ms slip changes not one pixel.

**Rejected derivations, with their numbers.** The codegen noise floor
(base ↔ stage 03 = **1.226 ms**) makes the base itself fail every stream — a
blind gate, not a strict one. A scheduler-quantum derivation was abandoned
because the ≈100.5 ms step could not be tied to a mechanism:
`CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768` (30.5 µs), the virtual central's
connection interval is 30 ms with `SweepDwell 4` = 120 ms, and **no traced
peripheral has a ≈100.5 ms cadence**.

**The bound is not rounded up**, so the base sits exactly at it with zero
headroom, and §4.4 of the report publishes the whole ladder at the rejected
Δ = 45.870 ms as well.

### Result

| stage | strict `cmp3` | **phase-tolerant, Δ = 145.440 ms** |
|---|---|---|
| **01 / 02 / 03** | 0 regressions | **PASS** — 0 regressions, 0 pre-existing-but-worse |
| **04-B / 05 / 06** | 8 regressions nav, 1 dash | **PASS on every gated stream** — 0 regressions both stimuli; **2 pre-existing-but-worse on navigation** |
| **07** | 9 regressions nav / 4 dash, **4 improvements each** | **PASS on every gated stream** — 0 regressions both stimuli; **2 pre-existing-but-worse on navigation** |

**All four acceptance framebuffers byte-identical to the committed goldens on
every image measured** (base, 03, 04-B, 07), 153,600 B each, `cmp` exit 0.

**A criterion change that flipped a passing stage would be a bug in the
criterion. It flips none:** stages 01/02/03 are clean under the new criterion,
and the four streams the base passes — `twim1 opt3001`, both ST25DV ports and
`twim2 lsm6dso` — still pass on every stage and both stimuli.

**Seven of the eight stage-04-B strict regressions are absorbed as phase**
(the OPT3001 wall-clipped burst, the LSM6DSO ODR block crossing one poll burst,
and the merged `twim1` bus hash the oracle already flags as unstable).
**The eighth, `counters/RADIO_TX`, is NOT absorbed — it is outside the
criterion entirely** and stays strictly gated and failing.

**What is not phase, and is charged:** on navigation, `spim_a` gains
**21 `P3` failures** and its peak `|δ|` goes 145.440 → **245.780 ms** (stage
04-B) / **281.670 ms** (stage 07), on a stream that already fails `P1 content`
for the §41 one-extra-frame residue. The criterion says so rather than hiding
it in a "pre-existing" bucket.

### Stage 07 also CLOSES three long-standing gaps

```
counters/ESB_MASTER_FRAMES   ship 0x175  base 0x176  S07 0x175  == shipped (both stimuli)
counters/ESB_ACKS            ship 0x175  base 0x176  S07 0x175  == shipped
counters/JBD_FRAMECOUNTER_P2 ship 0x2E65 base 0x2EA3 S07 0x2E65 == shipped (dashboard)
spim_a/p2_render/count       ship 12225  base 12289  S07 12225  == shipped (dashboard)
```

The `ESB_*` `+1` is iteration 43 §43.11's open item, left "untouched with its
falsification test unrun" by the stage04b record. **A −276 B relink closes it.**
Reported, not celebrated — the same mechanism moves everything else.

### The §9 prediction: 5 of 6 confirmed, 1 falsified

`stage04b_r7_validation.md` §9 predicted stage 07's capture in advance.
Confirmed: `twim1 p1_boot` **373**, OPT3001 **35** and sha `b759ccc5…`,
`twim2 p1_boot` sha `03537cda…` and `regprog` `6d3c4072…`, OPT3001 poll #13 in
the **earlier slot** (`4.200620 s`, not ≈4.3042 s), all four framebuffers
byte-identical. **Falsified: the merged `twim1 p1_boot` sha is `47a3cad0…`,
not `4f49068a…`** — that hash covers the cross-device interleaving of four
devices on one bus, which the oracle's own `determinism_verification` has always
flagged as unstable; the prediction should not have included it.

**One quantitative correction to §4 of that report.** It says the images past
the threshold land in the earlier slot "within 0.5 ms of each other". Stage 07
lands **3.02 ms** from stage 04-B — same slot, six times that spread. The slot
is real; the tightness was a property of the three images then measured.

### The stale shipped navigation oracle: REGENERATED

`recon/emulator/reports/display_sensor_oracle.json` was regenerated from the
seeded shipped capture. **0 fields removed; 8 corrected; 20 gained that the
committed file never carried; 357 added by the new train block.** The four
golden framebuffers are **byte-identical** after regeneration.

| field | committed | regenerated | cause |
|---|---|---|---|
| `counters/RADIO_TX` (+ `radio_esb/ble_radio_transmitted_frames`) | `0x230` | `0x232` | staleness — predates `emulation SetSeed` |
| `counters/VC_DATA_EVENTS` | `0x215` | `0x212` | staleness — seed |
| `counters/SCREEN_ID_ctx_d5` | absent | `0x0A` | staleness — counter added later |
| `twim1/p1_boot/stream_sha256` | `ef6fcb11…` | `33cbd8c1…` | staleness — seed (merged-bus interleaving) |
| `twim1/p2_render/stream_sha256` | `f418e5ba…` | `329565e4…` | staleness — seed |
| `jbd_journal_tail` | — | — | staleness — seed moves the sequence numbers |
| `saadc/whole_run/stream_sha256` | `660cdf3b…` | `ebf06b30…` | **script change** — iteration 42's RAM-pointer canonicalisation |
| 20 further fields | absent | present | **script change** — iteration 42's pointer + analogue-sample canonicalisations |

**No criterion was retired, so there is no `WITHDRAWN_annotations` block.**
`parity_criteria` (G-1…G-6, S-*) and `determinism_verification` carry through
byte for byte; the new criterion is published beside them at
`peripherals/<bus>/whole_run_trains/criterion`. The **dashboard** oracle
regenerated with **0 of 69 fields changed**, confirming both that it was current
and that the builder change is strictly additive.

### What the criterion stops catching — published so the residue stays measurable

1. absolute placement of a periodic train in wall time, up to **145.440 ms** —
   a wrong sleep constant, a dropped tick or a priority inversion whose whole
   effect is a sub-Δ displacement. *Kept visible by:* the strict per-phase
   `transaction_count`/`stream_sha256`, and the per-stream `max|delta|` the
   comparer prints for every stream including passing ones.
2. **read payload bytes** are not in the train key. *Kept visible by:*
   `stream_sha256`, `analogue_sample_payloads`, `stream_sha256_regprog`.
3. **burst counts at the observation wall**, when the train's own period
   predicts them. *Kept visible by:* the strict counts and the printed `note`.
4. **phase on ambiguous trains** — on stage 07 navigation **199 of 547** LSM6DSO
   poll bursts are excluded; on the dashboard **432 of 545**. *Kept visible by:*
   the `????` lines, which state how many of how many and the largest excluded δ.
5. **ordering inside a 145.440 ms window.** *Kept visible by:*
   `worst_admissible_inversion_ms` and the strict `stream_sha256`.
6. **`npm1300` phase is indeterminate** — three trains per stimulus with `|δ|`
   up to 7,497.653 ms are ambiguous.
7. **`RADIO_TX`, `ESB_*`, `VC_DATA_EVENTS`, `saadc`, `pdm0`, `gpiote*` are not
   covered at all** — no train decomposition; still gated strictly.
8. a shared bus can **merge two independent bursts** under `BURST_GAP_NS` once
   one shifts (measured on stage 07: a `070401` write landing 3.100 ms before
   the `080001…` init burst). That is a **false positive**, named `P0
   segmentation`, still failing. The repair — calibrate the gap per device from
   the shipped reference — is **not done**.

### Two findings the strict criterion never surfaced

* **The in-tree base fails `P5 order` on `twim1` npm1300**: "two bursts
  9,904.330 ms apart in the shipped run swapped order". A pre-existing ordering
  defect, invisible while the merged bus hash was already NE for other reasons.
* **`spim_a` navigation fails `P1 content` on every image including the base** —
  one animation-frame train in shipped that is absent from ours and one only in
  ours. The `sensor_parity_status.md` §41 residue, now gated as *content*,
  which no amount of phase tolerance will absorb.

### Reproducing

See `recon/analysis/phase_tolerant_criterion.md` §10. The one thing that has
changed for the better: **the committed
`recon/emulator/reports/display_sensor_oracle.json` may now be used directly as
the shipped navigation reference** — the stage04b record's warning to regenerate
it from `/private/tmp/g1_ship_seed_q1` no longer applies.

---

# ★ CONSOLIDATED GATE RECORD — the whole ladder at ONE head, 2026-07-27

**Read this first; the four records above are the working, this is the verdict.**
Full working: **`recon/analysis/refactor_consolidated_verdict.md`**.

The four records above were written at three different HEADs against three
different baselines, and answering "is the refactor proven?" required
reconciling them. This record regenerates stages 00→08 at one head, rebuilds all
nine images, measures every size gate, re-derives the phase bound, and states
one verdict per stage.

**Inputs.** HEAD `e7f35727` ("Type-disagreement repair 4"), working tree clean
except the unrelated untracked `.xapk`. Stage 00 was **stale on 177 inputs**;
stages 00→08 were **regenerated, never patched**, in zero transformer rounds.
*The concurrent parity agent landed a further 50 inputs mid-pass; stage 00 is
stale on those at the close. Every measurement below is at the generation stage
00 captured, which is `cmp`-identical to the base image of the three preceding
passes.*

## The table

| # | class declared → **measured** | strict `cmp3` | phase-tolerant, published 5 ms gap | **phase-tolerant, corrected segmentation** | evidence status at HEAD |
|---|---|---|---|---|---|
| 00 | `byte-identical` → identity | n/a | n/a | n/a | image `cmp`-identical to `g1-i44-base`, `g1-s4b-base`, `g1-td4-final` |
| 01 | ~~`byte-identical`~~ → **`size-changing`** (`text` −4, `rodata` −124) | 0 regressions | **PASS** | **PASS** | **VALID** — image `cmp`-identical to `g1-pt-s01` |
| 02 | `byte-identical` → **`byte-identical`** | 0 regressions | **PASS** | **PASS** | **VALID** (= 01) |
| 03 | `byte-identical` → **`byte-identical`** | 0 regressions | **PASS** | **PASS** | **VALID** — `cmp`-identical to `g1-s4b-s03` |
| 04 | `size-changing` → **`size-changing`** (`text` −76) | 8 regressions nav, 1 dash | PASS (0 REG, 2 pre-existing-worse) | **FAIL — 1 REGRESSION** | **INVALID** — image differs from `g1-s4b-s04` |
| 05 | `size-neutral` → **`byte-identical`** | inherits 04 | inherits 04 | **inherits 04's FAIL** | INVALID (= 04) |
| 06 | `byte-identical` → **`byte-identical`** | inherits 04 | inherits 04 | **inherits 04's FAIL** | INVALID (= 04) |
| 07 | `size-changing` → **`size-changing`** (`text` −276, `rodata` −8) | 9 regressions nav / 4 dash, 4 improvements each | PASS (0 REG, 2 pre-existing-worse) | **FAIL — 1 REGRESSION** | **INVALID** — image differs from `g1-pt-s07` |
| 08 | `size-changing` → **`byte-identical`** | inherits 07 | inherits 07 | **inherits 07's FAIL** | INVALID (= 07) |

## The four things this record changes

### 1. Stage 04 DID NOT COMPILE at HEAD, and the cause is C7c's FIFTH instance

```
lib/g1_lib_03.c:659: error: conflicting types for 'z_device_is_ready';
                            have '_Bool(const struct device *)'
      previous declaration ... with type '_Bool(const struct device *)'
```

The two declarations are **character-for-character identical**. Three members
carried `extern _Bool z_device_is_ready(const struct device *);` and the unit
declared `struct device` nowhere at file scope, so each declaration introduced
its own **parameter-list-scoped** incomplete type (C11 6.2.1p7). Stage 04's
`type` refusal rule compares declaration TEXT and structurally cannot see this.

**Repaired as a transformer change** (`t04.incomplete_tag_forwards` +
`blank_attributes`): every merged unit now emits a file-scope forward
declaration for every `struct`/`union` tag it names — unconditionally, because a
conditional form would have to reason about order and scope. **207
declarations across 107 of the 249 merged units.** 6 new tests.

Cost, named rather than left to be rediscovered: the block sits before the first
member, and stage 06's include hoisting keys on "the unit's first include
block", so its yield falls **268 -> 142 hoists**. Stages 05 and 07 are unchanged
field for field and stage 06 still measures `byte-identical`, so nothing
observable was paid.

The same unit exposed a **latent reconstruction defect** the parity harness
cannot see: three members pass three different things to that parameter
(`const struct device_raw *`, `(const void *)&rodata_87bf0`,
`(const void *)flash_device`).

**Add to C7c's list:** *identical declaration TEXT is not identical TYPE.*

### 2. The phase-tolerant PASS for stages 04–08 does not survive a corrected segmentation

The published verdict scored stages 04-B/05/06/07 as "PASS on every gated
stream, 0 regressions" — **but only because the BASE was failing the same stream
for an unrelated segmentation reason.** Re-derived from the raw captures at 28
burst-gap thresholds (no Renode; the builder is a pure function of a capture
directory, and a 5 ms re-derivation reproduces the committed oracle with 0 of
546 fields changed):

| image | `spim_a` navigation peak displacement | at 5 ms | **at 0.700 / 0.790 / 0.800 / 2.300 ms** |
|---|---:|---|---|
| in-tree base | 145.440 ms | FAIL `P1 content` | **PASS** |
| stage 03 | 145.380 ms | FAIL `P1 content` | **PASS** |
| stage 04-B | **245.780 ms** | FAIL | **FAIL — `P3 phase` on 24 bursts** |
| stage 07 | **281.670 ms** | FAIL | **FAIL — `P3 phase` on 22 bursts** |

**Δ re-derives to exactly 145.440 ms at every threshold in that band** — the
bound was not touched, and the change only ever makes a stage fail. The failing
burst counts are 24 / 22 with the §6 equal-population rule on and 22 / 21 with
the shipped rule; **the REGRESSION verdict is the same under both.** §44.3.4's
proposed T = 2.580 ms is refuted on the *dashboard*, which that sweep never ran.
No constant was adopted (the clean band is non-monotonic: T = 0.750 ms sits
between two clean values and introduces an `opt3001` `P0 segmentation`), but the
**verdict** must change regardless of the constant.

### 3. Two criterion claims corrected, one criterion field adopted

* **`our_boot_bringup.md` §44.7.1's "closable at zero cost" is FALSE as stated.**
  Landing the equal-population ambiguity rule at the shipped 5 ms gap moves the
  derived bound **145.440 ms → 7,498.630 ms** (a 51× widening), from an
  `npm1300` train with n=6 on *both* sides: the §44.3.1 membership swap keeps
  populations equal. It is free only in the corrected-segmentation band, where Δ
  is unchanged and the `twim2 lsm6dso` exclusion goes 200/548 → **0**. The two
  changes are **coupled**. Implemented, tested, off by default, in
  `recon/refactor/criterion_probe.py`.
* **`gap_separation.separated` is VACUOUS.** `max_intra <= BURST_GAP_NS <
  min_inter` is true by construction of `split_bursts` — measured `True` for all
  six devices, four captures, every threshold from 0.020 to 10 ms, including ones
  that demonstrably mis-segment. Reported, not edited (another agent's file).
* **`RADIO_TX` components ADOPTED at zero cost** — `BLE_link_TX := RADIO_TX −
  ESB_MASTER_FRAMES`, arithmetic on two fields the oracle already publishes.
  Reproduces §44.4's instrumented table exactly and extends it to the dashboard.
  **The in-tree base does NOT hold `RADIO_TX`**: `374 + 188` vs shipped
  `373 + 189` — both halves wrong, in opposite directions, recorded as EQ since
  §43.11. Stage 07 **closes the ESB half** (373 == shipped, both stimuli).

### 4. Every size gate now exists — and stage 01's was never run

`SIZE_GATE.json` existed for stages 04–07 only. All nine now measure against
their own predecessor's build. **Stage 08's is written and measures
`byte-identical`** with `"oracle_required": false`. **Stage 01's, run for the
first time, FAILED**: declared `byte-identical`, measured `size-changing`
(`text` −4, `rodata` −124) — which is exactly what withdrawing 100 backing
objects does. `driver.STAGES` row 1 is corrected to `size-changing`;
`test_size_gate.Registry` caught the manifest lagging the row immediately.

## Evidence status — read before quoting any R7 verdict

`our_boot_bringup.md` §44.9 item 6 carried the stage captures forward by
inference from base payload identity, and labelled it an inference. **The
inference is false at HEAD.** The in-tree base is `zephyr.bin` +16 B / `text`
+4 B and byte-different from `g1-i44-base`; stage 04-B's and stage 07's images
are byte-different from the ones the earlier passes booted (same sizes, different
bytes). Stage 01/02/03's images ARE `cmp`-identical to what was booted, so those
captures stand.

> **At HEAD there is no valid behavioural evidence for stages 04–08, and no
> valid base reference. Three captures per image are needed to close it.**

## Static ladder, this pass

```
9 app builds (00..08 + base)  exit 0        (stage 04 only after the C7c repair)
nm -u                         0 on all nine
duplicate GLOBAL definitions  0 on all nine
check_ram_pin_collisions app  596 bound OK / 0 escaping / 0 unknown (627 -> 596 upstream)
check_thread_create_stack_args --trials 120   10/10, exit 0
tools/verify_data.py          995/995 byte-exact, 56,279 B, 100.00 %
check-addresses, 8 pairs      identical, 2,567
stage trees 01..08            BYTE-IDEMPOTENT (content + symlink targets)
refactor test suite           157 / 157   (was 139; +6 tag-forwards, +12 criterion_probe)
net core                      NOT BUILT, NOT TOUCHED -- check_net_raw_literals and
                              verify_net_stock_data_window NOT RUN
```

## The remaining structural work — ~~measured, specified, NOT landed~~ **BUILT, 2026-07-27**

**Superseded.** Stage 09 `call_cohesion` was **built, registered, tested and
materialised** on 2026-07-27. Report:
**`recon/analysis/staged_refactor_stage09.md`**. The numbers below are the
verdict's §11.1 measurement and **every one of them was already stale when it
was written** — the ladder was regenerated at 15:28, four minutes after the
verdict was saved at 15:24. Both columns are kept so the drift is visible.

| | verdict §11.1 | **re-measured on the live stage 08 tree** |
|---|---:|---:|
| retained app TUs | 705 | **742** |
| single-source | 454 (64.4 %) | **493 (66.4 %)** |
| intra-module call edges between distinct TUs | 1,216 | **1,224** |
| call edges *inside* the merged units (stage 08) | 11 | **11** (249 units) |
| call-cohesion grouping absorbs | 100 → 605 TUs | **83 → 659 TUs** |
| no-adjacency ceiling absorbs | 523 → 182 TUs | **512 → 230 TUs** |

**1,224 against 11** — the ratio the stage exists for survives the correction.
Stage 04 groups on an axis nearly orthogonal to call structure.

### Stage 09 as landed

| | |
|---|---|
| declared class | **`size-changing`**, **`oracle_required: true`** |
| achieved class | **NOT MEASURABLE** — no linked image exists (see below) |
| result, sub-batch `C` (default) | **742 → 659 TUs, 55 merged units, 138 absorbed** |
| call edges now inside one unit | **85**, against stage 04's 11 — 0.044 → 1.55 per unit, **35×** |
| single-source share | **66.4 % → 66.3 %** — 56 of the 138 absorbed members were single-source, the other 82 were already stage 04 units. This stage improves the QUALITY of the grouping, not the FRACTION of the tree that is grouped. |
| `check-addresses 8 9` | **identical, 2,567** |
| compile | **PASS, first try after ONE transformer round** (round 1 found a new defect, below) |
| link | **FAIL — INHERITED. Stage 08's own tree fails identically at HEAD.** |
| per-object comparison | **1,630 of 1,630 common objects have identical allocatable size**; whole-archive allocatable total −64 B |
| idempotence | **PASS**, byte-identical tree and MANIFEST |
| test suite | **203 / 203** (was 157; +40 stage 09, +6 `check-partition`) |
| **outstanding obligation** | **the R7 oracle run. Not done, not inferred, not borrowed.** Renode was held by the concurrent agent. |
| sub-batch `M` | the no-adjacency ceiling, opt-in, **not the default** — it produces a module bucket, not a cohesive unit |

### ⚠ THE LADDER DOES NOT LINK AT HEAD, from stage 07 upward

Found while gating stage 09, and **not caused by it**: stage 08's own tree,
built at the same HEAD, fails with the byte-identical message.

```
recon/symbolized/app/display/display_close_screen.c:39:
    undefined reference to `display_close'
```

`display_close` was given internal linkage by **stage 07**, whose evidence
(`link_referenced_symbols.json`, provenance `/private/tmp/g1-s6-base`) says
nothing outside its object references it. In that build
`display_close_screen.c` **was a member of `g1_display_12.c`** — the same
object. Stage 04's merge partition has since moved, `display_close_screen.c` is
its own translation unit, and the call is now a relocation. `stagelib`
watches the evidence file's **content hash**; the file did not change, the
**tree it describes** did, and `driver.py status` reported stage 07 `current`
throughout. Same defect class as C7a–C7e: *a comparison that cannot see the
difference that matters* — here a hash, and the difference is which objects
exist.

Measured repair: regenerating the evidence from a build of HEAD's stage 06 tree
(which **does** link, exit 0) adds exactly **2** symbols to `referenced`
(`display_close`, `_puts_r`) and removes none, and refuses exactly **1** of
stage 07's 133 applied candidates. **Not run** — it is a shared evidence input
and an agent was mid-gate.

```sh
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s06-base
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py generate \
    --build /private/tmp/g1-s06-base
for n in 7 8 9; do … driver.py materialize $n; done
```

**New, additive, and it makes this unrepresentable rather than unlikely:**

```sh
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py \
    check-partition recon/refactor/stage_06_unit_composition/tree
#   -> STALE: 59 retained sources have no object in the evidence archive,
#             9 objects in the evidence are no longer retained
#   against evidence generated from HEAD's own stage 06 build -> "agrees", 0/0
```

Run it against the tree the consuming stage READS, before materializing any
stage that consumes the evidence. Six unit tests, no toolchain required.

### Consequence for every size gate in the table above

All eight `SIZE_GATE.json` files were measured against `/private/tmp/g1-cons-s0N`,
and those builds were made from the **pre-regeneration** ladder (their
`g1_display_12.c.obj` still contains `display_close_screen`). The
declared-vs-measured **contract** is sound and is now a test
(`test_every_size_gate_on_disk_agrees_with_the_registry`: every declared class
matches `driver.STAGES` and no stage came out worse than declared). The
**numbers** are stale and must be re-measured after the evidence repair.

### Sixth instance of the recurring defect class, found by stage 09's first build

A file-scope `extern` statement with a **comma-separated declarator list**:

```c
extern void update_box_presence_flag(void*,void*),init_config_fields_default9(void*),
            k_sleep(int,int),st25dv_build_and_write_ndef_records(void*,void*,void*),
            set_time_mark(void);
```

One `;`, one `extern`, **five declarations**. Stage 04's shape rule is
`line.count(";") > 1 or line.count("extern") > 1`, and `t03._decl_symbol`
returns the name before the *first* `(` — so `k_sleep(int,int)` is invisible to
every refusal rule in the pipeline, and it collided with
`extern int32_t k_sleep(k_timeout_t);` when stage 09 grouped the two files.
Repaired **fail-closed** in stage 09 (`t09.multi_declarator_externs`);
**exposure is 2 files corpus-wide, 1 of them already quarantined by the old
rule**, and `g1_core_01.c` proves stage 04 shipped a unit containing a
declaration none of its rules could read. The exact `t04` patch is in the stage
09 report §3.1 and was deliberately **not applied** while the ladder was being
regenerated by another agent.

### `gap_separation.separated` — vacuity confirmed, and now calibrated

Re-derived from the source: `split_bursts` defines `max_intra` as the largest
gap `<=` the threshold and `min_inter` as the smallest gap `>` it, so
`max_intra <= BURST_GAP_NS < min_inter` is a **tautology** — `True` on 42 of 42
blocks in the ten oracles on disk. New in this pass, from the raw captures and
no Renode: the real void ratio `min_inter / max_intra` per device.

| | at the shipped **5.000 ms** | at **0.790 ms** |
|---|---|---|
| devices with a ≥4× void | **1 of 6** (`opt3001` only) | **5 of 6** |
| worst ratio | `lsm6dso` **1.05** | `npm1300` **1.50** |

Five of six devices have **no bimodal void at all** at the shipped threshold —
independent, static corroboration of the corrected-segmentation finding, and it
identifies `npm1300` as the one genuinely mis-assigned train, which is the same
device whose train-membership swap blows the ambiguity rule's Δ to 7,498.630 ms.
The falsifiable replacement (`min_inter >= 4 × max_intra`) is written out in the
stage 09 report §6.1; the file belongs to another agent and was **not edited**.
