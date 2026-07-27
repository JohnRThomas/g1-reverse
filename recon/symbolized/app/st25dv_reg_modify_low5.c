#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c8fa @ 0x0007c8fa
 * public-name: st25dv_reg_modify_low5
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   ipc_ept_op_c_locked_retry                <= FUN_00025850 @ 0x00025850
 *   st25dv_reg_modify_low5                   <= FUN_0007c8fa @ 0x0007c8fa
 */
/* Reconstructed FUN_0007c8fa @ 0x7c8fa  (parity: 300/300 trials, PROVEN) */

extern int ipc_ept_op_b_locked_retry(int, int, void*, int, int, int);
extern int ipc_ept_op_c_locked_retry(int, unsigned int, unsigned int, int);

void st25dv_reg_modify_low5(int param_1, int param_2)
{
  int iVar1;
  unsigned char local;
  iVar1 = ipc_ept_op_b_locked_retry(param_1, 1, &local, 1, param_1, param_2);
  if (iVar1 == 0) {
    local = (local & ~0x1f) | (param_2 & 0x1f);
    ipc_ept_op_c_locked_retry(param_1, 1, &local, 1);
  }
}
