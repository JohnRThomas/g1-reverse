#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_dev_channel_dispatch_entry__param_0664 [param_0664; G1-original]
 * Raw function identity: 0x00084090.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084090 @ 0x00084090
 * public-name: dev_channel_dispatch_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_channel_dispatch_lookup              <= FUN_00084090 @ 0x00084090
 */
/* Reconstructed FUN_00084090 @ 0x84090  (parity: 300/300 trials, PROVEN) */

int dev_channel_dispatch_lookup(int param_1, unsigned int param_2)
{
  unsigned char *pbVar2, *pbVar3, *pbVar4;
  unsigned int uVar5;
  void *fn;
  int r6 = *(volatile int*)(param_1+4);
  int r2 = *(volatile int*)(param_1+8);
  fn = *(void**)(r2+0x20);
  if (fn == 0) {
    return 0xffffffa8;
  }
  uVar5 = *(volatile unsigned char*)(r6+0x18);
  if (uVar5 == 0) {
    return ((int(*)(int,unsigned int))fn)(param_1,param_2);
  }
  pbVar2 = *(unsigned char**)(r6+0x14);
  pbVar4 = pbVar2;
  do {
    pbVar3 = pbVar4+1;
    if (*pbVar4 == param_2) {
      return ((int(*)(int,unsigned int))fn)(param_1,param_2);
    }
    pbVar4=pbVar3;
  } while(pbVar3 != pbVar2+uVar5);
  return 0xffffff7a;
}
