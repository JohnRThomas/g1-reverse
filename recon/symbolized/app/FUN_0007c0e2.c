#include "g1_app_symbols.h"
/* named: FUN_0007c0e2 */
/* Reconstructed FUN_0007c0e2 @ 0x7c0e2  (parity: 300/300 trials, PROVEN) */

extern int ancs_get_conn_ctx(void);
extern int enqueue_uid(void *p);
extern void FUN_00072880(unsigned int a);

void FUN_0007c0e2(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int local_18 = param_1;
  unsigned int local_14 = param_2;
  unsigned int uStack_10 = param_3;
  (void)uStack_10;
  int iVar1 = ancs_get_conn_ctx();
  local_14 = (local_14 & 0xffffff00u) | 2u;
  (void)local_14;
  local_18 = param_1;
  int iVar2 = enqueue_uid(&local_18);
  if (iVar2 == 0) {
    FUN_00072880((unsigned int)iVar1 + 0x200);
  }
}

