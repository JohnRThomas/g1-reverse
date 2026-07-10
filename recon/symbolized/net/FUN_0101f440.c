#include "g1_net_symbols.h"
/* net-core FUN_0101f440 @ 0x101f440  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned short ushort;
typedef void (*code_v)(void);

extern void FUN_01008d00(uint, uint);          /* noreturn */
extern void *FUN_01009bc4(void *, int);
extern int FUN_01009d18(unsigned char, uint);
extern void FUN_0100cff4(void *, int);
extern int FUN_01012150(uint);
extern int FUN_010122a8(void);
extern int FUN_0101233c(uint);
extern void FUN_01012694(uint, unsigned char);
extern int FUN_010126b0(uint);
extern int FUN_010126c0(uint);
extern int FUN_010126c8(uint);
extern int FUN_010126e8(uint);
extern int FUN_01012700(uint);
extern void FUN_01012714(uint, void *);
extern int FUN_01013b4c(uint, void *, uint);
extern int FUN_010141d4(uint);
extern int FUN_0101e8a0(void *, uint);
extern int FUN_01029b24(int);
extern int FUN_01029b38(int);

int FUN_0101f440(uint param_1, unsigned char *param_2)
{
  int iVar4, iVar5;
  uint uVar7;
  char cVar8;
  ushort *puVar6;

  iVar4 = FUN_010122a8();
  if (iVar4 == 0) {
    return 0x42;
  }
  iVar4 = FUN_010126c0(param_1);
  if ((iVar4 != 0) && (0x7f < (uint)(*(volatile ushort *)(param_2 + 1) - 1))) {
    return 0x12;
  }
  iVar4 = FUN_010126c8(param_1);
  if ((iVar4 == 0) ||
      ((iVar4 = FUN_010141d4(param_1), iVar4 != 0) ||
       (iVar4 = FUN_01012150(param_1), iVar4 != 0))) {
    return 0xc;
  }
  iVar4 = FUN_0101233c(param_1);
  if (iVar4 == 0) {
    return 0x12;
  }
  ushort uVar2 = *(volatile ushort *)(param_2 + 1);
  FUN_01012694(param_1, param_2[3]);
  iVar5 = FUN_01009d18(*param_2, 3);
  iVar4 = FUN_01009d18(*param_2, 5);

  volatile int *DAT_0101f5d8 = (volatile int *)((uintptr_t)&g_net_ble_conn_setup_ok_cb) /*=0x210004dc*/;
  volatile int *piVar3 = DAT_0101f5d8;

  int bVar1;
  if (iVar5 == 0) {
    if (iVar4 != 0) {
      cVar8 = *(volatile char *)(iVar4 + 0xbd);
      goto LAB_0101f4d4;
    }
    goto LAB_after_dispatch; /* iVar5==0 && iVar4==0: fall through, iVar4 stays 0 */
  } else {
    bVar1 = iVar4 != 0;
    cVar8 = '\0';
    iVar4 = iVar5;
    if (bVar1) {
      uVar7 = 0x1747;
      goto LAB_0101f4c8;
    }
    goto LAB_0101f4d4;
  }

LAB_0101f4d4:
  if (*piVar3 != 0) {
    iVar4 = iVar4 + 0x40;
    iVar5 = FUN_01029b38(iVar4);
    if ((iVar5 != 0) && (iVar5 = FUN_01029b24(iVar4), iVar5 == 0)) {
      if (cVar8 == '\0') {
        int (*fp)(int, int, int) = (int (*)(int, int, int)) *(volatile int *)((uintptr_t)&g_net_ble_conn_setup_ok_cb) /*=0x210004dc*/;
        int p2 = *(volatile int *)(((uintptr_t)&g_net_ble_conn_create_ctx) /*=0x21000eac*/ + 0xc);
        iVar4 = fp(iVar4, p2, 0);
        if (iVar4 != 0) {
          uVar7 = 0x1760;
          goto LAB_0101f4c8;
        }
      } else {
        int (*fp2)(int) = (int (*)(int)) *(volatile int *)((uintptr_t)&g_net_ble_conn_setup_err_cb) /*=0x210004d8*/;
        iVar4 = fp2(iVar4);
        if (iVar4 != 0) {
          uVar7 = 0x175b;
          goto LAB_0101f4c8;
        }
      }
    }
  }

LAB_after_dispatch:;
  iVar4 = FUN_010126b0(param_1);
  if (iVar4 == 0) {
    iVar4 = FUN_01013b4c(param_1, 0, (uint)uVar2 * 10000);
    if (iVar4 == 0) {
      return 0;
    }
    uVar7 = 0x1769;
  } else {
    iVar4 = FUN_010126c0(param_1);
    if (((iVar4 != 0) && (iVar4 = FUN_010126e8(param_1), iVar4 == 0)) &&
        (*(volatile char *)(((uintptr_t)&g_net_ble_conn_role_cfg) /*=0x21001208*/ + 4) == '\0')) {
      return 0x12;
    }
    unsigned short outparam;
    puVar6 = (ushort *)FUN_01009bc4(&outparam, 1);
    if (puVar6 == (ushort *)0) {
      return 0xd;
    }
    FUN_0100cff4(puVar6, 0);
    *puVar6 = outparam;
    FUN_01012714(param_1, puVar6);
    iVar4 = FUN_010126e8(param_1);
    if (iVar4 == 0) {
      uVar7 = (uint)FUN_01012700(param_1);
    } else {
      uVar7 = 1;
    }
    iVar4 = FUN_0101e8a0(puVar6, uVar7);
    if (iVar4 != 0) {
      return iVar4;
    }
    iVar4 = FUN_01013b4c(param_1, puVar6, (uint)uVar2 * 10000);
    if (iVar4 == 0) {
      void (*fp3)(void *, void *, int) =
          (void (*)(void *, void *, int)) *(volatile int *)(((uintptr_t)&g_net_ble_conn_role_cfg) /*=0x21001208*/ + 0x24);
      if (fp3 != 0) {
        fp3(puVar6, puVar6 + 0xb1, 0);
        return 0;
      }
      return 0;
    }
    uVar7 = 0x178c;
  }

LAB_0101f4c8:
  FUN_01008d00(0x39, uVar7);
  __builtin_unreachable();
}

