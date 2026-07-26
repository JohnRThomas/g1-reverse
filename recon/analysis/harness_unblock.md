# Harness unblock — `.rodata` pointer equivalence, resolvable scratchpad, test runner

**Scope: `tools/**` only.** Nothing under `recon/{app,net,verified,symbolized,named,
readable_sources,application,symbols}` was modified — a concurrent agent owns those
trees. The three files this pass adds under `recon/analysis/` are this report,
`harness_unblock_regen_diff.json` and
`harness_unblock_negative_controls.json`. **Nothing was committed.**

Environment for every measurement below:
`PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python`,
working tree at commit `6aa09be0` plus the concurrent agent's uncommitted
`recon/**` edits.

### Files changed

| file | change |
|---|---|
| `tools/parity/emu.py` | **new** `ReadOnlyPointees` equivalence class + content-resolved format-arity lookup (§1) |
| `tools/cfg_verify.py` | catalog loads via `g1_paths`; 2 stale self-test anchors re-anchored; new self-test block for the equivalence class (§4) |
| `tools/g1_paths.py` | **new** — resolvable scratchpad + fail-closed committed-catalog fallback (§2) |
| `tools/run_tests.py` | **new** — the test runner (§3) |
| `tools/audit_negative_controls.py` | **new** — measures which self-test negative controls actually bite (§4.3) |
| `tools/build_symbol_map.py` | refgraph load made fail-closed; scratchpad resolvable |
| `tools/symbolize.py`, `tools/gen_linker.py` | `G1_SYMBOLIZE_OUT` / `G1_SYMBOLS_OUT` so a regeneration can be diffed, not dumped over the tree |
| 34 further `tools/*.py` | mechanical: the embedded `/private/tmp/.../bf259b2e-.../scratchpad` literal → `_g1_paths.scratchpad()` |

`tools/_trusted/**` was deliberately left untouched (frozen harness snapshot).
No `recon/**` source, catalog, header or linker script was written.

---

## 1. Blocker 1 — the `.rodata` pointer equivalence class

### 1.1 What was actually failing

`emu.compare` records, per external call, the ordered tuple

```
("C", index, *r0..r{arity-1}, "S", *stack_args, "F", *float_args, "T", indirect_target)
```

and hashes the whole event list. A log call's **format-string pointer is one of
those integers**. The shipped firmware passes `0x000a3b3f` because its string
lives at that flash address; a reconstruction that spells the same string as a C
literal passes the address of its own copy in its own `.rodata`. Identical
programs, different integers, `FAIL`.

Reproduced before touching anything, on `opt3007_chip_init` (`0x2e67c`), by
feeding `cfg_verify.verify(..., source_override=...)` a copy of the canonical
file with its 13 string addresses replaced by C literals (36 sites):

| variant | verdict at HEAD |
|---|---|
| canonical file, untouched | **PASS** |
| same file, literals inlined | **FAIL**, 2 mismatching trials |

The failing trace showed the original's `('C', 0, 670527, 670976, …)` —
`0xa3b3f`, `0xa3d00` — against the candidate's own `.rodata` addresses.

A **second, hidden** half of the same blocker: `REVIEWED_CALL_ARITIES_BY_FORMAT`
and `REVIEWED_CALL_STACK_ARITIES_BY_FORMAT` are keyed by
`(callee, format_string_flash_address)`. `opt3007_chip_init` has 22 such entries
selecting arity 2 or 3 per format string. An inlined literal misses every key,
the lookup falls back to the by-target default, and the recorded arity itself
diverges. Fixing only the argument comparison would not have unblocked this
function.

### 1.2 The equivalence class

New in `tools/parity/emu.py`: `ReadOnlyPointees`. A value observed in a compared
position is replaced by `("RO", <pointee bytes>)` **only when all five hold**:

1. it lands inside a **declared read-only extent**;
2. the pointee is a **NUL-terminated** byte string;
3. of length **1..256** (`RODATA_STRING_MAX`) — empty strings are excluded, or
   every NUL byte in the image would become one equivalence class;
4. every byte is **printable ASCII or `\t` `\n` `\r`**;
5. the address is a **string head** — the preceding byte is NUL, or the address
   is the first byte of its extent.

