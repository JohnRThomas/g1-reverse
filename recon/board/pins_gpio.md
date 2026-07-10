# Even G1 app-core — recovered GPIO / pin assignments

STEP 3a recovery. All entries below are extracted from PROVEN (parity-verified)
function bodies in `recon/named/` and from device/dt-spec structs read out of
`app_update.bin` (app link base 0xC200, mcuboot hdr 512) via `tools/extract.py`.

## GPIO port devices (nRF5340 app core)

| Device symbol | struct addr | DT name       | peripheral base | nRF port |
|---------------|-------------|---------------|-----------------|----------|
| `g_gpio0_dev` | 0x00087b60  | `gpio@842500` | 0x50842500      | **P0**   |
| `g_gpio1_dev` | 0x00087b48  | `gpio@842800` | 0x50842800      | **P1**   |

Port decode is confirmed in `nrf_gpio_pin_reconfigure` / `gpio_configure_pin_output`:
`pin>>5 == 0 → 0x50842500 (P0)`, `pin>>5 == 1 → 0x50842800 (P1)`; the register
written is `base + (pin<<2) + 0x200` = the per-pin `PIN_CNF[n]`.
(gpio0 cfg block @0x8b738 holds 0x50842500; gpio1 cfg block @0x8b728 holds 0x50842800.)

Pin-CNF field encoding (from `gpio_pin_cnf_build_fields` @0x85130 and
`nrf_gpio_pin_reconfigure` @0x67548): bit0 DIR, bit1 INPUT-buffer, bits2-3 PULL,
bits8-10 DRIVE, bits16-17 SENSE — standard nRF5340 `PIN_CNF`.

## Buttons (SW0 / SW1) — port P1

Source: `button_init` @0x17a40 (PROVEN 200/200), `read_sw0_pin` @0x17e30 (PROVEN),
and the `gpio_dt_spec` structs it configures.

| Signal | Pin    | Dir  | dt_spec @ | device      | notes |
|--------|--------|------|-----------|-------------|-------|
| SW0    | **P1.09** | input (IRQ) | 0x889d0 → {g_gpio1_dev, pin 9,  dt_flags 0x11} | g_gpio1_dev | debug str "SW0 GPIO" @0x99f81/0x99fa8; sense mask 0x5c00000; `read_sw0_pin` reads raw P1.09 |
| SW1    | **P1.10** | input (IRQ) | 0x889e0 → {g_gpio1_dev, pin 10, dt_flags 0x11} | g_gpio1_dev | sense mask 0x5c00000 (rev0) / 0x3c00000 (other rev, `get_board_rev_flag`) |

dt_flags 0x11 = ACTIVE_LOW + pull (buttons are active-low with pull). Interrupt
sense is armed via `FUN_00017858(spec, 0x5c00000/0x3c00000)`; IRQ dispatch through
`gpiote_irq_handler` → `gpio_nrfx_pin_interrupt_configure` @0x61624.

## Subsystem power / enable control lines — port P0

`button_init` drives these to fixed levels at boot via
`gpio_pin_set_checked(g_gpio0_dev, pin, level)` (helper @0x17768, PROVEN 300/300).
The `get_device_hw_id` debug string block (@0x9a0c6) names the four status rails:
`panel_power_status / tmr_status / nfc_lpd_status / touch_power_status`.

| Pin    | Boot level | dt_spec @ | Role (cited) |
|--------|-----------|-----------|--------------|
| **P0.24** | 1 | 0x889f8 → {g_gpio0_dev, pin 0x18} | **Panel / projector power enable** — asserted by `gpio_dt_spec_activate` @0x179ec (panel-on) and de-asserted by `panel_pwr_gpio_deassert` @0x179e0 (panel-off, called from `power_down_panel` @0x15fdc). `power_for_panel` @0x15df4 activates it after the panel-controller I2C bring-up. |
| **P0.23** | 0 | 0x889d8 → {g_gpio0_dev, pin 0x17} | subsystem enable rail (one of panel/nfc_lpd/touch group) |
| **P0.30** | 1 | 0x889e8 → {g_gpio0_dev, pin 0x1e} | subsystem enable rail |
| **P0.21** | 0 | 0x889f0 → {g_gpio0_dev, pin 0x15} | subsystem enable rail |
| **P0.19** | 0 | (direct set only) | subsystem enable rail |

