/* readable reconstruction; identity: FUN_0006f91c @ 0x0006f91c
 * public-name: lc3_spec_put_side
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_put_bits_generic                     <= FUN_00068908 @ 0x00068908
 *   lc3_spec_put_side                        <= FUN_0006f91c @ 0x0006f91c
 */
/* Reconstructed FUN_0006f91c @ 0x6f91c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lc3_put_bits_generic(...);
void lc3_spec_put_side(int param_1, int param_2, int param_3, int *param_4){
  uint8_t bVar1;
  int iVar2, iVar3, iVar4;
  uint32_t uVar5, uVar6;
  iVar3 = (param_3 * (param_2 + 3) + param_2 + 3) * 5;
  iVar4 = (iVar3 > 0x10) + 5;
  if (iVar3 > 0x20) iVar4 = (iVar3 > 0x10) + 6;
  iVar2 = param_4[1] >> 1;
  if (iVar2 < 1) iVar2 = 1;
  if (iVar3 > 0x40) iVar4 = iVar4 + 1;
  uVar5 = *(uint32_t*)(param_1 + 0x20);
  uVar6 = uVar5 + iVar4;
  if ((int)uVar6 < 0x21){
    *(uint32_t*)(param_1+0x20) = uVar6;
    *(uint32_t*)(param_1+0x1c) = *(uint32_t*)(param_1+0x1c) | ((iVar2 - 1) << (uVar5 & 0xff));
    bVar1 = *(uint8_t*)((char*)param_4 + 8);
  } else {
    lc3_put_bits_generic(param_1, iVar2 - 1, iVar4);
    uVar6 = *(uint32_t*)(param_1+0x20);
    bVar1 = *(uint8_t*)((char*)param_4 + 8);
  }
  uVar5 = uVar6 + 1;
  if ((int)uVar5 < 0x21){
    *(uint32_t*)(param_1+0x20) = uVar5;
    *(uint32_t*)(param_1+0x1c) = *(uint32_t*)(param_1+0x1c) | ((uint32_t)bVar1 << (uVar6 & 0xff));
    iVar3 = *param_4;
  } else {
    lc3_put_bits_generic(param_1, (uint32_t)bVar1, 1);
    uVar5 = *(uint32_t*)(param_1+0x20);
    iVar3 = *param_4;
  }
  if ((int)(uVar5 + 8) < 0x21){
    *(uint32_t*)(param_1+0x1c) = *(uint32_t*)(param_1+0x1c) | (iVar3 << (uVar5 & 0xff));
    *(uint32_t*)(param_1+0x20) = uVar5 + 8;
    return;
  }
  lc3_put_bits_generic(param_1, iVar3, 8);
}
