/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 5) — relocated `struct gpio_dt_spec` tables.
 *
 * button_init (and nfc_field_event_signal_sem) originally read their GPIO
 * descriptors straight out of the shipped image's rodata at the ABSOLUTE
 * addresses 0x88340 / 0x889d0 / 0x889e0.  Those pins (`rodata_88340`,
 * `rodata_889d0`, `rodata_889e0` in recon/symbols/g1_app_globals.ld) are
 * unrelocated, and two things are wrong with them in our build:
 *   (1) our relocated image holds completely different rodata at those
 *       addresses (nm: `00088340 R rodata_15f40`), and
 *   (2) the entries THEMSELVES embed an absolute `struct device *`
 *       (0x87b60 = gpio0, 0x87b48 = gpio1), so even a correct table address
 *       would still hand gpio_pin_configure_dt() a bogus port pointer.
 * A linker rebind cannot express (2): the tables have to be emitted by the
 * build so both the table address and the device pointers inside them are
 * relocated.  Contents are transcribed from app_update.bin (verified with
 * tools/extract.py); `g1_app_globals.ld` binds the recovered `rodata_*` pin
 * names to these definitions so every consumer picks them up.
 *
 * Original bytes (8 B per entry: device* @0, u8 pin @4, u16 dt_flags @6):
 *   0x88340: 9 x { 0x00087b60 (gpio0), pin, 0 }
 *            pins = 26, 25, 28, 27, 24, 19, 21, 30, 23
 *   0x889d0: { 0x00087b48 (gpio1), pin  9, dt_flags 0x0011 }
 *   0x889e0: { 0x00087b48 (gpio1), pin 10, dt_flags 0x0011 }
 *   (0x0011 = GPIO_ACTIVE_LOW | GPIO_PULL_UP)
 *
 * ITERATION 13 adds the panel-power descriptor that the same class had left
 * behind.  `power_for_panel` -> `gpio_dt_spec_activate` (0x179ec) and
 * `panel_pwr_gpio_deassert` (0x179f8) both `ldr r0,=0x000889f8 ; movs r1,#1/0 ;
 * b.w gpio_pin_set_dt`, and 0x889f8 was still a raw flash literal, so
 * gpio_pin_set_checked() received a bogus port pointer and asserted
 * (ZEPHYR FATAL ERROR 4 at 0.0477 s).  Transcribed from the image, the three
 * consecutive descriptors there are
 *   0x889e8: { 0x00087b60 (gpio0), pin 30, dt_flags 0 }
 *   0x889f0: { 0x00087b60 (gpio0), pin 21, dt_flags 0 }
 *   0x889f8: { 0x00087b60 (gpio0), pin 24, dt_flags 0 }
 * (0x87b60's name string is "gpio@842500" = gpio0; 0x87b48 is "gpio@842800"
 * = gpio1).
 *
 * The canonical parity bodies in recon/app/src/ are untouched.
 * See recon/emulator/reports/our_boot_bringup.md §Iteration 5.
 * ------------------------------------------------------------------------- */
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

/* Layout-identical to Zephyr's `struct gpio_dt_spec`
 * ({ const struct device *port; gpio_pin_t pin; gpio_dt_flags_t dt_flags; },
 * i.e. port@0, pin@4 (u8), dt_flags@6 (u16), sizeof = 8).  Spelled out locally
 * so this TU does not have to pull in <zephyr/drivers/gpio.h>, whose static
 * inlines collide with the recovered `gpio_pin_configure` reconstruction. */
struct g1_gpio_dt_spec {
	const struct device *port;
	unsigned char pin;
	unsigned short dt_flags;
};

#define G1_GPIO0 DEVICE_DT_GET(DT_NODELABEL(gpio0))
#define G1_GPIO1 DEVICE_DT_GET(DT_NODELABEL(gpio1))

/* was rodata_88340 (original 0x00088340) */
const struct g1_gpio_dt_spec g1_button_gpio_specs[9] = {
	{ .port = G1_GPIO0, .pin = 26, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 25, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 28, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 27, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 24, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 19, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 21, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 30, .dt_flags = 0 },
	{ .port = G1_GPIO0, .pin = 23, .dt_flags = 0 },
};

/* was rodata_889d0 (original 0x000889d0) */
const struct g1_gpio_dt_spec g1_gpio1_pin9_spec = {
	.port = G1_GPIO1, .pin = 9, .dt_flags = 0x0011
};

/* was rodata_889e0 (original 0x000889e0) */
const struct g1_gpio_dt_spec g1_gpio1_pin10_spec = {
	.port = G1_GPIO1, .pin = 10, .dt_flags = 0x0011
};

/* was rodata_889e8 (original 0x000889e8) */
const struct g1_gpio_dt_spec g1_gpio0_pin30_spec = {
	.port = G1_GPIO0, .pin = 30, .dt_flags = 0
};

/* was rodata_889f0 (original 0x000889f0) */
const struct g1_gpio_dt_spec g1_gpio0_pin21_spec = {
	.port = G1_GPIO0, .pin = 21, .dt_flags = 0
};

/* was rodata_889f8 (original 0x000889f8) -- the panel power-enable line */
const struct g1_gpio_dt_spec g1_gpio0_pin24_spec = {
	.port = G1_GPIO0, .pin = 24, .dt_flags = 0
};
