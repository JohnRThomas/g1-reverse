# Projector SPI pin provenance — are the recovered pins fixed, or identity-selected?

**Date:** 2026-07-29 · **Scope:** app core (`app_update.bin`, link base 0xC200) ·
**Method:** static resolution of the writer + Renode RAM watchpoint on the
projector-controller struct's pin bytes, on the **stock** image (`g1.resc`).

---

## 1. VERDICT — **(a) FIXED IMMEDIATES**

The projector SPI pin numbers are **compile-time constants in this firmware
image**. They are not read from a strap, a GPIO, UICR/FICR, a lookup table, or
any other identity input. There is exactly **one** writer of each pin byte, and
it runs **before** the firmware has read the DEVICE_ID straps at all.

Two instructions, both in `main` (`FUN_00016eb8` @ `0x16eb8`), set all six bytes:

```
;  r4 = device_info base (heap) ; projector-controller struct = r4 + 0xb10
0001719a  2f4b         ldr    r3, [pc, #0xbc]      ; -> literal @0x17258 = 0x0a090804
0001719c  c4f824ab     str.w  sl, [r4, #0xb24]     ; struct+0x14
000171a0  c4f8283b     str.w  r3, [r4, #0xb28]     ; struct+0x18  <-- mode/SCK/MOSI/MISO
000171a4  42f20b03     movw   r3, #0x200b
000171a8  a4f82c3b     strh.w r3, [r4, #0xb2c]     ; struct+0x1c  <-- SS / speed
000171ac  04f53163     add.w  r3, r4, #0xb10       ; = &projector_controller
000171b0  1846         mov    r0, r3
000171b2  0593         str    r3, [sp, #0x14]
000171b4  0ff0f2f9     bl     #0x2659c             ; install the ops vtable (see §3)
000171b8  00f042fc     bl     #0x17a40             ; button_init  <-- FIRST strap read, AFTER
```

Decoded (little-endian byte order at struct+0x18):

| struct off | value | meaning | provenance |
|---|---|---|---|
| +0x18 | `0x04` | bus/mode selector | literal word `0x0a090804` @ VA `0x17258` |
| +0x19 | `0x08` | **SCK = P0.08** | same literal |
| +0x1a | `0x09` | **MOSI = P0.09** | same literal |
| +0x1b | `0x0a` | **MISO = P0.10** | same literal |
| +0x1c | `0x0b` | **SS = P0.11** | `movw r3,#0x200b` immediate @ `0x171a4` |
| +0x1d | `0x20` | speed multiplier = 32 (→ 32 MHz) | same `movw` immediate |

These are the fields `spi_master_init` (`0x26418`) later reads via
`ldrb r7,[r4,#0x19]` / `ldrb.w ip,[r4,#0x1a]` / `ldrb.w lr,[r4,#0x1b]` /
`ldrb.w r8,[r4,#0x1c]` / `ldrb r3,[r4,#0x1d]`, exactly as stated in the brief.

**Consequence: the recovered pins P0.08 / P0.09 / P0.10 (and P0.11 for CS) are
universal for every unit running this image.** Nothing in the emulated
environment can change them. See §5 for the one honest limit on that statement.

---

## 2. The watchpoint evidence (the decisive measurement)

The struct is heap-allocated. A hook at `spi_master_init` entry reading `r0`
gave its address directly, reproducibly across three runs:

```
PROBE-INIT r0=0x20053c60 bytes18_1d=04 08 09 0a 0b 20
```

`0x20053c60` = `device_info(0x20053150) + 0xb10`, consistent with the static
`add.w r3, r4, #0xb10` above (and with `g1.resc`'s own note that
`device_info = *(0x200069fc) = 0x20053150`). So the pin bytes live at
`0x20053C78 … 0x20053C7D`.

Watchpoints were placed on **all six bytes at Byte, Word and DoubleWord width**,
write access, capturing PC and value, over a **30-second** stock boot
(`/private/tmp/g1pinprov/p3.resc`). The complete set of writes observed, in
`cpu.ExecutedInstructions` order:

```
SEQ 5140602  WP-B  +0x18  pc=0x00086c82  val=0x00      ; memset/zero of the allocation
SEQ 5140606  WP-B  +0x19  pc=0x00086c82  val=0x00
SEQ 5140610  WP-B  +0x1a  pc=0x00086c82  val=0x00
SEQ 5140614  WP-B  +0x1b  pc=0x00086c82  val=0x00
SEQ 5140618  WP-B  +0x1c  pc=0x00086c82  val=0x00
SEQ 5140622  WP-B  +0x1d  pc=0x00086c82  val=0x00
SEQ 5173848  WP-DW +0x18  pc=0x000171a0  val=0x0a090804   <-- THE WRITER (literal)
SEQ 5173850  WP-W  +0x1c  pc=0x000171a8  val=0x200b       <-- THE WRITER (movw imm)
SEQ 5173865  BUTTON_INIT-ENTRY (strap reader) pc=0x00017a40
SEQ 5186636  GPIO_PIN_GET pin=26        ; DEVICE_ID1
SEQ 5186668  GPIO_PIN_GET pin=25        ; DEVICE_ID2
SEQ 5186700  GPIO_PIN_GET pin=28        ; DEVICE_ID3
SEQ 5186732  GPIO_PIN_GET pin=27        ; DEVICE_ID4
SEQ 6085406  PROBE-INIT r0=0x20053c60 bytes18_1d=04 08 09 0a 0b 20
SEQ 6085628  NRFX_SPIM_INIT r0=0x20053c6c r1=0x20031258
```

**No other write to any of the six bytes occurred in 30 s of emulated runtime**,
which spans full display bring-up (three JBD pixel-window frames were pushed).

**The ordering is the structural proof against (b):** the four DEVICE_ID straps
(P0.26/25/28/27) are first read **12,788 instructions after** the pin bytes are
already written, inside `button_init` @`0x17a40`, which `main` calls at `0x171b8`
— four instructions *after* the `str.w`/`strh.w` pair. An identity read cannot
influence a value written before it exists.

End-of-run readback confirms nothing later changed them:

```
struct+0x18 dw: 0x0A090804
struct+0x1c dw: 0x0000200B
```

---

## 3. Why the two prior static scans failed, and why this one didn't

The install path is: `main` @`0x171b4` → `FUN_0002659c`, which is an ops-vtable
installer, not a pin setter:

```
0002659c  034b    ldr r3,[pc,#0xc]   ; 0x265ac = 0x00026419  spi_master_init
0002659e  0360    str r3,[r0]
000265a0  034b    ldr r3,[pc,#0xc]   ; 0x265b0 = 0x000262ad
000265a2  8360    str r3,[r0,#8]
000265a4  034b    ldr r3,[pc,#0xc]   ; 0x265b4 = 0x00026339
000265a6  4360    str r3,[r0,#4]
000265a8  7047    bx  lr
```

The pins are **not** written by `strb` and **not** built from `movs rD,#8..#11`.
They are written as **one 32-bit `str.w` of a PC-relative literal plus one
16-bit `strh.w` of a `movw` immediate**. Both prior scan shapes were therefore
looking for instructions that do not exist.

The byte run in the image is `04 08 09 0a` — **mode byte first**, then the three
pins. The previously-searched run `08 09 0a 0b` does not exist because `0x0b`
(SS) is *not* adjacent to MISO in memory: it comes from the separate `movw`.
Measured on `app_update.bin`:

| pattern | occurrences |
|---|---|
| `08 09 0a 0b` | **0** |
| `04 08 09 0a` | **1**, at VA `0x17258` (the literal above) |

The `0x0a090804` literal at `0x17258` is unique in the image, so there is no
alternative table of pin sets that some other path could select.

Callers, resolved by encoding-level BL scan over the whole image (not linear
disassembly, which desyncs on the `0x775d0` jump table):

| target | BL sites |
|---|---|
| `0x2659c` (ops installer) | `0x171b4` — **one**, in `main` |
| `0x26418` (`spi_master_init`) | **none** — reached only through the installed pointer |
| `0x26338`, `0x262ac` | **none** — likewise |

Word `0x00026419` occurs exactly once in the image, at `0x265ac`. So there is a
single projector-controller instance and a single pin-configuration site.

---

## 4. Corroboration

**4.1 Peripheral registers, re-measured here (not inherited).** After a 12 s
stock boot:

| register | value | decode |
|---|---|---|
| `0x5000A508` PSEL.SCK | `0x00000008` | P0.08 |
| `0x5000A50C` PSEL.MOSI | `0x00000009` | P0.09 |
| `0x5000A510` PSEL.MISO | `0x0000000A` | P0.10 |
| `0x5000A514` PSEL.CSN | `0xFFFFFFFF` | disconnected |
| `0x5000C508/50C/510/514` | all `0xFFFFFFFF` | SPIM4 fully disconnected |

Agrees with `pins_buses.md`. **The brief's inherited values are correct.**

**4.2 The firmware's own boot log, reproduced here** (`g_log_level`@`0x2000230c`
raised to 4 from a hook at `main` entry `0x16eb8`; UART0 analyzer attached):