Anything that fails any test keeps **exact address comparison**, byte for byte
what the harness did before. Non-string read-only objects — const tables,
function pointers, `struct device` pointers, section bounds, the 127
`ADDR_*_THUMB` symbols — are therefore *unaffected*.

Two extents exist, tried **in this order**:

| order | extent | who has it |
|---|---|---|
| 1 | the shipped flash image (`extract.read` over `app_update.bin`, VA `0xC200 .. 0xFAB8D`) | **both** sides |
| 2 | the candidate's own linked read-only tail, `[cand_va+cand_size, cand_va+len(cand))` | **candidate only** |

The order is the safety property, not a detail — see §1.4.

Applied at four compared positions: call arguments r0–r3, stack-passed call
arguments, 4-byte memory-write values, and the `i32` return value. Plus
`_format_table_lookup`, which resolves a reviewed per-format-string arity by
**content** when the raw address is not a table key, and falls back to the
by-target default when the content match is absent or ambiguous.

### 1.3 Discrimination proof

Five functions × seven variants, all through the real
`cfg_verify.verify()` entry point (`recon/**` never written; the variants are
`source_override` strings). Controls mutate only the **first** string, so a
single wrong pointer among 20–70 correct ones must still be caught.

| function | baseline | **inline** | corrupt (1 byte flipped) | swap (a *different real* image string) | null pointer | garbage `0xdeadbe00` | interior pointer (head+1) |
|---|---|---|---|---|---|---|---|
| `main` (33 addrs / 74 sites) | PASS | **PASS** | FAIL | FAIL | FAIL | FAIL | FAIL |
| `FUN_00019718` (7 / 24) | PASS | **PASS** | FAIL | FAIL | FAIL | FAIL | FAIL |
| `FUN_00021a40` (5 / 16) | PASS | **PASS** | FAIL | FAIL | FAIL | FAIL | FAIL |
| `FUN_00031fd8` (7 / 21) | PASS | **PASS** | FAIL | FAIL | FAIL | FAIL | FAIL |
| `opt3007_chip_init` (13 / 36) | PASS | **PASS** | FAIL | FAIL | FAIL | FAIL | FAIL |

35 of 35 cells as designed. These are exactly the five functions commit
`9361d2ef` measured as `PASS → FAIL → PASS`.

Why each control still bites:

* **corrupt** — content differs by one byte, `("RO", b"…")` differs, FAIL.
* **swap** — the substituted string is a genuine, valid, printable image string
  that passes every one of the five tests. It is simply the *wrong* one for that
  call site. This is the control that proves the class is keyed on content and
  not merely on "looks like a string".
* **null** — `0` is outside both extents; no normalization; `0` vs `0xa3b3f`, FAIL.
* **garbage `0xdeadbe00`** — outside the image and outside the candidate tail;
  no normalization; FAIL. Out-of-image and unmapped pointers can never be
  "equivalent" to anything.
* **interior pointer** — `head+1` fails rule 5 (its preceding byte is not NUL),
  so it is compared as a raw address, FAIL.

### 1.3.1 Wider sample — 24 more canonical app functions

The five above are the functions the blocker was *reported* on, so a random
sample was run the same way: 24 canonical `recon/app/src` files (deterministic
shuffle, seed 7) holding at least two image-string addresses, each through
baseline / inline / corrupt / swap.

| outcome | n | meaning |
|---|---:|---|
| **inline PASS, both controls FAIL** | **10** | unblocked, and discrimination intact |
| inline PASS, controls also PASS | 11 | **the site is invisible to the harness at all** — see below |
| probe compile-fail | 2 | artefact of the crude textual inliner, not the harness |
| baseline already FAIL | 1 | `ancs_disconnected`, pre-existing |

The 11 "vacuous control" cases are the honest part. They are **not** a weakening
introduced here: for every one tested, replacing the same address with a **null
pointer** *or* with out-of-image `0xdeadbe00` **also PASSes**.

```
FUN_00012080  garbage=PASS null=PASS      FUN_0004df88  garbage=PASS null=PASS
FUN_000189a0  garbage=PASS null=PASS      FUN_00051c68  garbage=PASS null=PASS
FUN_00019b54  garbage=PASS null=PASS      FUN_00055d08  garbage=PASS null=PASS
FUN_0005aba8  garbage=PASS null=PASS   (6 of 6 probed)
```

