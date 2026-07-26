# `.rodata` decode — CPUAPP and CPUNET

Generator: `recon/application/gen_app_rodata_sources.py`
Ledgers: `recon/ownership/rodata_decode_ledger.json` (app),
`recon/ownership/rodata_decode_ledger_net.json` (net)
Generated sources: `recon/application/rodata/` — **17 `.c` files + 2 `.ld`
fragments, none added to any CMake source list, no `recon/symbols/*.ld` edited,
nothing committed.**

Reproduce:

```sh
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py \
    --core app --elf /private/tmp/g1-i33c-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py \
    --core net --elf /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py --core app --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py --core net --check
```

`--check` is the determinism gate (10/10 and 9/9 files up to date on a rerun).
The byte-match gate is **on by default and runs before anything is written**:
candidates are compiled in a scratch directory, each defined symbol's bytes are
read back out of the object and compared with the shipped image; an object that
does not match is recorded as `deferred` and never becomes a file.

---

## 1. Sector extent (both edges proven, not assumed)

| core | sector | bytes | low edge | high edge |
|---|---|---:|---|---|
| app | `0x000879a8 .. 0x000f6d64` | 455,612 | highest catalogued function `FUN_00087996` ends at `0x879a6`; from `0x879b0` the image holds the Zephyr `struct init_entry` array (8-byte `{init_fn, device*}` records: `0x4c145`, `0x51199`, `0x61575`, … paired with `struct device` pointers into `0x87b..`), which is `.rodata`'s first subsection in `common-rom.ld` | `.data` load address, proven three independent ways by `gen_app_data_image.py --selftest` |
| net | `0x0103be56 .. 0x0103ed24` **runtime** | 11,982 | highest catalogued function `FUN_0103b650` ends at analysis `0x0103b656` = runtime `0x0103be56` | shipped net `.data` LMA `0x0103ed24` (`verify_net_stock_data_window.py`); `0x0103ed24 − 0x01008800 + 0xc3c` = 225,632 = `netcore_image.bin` exactly |

**CPUNET coordinate-space finding (new, and load-bearing).** The `rodata_<hex>`
pins in `recon/symbols/g1_net_globals.ld` are **RUNTIME** addresses (base
`0x01008800`), not analysis addresses — even though the net *function*
catalogue is in analysis space. Oracle, run over all 222 numeric net pins:
reading one byte early, **93** sit immediately after a NUL and start a printable
C string under `net_extract.read_runtime` versus **2** under `read_analysis`;
the runtime reads land exactly on `"(null)"`, `"HCI rpmsg TX"`, `"cpunet-esbs"`
and `"WEST_TOPDIR/zephyr/lib/…"`, while the analysis reads land mid-string
(`"f_timer.h"`, `"ion (%u)"`). All net reads in the generator go through
`read_runtime`; the function catalogue is converted explicitly with
`ANALYSIS_TO_RUNTIME_DELTA` and never by arithmetic on a bare integer.

## 2. Region model

