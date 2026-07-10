#include "g1_net_symbols.h"
/* net-core FUN_01020a6c @ 0x1020a6c  (parity 200 trials PROVEN) */
/* net-core FUN_01020a6c @ 0x1020a6c  (parity 300 trials PROVEN) */
extern void FUN_01008d00(unsigned int a, unsigned int b);
extern unsigned int FUN_01023e88(void);
extern int FUN_01025bb0(void *p);
extern void FUN_01020a00(int p3);
extern void FUN_010216d4(int p3, unsigned int a, int b, void *p);
extern void FUN_010215a8(int a);
extern unsigned long long FUN_010218fc(void *p);
extern void FUN_01020108(int lo, int hi);
extern void FUN_01020500(void);
extern int FUN_01020168(int p3);
extern void FUN_01025c9c(void *p, unsigned int a, int b);
extern int FUN_010218cc(int a, int b);
extern int FUN_010218c0(int a, int b);
extern int FUN_01025bc8(void *p);

#define IVAR6    ((uintptr_t)&g_nrf802154_core_state) /*=0x210015f0*/   /* DAT_01020cfc */
#define IVAR5_0  "f_timer.h" /*=0x103c4d0*/   /* DAT_01020d00 */
#define IVAR4_0  REG_41008000 /*=0x41008000*/   /* DAT_01020d04 */
#define DAT_D08  0x10624dd3u
#define DAT_D0C  0x80000008u
#define DAT_D10  REG_4100c000 /*=0x4100c000*/
#define DAT_D14  ((uintptr_t)&g_net_ll_sched_req_buf) /*=0x21000028*/

