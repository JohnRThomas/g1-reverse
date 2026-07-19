#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000232c0 @ 0x000232c0
 * public-name: format_device_serial_to_buf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_device_serial_to_buf              <= FUN_000232c0 @ 0x000232c0
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 * address symbols (name @ address):
 *   rodata_a8c37                             @ 0x000a8c37
 *   g_device_serial_buf                      @ 0x20003003
 */
/* Reconstructed FUN_000232c0 @ 0x232c0  (parity: 300/300 trials, PROVEN) */

extern unsigned int snprintf(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int format_device_serial_to_buf(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  snprintf(((unsigned long)&g_device_serial_buf) /*=0x20003003*/, 0x10, ((unsigned long)&rodata_a8c37) /*=0xa8c37*/, param_1, param_4);
  return 0;
}
