/* Reviewed net-core interior/shared-tail symbols.
 * These are address ownership aliases, not reconstructed function bodies. */
/* The original image loads 0x21000ea6 and accesses byte +1.  Keep the
 * second calibration byte inside the proven two-byte base object; this alias
 * allocates no storage.  See net_data_alias_resolutions.json. */
PROVIDE(g_21000ea7 = g_net_rssi_cal_offset + 1);
PROVIDE(FUN_01018f1a = 0x01018f1a); /* SDC LLCP store-result shared tail */
PROVIDE(FUN_01018f22 = 0x01018f22); /* SDC LLCP return shared tail */
PROVIDE(FUN_01018fac = 0x01018fac); /* SDC LLCP procedure continuation */
PROVIDE(FUN_0100b5f8 = FUN_0100ac34); /* 0x0100b5f8: exact b.w veneer */
