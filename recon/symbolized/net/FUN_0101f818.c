#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f818 @ 0x0101f818
 * public-name: FUN_0101f818
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_controller_random_init               <= FUN_0100f5d8 @ 0x0100f5d8
 *   callback_list_invoke_all                 <= FUN_010294c2 @ 0x010294c2
 */
/* net-core FUN_0101f818 @ 0x101f818  (parity 300 trials PROVEN) */

extern void FUN_0100ebc4(void);
extern void sdc_controller_random_init(void);
extern void FUN_0101e888(void);
extern void callback_list_invoke_all(unsigned int);

void FUN_0101f818(unsigned int param_1, unsigned int param_2)
{
  unsigned int base = G1N_21001230;

  FUN_0100ebc4();
  *(volatile unsigned int*)(base + 0x104) = param_2;
  callback_list_invoke_all(*(volatile unsigned int*)(base + 0x20c));
  FUN_0101e888();
  sdc_controller_random_init();
  *(volatile unsigned char*)(base + 0x218) = 1;
}
