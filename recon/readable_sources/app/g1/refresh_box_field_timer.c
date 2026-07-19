#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002542c @ 0x0002542c
 * public-name: refresh_box_field_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   refresh_box_field_timer                  <= FUN_0002542c @ 0x0002542c
 *   read_nfc_adc_scaled                      <= FUN_0007c830 @ 0x0007c830
 * address symbols (name @ address):
 *   g_box_field_timer                        @ 0x20007a24
 *   g_box_field_raw_timestamp                @ 0x20007a34
 */
/* Reconstructed FUN_0002542c @ 0x2542c  (parity: 300/300 trials, PROVEN) */

extern void read_nfc_adc_scaled(unsigned int);
void refresh_box_field_timer(void)
{
  unsigned int *puVar1 = (unsigned int *)((unsigned long)&g_box_field_raw_timestamp) /*=0x20007a34*/;
  read_nfc_adc_scaled(((unsigned long)&g_box_field_raw_timestamp) /*=0x20007a34*/);
  *(volatile unsigned int *)((unsigned long)&g_box_field_timer) /*=0x20007a24*/ = *(volatile unsigned int *)puVar1;
}
