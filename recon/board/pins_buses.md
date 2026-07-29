# G1 app-core — peripheral buses, instances & pins

Recovered from `app_update.bin` (base 0xC200) by decoding the Zephyr device
objects (`device.name/config/api`), their `pinctrl_dev_config` state tables, and
the `gpio_dt_spec` structs referenced by the driver-init functions in
`recon/named/`. Pinctrl words decoded with the NCS 2.5.1 `nrf-pinctrl.h` bitfield
(`FUN[31:16] INVERT[14] LP[13] DRIVE[12:9] PULL[8:7] PIN[6:0]`, PIN = port*32+n).

## nRF5340 SERIAL/peripheral base → instance map (confirmed from reg bases)

| Reg base      | nRF5340 instance | DT node        | Role                         |
|---------------|------------------|----------------|------------------------------|
| 0x50008000    | UARTE0 (SERIAL0) | `uart@8000`    | debug/console UART           |
| 0x50009000    | TWIM1  (SERIAL1) | `i2c@9000`     | I2C — opt3007 ALS + PMIC     |
| 0x5000A000    | SPIM2  (SERIAL2) | (runtime)      | projector control SPI (B)    |
| 0x5000B000    | TWIM3  (SERIAL3) | `i2c@b000`     | I2C — LSM6DSO IMU            |
| 0x5000C000    | SPIM4            | (runtime)      | projector control SPI (A, HS)|
| 0x50026000    | PDM0             | `pdm@26000`    | MEMS microphone              |
| 0x5002B000    | QSPI             | `qspi_nor`     | MX25R6435F 64 Mbit NOR flash |
| 0x50842500    | GPIO P0          | `gpio@842500`  | port 0                       |
| 0x50842800    | GPIO P1          | `gpio@842800`  | port 1                       |

No `pwm@` node exists in the firmware — there is **no PWM peripheral instance**.
Panel/OLED brightness is programmed by register writes over the projector SPI
(`set_brightness_to_panel_reg`, `jbd_panel_resume`), not by a PWM channel.

## Device → bus binding (from `device.config` structs)

| Device object (VA) | DT name        | Bus / instance | Addr | Driver (recon/named)          |
|--------------------|----------------|----------------|------|-------------------------------|
| 0x87bf0            | `mx25r6435f@0` | QSPI           | —    | `qspi_nor_*`, `nrfx_qspi_*`   |
| 0x87c50            | `i2c@b000`     | TWIM3          | —    | `i2c_nrfx_twim`               |
| 0x87d58            | `lsm6dso@6b`   | on TWIM3       | 0x6b | `lsm6dso_init_chip` (IMU)     |
| 0x87c68            | `i2c@9000`     | TWIM1          | —    | `i2c_nrfx_twim`               |
| 0x87d88            | `opt3001@45`   | on TWIM1       | 0x45 | `opt3007_chip_init` (ALS)     |
| 0x87c80            | `pmic@6b`      | on TWIM1       | 0x6b | nPM PMIC                      |
| 0x87bc0            | `uart@8000`    | UARTE0         | —    | `uart_nrfx_uarte`             |
| 0x87d40            | `pdm@26000`    | PDM0           | —    | `dmic_nrfx_pdm`               |
| (runtime struct)   | JBD panel      | SPIM4 / SPIM2  | —    | `spi_master_init` @0x26418    |

Note: the `opt3001@45` node is bound to the OPT**3007** driver in this firmware
(`opt3007_chip_init`, mfg/dev-id checked over I2C at 0x45).

## Pin assignments (from pinctrl state tables & gpio_dt_spec)

### QSPI — `mx25r6435f@0` (states @0x8b6b0, group @0x8b6d8, drive=H0H1)
| Signal | Pin   |
|--------|-------|
| SCK    | P0.17 |
| IO0    | P0.13 |
| IO1    | P0.14 |
| IO2    | P0.15 |
| IO3    | P0.16 |
| CSN    | P0.18 |

### TWIM3 — `i2c@b000` (IMU bus) — states @0x8b7c8
| Signal | Pin   |
|--------|-------|
| SDA    | P1.02 |
| SCL    | P1.03 |
(state 1 = sleep, same pins with LOW_POWER set)

### TWIM1 — `i2c@9000` (ALS + PMIC bus) — states @0x8b818
| Signal | Pin   |
|--------|-------|
| SDA    | P0.05 |
| SCL    | P0.04 |
(state 1 = sleep, LOW_POWER)

### UARTE0 — `uart@8000` — states @0x8baf4
| Signal | Pin   | Notes                     |
|--------|-------|---------------------------|
| TX     | P0.20 |                           |
| RX     | P0.22 | pull-up                   |
| RTS    | P3.31 | placeholder (unrouted)    |
| CTS    | P3.31 | placeholder (unrouted)    |
RTS/CTS both map to P3.31 → hardware flow control effectively unused.

### PDM0 — `pdm@26000` (microphone) — states @0x8b5c8
| Signal | Pin   |
|--------|-------|
| CLK    | P1.13 |
| DIN    | P1.14 |

