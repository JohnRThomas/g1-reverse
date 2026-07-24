# Display + Sensor Parity Oracle — shipped Even Realities G1 firmware

`display_sensor_oracle.json` is a **peripheral-transaction oracle** of the
SHIPPED G1 images running in Renode. Where `golden_boot_trace.json` records
*function entries* (control flow), this file records *what the firmware actually
did to the hardware*: every SPI byte the JBD microdisplay received, every I2C
byte every sensor exchanged, every SAADC/PDM/GPIOTE register access, and the
resulting **pixel-exact framebuffer**.

It is the diff target for owner-goal acceptance tier **E6 = graphics + sensor
parity** (see `recon/emulator/BUILD_BOOT_PARITY_PLAN.md`).

* Images (read-only): `app_update.bin` `e0614feb…b42fd3b`,
  `netcore_image.bin` `ec4e4b60…158f7ca4`.
* **The original really renders.** Two different dashboard strings are rendered
  by the firmware's own raster path, with zero pokes:
  * `golden_framebuffer_p1_boot_crop.png` → *"Your route is being generated…"*
  * `golden_framebuffer_p2_render_crop.png` → *"Navigate stopped due to app disconnection."*

---

## 1. Regenerate (verbatim)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_oracle
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py /tmp/g1_oracle
```

Wall-clock cost ≈ 2 min for the Renode run + ~20 s for the analysis.
Artifacts written to `recon/emulator/reports/`:

| file | what |
|---|---|
| `display_sensor_oracle.json` | the machine-readable oracle (≈1.2 MB) |
| `golden_framebuffer_{p1_boot,p2_render}.raw` | 153 600 B, 4 bpp packed, 320 B/row |
| `…​.pgm` / `…​.png` | 640×480 8-bit grayscale expansion (`nibble×17`) |
| `…​_crop.png` | lit-bbox crop, 3× upscale — human inspection only, **not** a diff target |

**Prerequisite (one-time, additive):** the two logging hooks in
`armemul/models/NRF5340_{SPIM,TWIM}.cs` described in §6 must be present.

## 2. Determinism knobs (identical to `golden_boot_trace.json`)

| knob | value |
|---|---|
| Global quantum | `0.000010` s |
| Core scheduling | serial (`MasterTimeSource.ExecuteInSerial = True`, set in `g1.resc`) |
| CC312 entropy | `NRF5340_CC3xx_RNG` seed `0x5340CC3105340CC3` |
| Virtual-time budget | **20.0 s**, split into two phases |
| Stimulus | identical to `armemul/scripts/g1-selfdrive.sh` |

| phase | virtual time | what runs |
|---|---|---|
| `p1_boot` | 0 → 6 s | autonomous boot; `vcentral` (virtual phone) connects over the modeled radio and ATT-writes the NUS frame `0a0600000000` |
| `p2_render` | 6 → 20 s | `lsm6dso PlayGesture "don"` (real Mahony-fusion wake) → `trigger_screen_state_change` → ESB L/R sync completes → dashboard blit |

Unlike the golden boot trace (stimulus-free), this oracle **needs** stimulus:
the panel blit is gated on the ESB L+R sync, so without the virtual lens and the
head-up gesture the firmware initialises the panel but never paints the canvas.

### 2.1 Determinism actually verified (not assumed)

The whole capture was run **twice end-to-end** and the two oracles diffed
field-by-field.

**Bit-identical across runs:**
* every framebuffer `sha256` and every `row_sha256`;
* `spim_a` stream hash for both phases (i.e. the *entire* display byte stream);
* `twim2` (LSM6DSO) stream hash for both phases;
* every `twim1` **per-device** stream hash (OPT3001, nPM1300, ST25DV, ST25DV-sys);
* `pdm0`, `saadc`, `gpiote0`, `gpiote1` register-access stream hashes;
* `JBD FrameCounter`, `display_on` flag, `esb_sync` byte, ESB PTX/ACK counts,
  and all firmware-event counts.

**NOT stable across runs (do not gate on these):**
* `peripherals/twim1/phases/*/stream_sha256` — the *merged* twim1 bus stream.
  Three independent firmware threads (ALS, PMIC, NFC) share that bus and their
  interleaving reorders. **Diff twim1 per device, never per bus.**
* `RADIO_TX`, `VC_DATA_EVENTS`, `announce_responses_injected` — ±2 frames of
  `NRF5340_RADIO` cadence; a property of the radio timing model, not of the
  firmware. Gate on the boolean outcome instead (link up / ESB sync == 2).

---

## 3. What the original does — display

`spim_a` = SPIM4 @0x4000A000 (the firmware calls it "SPIM2") → `JBD_Display`,
640×480 panel, 4 bpp, 320 B/row, 153 600 B address space; the active dashboard
canvas is 640×200 inside it (`recon/analysis/display_subsystem_report.md`).
`spim_b` (SPIM3 @0x4000C000, the alternate backend) sees **zero** transactions.

| phase | SPI transactions | pixel windows | `0x97` refreshes | framebuffer sha256 | lit px | bbox |
|---|---|---|---|---|---|---|
| `p1_boot` | 764 | 673 | 49 | `1d617c65…b193b953` | 656 | (178,267)–(449,287) 272×21 |
| `p2_render` | 2 881 | 2 752 | 129 | `b26c73b3…eedb8131` | 1 098 | (34,266)–(497,287) 464×22 |

Opcode histograms (`p1_boot`):
`0x02`×673, `0x97`×49, `0xC0`×10, `0x06`/`0x31`/`0x46`/`0xA3`×4,
`0x01`/`0x36`/`0x66`/`0x71`/`0x73`/`0x99`/`0xA9`×2, `0x9F`×1, `0xB9`×1.
`p2_render` is pure paint: `0x02`×2752, `0x97`×129 — **no re-init, no brightness
write** after boot.

### 3.1 Panel init sequence (exact, from the capture)

The firmware runs this block **twice** (t≈0.1017 s and t≈3.9242 s):

```
0x66                      0x46 payload=0F        <- brightness reg, high byte
0x99                      0x31 payload=04        <- brightness reg, latch
0x06                      0xA3
0x01 payload=10           0x97
0x02 full-panel clear:    0x06
     (x=0,y=0,  61440 B)  0xA9
     (x=0,y=192,61440 B)  0x36 payload=0612
     (x=0,y=384,30720 B)  0x46 payload=00        <- brightness reg, high byte
0xC0 payload=0000 ; 0x97  0x31 payload=04        <- brightness reg, latch
0xC0 payload=0014 ; 0x97  0xA3
0xC0 payload=1800 ; 0x97  0x97
0xC0 payload=1814 ; 0x97
0xC0 payload=0C0A ; 0x97  (after the FIRST block only:)
0x71 ; 0x97               0x9F tx=9F000000 rx=00004010   <- panel ID probe
0x73 ; 0x97               0xB9 payload=FF
```

* The `0x9F` ID probe is answered `0x4010` and accepted (`spi_read_id` @0x47724
  fires exactly once; `jdb_panel_init` requires 0x4010 or it logs
  *"JBD PANEL init failure!"*).
* The clear is 61440+61440+30720 = 153 600 B = the whole 640×480 panel, emitted
  as three 192/192/96-row bands — matching the report's "clear path blits
  192-row bands up to row 480".
* Brightness = the `0x46`/`0x31` pair (`set_brightness_to_panel_reg`), values
  `0F 04` then `00 04`.

### 3.2 Paint geometry

The dashboard renderer writes narrow per-row windows, never a full-canvas blit:

| window shape | `p2_render` count |
|---|---|
| `x=32`, 9 pixel bytes (18 px) | 2 646 |
| `x=32`, 10 pixel bytes | 21 |
| `x=120`, 240 pixel bytes (480 px) | 82 |
| `x=0`, 61440 / 30720 (full-panel clear) | 2 / 1 |

All lit content lands in rows **266–287** (22 rows), i.e. the text row of the
canvas at the default height/distance gears (3/3).

---

## 4. What the original does — sensors

| device | bus / addr | `p1_boot` txns | `p2_render` txns | exercised during boot? |
|---|---|---|---|---|
| LSM6DSO IMU | twim2 @0x6B | 1 089 | 1 200 | **yes** — full init + continuous polling |
| nPM1300 charger/fuel gauge | twim1 @0x6B | 291 | 508 | **yes** — full bank init + polling |
| OPT3001/OPT3007 ALS | twim1 @0x45 | 33 | 80 | **yes** — ID + config + result polling |
| ST25DV NFC EEPROM | twim1 @0x53 | 25 | 7 | **yes** (boot only, then idle) |
| ST25DV system port | twim1 @0x57 | 22 | 4 | **yes** (boot only, then idle) |
| SAADC | reg-level | 998 register accesses / 45 conversions over 20 s | | **yes** |
| GPIOTE0 (keys/touch) | reg-level | 25 register accesses | | **yes** (config at boot, 2 IN events) |
| GPIOTE1 | reg-level | **0** | | **never touched** |
| PDM0 (microphone) | reg-level | **2** register writes (pins only) | | **configured, never started** |
| ESB L↔R radio | net-core RADIO | 373 master PTX frames, 373 ACKs | | **yes**, in `p2_render` |

### 4.1 LSM6DSO IMU (twim2 @0x6B)
* `WHO_AM_I` (0x0F) read → **0x6C** (accepted).
* `CTRL3_C` (0x12) ← `05` (SW_RESET|IF_INC) then `44` (BDU|IF_INC).
* `CTRL1_XL` (0x10) ← `00`/`10`/`20`/`30` (accel ODR stepped 12.5→52 Hz);
  `CTRL2_G` (0x11) ← `00` — **the gyroscope is left disabled for the whole run**
  (`GyroscopeEnabled = False`; every 0x22 read returns `000000000000`).
* `CTRL6_C`(0x15)←`10`, `CTRL7_G`(0x16)←`80`, `CTRL9_XL`(0x18)←`E2`,
  `FUNC_CFG_ACCESS`(0x01)←`00`/`40`/`80` (bank switching), 0x0A←`00`, 0x62←`00`.
* Steady state: paired 6-byte reads of `0x22` (gyro out) and `0x28` (accel out)
  at ≈43 Hz — 249 pairs in `p1_boot`, 300 pairs in `p2_render`.
* During `p2_render` the accel reads carry the real gesture waveform
  (`2F004B000940`, `8D00E1000940`, `EA0077010940`, …), i.e. the head-up wake is
  genuinely fused by the firmware, not injected downstream.

### 4.2 OPT3001 ambient light (twim1 @0x45)
Manufacturer ID (0x7E) → `5449` ("TI"), device ID (0x7F) → `3001`; CONFIG (0x01)
written `CE10` then `CE90`; RESULT (0x00) polled (6 reads in boot, 80 txns in
`p2_render`). `ConversionReady = True` at end of run. This is the input to
`compute_lux_brightness_bucket` → auto-brightness.

### 4.3 nPM1300 (twim1 @0x6B)
Register banks 0x02–0x08 are all written during boot (charger enable, BUCK/LDSW
rails, ADC/fuel-gauge, GPIO, ship-mode/reset config), then banks 0x02/0x03/0x05/
0x07 are polled continuously. `ChargingEnabled = True` at end of run. The seeded
4500 mV battery is what drives the firmware's own SoC curve to 100 %.

### 4.4 ST25DV NFC EEPROM (twim1 @0x53 / 0x57)
System port UID read → `E002240123456789`; user memory read/written including
the NDEF header `E1404001`. All of it happens in `p1_boot`; afterwards the
device is essentially idle (4+7 transactions in 14 s).

### 4.5 SAADC
45 identical one-shot conversion cycles over 20 s (≈2.25 Hz):
```
CH3.PSELP ← 4 (AIN3)   CH3.PSELN ← 0   CH3.CONFIG ← 0x00020000 (TACQ=10 µs, GAIN=1/6, REF=internal)
CH0..2,CH4..7.PSELP ← 0        RESOLUTION ← 2 (12-bit)      OVERSAMPLE ← 0
RESULT.PTR ← 0x200275CE        RESULT.MAXCNT ← 1
ENABLE ← 1 ; TASKS_START ; TASKS_SAMPLE ; poll EVENTS_END ; TASKS_STOP ; ENABLE ← 0
```
`INTENSET ← 0x12` once at init. Only CH3/AIN3 is ever selected.

### 4.6 GPIOTE0 — touch / key edge inputs
No dedicated touch controller exists on this bus map; the capacitive/key inputs
arrive as **GPIO pin events**. The firmware configures exactly two IN channels
and enables their interrupts:

| CONFIG reg | value | decode |
|---|---|---|
| `CONFIG[7]` @0x52C | `0x22901` | MODE=Event, PSEL=9, PORT=1 → **P1.09**, POLARITY=HiToLo |
| `CONFIG[6]` @0x528 | `0x22A01` | MODE=Event, PSEL=10, PORT=1 → **P1.10**, POLARITY=HiToLo |

plus `INTENSET ← 0x80000000` (PORT event), `0x80` (IN[7]), `0x40` (IN[6]).
`EVENTS_IN[6]`/`EVENTS_IN[7]`/`EVENTS_PORT` are each cleared twice.
GPIOTE1 (secure domain) is never touched.

### 4.7 PDM0 — microphone
**The original writes exactly two PDM registers in this whole scenario:**
`PSEL.CLK ← 0x2D` (P1.13) and `PSEL.DIN ← 0x2E` (P1.14). `ENABLE` is never
written, `TASKS_START` never triggered, no DMA is programmed. The mic is
**pin-configured at boot and only started on a later stimulus** (a voice/record
command that this scenario does not send).

### 4.8 ESB L↔R sync (the pixel gate)
373 master PTX frames on channel 34 at on-air address `0x82`, all ACKed by the
virtual right lens; `device_info[0x105a]` reaches **0x02** and the display-on
flag `ctx+0xfe8` reaches **0x01**, which is what releases `sync_to_slave` and
lets `notify_display_mode` blit (15 blits observed). First master frames:
```
8282828282200311 00…00 4BFD   (announce, payload marker 0x11)
8282828282200340 000000000000800092654C002000CF00020000…  (state frame)
```

---

## 5. Parity pass/fail criteria for our rebuild

Run the same capture against our build, rebuild the oracle into a scratch
directory, and compare the two JSON files. Every criterion below is a hard
PASS/FAIL unless marked otherwise. (The criteria are also embedded in
`display_sensor_oracle.json` under `parity_criteria`.)

### Graphics
| id | criterion |
|---|---|
| **G-1** | `framebuffer.p2_render.sha256` == `b26c73b3…eedb8131` — **pixel-exact**, 153 600 B |
| **G-2** | `framebuffer.p1_boot.sha256` == `1d617c65…b193b953` |
| **G-3** | `peripherals.spim_a.phases.{p1_boot,p2_render}.stream_sha256` match — the exact ordered SPI byte stream (opcodes, payloads, MISO), i.e. same init, same blits, same order |
| **G-4** | *(localiser, not an extra gate)* on a G-1/G-2 failure, `framebuffer.*.row_sha256` gives the first differing panel row |
| **G-5** | the panel init sequence of §3.1 reproduced exactly: `0x9F` probe answered `0x4010` and accepted, the three-band full-panel clear, the five `0xC0` words `0000/0014/1800/1814/0C0A`, the `0x46`+`0x31` brightness pairs `0F 04` and `00 04` |
| **G-6** | `peripherals.spim_b` transaction count == **0** (our build must not use the alternate display backend) |

### Sensors
| id | criterion |
|---|---|
| **S-IMU** | `peripherals.twim2.phases.*.stream_sha256` match: identical LSM6DSO init writes (incl. gyro left **off**) and identical 0x22/0x28 polling cadence |
| **S-ALS** | `twim1 … devices.opt3001_ambient_light.stream_sha256` match per phase |
| **S-PMIC** | `twim1 … devices.npm1300_charger_fuelgauge.stream_sha256` match per phase |
| **S-NFC** | `twim1 … devices.st25dv_nfc_eeprom` **and** `st25dv_system_port` stream hashes match per phase |
| **S-ADC** | `peripherals.saadc.whole_run.stream_sha256` match (CH3/AIN3 only, 12-bit, no oversampling, 45 cycles) |
| **S-MIC** | `peripherals.pdm0.whole_run.stream_sha256` match — **exactly two writes**, `PSEL.CLK=0x2D`, `PSEL.DIN=0x2E`, and **no** ENABLE/START. A rebuild that starts the PDM here FAILS |
| **S-KEYS** | `peripherals.gpiote0.whole_run.stream_sha256` match (2 IN channels, CONFIG `0x22901`/`0x22A01`, INTENSET `0x80000000`/`0x80`/`0x40`); `gpiote1` access count == 0 |
| **S-ESB** | boolean, **not** counter-exact: `ESB_SYNC_ctx_105a` reaches `0x02`, `DISPLAY_ON_ctx_fe8` reaches `0x01`, ESB master PTX frames > 0 |

### Explicitly excluded from the gate
`twim1` *merged-bus* stream hash, `RADIO_TX`, `VC_DATA_EVENTS`,
`announce_responses_injected`, and any wall-clock or `tick` value — see §2.1.

---

## 6. How each peripheral was observed (and what changed in `armemul`)

| peripheral | method | invasiveness |
|---|---|---|
| `spim_a`, `spim_b` (JBD display) | **new** opt-in `TraceFile` property on `models/NRF5340_SPIM.cs` | additive, default off |
| `twim1`, `twim2` (all I2C sensors) | **new** opt-in `TraceFile` property on `models/NRF5340_TWIM.cs` | additive, default off |
| `pdm0`, `saadc`, `gpiote0`, `gpiote1` | Renode built-in `sysbus LogPeripheralAccess <p> true` | **no model change** |
| RADIO / ESB | pre-existing model counters + `esbslave DumpFirstN` | **no model change** |
| firmware-side consequences | `sysbus.cpuapp AddHook` at 0x47724 / 0x2bc2c / 0x2948c | **no model change** |

### The exact `armemul` change (108 added lines, 0 removed)

```
models/NRF5340_SPIM.cs | 56 ++++++++++
models/NRF5340_TWIM.cs | 52 ++++++++
```

Both are the same pattern:
* a `public string TraceFile { set; }` that opens/closes a `StreamWriter`
  (assigning `""` or calling `TraceClose()` flushes and closes it);
* one `if(traceWriter != null) traceWriter.WriteLine(...)` at the point where
  the model has **already** built the transfer buffers — SPIM right after
  `RegisteredPeripheral.FinishTransmission()`, TWIM right at the existing
  `LogLevel.Noisy` TX/RX log sites.

No register definition, event, interrupt, DMA pointer, timing path or data path
is touched; with `TraceFile` unset (the default) the added code is a single null
check. `g1.resc`, `platforms/nrf5340.repl`, the shipped images and every device
model are **unmodified**. To revert: `cd armemul && git checkout models/`.

**Evidence the hook does not perturb the firmware:** `scripts/g1-selfdrive.sh`
was run *before* the change and reported 1 098 lit pixels with bbox
(34,266)–(497,287) = 464×22. The traced capture *after* the change reproduces
exactly those numbers and the same framebuffer.

Trace line formats:
```
spim_a seq=<n> tick=<virtual-ns> txn=<tx bytes> rxn=<rx bytes> tx=<hex> rx=<hex>
TWIM1  seq=<n> tick=<virtual-ns> dev=0x<7-bit addr> dir=<W|R> n=<bytes> data=<hex>
```

### Independent cross-check of the framebuffer
`build_display_sensor_oracle.py` reconstructs the panel framebuffer **from the
SPI transaction stream alone** (its own decoder for opcode `0x02`: 3-byte
big-endian coordinate, `0xFF` marker, trailing dummy byte dropped, byte offset
`y*320 + x/2` with wrap) and compares it against the `JBD_Display` model's own
`DumpFrame` output. Both phases report `matches_spi_replay: true`, so the oracle's
pixel content is confirmed by two independent paths. It also matches the
`g1-selfdrive.sh` baseline (1 098 lit pixels, bbox 464×22).

---

## 7. Limitations / what could NOT be observed

1. **PDM audio data.** The original never starts the PDM in this scenario, so
   there is no audio DMA stream to capture. What *is* pinned is the negative:
   pins configured, peripheral never enabled. Capturing a real mic stream would
   need a stimulus that issues the firmware's record/voice command over BLE —
   not attempted here.
2. **Gyroscope samples.** `CTRL2_G` is left at 0, so all 549 gyro reads return
   zeros. The oracle pins the *absence* of gyro configuration, which is itself a
   parity requirement.
3. **QSPI settings store** (`Macronix_MX25U`) is not covered — it is storage,
   not display or sensor. `NRF5340_QSPI` is a different model class and has no
   `TraceFile` hook; if it is ever needed, `sysbus LogPeripheralAccess sysbus.qspi
   true` gives register-level coverage with no model change.
4. **Physical panel semantics of `0x01/0x06/0x31/0x36/0x46/0x66/0x71/0x73/0x97/
   0x99/0xA3/0xA9/0xB9/0xC0`** are unknown to the model (it journals them without
   side effects). The oracle therefore pins the *byte stream*, which is the right
   parity target regardless of what the panel does with it.
5. **`DashBoard_Reflash` @0x3727c never fired** as a Renode hook, while
   `notify_display_mode` @0x2948c fired 15 times and pixels were painted. Most
   likely 0x3727c is not a real instruction boundary (the same class of defect
   documented for the net-core ESB addresses in `g1-selfdrive.sh`). Treated as an
   instrumentation limitation, not as evidence about the firmware; the blit is
   proven by the SPI stream itself.
6. **Only the master (L) temple exists.** The right lens is the `ESB_VirtualSlave`
   model, so the oracle covers the master's display/sensor behaviour and the ESB
   frames it emits, not a second real firmware instance.
7. **`twim1` cross-device ordering is not reproducible** (see §2.1) — a real
   property of three threads sharing a bus under a 10 µs quantum, not a capture
   defect. Hence the per-device criteria.
