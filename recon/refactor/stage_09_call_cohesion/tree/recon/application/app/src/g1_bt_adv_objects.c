/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 22) — the three advertising objects that
 * `bt_start` (FUN_00019308 @ 0x00019308) hands to `bt_le_adv_start`.
 *
 * With the newlib printf family displaced (Batch 4) the device name is
 * formatted correctly for the first time and the firmware reaches
 *
 *     Advertising Even G1_R_FFFFFF failed to start (err -22)
 *
 * i.e. `bt_le_adv_start(params, ad, 2, sd, 1)` returns -EINVAL.  Three of its
 * four operands were still bound to ORIGINAL-image addresses that hold
 * unrelated bytes in this relocated build:
 *
 * 1. `rodata_8839c` — the 20-byte `struct bt_le_adv_param`.  `bt_start` copies
 *    it word by word into a stack local:
 *        uint32_t params[5];
 *        for (i = 0; i < 5; i++) params[i] = ((const uint32_t *)0x8839c)[i];
 *    so the extent is exactly 20 bytes = sizeof(struct bt_le_adv_param).
 *    g1_app_globals.ld still had the identity pin
 *    `PROVIDE(rodata_8839c = 0x0008839c)`, and iteration 21's string-rodata
 *    generator could not emit it because the bytes are a binary struct, not a
 *    NUL-terminated printable string.  MEASURED on /private/tmp/g1-i22a-app:
 *    address 0x0008839c in OUR image holds the ASCII
 *    `5f 74 79 70 65 73 2e 68 00 02 00 00 5f 73 74 64` ("_types.h..._std"),
 *    so `options` read 0x682e7365 — a word full of undefined
 *    BT_LE_ADV_OPT_* bits, which is precisely what `valid_adv_param()`
 *    rejects with -EINVAL.
 *
 *    Shipped bytes (app_update.bin @ 0x8839c, via tools/extract.py):
 *        00 00 00 00 | 01 00 00 00 | 60 01 00 00 | e0 01 00 00 | 00 00 00 00
 *    decoding as struct bt_le_adv_param {
 *        .id = 0, .sid = 0, .secondary_max_skip = 0,
 *        .options      = 0x00000001  (BT_LE_ADV_OPT_CONNECTABLE),
 *        .interval_min = 0x0160      (352 * 0.625 ms = 220 ms),
 *        .interval_max = 0x01e0      (480 * 0.625 ms = 300 ms),
 *        .peer         = NULL }
 *    — every field inside the ranges `valid_adv_param()` accepts.
 *
 * 2/3. `g_20002350` (the 1-entry scan-response array) and `g_20002358` (the
 *    2-entry advertising array).  Both are `.data` in the shipped image and
 *    both initialisers CONTAIN POINTERS, so the RAM-arena `.data` restore
 *    (recon/application/gen_app_data_image.py, pointer-word policy) drops the
 *    whole run: measured, the generated run table covers arena offset 0x348
 *    for 4 bytes and then nothing until 0x368, so 0x350..0x367 stayed ZERO.
 *    `bt_start` only writes `sd[0].data_len`, `sd[0].data`, `ad[1].type`,
 *    `ad[1].data_len` and `ad[1].data` at run time; `sd[0].type`, all of
 *    `ad[0]`, and `ad[1]`'s padding come from the initialiser.  With the
 *    array zeroed, `sd[0].type` advertised as 0x00 instead of
 *    BT_DATA_NAME_COMPLETE and `ad[0]` was an empty AD structure instead of
 *    the flags byte.
 *
 *    Shipped `.data` load image (LMA flash 0xf6d64 for VMA 0x20000000, the
 *    base proven three ways in gen_app_data_image.py):
 *        0x20002350  09 07 00 00 7c ac 09 00
 *                    -> sd[0] = { BT_DATA_NAME_COMPLETE, 7, "Even G1" }
 *                       (0x0009ac7c is rodata_9ac7c = "Even G1\0")
 *        0x20002358  01 01 00 00 e1 2f 00 20   00 00 00 00 00 00 00 00
 *                    -> ad[0] = { BT_DATA_FLAGS, 1, &0x20002fe1 }
 *                       ad[1] = zeroed, filled in by bt_start
 *        0x20002fe0  01 06 ff ...   -> the flags byte at 0x20002fe1 is 0x06 =
 *                       BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR.  That byte IS
 *                       restored by the arena data image, so ad[0].data is
 *                       bound to it rather than duplicated here.
 *
 *    `struct bt_data` is { uint8_t type; uint8_t data_len; const uint8_t
 *    *data; } — 8 bytes with `data` at +4 — which the shipped initialisers and
 *    bt_start's own `*(uint16_t *)(ad + 8) = 0x14ff` /
 *    `*(void **)(ad + 0x0c) = name_data` stores both confirm.  The next pin
 *    after the advertising array is `g_t_init = g1_ram_arena + 0x368`, so the
 *    array is exactly the two entries bt_start passes as `ad_len = 2`.
 *
 * As with g1_npm1300_linear_ranges.c and g1_st25dv_ops_table.c, a linker
 * rebind alone cannot express any of this because the object CONTENTS embed
 * pointers, so the objects are emitted here and the three pins are bound onto
 * them in recon/symbols/g1_app_globals.ld.  No canonical parity body changes;
 * bt_start still spells the pins.
 */
#include <stdint.h>
#include <zephyr/kernel.h>

/* "Even G1\0" — emitted byte-exactly by recon/application/gen_app_string_rodata.c
 * (iteration 21) from app_update.bin at 0x0009ac7c. */
extern const unsigned char rodata_9ac7c[];
/* The recovered RAM arena; g1_ram_arena[x] is the shipped image's 0x20002000+x. */
extern unsigned char g1_ram_arena[];

/* struct bt_le_adv_param, byte-exact from app_update.bin @ 0x0008839c. */
const uint8_t g1_bt_le_adv_param[20] __aligned(4)
	__attribute__((used, retain)) = {
	/* id, sid, secondary_max_skip, pad */
	0x00, 0x00, 0x00, 0x00,
	/* options      = BT_LE_ADV_OPT_CONNECTABLE */
	0x01, 0x00, 0x00, 0x00,
	/* interval_min = 0x0160 */
	0x60, 0x01, 0x00, 0x00,
	/* interval_max = 0x01e0 */
	0xe0, 0x01, 0x00, 0x00,
	/* peer         = NULL */
	0x00, 0x00, 0x00, 0x00,
};

struct g1_bt_data {
	uint8_t type;
	uint8_t data_len;
	uint8_t pad[2];
	const uint8_t *data;
};

/* 0x20002350: the scan-response array (bt_start passes sd_len = 1). */
struct g1_bt_data g1_bt_adv_scan_rsp[1] __aligned(4)
	__attribute__((used, retain)) = {
	{ 0x09, 0x07, { 0x00, 0x00 }, rodata_9ac7c },
};

/* 0x20002358: the advertising array (bt_start passes ad_len = 2 and fills
 * entry 1 with the 0xff manufacturer-data record at run time). */
struct g1_bt_data g1_bt_adv_data[2] __aligned(4)
	__attribute__((used, retain)) = {
	{ 0x01, 0x01, { 0x00, 0x00 }, &g1_ram_arena[0xfe1] },
	{ 0x00, 0x00, { 0x00, 0x00 }, (const uint8_t *)0 },
};
