#include "g1_app_symbols.h"
/* named: conn_ctx_cleanup_if_pending */
/* Reconstructed conn_ctx_cleanup_if_pending @ 0x81720  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_000816a2(int a, int b);
extern void FUN_0007350c(int a, int b, int c, int d);

void conn_ctx_cleanup_if_pending(int param_1)
{
  unsigned long long uVar2 = FUN_000816a2(param_1 + 0x2c, param_1);
  int iVar1 = (int)(uVar2 >> 32);
  if (((int)uVar2 != 0) && ((*(int *)(iVar1 + 0x30) != 0) || (*(int *)(iVar1 + 0x4c) != 0))) {
    FUN_0007350c(iVar1 + 0x50, iVar1, 0, 0);
  }
}

