#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025448 @ 0x00025448
 * public-name: refresh_and_read_box_field_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   refresh_box_field_timer                  <= FUN_0002542c @ 0x0002542c
 *   refresh_and_read_box_field_timer         <= FUN_00025448 @ 0x00025448
 * address symbols (name @ address):
 *   g_box_field_timer                        @ 0x20007a24
 */
/* Reconstructed FUN_00025448 @ 0x25448  (parity: 300/300 trials, PROVEN) */

extern void refresh_box_field_timer(void);
unsigned int refresh_and_read_box_field_timer(void)
{
  refresh_box_field_timer();
  return *(volatile unsigned int *)((unsigned long)&g_box_field_timer) /*=0x20007a24*/;
}
