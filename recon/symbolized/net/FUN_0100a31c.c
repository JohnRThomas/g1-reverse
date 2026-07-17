#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a31c @ 0x0100a31c
 * public-name: FUN_0100a31c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_quarter_get            <= FUN_01027af2 @ 0x01027af2
 *   controller_timing_delta_clamp            <= FUN_01027b32 @ 0x01027b32
 * address symbols (name @ address):
 *   g_net_storage_area_id                    @ 0x21000bc0
 */
/* net-core FUN_0100a31c @ 0x100a31c  (parity 300 trials PROVEN) */
extern unsigned int controller_timing_quarter_get(unsigned short);
extern unsigned int FUN_01027b0c(unsigned short);
extern unsigned int controller_timing_delta_clamp(unsigned short);

#define DAT_0100a43c ((unsigned long)&g_net_storage_area_id) /*=0x21000bc0*/

void FUN_0100a31c(int param_1, char param_2)
{
  unsigned short uVar1;
  unsigned short uVar2;
  int iVar3;
  int local_10;
  int local_c;

  iVar3 = *(volatile int *)(param_1 + 4);
  if (param_2 == 0) {
    *(volatile unsigned char *)(param_1 + 1) = 0;
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(volatile unsigned short *)(param_1 + (local_10 + 0xc) * 2) = 0;
      *(volatile unsigned short *)(param_1 + (local_10 + 0x10) * 2) = 0;
      *(volatile unsigned int *)(local_10 * 4 + param_1 + 4) = 0;
      *(volatile unsigned char *)(local_10 + param_1 + 0x14) = 0;
    }
    uVar2 = (unsigned short)(FUN_01027b0c(*(volatile unsigned short *)DAT_0100a43c) & 0xffffu);
    uVar1 = (unsigned short)(controller_timing_delta_clamp(*(volatile unsigned short *)DAT_0100a43c) & 0xffffu);
    *(volatile int *)(param_1 + 4) = iVar3;
    *(volatile unsigned short *)(param_1 + 0x20) = uVar1;
    *(volatile unsigned int *)(param_1 + 8) = iVar3 + (unsigned int)uVar1;
    *(volatile unsigned short *)(param_1 + 0x22) = uVar2;
    *(volatile int *)(param_1 + 0xc) = iVar3;
    *(volatile unsigned short *)(param_1 + 0x24) = uVar1;
    *(volatile unsigned int *)(param_1 + 0x10) = iVar3 + (unsigned int)uVar1;
    *(volatile unsigned short *)(param_1 + 0x26) = uVar2;
  } else {
    *(volatile unsigned char *)(param_1 + 1) = 1;
    uVar1 = (unsigned short)(controller_timing_quarter_get(*(volatile unsigned short *)DAT_0100a43c) & 0xffffu);
    for (local_c = 0; local_c < 4; local_c = local_c + 1) {
      *(volatile unsigned short *)(param_1 + (local_c + 0xc) * 2) = 0;
      *(volatile unsigned short *)(param_1 + (local_c + 0x10) * 2) = uVar1;
      *(volatile unsigned int *)(local_c * 4 + param_1 + 4) = iVar3 + local_c * uVar1;
      *(volatile unsigned char *)(local_c + param_1 + 0x14) = 0;
    }
  }
  return;
}