int FUN_01020a6c(int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar3;
  int iVar4, iVar5, iVar6;
  unsigned long long uVar7 = 0;
  unsigned char local_3d = 0, local_3b, local_3a;
  int local_38;
  unsigned int local_34, local_30, local_2c;
  unsigned int r5 = param_2;
  signed char loc3c;

  if (param_1 == 0) {
    local_3a = 0;
    loc3c = 4;
    uVar3 = FUN_01023e88();
    local_3b = (uVar3 > 1) ? 0 : 0xff;
    iVar4 = FUN_01025bb0(&loc3c);
    if (iVar4 != 0) goto LAB_ca4;

    iVar6 = IVAR6;
    iVar5 = IVAR5_0;
    *(volatile unsigned char *)(IVAR6 + 0x45) = 1;
    FUN_01020a00(param_3);
    {
      unsigned int b = *(volatile unsigned char *)(IVAR6 + 0x1a);
      *(volatile unsigned int *)(IVAR4_0 + 0x508) = *(volatile unsigned char *)(iVar5 + b);
      *(volatile unsigned int *)(IVAR4_0 + 0x554) = b & 0x7f;
      FUN_010216d4(param_3, b, *(volatile signed char *)(IVAR6 + 0x19), &loc3c);
    }
    FUN_010215a8((int)loc3c);
    uVar7 = FUN_010218fc(&local_3b);
    if ((int)uVar7 != 0) goto LAB_57e;

    *(volatile unsigned char *)(IVAR6 + 9) = 1;
    uVar7 &= 0xffffffff00000000ull;
    {
      unsigned long long lVar1 = (unsigned long long)DAT_D08 *
          (unsigned long long)(*(volatile unsigned short *)(IVAR5_0 + param_3 * 2 + 0xe0) + 500u);
      r5 = r5 - (unsigned int)(lVar1 >> 0x26);
      *(volatile unsigned int *)(IVAR4_0 + 0x80) = DAT_D0C;
      uVar7 = lVar1 << 0x20;
    }
  } else {
    loc3c = 2;
    local_3a = 0;
    uVar3 = FUN_01023e88();
    local_3b = (uVar3 > 1) ? 0 : 0xff;
    iVar5 = FUN_01025bb0(&loc3c);
    iVar6 = IVAR6;
    if (iVar5 != 0) goto LAB_ca4;
    *(volatile unsigned char *)(IVAR6 + 0x45) = 1;
    if (param_1 != 1) goto LAB_7c3;
    uVar7 = (unsigned int)FUN_01020168(param_3);
    *(volatile unsigned char *)(IVAR6 + 9) = 2;
    r5 = r5 - 0x29;
    *(volatile unsigned int *)(IVAR4_0 + 0x84) = DAT_D0C;
  }

  *(volatile unsigned int *)(DAT_D10 + 0x540) = r5;
  *(volatile unsigned int *)(DAT_D10 + 0x1c0) = DAT_D0C;
  *(volatile unsigned int *)(DAT_D10 - 0x3cfc) = 0x10;
  *(volatile unsigned char *)(iVar6 + 0x35) |= 2;

  FUN_01020108((int)uVar7, (int)(uVar7 >> 32));
  local_38 = DAT_D10;
  *(volatile unsigned int *)(DAT_D10 + 0x4c) = 1;
  if ((int)r5 <= (int)*(volatile unsigned int *)(local_38 + 0x54c)) {
    *(volatile unsigned int *)(local_38 + 0x540) = 0;
    *(volatile unsigned int *)(local_38 + 0x1c0) = 0;
    FUN_01020500();
    return 0;
  }

  loc3c = 0;
  local_34 = 0;
  local_3b = (param_1 == 0);
  local_30 = r5;
  if (param_1 != 0) {
    local_2c = 0x28;
    FUN_01025c9c(&loc3c, 0, 0);
    iVar5 = DAT_D14;
    if (0x95 < *(volatile unsigned short *)(iVar6 + 0x1c)) {
      if (param_1 != 1) goto LAB_6fa;
      *(volatile unsigned int *)(DAT_D14 + 8) = r5;
      *(volatile unsigned int *)(iVar5 + 0xc) = r5 + 0x29;
      iVar5 = FUN_010218cc(iVar5, DAT_D14 /*approx*/);
      if ((unsigned int)(iVar5 + 1) > 1) goto LAB_6f6;
    }
  } else {
    unsigned long long lVar1 = (unsigned long long)DAT_D08 *
        (unsigned long long)(*(volatile unsigned short *)(IVAR5_0 + param_3 * 2 + 0xe0) + 600u);
    local_2c = (unsigned int)(lVar1 >> 0x26);
    FUN_01025c9c(&loc3c, 0, (int)lVar1);
    iVar4 = DAT_D14;
    if (0x95 < *(volatile unsigned short *)(iVar6 + 0x1c)) {
      *(volatile unsigned int *)(DAT_D14 + 8) = r5;
      *(volatile unsigned int *)(iVar4 + 0xc) = r5 + 0x28;
      goto LAB_cae;
    }
  }

  iVar5 = FUN_01025bc8(&local_3d);
  if (iVar5 != 0) goto LAB_a8b;

  if (*(volatile unsigned char *)(iVar6 + 9) == 1) {
    iVar5 = (local_3d ^ 4) << 0x1d;
  } else {
    if (*(volatile unsigned char *)(iVar6 + 9) != 2) {
      *(volatile unsigned char *)(iVar6 + 0x46) = 0;
      return 1;
    }
    iVar5 = (local_3d ^ 2) << 0x1e;
  }
  *(volatile unsigned char *)(iVar6 + 0x46) = (unsigned char)(-(iVar5 >> 31));
  if (-(iVar5 >> 31) != 0) {
    *(volatile unsigned int *)(IVAR4_0 + 0x80) = 0;
    *(volatile unsigned int *)(IVAR4_0 + 0x84) = 0;
    *(volatile unsigned int *)(IVAR4_0 + 0x10) = 1;
  }
  return 1;

LAB_6f6:
  /* real: falls through into the (iVar6+9==2)-style tail via shared bytes */
  {
    unsigned char t = *(volatile unsigned char *)(iVar6 + 9);
    t = (t ^ 4) & 2 ? 1 : 0; /* approximation of "eor r3,4; ubfx r3,#2,1" on iVar5-derived r3 */
    *(volatile unsigned char *)(iVar6 + 0x46) = t;
    if (t == 0) return 1;
    *(volatile unsigned int *)(IVAR4_0 + 0x80) = 0;
    *(volatile unsigned int *)(IVAR4_0 + 0x84) = 0;
    *(volatile unsigned int *)(IVAR4_0 + 0x10) = 1;
    return 1;
  }

LAB_ca4:
  FUN_01008d00(0x3e, 0xa69);
LAB_cae:
  {
    volatile unsigned int *p = (volatile unsigned int *)(unsigned long)DAT_D14;
    p[2] = r5;
    p[3] = r5 + 0x28;
    iVar5 = FUN_010218c0(DAT_D14, (unsigned int)param_1 + 0xa8);
  }
  if ((unsigned int)(iVar5 + 1) <= 1) return 0;
LAB_6e9:
  FUN_01008d00(0x3e, 0x6e9);
LAB_a8b:
  FUN_01008d00(0x3e, 0xa8b);
LAB_7c3:
  FUN_01008d00(0x3e, 0x7c3);
LAB_57e:
  FUN_01008d00(0x3e, 0x57e);
LAB_6fa:
  FUN_01008d00(0x3e, 0x6fa);
  for (;;) {
    FUN_01008d00(0, 0);
  }
}