```
uart0: spi_master_init(): *SPIM(4)speed=32M, sck=8, mosi=9, miso=10, ss=11
uart0: spi_master_init(): spim(bus=4): init finish
```

Note the firmware's second line calls the `%d` **`bus`**, confirming that
`SPIM(4)` prints the struct's `+0x18` *mode/bus selector*, **not** the nRF SPIM
instance number. The hardware actually driven is **SPIM2 @ `0x5000A000`**. This
is confirmed from the image: `spi_master_init` picks the `nrfx_spim_t` as

* `mode == 3` → `{p_reg = 0x5000C000, drv_inst_idx = 0}` (literal @`0x26558`) = SPIM4
* otherwise (here `mode == 4`) → `{p_reg = 0x5000A000, drv_inst_idx = 1}`
  (the two words at `0x883b0`) = SPIM2

`pins_buses.md`'s mode→instance table is correct; the `SPIM(4)` string is just
an easy misread.

**4.3 `nrfx_spim_init` argument capture.** Hook at `0x671d8` reading the config
struct it is handed:

```
NRFX_SPIM_INIT cfg=0x20031258 sck=8 mosi=9 miso=10 ss=11
```

---

## 5. Bounding the claim — what is universal, what is not

* **SCK P0.08, MOSI P0.09, MISO P0.10, CS P0.11, 32 MHz, bus/mode 4** are
  immediates in the image. Any unit running **this** `app_update.bin` drives
  exactly these pins. Nothing about the emulated environment selects them.
* The emulator's DEVICE_ID straps read **0**: `gpio0.IN` @`0x50842510` =
  `0x00540400`, i.e. bits 25–28 all clear. *(Caveat: this Renode `gpio0` model
  returns `IN == OUT`, so treat the strap level as indicative rather than
  authoritative.)* **This is irrelevant to the verdict** — the pins are written
  before any strap is read, so no strap value could have produced a different
  result.
* **The one limit, stated plainly:** this proves the pins are constants *in this
  image*. It does not prove Even Realities ships the same image to every
  hardware variant. If a variant exists with different projector wiring, it
  would have to carry a *different firmware build* with a different literal at
  `0x17258`. Nothing here can see other builds. But for the purpose that
  motivated the question — another project adopting these pins for a port
  against this firmware — the pins are safe, and they are safe for the strongest
  available reason: the firmware ignores board identity when choosing them.

---

## 6. Correction: `ss = 11` is **not** "firmware-declared only"

`pins_buses.md` currently caveats P0.11 as declared-but-unconfirmed because
`PSEL.CSN` stays `0xFFFFFFFF`. That reasoning is right about `PSEL.CSN` but the
conclusion is too weak — **P0.11 is register-confirmed, just through GPIO rather
than through the SPIM CSN route.** Watchpoints on `gpio0` during a stock boot:

```
NRFX_SPIM_INIT cfg=0x20031258 sck=8 mosi=9 miso=10 ss=11
WP OUTSET    0x50842508 pc=0x000852f6 val=0x00000800   ; bit 11 -> P0.11 driven high
WP PIN_CNF11 0x5084272C pc=0x00066eae val=0x00000303   ; DIR=out, input buffer disconnected
WP OUTCLR    0x5084250C pc=0x0008530e val=0x00000800   ; P0.11 asserted low
... OUTSET/OUTCLR of bit 11 repeating in lockstep with every JBD transfer ...
```

`0x852e6` is `nrf_gpio_pin_set` (writes `OUTSET`, `+0x8`), `0x852fe` is
`nrf_gpio_pin_clear` (writes `OUTCLR`, `+0xc`), `0x66e70` is
`nrf_gpio_cfg_output`. So `nrfx_spim_init` performs the standard
`pin_set` + `cfg_output` on `ss_pin = 11`, and P0.11 is then toggled around
every transfer — active-low software chip-select on **P0.08/09/10 + P0.11**.

*(Note: reading `PIN_CNF[11]` back after the run returns the reset value `0x2` —
this Renode `gpio0` model does not persist `PIN_CNF`. The **write** of `0x303`
is what is observed, and that is the evidence.)*

---

## 7. Proposed correction to `recon/board/pins_buses.md`

**First, a discrepancy with the brief:** `pins_buses.md` has **no line
containing the word "Open"** (`grep -i open recon/board/pins_buses.md` → no
matches). The claims that need correcting are in the "Projector control SPI"
block, lines 91–126. **I have not edited the file**; below is the proposed text.

### 7.1 Replace lines 120–122 (the "cannot be recovered statically" claim)

Current — **this inference is wrong**:

