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
(1,609 app / 923 net, encoding 677 + 312 manifest exclusions), **never a
directory glob**. `input_set.py` derives the set from those lists, plus the
`.inc` fragments the retained sources `#include`, the hand-written integration
TUs in `recon/application/{app,net}/src`, the generated
`recon/application/rodata/*.c`, and the pin/declaration artifacts
`recon/symbols/g1_{app,net}_{globals.ld,symbols.h}` that a withdraw-transaction
has to edit in the same breath as an inline.

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
| 03 (next) | authoritative `assert_post_action` / `assert_print` prototype (160 declarations, 58 spellings), read off the shipped prologues; and enumerate `.h` fragments in `input_set.py` (stage 02 §5.3 found two wrong declarations invisible to the pipeline) | decides 160 declarations at once; will change codegen where the local one was wrong |
| 04 | MMIO accessor macros per width, with a signedness audit | **first stage that can change codegen**; C8 applies. Stage 02 already reduced 84 accessor spellings to 52, which is the prerequisite. |
| 05 | net renaming from upstream-identified symbols | 0 B, gated by a real link (C6) |
| 06 | module materialisation / directory move | file-layout only; both builds must emit byte-identical images |
| 07 | struct typing | the stage that can grow the image; budget it |

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

**Timing note on that record.** All Stage 02 builds and all six our-build
captures completed by 04:15:48; the concurrent parity agent landed a ~1,800-file
batch at 04:19:48 which moved **75** pipeline inputs and made stage 00 stale
again. Nothing in the record was measured against a moving input, but the stages
must be regenerated before the next measurement. The R7 verdict above stands for
the inputs it names (HEAD `a2f3303d`, clean tree); re-running it after that batch
is the next stage's first job, not a repair of this one.