The cause is pre-existing and structural: these functions store the pointer into
a **local stack record** and pass `&record`. Stack writes are deliberately
excluded from the write trace as an implementation detail, and a stack record's
*contents* are only compared when a reviewed `stack_objects` declaration exists
for that call site — none does here. So the value never reaches a compared
position, with or without this change. `FUN_0005aba8` is the clearest example:
`frame.log.message = (iVar2==0) ? 0x000f49d4 : 0x000f49ed;` then
`FUN_00082a42(0x88128, 0x1040, &frame.log)`.

**Consequence for the batch.** For those sites an inline PASS is *not* evidence
that the literal is correct — the harness is blind there either way. Byte-level
verification against the shipped image (which G6 already does before any edit:
"all 1,411 candidates were byte-compared against the shipped image") remains the
governing check for them, not parity. This is a pre-existing coverage gap in
stack-passed record contents, now measured; closing it means reviewed
`stack_objects` declarations, which is a separate piece of work.

### 1.4 Why no false PASS is introduced

**Normalization is a pure function of the observed value on each side.** Two
*equal* values therefore always normalize to *equal* identities. The verdict can
only change for pairs where the two sides observed **different** addresses whose
pointees are byte-identical strings.

For that class the two programs are indistinguishable to every observer: the
region is read-only — never written by either side, so no write trace can
separate them — and the callee is a deterministic order-keyed oracle, so no
callee can compare the pointer's identity. A `const char *` whose bytes are
equal *is* the same value.

The residual, and it is stated rather than dismissed: **two distinct
byte-identical strings in the shipped image become interchangeable.** A
reconstruction that passed the address of a duplicate string would pass. Since
neither is ever written and no consumer can observe which copy it holds, that is
sound; but it is a real, measurable widening and it is the only one.

**The extent order is what guarantees no PASS is lost.** The shipped image is
searched first, by *both* sides, so any address the image decodes resolves
identically on both — HEAD's verdict is preserved exactly. The candidate's own
tail is the single asymmetric element (the original has no such object), and it
is consulted only for addresses the image does **not** decode as a string. Had
the order been reversed, a reconstruction that spells a raw address landing
inside its own compiled `.rodata` could have been normalized on one side only,
turning a PASS into a FAIL.

That asymmetry is instrumented rather than assumed: `emu.RO_OWN_TAIL_HITS`
counts every resolution served by the candidate-own extent.

| corpus sweep (deterministic random sample, real `cfg_verify.verify`) | result | own-tail hits |
|---|---|---|
| 150 `recon/app/src` functions | 149 PASS, 1 FAIL | **0** |
| 80 `recon/net/src` functions | 78 PASS, 1 `noaddr`, 1 `nosize` | **0** |

The single app FAIL is `FUN_00087184`, and it **fails identically at HEAD** —
an MMIO read-ordering divergence (`('R', 0x41d0…)` before/after `('R', 0x41c1…)`),
nothing to do with this change. `noaddr`/`nosize` are two net sources without a
parseable `@ 0x…` header / catalog size; also pre-existing.

Zero own-tail hits across 230 functions means those runs are provably identical
to HEAD, not merely equal in verdict.

Existing checks are unchanged in strength: no test was deleted or relaxed, the
float harness of `68a9a389` (1,661 cases) is untouched, and the `-Os`/
`-ffp-contract` build contracts, stack-object coverage, direct-target identity,
fault-parity and prefix-proof machinery are all as they were.

### 1.5 Net core is deliberately NOT enabled

`RODATA_EQUIVALENCE_CORES = ("app",)`.

CPUNET has **two overlapping flash coordinate spaces** — analysis base
`0x01008000` (function identities, CFG positions) and runtime base `0x01008800`
(absolute pointers stored in the image). `tools/net_address_space.py` refuses to
classify an untyped integer in the overlap precisely because only provenance
distinguishes them. A content lookup against the wrong space would decode a
**different object** and could, in principle, manufacture a match. Since the 49
net G6-B3 candidates and all 116 net `string_literal` candidates are already
deferred for unrelated reasons (`nm` shows 0 net `rodata_*` objects and
`g1_net_rodata_0*.c` is not wired), enabling it would add risk for no benefit.
Net keeps exact address comparison; the switch is one tuple entry when the net
rodata objects are wired and a provenance rule exists.

### 1.6 What this unblocks

`recon/ownership/literal_inline_plan.json`, classification `inline`:

