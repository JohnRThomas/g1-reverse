#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_lc3_bits_t__param_0366                 [param_0366; library]
 * Raw function identity: 0x0006b378.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006b378 @ 0x0006b378
 * public-name: lc3_ltpf_put_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_put_bits_generic                     <= FUN_00068908 @ 0x00068908
 *   lc3_ltpf_put_data                        <= FUN_0006b378 @ 0x0006b378
 */
/* Reconstructed FUN_0006b378 @ 0x6b378  (parity: 300/300 trials, PROVEN) */

extern void lc3_put_bits_generic(int a, unsigned int b, unsigned int c, unsigned int d);

void lc3_ltpf_put_data(int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char bVar1;
  int iVar2;
  int iVar3;
  unsigned int uVar4;
  unsigned int uVar5;

  uVar4 = *(unsigned int *)(param_1 + 0x20);
  uVar5 = uVar4 + 1;
  bVar1 = *param_2;
  if ((int)uVar5 < 0x21) {
    *(unsigned int *)(param_1 + 0x20) = uVar5;
    *(unsigned int *)(param_1 + 0x1c) = *(unsigned int *)(param_1 + 0x1c) | ((unsigned int)bVar1 << (uVar4 & 0xff));
    iVar2 = uVar4 + 10;
    iVar3 = *(int *)(param_2 + 4);
  } else {
    lc3_put_bits_generic(param_1,(unsigned int)bVar1,1,0);
    uVar5 = *(unsigned int *)(param_1 + 0x20);
    iVar3 = *(int *)(param_2 + 4);
    iVar2 = uVar5 + 9;
  }
  if (iVar2 < 0x21) {
    *(unsigned int *)(param_1 + 0x1c) = *(unsigned int *)(param_1 + 0x1c) | ((unsigned int)iVar3 << (uVar5 & 0xff));
    *(int *)(param_1 + 0x20) = iVar2;
    return;
  }
  lc3_put_bits_generic(param_1,iVar3,9,param_4);
}
