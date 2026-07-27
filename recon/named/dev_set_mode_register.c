#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000841fc @ 0x000841fc
 * public-name: dev_set_mode_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 *   dev_set_mode_register                    <= FUN_000841fc @ 0x000841fc
 */
/* Reconstructed dev_set_mode_register @ 0x841fc  (CFG-directed candidate) */
/* Reconstructed dev_set_mode_register @ 0x841fc  (dev_set_mode_register)
 *
 * ITERATION-13 DEFECT FIX (dropped outgoing argument, same family as
 * 0x83d80 / 0x83dba / 0x83e0e): the callee at 0x83e0e takes FIVE arguments --
 * the fifth, an 8-bit write mask, travels on the stack -- and the previous
 * reconstruction declared it with four and dropped the mask entirely.
 * The original computes the mask in r2 and hands it over through its own
 * incoming 5th-argument slot before tail-branching:
 *     84216  movne r2,#0x47            ; mask when mode != 1
 *     84218  moveq r2,#0xb8            ; mask when mode == 1
 *     8422a  str   r2,[sp,#4]          ; == entry sp+0, the outgoing 5th arg
 *     8422c  movs  r2,#12              ; register selector (0xc / 0xd / 0xe)
 *     8422e  movs  r1,#4
 *     84230  ldr   r0,[r0,#28]
 *     84232  ldr.w r4,[sp],#4
 *     84236  b.w   0x83e0e
 */
#include <stdint.h>
extern int dev_reg_modify_bits(int, unsigned int, unsigned int, unsigned int, unsigned char);
uint32_t dev_set_mode_register(int param_1, int param_2, char param_3, uint32_t param_4,
                      char param_5)
{
  int eq = (param_2 == 1);
  uint32_t uVar1 = (uint8_t)(param_3 + 1);
  unsigned char mask = eq ? 0xb8 : 0x47;
  if (eq) uVar1 <<= 3;
  if (!eq) param_4 = uVar1 | (param_4 << 6);
  else     param_4 = uVar1 | (param_4 << 7);
  param_4 = param_4 & 0xff;
  uint32_t uVar2;
  if (param_5 == 1) uVar2 = 0xd;
  else if (param_5 == 2) uVar2 = 0xe;
  else if (param_5 != 0) return 0xffffff7a;
  else uVar2 = 0xc;
  return dev_reg_modify_bits(*(volatile int*)(param_1 + 0x1c), 4, uVar2,
                      param_4 & 0xff, mask);
}
