/* Reviewed net-core interior/shared-tail symbols.
 * These are address ownership aliases, not reconstructed function bodies. */
/* The original image loads 0x21000ea6 and accesses byte +1.  Keep the
 * second calibration byte inside the proven two-byte base object; this alias
 * allocates no storage.  See net_data_alias_resolutions.json. */
PROVIDE(g_21000ea7 = g_net_rssi_cal_offset + 1);
/* Reviewed CPUNET read-only/address residues.  The first spelling was
 * historically misclassified as rodata but is an odd Thumb-valued callback;
 * the second is an interior address in the existing nrf_timer.h path string.
 * Neither expression allocates storage.  See net_rodata_gap_resolutions.json. */
PROVIDE(rodata_103a749 = 0x0103a749);
PROVIDE(rodata_103c4cc = rodata_103c4d0 - 4);
PROVIDE(FUN_01018f1a = 0x01018f1a); /* SDC LLCP store-result shared tail */
PROVIDE(FUN_01018f22 = 0x01018f22); /* SDC LLCP return shared tail */
PROVIDE(FUN_01018fac = 0x01018fac); /* SDC LLCP procedure continuation */
PROVIDE(FUN_0100b5f8 = FUN_0100ac34); /* 0x0100b5f8: exact b.w veneer */
