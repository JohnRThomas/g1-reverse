#include "g1_net_symbols.h"
/* net-core FUN_0100a664 @ 0x100a664  (parity 300 trials PROVEN) */
extern void FUN_01008d00(int, int);
extern int FUN_010279e6(int, int, int);
extern int FUN_01027258(unsigned int *, unsigned int);

#define P_0100a6e8 ((uintptr_t)&g_net_pool_blk_cnt) /*=0x21000bec*/
#define P_0100a6ec ((uintptr_t)&g_net_pool_blk_size) /*=0x21000bf0*/

unsigned int FUN_0100a664(unsigned char param_1, unsigned char param_2, unsigned int param_3, char param_4)
{
  unsigned int local_18 = param_3;
  char local_13 = param_4;
  unsigned char local_12 = param_2;
  unsigned char local_11 = param_1;
  int local_c;
  unsigned int uVar1;
  unsigned int *puVar2;

  if (!(((param_3 & 7) != 0) && ((param_3 & 3) == 0))) {
    FUN_01008d00(0x4c, 0x1f);
  }
  local_c = FUN_010279e6(0, local_11, 0x10e);
  puVar2 = &local_18;
  if (local_13 != 0) {
    puVar2 = (unsigned int *)0;
  }
  uVar1 = FUN_01027258(puVar2, local_c * (unsigned int)local_12);
  if (local_13 != 1) {
    *(volatile unsigned int *)P_0100a6e8 = local_18;
    *(volatile unsigned int *)P_0100a6ec = (unsigned int)local_c;
  }
  return uVar1;
}

