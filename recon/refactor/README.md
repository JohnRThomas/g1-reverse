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
| 02 (next) | spelling normalisation of the volatile accessors (one type only) | textual, codegen-identical; gate is a byte-identical `.o` |
| 03 | `__ASSERT` / noreturn macro extraction | depends on 01 having produced the literals |
| 04 | MMIO accessor macros per width, with a signedness audit | **first stage that can change codegen**; C8 applies |
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