| core | class | candidates |
|---|---|---|
| app | `string_literal` | **1,918** |
| net | `string_literal` | 116 *(still blocked, §1.5)* |
| app+net | `nrf_peripheral_register` / `cortex_scs_register` | 58 *(not strings — never blocked by this)* |

1,235 candidates have at least one canonical-tree site, spanning **535 distinct
canonical files** (405 app / 130 net). The app half of that — and with it G6-B2
and the 3,494 canonical-tree sites commit `9361d2ef` deferred — is what this
lifts.

---

## 2. Blocker 2 — dead scratchpad path and missing `symbol_map.json`

### 2.1 What was there

`SCR = "/private/tmp/claude-501/…/bf259b2e-…/scratchpad"` was embedded in **42
live Python files**; 40 were migrated. The two left alone are
`tools/_trusted/{recon_kit,truesize}.py` — an unreferenced pinned snapshot of
the harness whose whole point is to be a frozen copy; touching it would defeat
it. 18 non-Python files (`.wf.js` workflow descriptions and two logs) also carry
the string and are documentation, not code. The
directory still exists on this machine and still holds `app_funcs.json`,
`net_funcs.json`, `classified.json` — but it belongs to a finished session
inside `/private/tmp`, no checkout recreates it, and `symbol_map.json` /
`symbol_map_net.json` were gone, so `symbolize.py` and `gen_linker.py` could not
run at all.

### 2.2 The fix

New `tools/g1_paths.py`. Resolution order, first hit wins:

1. `$G1_SCRATCHPAD` — explicit override;
2. the legacy session directory **if it still exists** — deliberately preferred,
   because its `app_funcs`/`classified`/`net_funcs` are *newer* than the
   committed snapshots (4,786,565 B vs 4,772,195 B for `app_funcs.json`), so
   every existing verdict stays bit-for-bit reproducible;
3. `<repo>/recon/generated/cache` — repo-relative default for a clean checkout.

`load_catalog(name)` looks in the resolved scratchpad, then falls back to the
committed `recon/catalogs/<name>.gz`, and **raises `MissingCatalog` when neither
exists**. That is the fix for the fake-all-clear hazard: an absent catalog can no
longer be mistaken for an empty corpus. The nine `json.load(open(SCR + …))` sites
in `cfg_verify.py`, `reverify.py`, `recon_kit.py`, `net_recon_kit.py` and
`parity/recon.py` now go through it.

Proven:

```
$ G1_SCRATCHPAD=<empty dir> python -c "…"
scratchpad=<empty dir>  app_funcs.json=committed classified.json=committed
net_funcs.json=committed ref_db.json=committed refgraph_app.json=committed
refgraph_net.json=committed
app sizes from committed fallback: 2391          # vs 2417 from the live scratchpad
MissingCatalog: symbol_map.json is in neither the scratchpad (…) nor recon/catalogs.
```

`build_symbol_map.py` had its own instance of the same hazard: the Ghidra
refgraph was loaded under a bare `try/except` that fell back to an **empty
graph**, and with no graph every mask and magic word becomes eligible to be a
symbol. It is now `load_catalog("refgraph_<core>.json")` — fail-closed.

`symbolize.py` and `gen_linker.py` also gained `G1_SYMBOLIZE_OUT` /
`G1_SYMBOLS_OUT` env overrides, so a regeneration can be produced into a scratch
tree and **diffed** before anyone lets it near the committed one.

### 2.3 `symbol_map.json` regenerated; both generators run again

```
$ python tools/build_symbol_map.py app     # 4,155 addresses; 1,603 rodata strings
$ python tools/build_symbol_map.py net     # 1,045 addresses;   106 rodata strings
$ python tools/symbolize.py app --write    # 2,140 files  (into a SCRATCH tree)
$ python tools/symbolize.py net --write    # 1,124 files  (into a SCRATCH tree)
$ python tools/gen_linker.py  app          # 2,816 symbols pinned
$ python tools/gen_linker.py  net          #   481 symbols pinned
```

All six run clean. **They do not reproduce the committed trees.**

### 2.4 ⚠ Regeneration would destroy committed work — DO NOT run `--write` over `recon/**`

Full per-file receipt: `recon/analysis/harness_unblock_regen_diff.json`.

