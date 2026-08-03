# G1disasm2 — Even Realities G1 firmware reconstruction

Reconstruction of the **Even Realities G1** smart-glasses firmware, from the
owner's own shipped binaries into buildable NCS 2.5.1 / Zephyr C.

Target: **Nordic nRF5340**, dual core.

| | |
|---|---|
| CPUAPP | `app_update.bin`, link base `0xC200` (MCUboot header at `0x200`) |
| CPUNET | `netcore_image.bin`, analysis base `0x01008000`, runtime/link base `0x01008800` |

> **Every claim in this file is a measurement, with the command that produced it.**
> An earlier incarnation of this document asserted the project "compiles, links and
> packages" for many commits *after* that had stopped being true — the regression
> was found by baseline-checking, not by reading the README. Numbers below were
> re-measured on **2026-07-29**; re-run them rather than trusting them.

---

## State

### Both cores build and link

```bash
recon/application/build_cohesive.sh app /tmp/g1-app
recon/application/build_cohesive.sh net /tmp/g1-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
```

| core | result | flash | RAM | undefined syms |
|---|---|---|---|---|
| app | exit 0, 0 `error:` | 956,840 B / 982,528 B — **97.39 %** | 253,765 B — 56.32 % | **0** |
| net | exit 0, 0 `error:` | 225,581 B / 226 KB — **97.48 %** | 62,868 B — 95.93 % | **0** |

⚠ **The net core's `-DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF` flag is required.** The
default retain-all mode is an *ownership audit*, not a physical link, and is
**expected** to overflow FLASH by ~303 KB. That overflow is not a defect.

### It boots, and it renders

Loaded into [Renode](https://renode.io) via the `armemul` platform, the
reconstruction boots both cores, brings up rpmsg IPC, advertises and accepts a
BLE connection, drives the ESB L/R link, and paints the display.

The **JBD013VGA-4010** micro-LED projector output is reconstructed independently
from the SPI byte stream and compared pixel-for-pixel against the shipped
firmware's:

```
dashboard  p1_boot    byte-identical      dashboard  p2_render  byte-identical
navigation p1_boot    byte-identical      navigation p2_render  byte-identical
```

Peripheral traffic matching the shipped firmware byte-for-byte includes the
display SPI stream (whole-run transaction count exact), IMU (LSM6DSO), PMIC
(nPM1300), ambient light (OPT3001), NFC (ST25DV, including the WLC NDEF record
payloads), ADC (998/998 conversions), GPIOTE keys, and the ESB radio frame count.

Captures are deterministic under a fixed seed (`G1_SEED`); two runs of the same
image are byte-identical **including the tick column**.

---

## Layout

| path | what it is |
|---|---|
| `recon/app/src`, `recon/net/src` | **canonical evidence trees** — flat, address-keyed (`FUN_<addr>.c`), one function per file. 2,153 app / 1,177 net. Never refactored. |
| `recon/symbolized/{app,net}` | the **compiled** sources — what the build actually consumes |
| `recon/refactor/` | the staged refactor ladder — 10 stages, each in its own directory |
| `recon/application/` | the cohesive build (CMake, prj.conf, generated source lists) |
| `recon/board/` | devicetree overlay, pin/bus map, board evidence |
| `recon/emulator/` | Renode capture scripts, display/sensor oracles, bring-up reports |
| `tools/` | extraction, parity, naming, and the `modtest` harness |
| `recon/tests/` | golden test vectors — 947 app, 376 net |
| `recon/analysis/` | measurement reports; the primary written record |
| `AGENTS.md` | **entrypoint** — current phase, open items, and what is *not* evidence |

**The canonical trees are evidence, not source you edit for taste.** Roughly 40
tools and 50 test files resolve functions inside them by
`os.path.join(<flat dir>, name + ".c")`. Refactoring transformations never land
there; each step materialises its own directory under `recon/refactor/`.

---

## The refactor ladder

`stage_N = transformer(stage_N-1)` — reproducible, zero hand-edits, compiles first
try. A compile failure is proof the *transformer* is wrong, not a task to hand-fix.

```
00 snapshot → 01 literals → 02 dedupe → 03 modules → 04 cohesive TU
   → 05 composition → 06 unit composition → 07 internal linkage
   → 08 call order → 09 call cohesion
```

Result: **1,615 app translation units → ~660**, across 22 module directories;
include directives 2,423 → 850. Eight of ten steps are proven by **byte-identical
captures**; the rest by a phase criterion whose bound is derived from
shipped-vs-shipped, never from our own build's error.

`recon/refactor/README.md` holds the authoritative gate record. `driver.py status`
reports staleness; a stale stage is **regenerated, never patched**.

```bash
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py status
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize 9
```

---

## Testing

`tools/modtest` generates golden vectors by emulating each function's **original
bytes from the shipped image** under Unicorn. The oracle is the original
firmware — never our reconstruction, which would only prove self-consistency.
Vectors bind to **symbols**, so one vector runs against both the canonical and
refactored trees.

```bash
PYTHONSAFEPATH=1 .venv/bin/python tools/modtest/cli.py run app <symbol>
PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_guards.py
```

Every run reports **measured instruction coverage** and a **mutation kill rate**;
vectors are stamped with a harness revision and replay **fails closed**.

**Current quality — below target, stated plainly:** no module meets the 70 %
coverage bar; coverage runs ~48–70 % by module (`ui` is worst at 10 %), and kill
rate sits near 60–70 %. A suite that passes while touching a fraction of the code
licenses restructuring it cannot see, so these numbers gate the next phase.

---

## Conventions that will bite you

- **`PYTHONSAFEPATH=1` on every Python invocation.** A local `struct.py` shadows
  the stdlib module otherwise. Use `.venv/bin/python`.
- **App image reads go through `tools/extract.py`** — the MCUboot header offsets
  everything by `0x200`. A naive `va - 0xC200` yields garbage.
- **The net core has two address spaces** — analysis `0x01008000` vs runtime
  `0x01008800`, delta `0x800`. Use `tools/net_address_space.py`. At least three
  separate defects trace to conflating them.
- **`cfg_verify` is not evidence.** It passes broken code, and has been shown
  blind in both directions — passing a body with every log pointer replaced by
  garbage, and *failing* a correct repair. Never cite a green result from it.
- **`human: true` in the name catalogs means "not a raw `FUN_xxxx` stub"** — it
  records name *shape*, not provenance, and implies no review.
- **Don't anchor parsers at end of line.** Eight separate defects here came from
  scanners defeated by trailing comments, `-aux-info` suffixes, comma-separated
  declarators, and jump tables disassembling as plausible instructions.

---

## Known-open

- Three previously-named "real defects" are now classified **undecidable** — the
  oracle does not model callee out-parameters, which accounts for them and for 27
  of the net core's failures.
- `i2c_read_reg16_be` is a **false proof**: a 32-byte descriptor spelled as six
  loose locals. Passes the harness; wrong.
- QSPI/external flash is stock `nordic,qspi-nor` and correctly configured against
  the shipped `qspi_nor_config`, but **untraced** — no capture exercises it.
- The emulator's JBD model may drop one byte per `0x02` transaction; the firmware
  itself disagrees on the trailing dummy byte. Unresolved, and it would touch
  every framebuffer comparison.
- Coverage and kill rate are below bar corpus-wide (see Testing).

`AGENTS.md` carries the maintained list.

---

## Provenance and scope

This is recovery of firmware from hardware the author owns, for interoperability
and repair. Third-party datasheets referenced for register semantics are cited in
`recon/analysis/` and not redistributed here. Nothing in this tree has been run on
physical hardware — every behavioural claim above is measured in emulation.
