#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_lc3_bwdet_state__param_0368            [param_0368; library]
 * Raw function identity: 0x00068b2c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00068b2c @ 0x00068b2c
 * public-name: lc3_bwdet_put_bw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_put_bits_generic                     <= FUN_00068908 @ 0x00068908
 *   lc3_bwdet_put_bw                         <= FUN_00068b2c @ 0x00068b2c
 */
/* Reconstructed FUN_00068b2c @ 0x68b2c  (parity: 300/300 trials, PROVEN) */

extern void lc3_put_bits_generic(int,unsigned int,unsigned int);
void lc3_bwdet_put_bw(int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;
  int iVar2;
  uVar1 = (param_2 > 1) ? 1 : 0;
  if (param_2 != 0) uVar1 += 1;
  if (param_2 > 3) uVar1 += 1;
  if (uVar1 != 0) {
    iVar2 = uVar1 + *(unsigned int*)(param_1+0x20);
    if (iVar2 > 0x20) {
      lc3_put_bits_generic(param_1, (unsigned int)param_3, uVar1);
      return;
    }
    *(unsigned int*)(param_1+0x1c) = *(unsigned int*)(param_1+0x1c) | (param_3 << (*(unsigned int*)(param_1+0x20) & 0xff));
    *(int*)(param_1+0x20) = iVar2;
  }
}