> Verified here before adoption: the byte run `08 09 0a 0b` does **not** occur
> anywhere in `app_update.bin`, confirming the pins are genuinely runtime-assigned
> and cannot be recovered statically.

Proposed replacement:

> **The pins ARE static, and the earlier "cannot be recovered statically"
> inference is WITHDRAWN.** The search pattern was wrong, not the image. All six
> bytes are immediates in `main` (`0x16eb8`): `str.w r3,[r4,#0xb28]` @`0x171a0`
> stores the PC-relative literal `0x0a090804` @ VA **`0x17258`** (mode 4, SCK 8,
> MOSI 9, MISO 10) and `strh.w r3,[r4,#0xb2c]` @`0x171a8` stores the `movw`
> immediate `0x200b` (SS 11, speed ×32). The in-image byte run is therefore
> `04 08 09 0a` — mode byte first — which occurs **exactly once**; `08 09 0a 0b`
> does not occur because SS is not adjacent to MISO in memory. A RAM watchpoint
> on the struct bytes over a 30 s stock boot shows these two instructions are the
> **only** writers. Provenance analysis: `recon/analysis/projector_pin_provenance.md`.

### 7.2 Replace the CSN caveat, lines 107–111

Current:

> **CSN caveat — do not present all four pins as equally confirmed.** … So
> SCK/MOSI/MISO are *register-confirmed*; **P0.11 as chip-select is
> firmware-declared only.**

Proposed replacement:

> **CSN routing note.** `PSEL.CSN` stays disconnected because `nrfx_spim` drives
> `ss_pin` in **software**. P0.11 is nevertheless **register-confirmed**, via
> GPIO instead of SPIM: `nrfx_spim_init` is handed `ss=11`
> (`{sck=8,mosi=9,miso=10,ss=11}` captured at `0x671d8`) and performs
> `nrf_gpio_pin_set(11)` (`OUTSET` `0x50842508` ← `0x800`, from `0x852f6`) then
> `nrf_gpio_cfg_output(11)` (`PIN_CNF[11]` `0x5084272C` ← `0x00000303`, from
> `0x66eae`); P0.11 is then toggled `OUTCLR`/`OUTSET` around every transfer.
> **All four pins are equally confirmed.**

### 7.3 Add, after the mode→instance sentence on line 89

> The `%d` in the boot log's `*SPIM(%d)` is the struct's `+0x18` **bus/mode
> selector**, not the nRF SPIM instance — the firmware's next line spells it
> `spim(bus=4)`. Mode 4 selects the `nrfx_spim_t` `{0x5000A000, idx 1}` stored at
> `0x883b0` (**SPIM2**); mode 3 selects `{0x5000C000, idx 0}` (SPIM4), from
> `spi_master_init`'s own literal pool at `0x26558`.

### 7.4 Add a provenance line to the recovered-pins table caption

> **Provenance: fixed immediates, not board-selected.** The DEVICE_ID straps
> (P0.26/25/28/27) are first read 12,788 instructions *after* the pin bytes are
> written, in `button_init` @`0x17a40`, which `main` calls at `0x171b8` — four
> instructions after the write. Board identity therefore cannot influence these
> pins in this image. See `recon/analysis/projector_pin_provenance.md` §1–§2.

---

## 8. Reproduction

Throwaway probe scripts (not committed) under `/private/tmp/g1pinprov/`:

| script | what it establishes |
|---|---|
| `p1.resc` | PSEL readback of both SPIM boxes; `r0` at `spi_master_init` |
| `p3.resc` | the decisive run — all-width watchpoints on the six pin bytes + strap-read ordering, 30 s |
| `p5.resc` | `nrfx_spim_init` config capture + GPIO `OUTSET`/`OUTCLR`/`PIN_CNF[11]` watchpoints |
| `p6.resc` | firmware's own `*SPIM(4)…sck=8, mosi=9, miso=10, ss=11` boot line, UART0 analyzer |

All runs: `echo "i @<script>" | ~/tools/Renode.app/Contents/MacOS/renode
--disable-xwt --console --plain`, cwd `~/Projects/armemul`, stock `g1.resc`,
no model changes. `models/NRF5340_SPIM.cs`, `models/NRF5340_TWIM.cs` and
`models/BLE_VirtualCentral.cs` were re-hashed before and after and are unchanged
(`BLE_VirtualCentral.cs` = `1f10e117632a1bb35668b68a8d70d5f9c3682740116eac7a077bbb2046112572`).

Static helpers: `/private/tmp/g1pinprov/{dis,words,find,bytefind,blscan}.py`.

**No `cfg_verify` result is cited anywhere in this report.**
