#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_event_record__param_0049               [param_0049; G1-original]
 *   param_2          => struct g1_layout_event_record_desc__param_0050          [param_0050; G1-original]
 * Raw function identity: 0x00025090.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00025090 @ 0x00025090
 * public-name: event_record_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   event_record_init                        <= FUN_00025090 @ 0x00025090
 * address symbols (name @ address):
 *   rodata_24a41                             @ 0x00024a41
 *   rodata_25021                             @ 0x00025021
 *   rodata_7c38b                             @ 0x0007c38b
 */
/* Reconstructed FUN_00025090 @ 0x25090  (parity: 300/300 trials, PROVEN) */

unsigned int event_record_init(unsigned char *param_1, unsigned int *param_2)
{
  unsigned int uVar1 = 7;
  if (param_1 != 0 && param_2 != 0) {
    *param_1 = 7;
    uVar1 = 0;
    *(unsigned int *)(param_1 + 4) = ((unsigned long)&rodata_7c38b) /*=0x7c38b*/;
    *(unsigned int *)(param_1 + 8) = ((unsigned long)&rodata_24a41) /*=0x24a41*/;
    *(unsigned int *)(param_1 + 0xc) = ((unsigned long)&rodata_25021) /*=0x25021*/;
    *(unsigned int *)(param_1 + 0x10) = *param_2;
    *(unsigned int *)(param_1 + 0x14) = param_2[1];
    *(unsigned short *)(param_1 + 0x18) = *(unsigned short *)(param_2 + 2);
  }
  return uVar1;
}
