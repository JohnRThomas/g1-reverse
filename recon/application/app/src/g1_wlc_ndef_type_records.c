/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 40) — the two NFC-Forum Wireless-Charging
 * NDEF record TYPE descriptors.
 *
 * `wlccap_record_encode` (original 0x25020) and `wlcstai_record_encode`
 * (0x25058) each call
 *
 *     opt_field1_set(node, 1, <descriptor>)
 *
 * with the literal-pool constants 0x200023c4 and 0x200023bc.  Those are
 * 8-byte objects in the shipped `.data`:
 *
 *     LMA(0x20000000 + x) = 0xf6d64 + x   (gen_app_data_image.py header)
 *     0x200023bc -> flash 0xf9120: dc f1 09 00 07 00 00 00 = { 0x0009f1dc, 7 }
 *     0x200023c4 -> flash 0xf9128: e4 f1 09 00 06 00 00 00 = { 0x0009f1e4, 6 }
 *
 * and tools/extract.py at 0x9f1d0 reads
 *
 *     "dc_nfc_init\0"  "WLCSTAI\0"  "WLCCAP\0"  "_st25dv_write  ret %d"
 *
 * so 0x0009f1dc is the ASCII "WLCSTAI" (7 characters, the WLC Status-and-
 * Information record type name) and 0x0009f1e4 is "WLCCAP" (6, the WLC
 * Capability record type name).  `opt_field1_set` reads the descriptor as
 * `{ const void *value; unsigned char len; }`: it rejects the pair when the
 * pointer is NULL and the length is non-zero, stores the length into node[1]
 * and the pointer into node[4..7].
 *
 * WHY THIS IS EMITTED RATHER THAN PINNED.  Both words are ORIGINAL-IMAGE FLASH
 * POINTERS, so the arena `.data` restore drops the whole group:
 * `gen_app_data_image.py`'s pointer policy only restores a structured group
 * when every pointer word in it resolves to a catalogued function or a
 * self-referential SRAM address, and a pointer to a bare rodata string is
 * neither.  Measured: `g1_arena_data_runs` in the generated
 * app/src/g1_app_data_image.c jumps 0x385 -> 0x3f4, i.e. arena offsets
 * 0x3bc and 0x3c4 stay ZERO.  Neither string is emitted either --
 * app/src/g1_app_string_rodata.c has no "WLCSTAI"/"WLCCAP" and
 * recon/symbols/g1_app_globals.ld has no rodata_9f1dc / rodata_9f1e4 pin.
 * With the descriptor zeroed, `opt_field1_set` sees value == NULL with
 * len == 0 (the group is all zero, so it does NOT even return the error) and
 * every WLC record would be serialized with an EMPTY type name.
 *
 * Emitting the pair relocates both the descriptors and the strings they point
 * at; recon/symbols/g1_app_globals.ld binds the `g_wlcstai_record_type` and
 * `g_wlccap_record_type` pins onto them.  Same mechanism as iteration 10's
 * g1_st25dv_ops_table.c: the arena slots 0x3bc..0x3cc become dead storage,
 * exactly like g_st25dv_i2c_dev at 0x3cc.  The canonical parity bodies in
 * recon/app/src are untouched.
 * ------------------------------------------------------------------------- */

/* was rodata_9f1dc (original 0x0009f1dc, 8 B incl. NUL) */
static const char g1_wlc_type_name_wlcstai[] = "WLCSTAI";
/* was rodata_9f1e4 (original 0x0009f1e4, 7 B incl. NUL) */
static const char g1_wlc_type_name_wlccap[] = "WLCCAP";

struct g1_wlc_ndef_type_record {
	const char *type_name;
	unsigned int type_name_len;
};

/* `retain`: the pin bindings below are lazy linker-script PROVIDEs, which do
 * not root the section against --gc-sections. */

/* was 0x200023bc (shipped .data, 8 B) */
const struct g1_wlc_ndef_type_record g1_wlcstai_ndef_type
	__attribute__((used, retain)) = {
	g1_wlc_type_name_wlcstai, 7u,
};

/* was 0x200023c4 (shipped .data, 8 B) */
const struct g1_wlc_ndef_type_record g1_wlccap_ndef_type
	__attribute__((used, retain)) = {
	g1_wlc_type_name_wlccap, 6u,
};