(The four dt_spec-backed lines P0.24/23/30/21 plus P0.19 map to the panel_power /
tmr / nfc_lpd / touch_power power-status rails; exact per-rail assignment beyond
P0.24=panel is not individually string-labelled in the boot code.)

## Hardware-ID / board-revision strap pins (inputs) — port P0

Read in `button_init` via single-arg `gpio_pin_get_checked` @0x17980 (PROVEN),
which is hard-wired to `g_gpio0_dev` (0x87b60). Debug strings @0x99fe8-0x9a072
label them `DEVICE_ID1..4_PIN`:

| Signal        | Pin       | Dir   | debug str |
|---------------|-----------|-------|-----------|
| DEVICE_ID1    | **P0.26** | input | @0x99fe8 |
| DEVICE_ID2    | **P0.25** | input | @0x9a016 |
| DEVICE_ID3    | **P0.28** | input | @0x9a044 |
| DEVICE_ID4    | **P0.27** | input | @0x9a072 |

These four form `device_compat_val` (@0x9a0a0) — a board-variant strap read at boot.
(button_init also does readback `gpio_pin_get_raw_checked(g_gpio0_dev, {0x18,0x13,0x15,0x1e})`
= the P0.24/19/21/30 output rails above.)

## QSPI external-flash bus — port P0

Source: `qspi_configure_pins_and_interface` @0x66aXX (PROVEN), pins validated as
exact constants and configured via `gpio_configure_pin_output(pin, 3)`
(drive H0H1) / `nrf_qspi_pins_set`.

| QSPI signal | Pin       | how |
|-------------|-----------|-----|
| SCK  | **P0.17** (0x11) | `gpio_configure_pin_output(0x11, 3)` literal; also validated `param[1]==0x11` |
| CSN  | **P0.18** (0x12) | validated `param[2]==0x12` |
| IO0  | **P0.13** (0x0d) | validated `param[3]==0x0d` |
| IO1  | **P0.14** (0x0e) | validated `param[4]==0x0e` |
| IO2  | **P0.15** (0x0f) | optional, `param[5]==0x0f` |
| IO3  | **P0.16** (0x10) | optional, `param[6]==0x10` |

QSPI peripheral regs at 0x5002b000 (IRQ 0x2b). These drive the app-core external
flash and are not projector-related.

## Projector / panel control summary

The projector (JBD micro-display) is driven over an **I2C register bus**, not GPIO —
see `power_for_panel` @0x15df4, `power_down_panel` @0x15fdc, `jdb_panel_init`,
`panel_on/panel_off`, `projector_reset_sequence` (all use `dev_write_reg3` /
`dev_reg_modify_bits` against controllers @0x87cf8 and @0x87d10). The only
projector-related **GPIO** line is the panel power enable **P0.24**
(dt_spec 0x889f8), asserted/deasserted by `gpio_dt_spec_activate` /
`panel_pwr_gpio_deassert`.

## Pins recovered (count)

- P1: 2 (SW0 P1.09, SW1 P1.10)
- P0 power/enable: 5 (P0.24 panel/projector power, P0.23, P0.30, P0.21, P0.19)
- P0 hardware-ID straps: 4 (P0.26/25/28/27)
- P0 QSPI flash: 6 (P0.17 SCK, P0.18 CSN, P0.13-16 IO0-3)

Total: **17 pins** across P0/P1, all cited to PROVEN function bodies or
in-image dt_spec/device structs. No dedicated user LED GPIO is driven in the
recovered app-core boot path (status is reported over the panel-controller I2C
rails, not discrete LED pins).
