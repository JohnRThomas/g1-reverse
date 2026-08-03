#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010215f4 @ 0x010215f4
 * public-name: controller_radio_time_mode1_to_mode2
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_radio_time_mode1_to_mode2     <= FUN_010215f4 @ 0x010215f4
 * address symbols (name @ address):
 *   rodata_103c5c4                           @ 0x0103c5c4
 */
/* net-core FUN_010215f4 @ 0x10215f4  (parity 300 trials PROVEN) */

int controller_radio_time_mode1_to_mode2(int param_1, int param_2) {
  volatile unsigned short *DAT_0102160c = (volatile unsigned short *)((unsigned long)&rodata_103c5c4) /*=0x103c5c4*/;
  unsigned int DAT_01021610 = 0x10624dd3;
  return param_1 - 2 + (unsigned int)(((unsigned long long)DAT_01021610 * (unsigned long long)(DAT_0102160c[param_2] + 999)) >> 0x26);
}