| | committed | regenerated | byte-identical | would change | committed-only |
|---|---:|---:|---:|---:|---:|
| `recon/symbolized/app` | 2,141 | 2,140 | 1,450 | **690** | 1 (`FUN_0007c86c.c`) |
| `recon/symbolized/net` | 1,155 | 1,124 | 896 | **228** | 31 |

The plan's figure of "37 hand-edited symbolized files" is a **substantial
under-count**; the true reconciliation debt is 690 + 228 files. Classified by
what the diff touches:

| change class | app | net |
|---|---:|---:|
| G6 inlined string literal would be reverted to `&rodata_<hex>` | 247 | — |
| `rodata_<hex>` symbol spelling differs | 135 | ~10 |
| inlined string only | 105 | — |
| `#include "../../headers/…"` → `"../headers/…"` (hand-fixed include depth) | 34 | 26 |
| mixed / other / comment-only | 169 | 192 |

And the linker scripts:

| | committed `PROVIDE` | regenerated `PROVIDE` | only-committed | only-regenerated |
|---|---:|---:|---:|---:|
| `g1_app_globals.ld` | 2,026 | **2,816** | 930 | **1,720** |
| `g1_net_globals.ld` | 457 | 481 | 211 | 235 |

Regenerating `g1_app_globals.ld` today would **resurrect ~790 net-new numeric
pins**, undoing the 1,344 pins commit `9361d2ef` retired — each of which was
deliberately converted from a silent address-resurrection hazard into a link
error. That is a direct regression of a shipped gain.

**Conclusion.** The generators are runnable again, which is what Blocker 2 asked
for, and that is enough to make `production_refactor_plan.md` §4.2 step 5
(the generator round-trip audit) *possible*. It
is not enough to make it *pass*. The correct sequence is the plan's own Batch 1
step 1: push the downstream edits back into `recon/named` / `recon/net/named`
first, re-run, and only then let the generator own the tree — ideally behind the
overlay-manifest gate `production_refactor_plan.md` §4.3 proposes.

---

## 3. Blocker 3 — test runner and baseline

New `tools/run_tests.py`. One subprocess per file with a wall-clock timeout,
because these are proof scripts (Unicorn, `arm-none-eabi-gcc`, corpus sweeps),
not unit tests: `unittest discover` would import all 159 into one interpreter
that none of them was written for, and one hang would take the run with it. A
timeout is reported as a timeout, never as a pass.

```
$ PYTHONSAFEPATH=1 .venv/bin/python tools/run_tests.py -j 5 --timeout 900 \
      --json <out>.json
total 159  fail=74  pass=85  (148s wall)
```

**Baseline: 85 pass / 74 fail / 0 timeout, out of 159.**

The same runner against a clean `git checkout -- tools/` (HEAD) gives
**85 pass / 74 fail** with **zero per-file status differences** — every one of
the 74 failures is pre-existing and none of this pass's `tools/` changes caused
or fixed any of them.

Failure classes:

| # | class |
|---:|---|
| 25 | reads a `/private/tmp/g1-*-…/zephyr/…` build directory that no longer exists |
| 23 | assertion failure — committed receipt vs freshly rebuilt receipt has drifted |
| 19 | error raised inside the test (mostly the same missing-artefact cause) |
| 4 | missing repo-relative file |
| 1 | `ModuleNotFoundError: 'tools'` (`test_app_root_topology_gate.py` imports `tools.x`) |
| 1 | receipt sha mismatch (`test_mmio_parity_inventory.py`) |
| 1 | subprocess failure (`test_app_source_view.py`) |

Per the brief, none were fixed. The dominant class — a third of the suite —
depends on ephemeral `/private/tmp` build directories, which is the *same*
disease as Blocker 2 one level up.

One runner bug worth recording, because it manufactured 60+ false failures on
the first attempt: setting `PYTHONPATH = TOOLS + ":" + os.environ.get("PYTHONPATH","")`
emits a **trailing separator** when the outer variable is empty, an empty
`PYTHONPATH` entry means *the current directory*, and the repo root contains
`struct.py` — which shadows the stdlib `struct` module. The baseline above is
from the corrected runner.

---

## 4. `cfg_verify --self-test`

### 4.1 What was broken, and exactly what changed

