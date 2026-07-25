/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 15) — the nPM1300 charger `linear_range`
 * tables (original 0x8ba64 .. 0x8baac).
 *
 * `panel_temp_calibration_init` (FUN_00062644 @ 0x62644, the recovered
 * `npm1300_charger_init`) looks its devicetree values up in four
 * `struct linear_range` arrays through the pins `rodata_8ba64`,
 * `rodata_8ba7c`, `rodata_8ba88` and `rodata_8ba94`.  Those four pins were
 * still IDENTITY pins — `PROVIDE(rodata_8ba94 = 0x0008ba94)` — i.e. raw
 * ORIGINAL-image flash addresses.  Our build puts unrelated code at 0x8ba94,
 * so the lookup read garbage.
 *
 * MEASURED (iteration 15, build g1-i15b, 0.15 s):
 *   main+0x546  bl panel_temp_calibration_init
 *   45d62       bl layout_select_region(rodata_8ba94, cfg->term_microvolt, ..)
 *   45d66       adds r0,#22 ; 45d68 bne  -> NOT taken, so r0 == -22 (-EINVAL)
 *   45d6a       mvn r4,#21  -> return -22
 * and main then took its failure branch at 0x16e1c/0x16d5a -> 0x16f0c,
 * SKIPPING `call_hook(context, 0xb6c)` (= `jdb_panel_init`),
 * `pt_nfc_eeprom_link_start()` and `notification_system_init()`.  That single
 * -EINVAL is what kept E4 (panel init + BLE advertising) out of reach.
 *
 * The bytes below are read verbatim from app_update.bin at 0x8ba64 and decode
 * exactly as Zephyr 3.4.99's `drivers/mfd|charger/npm1300_charger.c` tables:
 *
 *   0x8ba64 vbus_limit_ranges    { 100000,      0, 1,  1 }, { 500000, 100000, 5, 15 }
 *   0x8ba7c dischg_limit_ranges  { 268090,   3230, 83, 415 }
 *   0x8ba88 charger_current_ranges { 32000,   2000, 16, 400 }
 *   0x8ba94 charger_volt_ranges  { 3500000, 50000, 0,  3 }, { 4000000, 50000, 4, 13 }
 *
 * All four are interior views of ONE contiguous 72-byte rodata block, so they
 * are emitted as one object and the four pins are bound at their original
 * relative offsets in recon/symbols/g1_app_globals.ld — the same argument the
 * RAM arena uses.  A linker rebind alone cannot express this because the
 * ORIGINAL ADDRESS ITSELF is what the recovered code dereferences.
 *
 * (recon/data/rodata_0x8ba64.c is the byte-verified data owner for the first
 * 52 bytes of the same block; it stops at 0x8ba98, four bytes into
 * charger_volt_ranges, so it cannot serve as the binding target.  It is left
 * untouched so the verified-data byte-match ledger stays exactly as generated.)
 */
#include <stdint.h>
#include <zephyr/kernel.h>

const uint8_t g1_npm1300_linear_ranges[72] __aligned(4)
	__attribute__((used, retain)) = {
	/* 0x8ba64  vbus_limit_ranges[0] = { 100000, 0, 1, 1 } */
	0xa0, 0x86, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00,
	/* 0x8ba70  vbus_limit_ranges[1] = { 500000, 100000, 5, 15 } */
	0x20, 0xa1, 0x07, 0x00, 0xa0, 0x86, 0x01, 0x00, 0x05, 0x00, 0x0f, 0x00,
	/* 0x8ba7c  dischg_limit_ranges[0] = { 268090, 3230, 83, 415 } */
	0x3a, 0x17, 0x04, 0x00, 0x9e, 0x0c, 0x00, 0x00, 0x53, 0x00, 0x9f, 0x01,
	/* 0x8ba88  charger_current_ranges[0] = { 32000, 2000, 16, 400 } */
	0x00, 0x7d, 0x00, 0x00, 0xd0, 0x07, 0x00, 0x00, 0x10, 0x00, 0x90, 0x01,
	/* 0x8ba94  charger_volt_ranges[0] = { 3500000, 50000, 0, 3 } */
	0xe0, 0x67, 0x35, 0x00, 0x50, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
	/* 0x8baa0  charger_volt_ranges[1] = { 4000000, 50000, 4, 13 } */
	0x00, 0x09, 0x3d, 0x00, 0x50, 0xc3, 0x00, 0x00, 0x04, 0x00, 0x0d, 0x00,
};
