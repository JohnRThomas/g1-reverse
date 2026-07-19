#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032ee4 @ 0x00032ee4
 * public-name: is_battery_critical
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed is_battery_critical @ 0x32ee4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;u8 is_battery_critical(void){return *(volatile u8*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/;}