### Projector control SPI — SPIM4 (0x5000C000) / SPIM2 (0x5000A000)
Pins are **assigned at runtime**, not via static pinctrl. `spi_master_init`
(@0x26418) reads SCK/MOSI/MISO/CS pin numbers from the projector-controller
struct (byte fields at +0x18…+0x1d) and hands them to `nrfx_spim_init`. Two
projectors (L/R): control mode 3 → SPIM4 (high-speed), mode 4 → SPIM2.

**RECOVERED 2026-07-29 — the earlier “leave them as overlay TODOs, fill from a
live board” conclusion is WITHDRAWN.** The premise was right (the pins are not
constants in the image) but the conclusion was wrong: the firmware *programs*
them into the SoC pin-routing registers during bring-up, so they can simply be
read back after an emulator boot. No live board is needed.

| Signal | SPIM2 @0x5000A000 | Evidence |
|--------|-------------------|----------|
| SCK    | **P0.08** | `PSEL.SCK`  (+0x508) = `0x00000008` |
| MOSI   | **P0.09** | `PSEL.MOSI` (+0x50C) = `0x00000009` |
| MISO   | **P0.10** | `PSEL.MISO` (+0x510) = `0x0000000A` |
| CSN    | *(see below)* | `PSEL.CSN` (+0x514) = `0xFFFFFFFF` — DISCONNECTED |

SPIM4 @0x5000C000: all `PSEL` = `0xFFFFFFFF` — fully disconnected. **Only one
lens is driven** in the traced configuration.

**CSN caveat — do not present all four pins as equally confirmed.** The firmware
declares `ss=11`, but `PSEL.CSN` stays disconnected because `nrfx_spim` drives
`ss_pin` in **software** (a GPIO toggled around each transfer) rather than
through the SPIM hardware CSN route. So SCK/MOSI/MISO are *register-confirmed*;
**P0.11 as chip-select is firmware-declared only.**

Corroborated independently by the firmware's own boot log — the format string is
present verbatim in the shipped image (`%s(): *SPIM(%d)speed=%dM, sck=%d,
mosi=%d, miso=%d, ss=%d`), and prints
`spi_master_init(): *SPIM(4)speed=32M, sck=8, mosi=9, miso=10, ss=11`.
To see it, raise `g_log_level` @ `0x2000230c` above 2 — note a pre-`start` write
is clobbered by cstart, so set it from a hook at `main()` entry @ `0x16eb8`.

Verified here before adoption: the byte run `08 09 0a 0b` does **not** occur
anywhere in `app_update.bin`, confirming the pins are genuinely runtime-assigned
and cannot be recovered statically.

Source: cross-session report from the ARMemul nRF5340 emulator fork (2026-07-29),
two independent confirmations in agreement. Reproduction:
`scripts/g1-dump-pins.sh` and `docs/g1-pin-map-dump.md` in that tree.

> **General technique, worth reusing:** anything the firmware configures at
> runtime rather than via devicetree can be read out of the peripheral registers
> after an emulator boot. This applies to every other “board-provisioned”
> unknown in this document.

Same method also re-confirmed (all matching `board-map.md`): TWIM1 SCL P0.04 /
SDA P0.05 · TWIM2 SCL P1.03 / SDA P1.02 · PDM CLK P1.13 / DIN P1.14 · QSPI
SCK P0.17, CSN P0.18, IO0–IO3 P0.13–P0.16. Console UART TXD P0.20 / RXD P0.22
comes from the PSEL *write* log only — that UART model discards PSEL writes, so
it cannot be read back.

**Live-hardware cross-check is NOT possible with the firmware on the device.**
The left leg connects (NUS + SMP advertised), but the live `0x2f` endpoint reads
**QSPI flash offsets** bounded `[0, 0x02000000)` — its `offset` is a flash
offset, not a CPU address — so the `0x5000_0000` peripheral window and RAM are
unreachable. Probed and confirmed: `0x5000A508`, `0x5000C508` and `0x20000000`
all return status=1 (out of bounds), while a `0x134000` baseline read returns
correct QSPI data. Reaching registers would need a memread variant with wider
bounds, i.e. a flash — no-revert on this firmware.

## GPIO control lines (from `button_init`/`FUN_00017a40`, `panel_pwr_gpio_deassert`, `read_sw0_pin`)

| Pin   | Port | Direction | Function (inferred)                     |
|-------|------|-----------|------------------------------------------|
| P1.09 | gpio1| input,IRQ | SW0 button (`read_sw0_pin` reads pin 9)  |
| P1.10 | gpio1| input,IRQ | second button / touch input              |
| P0.24 | gpio0| output    | panel power enable (`panel_pwr_gpio_deassert`) |
| P0.19 | gpio0| output    | projector/panel control                  |
| P0.21 | gpio0| output    | projector/panel control                  |
| P0.23 | gpio0| output    | projector/panel control                  |
| P0.30 | gpio0| output    | projector/panel control                  |
| P0.25,26,27,28 | gpio0 | — | additional control lines (gpio_dt_spec array @0x88340) |

(Init sets P0.24=1, P0.19=0, P0.21=0, P0.30=1, P0.23=0 at boot.)
