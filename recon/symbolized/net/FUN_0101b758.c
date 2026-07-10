#include "g1_net_symbols.h"
/* net-core FUN_0101b758 @ 0x101b758  (parity 300 trials PROVEN) */
#define P_0101b7e0 ((uintptr_t)&g_net_conn_teardown_busy_flag) /*=0x2100111c*/

extern void FUN_01008d00(int, int);
extern int FUN_01009dd8(void *);
extern int FUN_01009d18(int, int);
extern void FUN_0102411c(int);
extern int FUN_01022ebc(int);
extern void FUN_0101dd0c(int);

void FUN_0101b758(void)
{
  unsigned char *puVar1;
  int iVar2;
  int iVar3;
  short *local_28;
  int uStack_24;

  puVar1 = (unsigned char *)P_0101b7e0;
  *(volatile unsigned char *)P_0101b7e0 = 1;

L_loop_top:
  local_28 = (short *)0;
  uStack_24 = 0;

L_inner:
  iVar3 = FUN_01009dd8(&local_28);
  if (iVar3 != 0) goto LAB_end;
  if (local_28 == (short *)0 || *((unsigned char *)local_28 + 0x300) == 0) goto L_inner;

  if (*local_28 == (short)-1) goto LAB_end;
  iVar3 = FUN_01009d18(*local_28, 0);
  if (iVar3 == 0) goto L_abort1;

  FUN_0102411c(*(unsigned char *)(iVar3 + 0x301));
  *(unsigned char *)(iVar3 + 0x300) = 0;
  iVar2 = FUN_01022ebc(*(unsigned char *)(iVar3 + 0x301));
  if (iVar2 == 0) goto L_abort2;

  *(unsigned char *)(iVar3 + 0x301) = 0x20;
  FUN_0101dd0c(iVar3 + 0x2d8);
  goto L_loop_top;

L_abort1:
  FUN_01008d00(0x35, 0x1d0);
L_abort2:
  for (;;) {
    FUN_01008d00(0x35, 0x1bf);
  }

LAB_end:
  *puVar1 = 0;
  return;
}

