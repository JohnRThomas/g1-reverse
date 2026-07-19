#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063bcc @ 0x00063bcc
 * public-name: app_event_submit_power
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   app_event_alloc                          <= FUN_0004f564 @ 0x0004f564
 *   app_event_submit_power                   <= FUN_00063bcc @ 0x00063bcc
 * address symbols (name @ address):
 *   rodata_fa9cc                             @ 0x000fa9cc
 */
/* Reconstructed FUN_00063bcc @ 0x63bcc  (parity: 300/300 trials, PROVEN) */

extern unsigned int app_event_alloc(unsigned int a);
void app_event_submit_power(void) {
  unsigned int r = app_event_alloc(0xc);
  if (r != 0) {
    *(unsigned int*)(r + 4) = ((unsigned long)&rodata_fa9cc) /*=0xfa9cc*/;
  }
}
