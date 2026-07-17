#include "g1_net_symbols.h"
/* net-core FUN_0101746c @ 0x101746c  (parity 200 trials PROVEN) */
/* net-core FUN_0101746c @ 0x101746c  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char i8;
typedef unsigned char undefined1;

extern void FUN_01008d00(u32, u32);
extern i8 FUN_0100bc50(void);
extern i8 FUN_0100bc5c(u8, u32, u32);
extern int FUN_0100ca98(u32, void *, void *);
extern int FUN_0100cad4(void);
extern u32 FUN_0100cb10(void);
extern void FUN_0100cb28(void);
extern i8 FUN_01010890(u8, u32);
extern int FUN_010199cc(void);
extern int FUN_01029b24(int);

#define DAT_01017648 0x21000f90u
#define DAT_0101764c ((unsigned long)&g_net_conn_event_cb) /*=0x21000214*/
#define DAT_01017650 ((unsigned long)&g_sdc_ll_ctx_param) /*=0x21001019*/
#define DAT_01017654 ((unsigned long)&g_net_ctrlblk_chan_field) /*=0x21001008*/

void FUN_0101746c(int param_1, u32 param_2, int param_3)
{
  volatile u8 *b;
  volatile u16 *h;
  volatile u32 *w;
  int iVar2;
  int iVar5;
  i8 cVar3 = 0;
  i8 cVar7;
  u32 uVar6 = 0;
  u32 uVar4;

  iVar2 = DAT_01017648;
  if (param_2 == 7) {
    iVar5 = *(volatile int *)(param_1 + 4);
    if (iVar5 == 0 && param_3 == 0) {
      *(volatile u8 *)(DAT_01017648 + 0x82) = 1;
      if (*(volatile u8 *)(DAT_01017648 + 0xab) == 0) {
        return;
      }
      iVar5 = FUN_01029b24(*(volatile int *)(iVar2 + 0xac) + 0x50);
      if (iVar5 != 0) {
        return;
      }
      *(volatile u8 *)(iVar2 + 0x83) = 1;
      return;
    }
    cVar3 = 0;
    if (iVar5 != 0) {
      if ((*(volatile i8 *)(param_1 + 0x11) == 1) &&
          ((*(volatile u8 *)(iVar5 + 5) & 0xc0) == 0x40) &&
          (*(volatile i8 *)(DAT_01017648 + 0x7c) != 0)) {
        if ((param_3 == 0) && (*(volatile i8 *)(DAT_01017648 + 0xb9) == 1)) {
          iVar5 = FUN_0100cad4();
          *(volatile i8 *)(iVar2 + 0x7c) = (i8)iVar5;
          if (iVar5 == 0) goto LAB_010174a0;
        }
LAB_01017542:
        uVar6 = FUN_0100cb10();
        *(volatile u16 *)(iVar2 + 0x78) = (u16)((uVar6 & 0xff) | ((uVar6 & 0xff) << 8));
        *(volatile u8 *)(iVar2 + 0x80) = 1;
      } else {
LAB_010174a0:
        uVar6 = (u32)*(volatile u8 *)(iVar2 + 0x78);
      }
      if (uVar6 == 0xff) {
        cVar3 = FUN_01010890((u8)*(volatile i8 *)(param_1 + 0x11), (u32) * (volatile u32 *)(param_1 + 4));
        iVar5 = FUN_0100bc5c((u8)*(volatile i8 *)(param_1 + 0x11), (u32) * (volatile u32 *)(param_1 + 4), DAT_01017654);
        if (iVar5 == 0) {
          *(volatile u16 *)(iVar2 + 0x82) = 0;
          return;
        }
      } else {
        u8 local_21;
        u8 auStack_20[8];
        iVar5 = FUN_0100ca98(uVar6, &local_21, auStack_20);
        if (iVar5 == 0) {
          FUN_01008d00(0x32, 0xd21);
          __builtin_unreachable();
        }
        cVar3 = FUN_01010890(local_21, (u32)(unsigned long)auStack_20);
      }
      goto LAB_010174c4;
    }
    cVar7 = *(volatile i8 *)(DAT_01017648 + 0x4d);
    if (param_3 == 0) {
LAB_0101758e:
      if ((int)((u32)*(volatile u8 *)(param_1 + 1) << 0x1b) < 0) goto LAB_01017594;
    } else {
LAB_0101760c:
      if (*(volatile i8 *)(iVar2 + 0x82) == 0) goto LAB_0101759c;
      if (*(volatile int *)(param_1 + 4) != 0) goto LAB_010174cc;
    }
    iVar5 = FUN_010199cc();
    if (((iVar5 == 0) ||
         (cVar3 = *(volatile i8 *)(iVar2 + 0x82), *(volatile i8 *)(iVar2 + 0x82) == 0)) &&
        (cVar3 = cVar7, cVar7 == 0)) {
      cVar3 = FUN_0100bc50();
    }
  } else {
    if (*(volatile int *)(param_1 + 4) != 0) {
      if ((*(volatile i8 *)(param_1 + 0x11) == 1) &&
          ((*(volatile u8 *)(*(volatile int *)(param_1 + 4) + 5) & 0xc0) == 0x40) &&
          (*(volatile i8 *)(DAT_01017648 + 0x7c) != 0)) {
        goto LAB_01017542;
      }
      goto LAB_010174a0;
    }
    cVar3 = 0;
LAB_010174c4:
    cVar7 = *(volatile i8 *)(iVar2 + 0x4d);
    if (6 < param_2) {
      if (8 < param_2) {
LAB_0101759c:
        cVar3 = 0;
        goto LAB_010174d0;
      }
      if (param_3 != 0) goto LAB_0101760c;
      if (*(volatile int *)(param_1 + 4) == 0) goto LAB_0101758e;
    }
LAB_010174cc:
    if (cVar7 == 0) goto LAB_010174d0;
LAB_01017594:
    cVar3 = 1;
  }
LAB_010174d0:
  {
    volatile u32 *puVar8 = (volatile u32 *)DAT_0101764c;
    *(volatile i8 *)(iVar2 + 0x82) = cVar3;
    if (*puVar8 != 0) {
      uVar4 = ((u8(*)(int, int))(*puVar8))(param_1, param_3);
      *(volatile u8 *)(iVar2 + 0x83) = (u8)uVar4;
    }
  }
  {
    volatile u32 *puVar8b = *(volatile u32 **)(param_1 + 4);
    if (puVar8b != 0) {
      *(volatile u8 *)(iVar2 + 0x90) = *(volatile u8 *)(param_1 + 0x11);
      iVar5 = DAT_01017650;
      *(volatile u32 *)(iVar2 + 0x89) = puVar8b[0];
      *(volatile u16 *)(iVar5 + 4) = *(volatile u16 *)((u8 *)puVar8b + 4);
    }
  }
  if ((*(volatile int *)(param_1 + 8) != 0) && (param_2 == 7) &&
      (*(volatile i8 *)(iVar2 + 0x78) != -1) && (*(volatile short *)(iVar2 + 0x82) != 0)) {
    FUN_0100cb28();
    *(volatile u8 *)(iVar2 + 0x81) = 1;
  }
}