A pin's extent is `[pin_va, next_boundary)`, boundaries being every other
numeric pin VA, the start and end of every already-emitted object
(`recon/data/*.c`, `g1_app_string_rodata.c`, `g1_app_font_rodata.c`,
`recon/net/data/*.c`) and the sector edges — the same two-sided argument
iteration 33 used for the font directory ("`0x98e3c` is where the next
recovered rodata symbol begins"), applied uniformly.

Consecutive pins whose extents touch are emitted as **one object** named after
the run's first pin, with the interior pins re-pinned as
`PROVIDE(rodata_X = <run> + delta)` in the generated fragment (precedent:
`PROVIDE(rodata_883b0 = rodata_0x88340 + 0x70)`). Emitting each pin separately
would let the linker split bytes the shipped image had adjacent — which is
exactly how the font directory and blob are read. The one place a run *is*
split is a pin that starts its own NUL-terminated string: a string is addressed
by its first byte and every reader stops at its NUL, so nothing can index out of
it, and splitting there restores `--gc-sections` granularity (this matters: the
net string table was otherwise one 11 kB all-or-nothing object on an image at
97 % of flash).

## 3. Inventory and classification

### CPUAPP — sector 455,612 B

| class | bytes | share |
|---|---:|---:|
| already emitted before this pass (`recon/data` 993 tables + string/font blocks) | 105,902 | 23.2 % |
| **emitted and byte-verified by this pass** | **251,039** | **55.1 %** |
| deferred by this pass (pointer-bearing, unresolved) | 2,200 | 0.5 % |
| unreferenced — no pin, no object, 279 gaps | 96,471 | 21.2 % |

### CPUNET — sector 11,982 B

| class | bytes | share |
|---|---:|---:|
| already emitted before this pass | 0 | 0.0 % |
| **emitted and byte-verified by this pass** | **7,796** | **65.1 %** |
| deferred by this pass | 3,860 | 32.2 % |
| unreferenced — 2 gaps (`0x0103be56` 282 B, `0x0103c190` 44 B) | 326 | 2.7 % |

## 4. Objects emitted, by kind — all byte-verified

| core | kind | C type | regions | bytes | verification |
|---|---|---|---:|---:|---|
| app | `string` | `const char []` | 264 | 9,112 | byte-exact |
| app | `string_pool` | `const char []` | 31 | 3,169 | byte-exact |
| app | `u8_table` | `const unsigned char []` | 2 | 66,574 | byte-exact |
| app | `blob` | `const unsigned char []` | 48 | 173,428 | byte-exact |
| app | `zero_fill` | `const unsigned char []` | 3 | 16 | byte-exact |
| app | `ptr_record` | `const unsigned long []` (relocated) | 2 | 232 | **byte-exact modulo relocation** |
| app | **total** | | **350** | **252,531** | 348 byte-exact + 2 modulo-relocation |
| net | `string` | `const char []` | 82 | 2,449 | byte-exact |
| net | `string_pool` | `const char []` | 30 | 4,704 | byte-exact |
| net | `blob` | `const unsigned char []` | 5 | 643 | byte-exact |
| net | **total** | | **117** | **7,796** | 117 byte-exact |

Each object is defined once, with the correct C type, and carries the shipped
pin name through `__asm__("rodata_<hex>")` — so the definition is typed while
`recon/symbols/g1_app_symbols.h`'s `extern const unsigned char rodata_X[];`
still binds at link time and no header has to change. All 17 files compile
clean with the pinned toolchain (`-Os -mcpu=cortex-m33 -mthumb -ffreestanding
-fdata-sections`).

**How each kind was decided (evidence, not shape-guessing):**

* **strings** — the extent is exactly a chain of NUL-terminated printable
  ASCII or valid UTF-8 runs. UTF-8 matters here: much of the G1 UI text is
  Chinese (`e5 be ae e4 bf a1` = the WeChat label at `0x9d789`), and treating
  those as opaque blobs would have hidden what they are. The decoded text is
  in each object's comment.
* **`u8/u16/u32_table`** — width read off the **access footprint**: the
  literal-pool word in `.text` that names the region is located, the
  `ldr rD,[pc,#imm]` that loads it is disassembled, and the width of the first
  memory access through `rD` (with intra-function taint propagation) is
  recorded. Only two app regions have that evidence — `rodata_aae20`
  (66,560 B, `ldrb` at `0x3b9b8` / `0x3c186` / `0x3d244`) and `rodata_f1590`
  (14 B, `ldrb` at `0x4e996`). **This is the honest limit of the technique on
  this image:** 251/253 in-sector pins are named by a `.text` literal, but only
  80 of those literal sites carry an in-function `ldr rD,[pc]` and the address
  is usually passed straight to a callee, so the width lives in the callee.
  Where width is not proven, the region is emitted as a byte-exact
  `unsigned char []` and the ledger records `width evidence: none` — nothing is
  guessed. Promoting the rest needs interprocedural argument taint, which is a
  separate piece of work.
* **blobs** — the large app blobs are the **three unrecovered font families**
  (`our_boot_bringup.md` §33.12 item 4). Their byte histograms are dominated by
  `0x00`/`0x0f`/`0xf0`/`0xff`, the signature of packed 4bpp glyph bitmaps:
  `rodata_aae20` 66,560 B, `rodata_d753a` 40,192 B, `rodata_d43bf` 11,700 B,
  `rodata_e17da` 11,310 B, `rodata_ce483` 6,800 B, `rodata_ca153` 5,800 B and
  ~30 smaller ones — 239 kB in total, previously emitted nowhere at all.
* **pointer-bearing regions** — any 4-aligned region ≤ 4,096 B with even one
  pointer-looking word, or any larger region with ≥ 20 % pointer-word density.
  Larger sparse regions use density because a 66 kB glyph blob contains
  thousands of incidental words inside the flash window (nibble runs like
  `00 f0 0f 00`). The string test runs **before** the pointer test: ASCII is
  full of 4-aligned words that land in a pointer window (any string with a
  space gives `0x20xxxxxx`, inside CPUNET's SRAM window — `"HCI rpmsg TX"`
  scored as pointer-bearing until the order was fixed).

**Relocated pointer objects.** The two emitted ones use the `__asm__`-alias
mechanism of `recon/emulator/reports/pointer_rebind.md` — no raw absolute word
is ever stored:

```c
extern const unsigned char __g1_rp_l2cap_accept[] __asm__("l2cap_accept");
const unsigned long g1_ro_87fc8[15] __asm__("rodata_87fc8") = {
    0x00000005,                                          /* scalar */
    (unsigned long)((const unsigned char *)__g1_rp_l2cap_accept + 1), /* was 0x00057469 */
    ...
```

For these, byte equality holds **only modulo relocation**, and that is stated
as such everywhere. The gate compares every non-pointer byte against
`app_update.bin` with the pointer windows masked, **and** additionally requires
the object to carry an `R_ARM_ABS32` relocation at exactly each masked offset
naming exactly the expected symbol. Status is recorded as
`byte-exact-modulo-relocation`, never as `byte-exact`.

## 5. Pins retired

| | app | net |
|---|---:|---:|
| numeric `rodata_` pins retired (all, incl. currently unreferenced) | **504** | **126** |
| of which via the interior-pin `.ld` fragment | 154 | 9 |

Against the **currently-absolute** pins — `nm` class `A`, the class §33.7 named
"356 absolute `A` symbols … the class is real and unswept" (341 today for app):

| status | app (of 341) | net (of 142) |
|---|---:|---:|
| already correctly rebound by an expression `PROVIDE` (`= sym + delta`); `A` only because ld folds the resolved expression | 12 | 1 |
| **retired by this batch** | **188** | **73** |
| falls in a region this batch **defers** | 65 | 31 |
| outside the sector, in `.text` (literal-pool words / Thumb code addresses Ghidra spelled `rodata_`) | 71 | 37 |
| outside the sector, in the `.data` load image (owned by `gen_app_data_image.py`) | 5 | 0 |
| unaccounted | **0** | **0** |

So the honest headline: **188 of the 341 app pins and 73 of the 142 net pins,
i.e. 261 of 483 across both cores, are retired by objects that byte-match the
shipped image today.** A further 12+1 were never really unswept. The rest is
enumerated below.

## 6. Deferred, with reasons

**App — 17 regions, 4,521 B** (all pointer-bearing; none is a string, blob or
numeric table).

| region | bytes | reason |
|---|---:|---|
| `rodata_87b30` | 252 | 40/50 pointer words unresolved (22 SRAM) — the `struct device` / `init_entry` neighbourhood |
| `rodata_8a3e0` | 2,112 | 140/144 unresolved |
| `rodata_880d8` | 488 | 39/63 unresolved |
| `rodata_88480` | 336 | 18/28 unresolved |
| `rodata_8ac30` | 276 | 26/46 unresolved (8 SRAM) |
| `rodata_9873c` | 364 | 2/4 unresolved (2 SRAM) |
| `rodata_99014` | 120 | 5/5 unresolved |
| `rodata_8bb90` | 89 | pointer-bearing but not word-sized (1-byte tail) — extent must be re-derived first |
| 9 more | 484 | same two causes |

**Net — 5 regions, 3,860 B**: `rodata_103bf70` (544 B, 18/62 unresolved, 13
SRAM), `rodata_103c24c` (2,772 B, 78/120 unresolved), `rodata_103d758` (163 B)
and `rodata_103eba0` (369 B) not word-sized, `rodata_103ed18` (12 B).

Two causes only, and both are deliberate:

1. **Atomic EXCLUDE** (`gen_app_data_image.py`'s proven policy): a table that
   gets its selectors but not its handlers is strictly worse than an all-zero
   one, so unless **every** pointer word resolves to a symbol this project
   defines, the whole region is held back. Unresolved words are of three sorts,
   all recorded per region in the ledger: SRAM addresses (need the `.data`/RAM
   relocation classes), flash addresses inside objects nothing has named yet,
   and — for the biggest net region — words like `0x01010101` and `0x01008800`
   that are almost certainly **data, not pointers**, mis-flagged by the window
   test. Those two are conservative deferrals and are the best manual-review
   candidates.
2. **Not word-sized**: the run's derived extent has a 1–3 byte tail, so the
   pointer words cannot be laid out without first re-deriving the extent.

Nothing is deferred for failing the byte-match gate: **every object the gate
ran on passed** (348 byte-exact + 2 modulo-relocation for app, 117 byte-exact
for net).

## 7. What is still not covered

* **96,471 B of app `.rodata` (21.2 %) that no pin and no object names**, in
  279 gaps; the largest are `0x90c5c` (30,948 B — a monotone `uint32` sequence
  starting 3, 4, 5, 6 …), `0xa49ef` (6,910 B), `0x88a54` (5,628 B — a float
  table stepping 0.005: `0x3ba3d70a`, `0x3c23d70a`, `0x3c75c28f` …),
  `0x8ed57` (4,361 B), `0x8dc96` (4,282 B — `{u16 width, u16 cumulative}`
  glyph-directory shape). These carry no symbol, so no reconstructed source can
  currently read them and emitting them would add flash for an object with no
  referrer. They are listed in the ledger's `unreferenced_regions` so a later
  pass can attach them to whatever object really owns them — several are
  visibly interior continuations of a neighbouring table.
* **113 out-of-sector `rodata_` pins** (71 app + 37 net in `.text`, 5 app in
  the `.data` load image). The `.text` ones are literal-pool words and Thumb
  code addresses that Ghidra spelled `rodata_`; they need the
  `net_rodata_gap_resolutions.json` treatment (classify as code pointer / alias
  / real table), not a rodata decode. The `.data` ones belong to
  `gen_app_data_image.py`.
* **`recon/structs/struct_catalog_app.json` contributed nothing here.** All 676
  verified layouts are based at RAM globals; **zero** of them is based in the
  `.rodata` range, so no region could be emitted as a real struct array from the
  catalogue. The struct-typed rodata objects the project has (`gpio_dt_spec`,
  `linear_range`, the ST25DV ops vtable, the BT advertising operands) were all
  hand-identified and are already in `recon/application/app/src`. Extending the
  catalogue into `.rodata` is the prerequisite for turning the decoded blobs
  into typed struct arrays.

## 8. Recommended wiring order — safest first

Wire **when the parity bring-up pauses**, one batch per build, checking
`nm -u` (0 undefined), duplicate-definition count and the flash figure after
each. Batch 1 alone is the whole "log strings garble under `_FORTIFY_SOURCE`"
class; batch 4 is the one that changes the flash budget materially.

| # | batch | files | regions | bytes | bytes pulled in **today** (referenced pins only) | why this order |
|---|---|---|---:|---:|---:|---|
| 1 | **app strings + string pools** | `g1_app_rodata_0*.c` (string regions) | 295 | 12,281 | 2,099 | Zero pointers, zero adjacency risk, identical in kind to `g1_app_string_rodata.c` which is already in the build. `--gc-sections` drops the unreferenced ones. |
| 2 | **net strings + string pools** | `g1_net_rodata_0*.c` (string regions) | 112 | 7,153 | 4,506 | Same class. **Check flash first** — see the warning below. |
| 3 | **small blobs + zero-fill, both cores** (every emitted non-string region < 1 kB) | both prefixes | 54 | 4,958 | 2,289 | Byte-exact, no pointers, negligible flash. |
| 4 | **the four font/bitmap blobs** *(with `g1_app_rodata_interior.ld`)* | `g1_app_rodata_0*.c` | 4 | 235,703 | 235,703 | This is the §33.12 item 4 fix — `rodata_aae20` 66,560 B, `rodata_c7956` 63,517 B, `rodata_d753a` 59,944 B, `rodata_bc097` 45,682 B, the remaining font families' packed 4bpp glyph bitmaps. **Must** go together with the interior-pin fragment, and preferably **one blob per build** so a raster regression is attributable to one family. |
| 5 | **the two relocated `ptr_record` objects** | `g1_app_rodata_ptr.c` | 2 | 232 | 232 | Relocation-bearing: needs the `nm -u` gate to confirm every `__asm__` alias target is defined by the link. |
| 6 | *(work, not wiring)* resolve the 22 deferred pointer regions | — | 22 | 8,381 | — | Retires a further 65 app + 31 net absolute pins. Start with `rodata_103c24c` and `rodata_103ed18`, whose "unresolved pointers" (`0x01010101`, `0x01008800`) look like mis-flagged data. |
| 7 | *(work, not wiring)* the 96 kB of unreferenced app `.rodata` | — | 279 | 96,471 | — | Needs owners, not decoding. |

**Wiring mechanics, in this order:**

1. Add the chosen `.c` files to `recon/application/app/CMakeLists.txt` /
   `net/CMakeLists.txt` (explicit source lists — the directory is not globbed,
   so simply creating the files changed nothing, which is why this pass is
   inert).
2. Ensure `-fdata-sections` is in effect for them, or batch 4's 240 kB is not
   gc-droppable.
3. For batch 4, **first delete the 154 matching
   `PROVIDE(rodata_X = 0x…)` lines** from `recon/symbols/g1_app_globals.ld`
   (9 for net), *then* include `g1_app_rodata_interior.ld`. Two `PROVIDE`s for
   one symbol is a conflict, not an override. The fragment header repeats this.
4. Re-run `--check` after any regeneration so the tree stays deterministic.

**Flash budget — read before batches 2 and 4.**

* App is at 635,096 / 982,528 B = 64.64 %. The app regions whose pins are
  referenced *today* total 240,044 B, so wiring app batches 1, 3, 4 and 5 takes
  the image to roughly **89 %** — and 235,703 B of that is batch 4 alone. It
  fits, but it is the single largest flash change this project has made, and
  almost all of it is font pixels; hence the one-blob-per-build
  recommendation. Batches 1, 3 and 5 together cost only 4,341 B.
* **Net is at ~225,073 / 231,424 B = 97.3 %.** Batch 2's referenced bytes alone
  are 4,506 B, which would put it at **99.2 %**. Wire net only after
  re-measuring, and be ready to take only the strings the raster/log path
  actually reaches rather than the whole batch.

## 9. Honesty notes

* Every number above is from a command that was run. The verification gate was
  executed on all 467 emitted objects; 465 are `byte-exact` and 2 are
  `byte-exact-modulo-relocation` with the relocation identity checked. No
  object was counted as matching without the compile-and-compare having run.
* No claim is made that a wired build boots, links or renders — **nothing was
  wired and no image was built this pass**, by instruction.
* Element widths are unproven for all but two regions and those regions are
  emitted as byte arrays and labelled as such. `blob` means "byte-exact and its
  element type is not yet proven", not "unknown bytes".
* The 22 deferred pointer regions are conservative, not impossible: the ledger
  records, per region, how many words resolve, how many are SRAM, and the first
  unresolved value, so the follow-up is a work list rather than a re-analysis.

---

## 10. WIRED — P4 iteration 35 (measured; supersedes §9's "nothing was wired")

`recon/emulator/reports/our_boot_bringup.md` §35.  Two builds, both linking
with **0 undefined, 0 duplicate globals, no `--allow-multiple-definition`, no
weak symbols**.

| build | what was wired | FLASH | % of 982,528 B | Δ |
|---|---|---:|---:|---:|
| `g1-i34a-app` | nothing from this decode | 737,504 B | 75.06 % | — |
| `g1-i35a-app` | `g1_app_rodata_02.c` — batch 4's `rodata_d753a` (59,944 B glyph bitmaps) + 4 interior pins | 800,264 B | 81.45 % | **+62,760 B** |
| **`g1-i35b-app`** | **files 01–07** = batch 1 + batch 3 + batch 4's `rodata_c7956` and `rodata_bc097` + 148 interior pins | **921,576 B** | **93.80 %** | **+184,072 B** |

RAM is **unchanged** (253,765 B) in both — the decode is all `.rodata`.

### What this pass got right, and the one thing it missed

Right: every wired object is byte-exact **in the linked ELF**, not just in the
source.  Read back out of `zephyr.elf`'s PT_LOAD and compared with
`app_update.bin`: `rodata_d753a` (59,944 B) **True**, and the interior
arithmetic survives the link (`rodata_c7956 = 0x0b889d`,
`rodata_c81a3 = 0x0b90ea` = `+0x84d`).  Wiring `rodata_d753a` is what
eliminated iteration 34's `fortify_chk_fail` reboot and produced the project's
**first dashboard render**.

Missed: §2's region model treats an **already-emitted object** as a boundary,
so where `gen_app_string_rodata.py` had wrongly emitted a **2-byte string
stub** the decode recorded *no region at all* and the real data was never
emitted.  Three of the four objects the dashboard needed were in exactly that
state — `rodata_98e3c` / `_98fbc` / `_98fe8`, the glyph directories of font
style 3 and both clock-digit families (384 + 44 + 44 B).  They had to be
recovered by hand into `g1_app_font_rodata.c`.  **Any future pass should treat
a suspiciously short "already emitted" object as a boundary to re-derive, not
to trust.**  (`rodata_8ac2c` was the same stub over a region that
`recon/data/rodata_0x8ac20.c` already owned byte-exactly; it is now
`PROVIDE(rodata_8ac2c = rodata_0x8ac20 + 0xc)`.)

### Correction to §8's flash estimate

§8 predicted ~89 % on the basis of "referenced pins only" (240,044 B) and
`--gc-sections` dropping the rest.  Measured, `--gc-sections` drops **nothing**
here: `recon/application/app/g1_verified_rodata_keep.ld` contains
`KEEP(*rodata_*.c.obj(".rodata.rodata_*"))`, and the generated file names
`g1_app_rodata_0N.c` match `*rodata_*.c.obj`, so **every** object in a wired
file is retained.  The real cost is the file's full declared size.  That is why
`g1_app_rodata_00.c` (68,690 B) is **withheld**: it would put the image at
**990,265 B against a 982,528 B partition**.  Wiring it needs either a
narrower KEEP pattern or a per-object split of that file.

### Corrections to §8's wiring mechanics

* The 154-line `g1_app_rodata_interior.ld` **cannot be included as a unit**
  unless files 00–07 *and* `g1_app_rodata_ptr.c` are all wired: 6 of its lines
  re-pin onto `rodata_87fc8` / `rodata_88388` (batch 5) and `rodata_8af10` /
  `rodata_a8e98` (file 00), and GNU ld rejects a `PROVIDE` whose expression
  names an undefined symbol.  Iteration 35 wrote the **148 usable lines
  directly into `g1_app_globals.ld`, in place of the numeric pins they
  replace** — the same deletion the fragment's header demands, the same
  expressions, one source of truth.
* The numeric pin of a **run base** that is now a real object should be
  **deleted, not left inert**: if the object is ever dropped, an inert
  `PROVIDE(rodata_X = 0x…)` silently resurrects the original-image address and
  the reader gets garbage again, whereas with the pin gone the link fails
  loudly.  Done for `rodata_d753a`.
* Duplicate check before wiring: 9 symbols (`rodata_9adaa`, `rodata_9d7b8`,
  `rodata_a819e`, `_a81b7`, `_a81d0`, `_a81e6`, `_a81fa`, `_a835e`, `_a8373`)
  are defined by **both** `g1_app_string_rodata.c` and `g1_app_rodata_00.c`.
  They cost nothing today only because file 00 is withheld; wiring it must
  withdraw those nine stubs first.

### Status by batch

| batch | status |
|---|---|
| 1 — app strings + string pools | **WIRED** (files 01–07 portion) |
| 2 — net strings | not wired; net is still at ~97.3 % of its partition |
| 3 — small blobs + zero-fill, app | **WIRED** (files 01–07 portion) |
| 4 — the four font/bitmap blobs | **3 of 4 WIRED**: `rodata_d753a` (59,944 B), `rodata_c7956` (63,517 B), `rodata_bc097` (45,682 B).  `rodata_aae20` (66,560 B, file 00) does not fit — see above |
| 5 — the two relocated `ptr_record` objects | not wired |
| 6, 7 — deferred regions and the 96 kB unreferenced | unchanged |
