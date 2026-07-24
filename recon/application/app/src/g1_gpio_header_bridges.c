/* ---------------------------------------------------------------------------
 * LIBRARY DISPLACEMENT — Batch 0 (goal G2, P4 iteration 7 Step B).
 *
 * `recon/ownership/library_displacement_report.md` §3a/§4 identifies four
 * out-lined `zephyr/include/zephyr/drivers/gpio.h` static inlines as the
 * highest-value displacement candidates:
 *
 *   VA         current symbol              real gpio.h identity
 *   0x00017688 gpio_pin_configure_17688    gpio_pin_configure_dt
 *   0x00017858 gpio_pin_configure          gpio_pin_interrupt_configure_dt
 *   0x000177c4 gpio_pin_get_raw_checked    gpio_pin_get_raw
 *   0x00017980 gpio_pin_get_checked        gpio_pin_get   (on the gpio0 port)
 *
 * Identity evidence is the `__ASSERT` file literal
 * "WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" in each literal pool —
 * that text exists ONLY inside those header inline bodies.  Their four
 * reconstruction TUs are excluded in `recon/ownership/adoption_manifest.json`
 * and therefore no longer appear in `recon/generated/app_retained_sources.cmake`.
 *
 * A header `static inline` has no external symbol to bind to, so displacement
 * cannot be a linker rebind: the recovered CALLERS still emit a `BL` to the
 * out-lined identity.  This TU re-expresses each historical identity as a thin
 * bridge over the real API, so the compiler re-inlines the genuine gpio.h body
 * here and every caller gets the upstream semantics with no source change to
 * the recovered bodies (`button_init`, `read_sw0_pin`,
 * `nfc_field_event_signal_sem`).
 *
 * Why this is the right displacement (per identity, from the recovered bodies
 * and the original image bytes):
 *  * 0x17688 reads spec->port / spec->pin / spec->dt_flags, ORs `dt_flags`
 *    with the caller's flags and tail-calls `api->pin_configure` — i.e.
 *    `gpio_pin_configure_dt(spec, extra_flags)`.
 *  * 0x17858 masks GPIO_INT_{DISABLE,ENABLE,EDGE} (0x1600000) and
 *    GPIO_INT_{LOW_0,HIGH_1} (0x6000000), flips the trigger when
 *    GPIO_INT_LEVELS_LOGICAL (0x800000) and `data->invert` disagree, and
 *    dispatches `api + 0x18` (`pin_interrupt_configure`) — i.e.
 *    `gpio_pin_interrupt_configure_dt(spec, flags)`.  The candidate JSON
 *    records the coarser `gpio_pin_configure`; the byte-level dispatch slot
 *    and the flag masks pin it to the interrupt variant.
 *  * 0x177c4 dispatches `api + 4` (`port_get_raw`) and returns
 *    `(value & BIT(pin)) != 0` — `gpio_pin_get_raw(port, pin)`.
 *  * 0x17980 does the same but XORs `data->invert` first, and hard-codes the
 *    gpio0 device — `gpio_pin_get(gpio0, pin)`.
 *
 * The recovered callers declare these with loose `unsigned int` prototypes;
 * that is ABI-compatible on AAPCS (pointer and u32 both travel in r0/r1) and
 * needs no change on their side.  `gpio_pin_get_checked`'s reconstruction took
 * two extra junk arguments that the original never used; `button_init` already
 * calls it with one.
 *
 * See recon/emulator/reports/our_boot_bringup.md §Iteration 7 Step B.
 * ------------------------------------------------------------------------- */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

/* 0x00017688 */
int gpio_pin_configure_17688(const struct gpio_dt_spec *spec,
			     gpio_flags_t extra_flags)
{
	return gpio_pin_configure_dt(spec, extra_flags);
}

/* 0x00017858.  The historical identity is spelled `gpio_pin_configure`, which
 * collides with gpio.h's own inline of that name, so the symbol is attached
 * with an `__asm__` label — the same conflict-free mechanism
 * recon/emulator/reports/pointer_rebind.md uses for function-pointer aliases. */
int g1_gpio_pin_interrupt_configure_bridge(const struct gpio_dt_spec *spec,
					   gpio_flags_t flags)
	__asm__("gpio_pin_configure");

int g1_gpio_pin_interrupt_configure_bridge(const struct gpio_dt_spec *spec,
					   gpio_flags_t flags)
{
	return gpio_pin_interrupt_configure_dt(spec, flags);
}

/* 0x000177c4 */
int gpio_pin_get_raw_checked(const struct device *port, gpio_pin_t pin)
{
	return gpio_pin_get_raw(port, pin);
}

/* 0x00017980 */
int gpio_pin_get_checked(gpio_pin_t pin)
{
	return gpio_pin_get(DEVICE_DT_GET(DT_NODELABEL(gpio0)), pin);
}