At HEAD the suite **aborted** on the first of two negative controls whose
`correct` anchor no longer occurs in the source it names — the source was
rewritten after the control was written, `assert correct in source` fired, and
every control after it was never reached. Both were re-anchored on the current
text, preserving the mutation's intent:

| control | old anchor (gone from the source) | new anchor | mutation |
|---|---|---|---|
| `net_directed_negative_sources` → `FUN_0100f5d8` | `(pre_shift_mix << 26)` | `rotate_left(state_a, 26)` | `26` → `25`: move the recovered rotate one position |
| `directed_negative_sources` → `FUN_00065324` | `FUN_00065000(param_1, param_2);` | `FUN_00065000(domain);` | forward `0` instead of the live argument |

Both **bite**, measured individually:

```
FUN_0100f5d8  unmutated: PASS | mutated: FAIL  (checked 5, mismatches 3)
FUN_00065324  unmutated: PASS | mutated: FAIL  (checked 1, mismatches 1)
```

A new control block was **added** for the equivalence class of §1 — seven
fixture-level cases plus an end-to-end `verify()` triple on
`opt3007_chip_init` (unmutated PASS, literals-inlined PASS, corrupted-literal
FAIL). The `opt3007` case matters because its 22
`REVIEWED_CALL_ARITIES_BY_FORMAT` entries are keyed by the shipped format-string
address, so it exercises the content-resolved arity lookup as well as argument
comparison. All ten assertions verified:

```
same flash address        pass=True   expect=True
same string as C literal  pass=True   expect=True     <- the equivalence class
different real image str  pass=False  expect=False
null pointer              pass=False  expect=False
out-of-image 0xdeadbe00   pass=False  expect=False
interior of the string    pass=False  expect=False
non-string rodata object  pass=False  expect=False    <- byte-verified table @0x87b30
opt3007 unmutated         PASS
opt3007 literals inlined  PASS
opt3007 corrupted literal FAIL
```

Nothing was deleted, relaxed, or made conditional.

### 4.2 The suite still does not go green — and did not before

With the anchors repaired the run advances and then stops at a **different**
control, `net_directed_negative_sources` → `FUN_01019750`
(`extern int FUN_0100ca98(uint8_t, void*)` → `int8_t`): the mutation applies
cleanly and the verdict is still **PASS**. It is one of the reported vacuous
controls, and it is vacuous **at HEAD**:

```
new emu.py  -> mutated: PASS  checked 8
HEAD emu.py -> mutated: PASS  checked 8      # git checkout -- tools/parity/emu.py
```

So the two stale anchors were *masking* it. Repairing them did not break
anything; it made an already-dead control visible. Per the brief, unrelated
pre-existing failures were not fixed.

### 4.3 New tool: `tools/audit_negative_controls.py`

The structural problem is that `--self-test` asserts, so one dead control hides
the rest — which is how two stale anchors hid the corpus for however long. This
tool runs the same controls **without asserting** and reports each as `BITE` /
`VACUOUS` / `STALE-ANCHOR` / `NO-SOURCE` / `NOOP` / `ERROR`, with `--static`,
`--start`, `--limit`, `--core` and `--list-name` for sharding.

Static pass, after the two re-anchors:

```
$ python tools/audit_negative_controls.py --static
controls examined: 406
  STATIC-OK        406
```

**406** is exactly the control count the brief cites, and there are now **zero**
stale anchors, zero missing sources and zero no-op mutations. The dynamic pass
(one `verify()` per control) is the measurement that turns "397 of 406 bite"
into a named list; it runs for hours, so it is left as a sharded command rather
than a number quoted here:

```
$ tools/audit_negative_controls.py --start 0 --limit 68 --json shard0.json   # x6
```

**Dynamic pass — partial, and the partiality matters.** A first sharded run
covered **294 of 406** controls before it was stopped: **293 BITE, 1 VACUOUS**.
The one dead control it named is `app_random_negative_sources` →
`FUN_0004e604` (`FUN_0004e540(param_1, &local_24)` → wrong argument), a
*random*-budget list, so the audit's budget matched the suite's there and the
result is directly comparable.

That first run used a uniform 8-trial random budget for every control, which is
**wrong for the 301 controls in the `*_directed_*` lists** — the suite asserts
those with `trials_random=0`, and extra random trials can only make a control
*more* likely to bite. A BITE measured at 8 trials therefore does not prove the
suite's assertion at 0. The tool was corrected to mirror the suite's per-list
budget and re-launched; that run had not finished at hand-off.

