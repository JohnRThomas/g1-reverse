# G1 CPUAPP display / projector subsystem

Reverse-engineered from the reconstructed CPUAPP sources (all cited functions are
parity-proven, 300/300). Covers the physical screen, pixel format / transparency,
brightness, and the user-facing **display height** and **distance** settings.

## 1. The screen

A **JBD (Jade Bird Display) monochrome green micro-LED microdisplay**, one per eye,
driven over SPI.

- `jdb_panel_init` reads the panel SPI ID and only accepts **`0x4010`** (else logs
  `"JBD PANEL init failure!"`), storing it in `g_panel_spi_id`.
- **640×200, 4 bits/pixel.** Framebuffer (`projector_fill_framebuffer`) is **64000
  bytes** = 640·200·4/8. Width is pinned by the transport: `projector_write_pixel_data`
  moves `0xf000` (61440) bytes per `0xc0` (192) rows → 320 bytes/row → **640 px/row**
  (two 4-bit pixels per byte). Pixel address packing in `projector_transfer_pixel_chunk`
  is **10-bit X, 9-bit Y** (`(x & 0x3ff) | (y << 10)`); the panel address space is
  larger than the 640×200 active image (clear path blits 192-row bands up to row 480).
- **Monochrome green, 16 luminance levels** (4 bpp). No color channel.
- **Dual, one per temple/eye**: `master_display_thread` / `slave_display_thread`,
  `display_panel_is_secondary`. The master temple syncs state to the slave over the
  inter-temple link.

SPI pixel packet: `[0x02, addr_hi, addr_mid, addr_lo, 0xFF, …pixels]`, followed by
`0x97` (display update) and a 1 ms settle.

## 2. Pixel "transparency"

**No alpha channel — transparency is physical.** The optics are an additive waveguide
combiner, so a pixel's only property is how much green light it emits:

- `0x0` = LED off = **transparent** (real world shows through).
- `0xF` = full-bright green overlaid on the world.
- 1–14 = dimmer green (anti-aliased edges / grayscale).

`pixelto4bithex` is the rasterizer: it expands a 1-bit source bitmap to 4 bpp, mapping
a set bit → `0xF` and a clear bit → `0x0`. Undrawn pixels stay 0 and are see-through —
"black" and "transparent" are the same state on this display.

## 3. Brightness — two independent layers

**Per-pixel luminance** (the image content): the 4-bit value above.

**Global panel brightness** (`set_display_brightness` → `set_brightness_to_panel_reg`):
- User scale **0–100 %**, clamped, stored **per eye** at `device_info+0x1090` / `+0x1091`,
  persisted to flash.
- Converted to a 16-bit panel drive register: scaled by constant **`0x6F` (111)** times a
  per-device calibration word at `device_info+0xed8` (`panel_temp_calibration_init`),
  written via SPI command **`0x46`** then `0x31`. Sets micro-LED drive current/PWM — a
  global gain, not per-pixel.
- `set_brightness_to_panel_reg_in_running` is the runtime-adjust variant;
  `set_brightness_lum_base` sets the base luminance.

**Auto-brightness**: `compute_lux_brightness_bucket` reads the **OPT3001/OPT3007 ambient
light sensor** (`opt3001_read_lux_raw`) and buckets lux into a brightness level (returns
`0xFF` when the sensor isn't ready), feeding the global brightness register.

## 4. Display **height** and **distance** settings

Two discrete "gear" settings the phone app exposes, received over BLE as
`raster_config_info {enable, raster_height_gear, canvas_distance_gear}`
(`BLE_GET_RASTER_CONFIG` / `BLE_REQ_...`). They are stored in `device_info`:

| Setting | Field | Default |
|---|---|---|
| Display **height** | `raster_height_gear` @ `device_info+0xec0` | **3** |
| Virtual **distance** | `canvas_distance_gear` @ `device_info+0xec1` | **3** |

Defaults set by `reset_usr_setting` / `load_usr_setting` (`0x0303`). The master temple
pushes both gears to the slave (`slave_display_thread` writes `+0xec0/+0xec1` from the
remote value) so both eyes use the same gear numbers.

**`cal_panel_canvas_coord`** translates the two gears into a canvas pixel offset
`(canvas_x, raster_y)`; `ui_raster_height_task` then stores X→`device_info+0xec4`,
Y→`device_info+0xeb8`, clears the screen and redraws (`ui_DashBoard_task`), caching the
values in `g_display_canvas_x_cache` / `g_display_canvas_y_cache`.

### Height → vertical shift (`raster_height_gear`)

```
raster_y = (8 - gear) * 35            # pixels, applied equally to BOTH eyes
```

| gear | 0 | 1 | 2 | 3 (default) | 4 | 5 | 6 | 7 | 8 |
|---|--|--|--|--|--|--|--|--|--|
| raster_y (px) | 280 | 245 | 210 | 175 | 140 | 105 | 70 | 35 | 0 |

So each height step moves the whole canvas **35 px** vertically (gear 8 = top, gear 0 =
lowest) — this is how high/low the floating HUD sits in the field of view. Same offset
on both eyes.

### Distance → per-eye horizontal shift = binocular convergence (`canvas_distance_gear`)

```
canvas_x = {1:+22, 2:+8, 3/default:0, 4:-4, 5:-8, 6:-10, 7:-12, 8:-14, 9:-16}
if device_type == 1:  canvas_x = -canvas_x      # opposite sign on the other temple
```

| gear | 1 | 2 | 3 (default) | 4 | 5 | 6 | 7 | 8 | 9 |
|---|--|--|--|--|--|--|--|--|--|
| canvas_x (px, one eye) | +22 | +8 | 0 | −4 | −8 | −10 | −12 | −14 | −16 |

The key detail: the X offset is **negated for one temple**, so the left and right images
shift in **opposite** horizontal directions. That changes the **binocular disparity /
convergence angle** between the two eyes' images, which the brain interprets as the
virtual screen being **nearer or farther**. There is no optical focus change — the
micro-LED display is fixed-focus — so the "distance" control is a pure **stereoscopic
vergence** effect implemented as an equal-and-opposite horizontal pixel offset per eye.
(Vertical/height is common to both eyes; only the horizontal/distance axis is mirrored.)

After applying either gear, `ui_raster_height_task` writes status byte `0x26` at
`device_info+0x104c` and signals the display semaphore to trigger a redraw at the new
canvas position.
