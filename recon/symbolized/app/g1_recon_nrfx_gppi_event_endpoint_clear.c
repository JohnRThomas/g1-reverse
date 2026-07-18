#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064fa8 @ 0x00064fa8
 * public-name: g1_recon_nrfx_gppi_event_endpoint_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a09                             @ 0x000f6a09
 *   rodata_f6a46                             @ 0x000f6a46
 */
/* Reconstructed g1_recon_nrfx_gppi_event_endpoint_clear @ 0x64fa8.
 * Raw identity/back-map: FUN_00064fa8.  Parity: 300/300 trials, PROVEN.
 */

extern unsigned long long assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int);
void g1_recon_nrfx_gppi_event_endpoint_clear(
    unsigned int channel, int event_endpoint,
    unsigned int param_3, unsigned int param_4)
{
  if (event_endpoint == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6a46) /*=0xf6a46*/,((unsigned long)&rodata_f6a09) /*=0xf6a09*/,0x5c);
    event_endpoint = (int)(assert_post_action(((unsigned long)&rodata_f6a09) /*=0xf6a09*/,0x5c) >> 32);
  }
  *(unsigned int *)(event_endpoint + 0x80) = 0;
  return;
}