The dynamic pass ran to completion over **all 406** controls:
**399 BITE, 6 VACUOUS, 1 VACUOUS-FAIL**. Full receipt:
`recon/analysis/harness_unblock_negative_controls.json`.

That reconciles exactly with the brief. 406 controls, 9 not biting at HEAD =
**2 stale anchors** + **7 dead controls**. This pass repaired the 2 anchors and
both now bite, so 397 → **399 bite**; the remaining 7 are all pre-existing and
all named below.

The run also produced a distinction the first pass's labels missed, and the tool
now names it explicitly:

* `VACUOUS` — the mutated source still verifies `PASS`. The suite's `assert`
  fires and the run aborts.
* `VACUOUS-FAIL` — `verify()` returns `FAIL` **with `checked == 0`**: no case
  was generated, so nothing was exercised. The suite's `assert status == "FAIL"`
  is **satisfied**. This is the worse kind: it looks green forever.

Dead controls named so far, each **verified pre-existing by re-running it
against `git checkout -- tools/parity/emu.py`**:

| control | list | audit verdict | HEAD |
|---|---|---|---|
| `FUN_01019750` (`uint8_t` → `int8_t`) | `net_directed_negative_sources` | VACUOUS | PASS, checked 8 — dead |
| `FUN_010388c8` (`FUN_0103b442(p,1)` → `(p,2)`) | `net_random_negative_sources` | VACUOUS | PASS, checked 8 — dead |
| `FUN_00081080` (`~0x8000u` → `~0x4000u`) | `directed_negative_sources` | VACUOUS-FAIL | FAIL, **checked 0** — dead but asserts green |
| `FUN_0004e604` (`FUN_0004e540(param_1, &local_24)`) | `app_random_negative_sources` | VACUOUS | — |
| `FUN_0004e780` (`0x0007f211`) | `app_random_negative_sources` | VACUOUS | — |
| `FUN_0004ee68` (`FUN_00080d3e(*context, work.common + 4)`) | `app_random_negative_sources` | VACUOUS | — |
| `ancs_connected` (`*(volatile unsigned char*)(iVar5+0x367) = 1;`) | `app_random_negative_sources` | VACUOUS | — |

**Seven dead controls** — exactly the population the brief reported, now named.
None was caused by this pass: the three re-run against
`git checkout -- tools/parity/emu.py` behave identically at HEAD, and the other
four live in `app_random_negative_sources`, a list this pass does not touch.
**Four of the seven sit in that one list**, which is where to start.

Also worth flagging for whoever picks this up: `FUN_00081080` is the dangerous
shape. It satisfies `assert status == "FAIL"` while `checked == 0`, so it has
been reporting green while proving nothing, and no amount of running the suite
would ever have revealed it. That is the reason `audit_negative_controls.py`
distinguishes `VACUOUS-FAIL` from `VACUOUS` at all.

---

## 5. Still blocked

1. **Net string literals (116 candidates).** §1.5 — needs a provenance rule for
   the CPUNET analysis/runtime overlap, and the net rodata objects wired first.
2. **The nine-tree reconciliation (918 files).** §2.4. `symbolize.py` runs, but
   running it over `recon/**` reverts G6 and ~790 retired linker pins. Blocked on
   a push-back pass that only the tree owner can do.
3. **74 pre-existing test failures**, a third of them on vanished `/private/tmp`
   build directories. Establishing them was in scope; fixing them was not.
4. **Non-string read-only objects** keep exact address comparison by design. If a
   future batch needs to inline a const *table*, that is a separate equivalence
   class needing a known extent, and this one will not cover it.
5. **`tools/full_link.py app` fails**, and failed before this pass
   (`spawn_display_thread.c` needs `<zephyr/kernel.h>`); untouched here.
6. **7 dead self-test controls** (§4.3), four of them in
   `app_random_negative_sources`. Repairing them means finding a mutation that
   is actually observable for each body — reviewer work, not mechanical.
7. **Stack-passed record contents** are only compared when a reviewed
   `stack_objects` declaration exists, so ~45 % of the sampled string sites are
   invisible to parity in either direction (§1.3.1). Pre-existing; measured
   here for the first time. Closing it is the highest-value remaining harness
   improvement, and it is independent of everything above.
