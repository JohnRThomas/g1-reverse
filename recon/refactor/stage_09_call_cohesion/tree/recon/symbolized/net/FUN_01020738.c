#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020738 @ 0x01020738
 * public-name: FUN_01020738
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   rodata_10208e1                           @ 0x010208e1
 *   g_net_ble_session_key_buf                @ 0x2100163c
 */
/* net-core FUN_01020738 @ 0x1020738  (parity 300 trials PROVEN) */

extern int FUN_01025bd4(unsigned int a);
extern void sdc_assertion_fail(unsigned int a, unsigned int b);

void FUN_01020738(unsigned int *param_1)
{
  int r = FUN_01025bd4(((unsigned long)&rodata_10208e1) /*=0x10208e1*/);
  if (r == 0) {
    volatile unsigned int *dst = (volatile unsigned int*)((unsigned long)&g_net_ble_session_key_buf) /*=0x2100163c*/;
    dst[0]=param_1[0]; dst[1]=param_1[1]; dst[2]=param_1[2]; dst[3]=param_1[3];
    return;
  }
  for (;;) {
    sdc_assertion_fail(0x3e, 0x8c0);
  }
}
