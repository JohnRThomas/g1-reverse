/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 38) — the SAADC `struct adc_channel_cfg`
 * that `adc_nfc_init` hands to `adc_channel_setup`.
 *
 * `adc_nfc_init` (original 0x24b98) does
 *
 *     api->channel_setup(&rodata_87c20, &rodata_88a2a);
 *
 * where `rodata_87c20` is the "adc@e000" struct device.
 *
 * `rodata_87c20` was rebound onto the real DT device in iteration 11, but
 * `rodata_88a2a` — the channel configuration it points at — was left as a bare
 * `PROVIDE(rodata_88a2a = 0x00088a2a)`, i.e. an ORIGINAL-image flash address.
 * In the rebuilt image those seven bytes hold unrelated content, so
 * `adc_channel_setup` configured a wrong (or out-of-range) channel and
 * `adc_nfc_run`'s `adc_read` — which selects `channels = BIT(3)` — then bailed
 * out with the driver's own diagnostic.
 *
 * MEASURED FAILURE (build g1-i37a-app, Renode `run.out`): our `saadc` register
 * stream stops after `CH0/CH1/CH2.PSELP <- 0`.  All three writes come from PC
 * 0x5EED6 = `adc_nrfx_read+0xd6`, the per-channel deselect store of the
 * driver's channel loop, i.e. it walked the channel mask and gave up the moment
 * it reached channel 3 -- the "Channel 3 not configured" path.  The shipped
 * firmware instead goes on to program `CH3.PSELP <- 4`, `CH3.PSELN <- 0`,
 * `CH3.CONFIG <- 0x00020000` and run the conversion.  Whole-run access count:
 * ours 95 vs the oracle's 998.
 *
 * The shipped configuration, read straight out of app_update.bin at 0x88a2a
 * (tools/extract.py):
 *
 *     00 04 00 00 03 04 00
 *     ^^ gain             = 0 = ADC_GAIN_1_6
 *        ^^ reference     = 4 = ADC_REF_INTERNAL
 *           ^^^^^ acquisition_time = 0 = ADC_ACQ_TIME_DEFAULT
 *                 ^^ channel_id = 3, differential = 0
 *                    ^^ input_positive = 4 = NRF_SAADC_INPUT_AIN3
 *                       ^^ input_negative = 0 = NRF_SAADC_INPUT_DISABLED
 *
 * The shipped image packs `struct adc_channel_cfg` with 1-byte enums — the
 * object is only 2-byte aligned at 0x88a2a, which a 4-byte-enum layout could
 * not be — and so does this build (`-fshort-enums` is the arm-eabi default).
 * VERIFIED: the object this TU emits is `00 04 00 00 03 04 00`, BYTE-IDENTICAL
 * to the shipped seven bytes, so the pin is byte-exact and not merely
 * semantically equivalent.
 *
 * Cross-check against `display_sensor_parity.md` §4.5, which decodes the
 * shipped SAADC register writes independently: TACQ = 10 us (the driver's
 * default for ADC_ACQ_TIME_DEFAULT), GAIN = 1/6, REF = internal, 12-bit, no
 * oversampling, CH3/AIN3 only.
 *
 * `recon/symbols/g1_app_globals.ld` binds the `rodata_88a2a` pin onto this
 * object.  No canonical parity body is changed.
 * ------------------------------------------------------------------------- */

#include <zephyr/drivers/adc.h>
#include <hal/nrf_saadc.h>

/* was rodata_88a2a (original 0x00088a2a) */
/* `retain`: the rodata_88a2a binding is a lazy linker-script PROVIDE, which
 * does not root the section against --gc-sections. */
const struct adc_channel_cfg g1_adc_nfc_channel_cfg __attribute__((used, retain)) = {
	.gain             = ADC_GAIN_1_6,
	.reference        = ADC_REF_INTERNAL,
	.acquisition_time = ADC_ACQ_TIME_DEFAULT,
	.channel_id       = 3,
	.differential     = 0,
	.input_positive   = NRF_SAADC_INPUT_AIN3,
	.input_negative   = NRF_SAADC_INPUT_DISABLED,
};
