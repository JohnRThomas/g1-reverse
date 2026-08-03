#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000232b0 @ 0x000232b0
 * public-name: get_device_serial_buf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_serial_buf                    <= FUN_000232b0 @ 0x000232b0
 * address symbols (name @ address):
 *   g_device_serial_buf                      @ 0x20003003
 */
/* Reconstructed FUN_000232b0 @ 0x232b0  (parity: 300/300 trials, PROVEN) */

unsigned int get_device_serial_buf(void){
  return ((unsigned long)&g_device_serial_buf) /*=0x20003003*/;
}
