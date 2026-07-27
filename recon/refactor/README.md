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
`test_size_gate.py` pins all of this (25 tests); the suite is **105/105**.

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
| 01 | literal inlining | value-preserving substitution in argument position; no control flow, no MMIO, no layout |
| 02 | **block dedupe (LANDED)** — volatile-accessor spelling normalisation (one type only), plus the `G1_NORETURN_CALL` / `G1_LOG_ROUTE` / `G1_ASSERT_FAIL` macros and the log-prototype convergence residue. Stage 03's `__ASSERT` / noreturn extraction was folded in here because it is the same class of token-identical statement macro. | textual, codegen-identical; gate is a byte-identical `.o`, and it held: both cores' `zephyr.bin` byte-identical to stage 01, 4,594/4,598 objects byte-identical. Report: `recon/analysis/staged_refactor_stage02.md` |
| 03 | **module structure (LANDED, app core only)** — the `input_set.py` `.h`-fragment fix stage 02 filed as blocking, plus the first STRUCTURAL transform: 1,621 app sources moved into 22 cohesive module directories (build lists regenerated in the same transaction, list order preserved exactly), and 99 module-wide type-identical `extern` declarations hoisted into 16 generated module headers. Net untouched and therefore byte-identical by construction. | file layout + declaration siting only; gate is a byte-identical `zephyr.bin`, and it held on both cores. **Harvest: 1,014 symbol/module type disagreements, 446 of them against the symbol's own definition, 175 about arity.** Report: `recon/analysis/staged_refactor_stage03.md` |
| 03b (partly done, upstream) | **repair the declaration disagreements** in the CANONICAL trees (stage 03 `DEFECTS.json`). The parity agent's type-disagreement pass took the census from 1,014 to **833** (measured by re-running stage 03's own agreement test at HEAD `50929c5d`). | blocking prerequisite for a *blanket* cohesive-TU merge; still the single thing standing between stage 04's 695 translation units and 243. R1 means this work is the parity agent's, not the pipeline's. |
| 04 | **scoped cohesive-TU merge, app core only — DEFAULT IS NOW SUB-BATCH `B`** — maximal ORDER-PRESERVING runs of consecutive retained sources inside one module that provably cannot collide. Seven refusal rules (`type`, `dupdef`, `static`, `typedef`, `macro`, `asmname`, `tag`/`enumconst`, `includes`); quoted repository headers are *read* and folded rather than refused. `A` and `B` now **partition** the clean runs and the R7 gate below charged 100 % of the damage to `A`, so `B` is the default: **1,615 → 700 TUs, 249 merged units, 1,164 files absorbed.** | **the first stage that CANNOT be gated on `cmp zephyr.bin`.** Declared codegen class **`size-changing`**, measured `.text` **−76 B** for `B` alone (−12 B for `A`, −88 B for `AB`) — so **an oracle run is REQUIRED and has NOT been done for `B`**. Reports: `recon/analysis/staged_refactor_stage04.md` (the original AB build), `recon/analysis/stage04_r7_validation.md` (the gate), `recon/analysis/staged_refactor_stage05.md` (the rework). |
| 05 | **cohesive composition, app core only** — turns stage 04's concatenated units into composed ones: one include block per unit (repeats of *provably idempotent* headers withdrawn, never moved — 2,423 → 850 directives, worst unit 49 → 6), one declaration site per symbol per unit (146 duplicates withdrawn), one-line member banners, every `identity:` banner preserved byte for byte. Sub-batch `S` (internal linkage for TU-private symbols: 241 candidates) is opt-in and **not applied**. | declared `size-neutral`, **measured `byte-identical` — `zephyr.bin` `cmp`-identical to stage 04's, 956,276 B.** Needs no oracle of its own; inherits stage 04's unproven status. Report: `recon/analysis/staged_refactor_stage05.md` |
| 06 (was 05) | MMIO accessor macros per width, with a signedness audit | **stage that can change codegen** by value; C8 applies. Stage 02 already reduced 84 accessor spellings to 52, which is the prerequisite. |
| 07 | net renaming from upstream-identified symbols | 0 B, gated by a real link (C6) |
| 08 | struct typing | the stage that can grow the image; budget it |

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
