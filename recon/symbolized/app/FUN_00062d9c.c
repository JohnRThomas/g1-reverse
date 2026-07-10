#include "g1_app_symbols.h"
/* named: FUN_00062d9c */
/* Reconstructed FUN_00062d9c @ 0x62d9c  (parity: 300/300 trials, PROVEN) */
extern void FUN_0004d944(int,int,void*,int);
extern void arch_irq_enable(int);
extern void FUN_0005010c(int,int,int);
extern int  uarte_nrfx_configure(int,int);
extern void nrfx_gppi_channels_enable(int);
extern int  FUN_0006540c(int);
extern int  pinctrl_apply_state /*compiler-clone .constprop.0*/(int);
extern void net_buf_simple_push_mem(int,int,int);
extern void k_timer_init(int,int,int,...);
#define VI(a) (*(volatile int*)(a))
#define VW(a) (*(volatile int*)(a))
#define VC(a) (*(volatile char*)(a))

int FUN_00062d9c(int param_1){
  int iVar1,iVar2,iVar6,uVar3;
  int puVar7 = VI(param_1+4);
  int piVar5 = VI(param_1+0x10);
  int puVar4 = VI(puVar7);
  int st[4];
  FUN_0005010c(8,1,0);
  arch_irq_enable(8);
  VW(puVar4+0x500) = 0;
  VW(piVar5) = param_1;
  iVar1 = pinctrl_apply_state /*compiler-clone .constprop.0*/(VI(puVar7+0xc));
  if (iVar1 < 0) return iVar1;
  iVar1 = uarte_nrfx_configure(param_1, piVar5+4);
  if (iVar1 != 0) return iVar1;
  if ((int)(VI(puVar7+4) << 0x1e) < 0) {
    iVar2 = FUN_0006540c(piVar5+0x1c);
    if (iVar2 != 0x0bad0000) {
      FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88290*/,0x1040,st,0);
      return -5;
    }
    net_buf_simple_push_mem(VC(piVar5+0x1c), puVar4+0x120, puVar4+0xc);
    nrfx_gppi_channels_enable(1 << (unsigned int)VC(piVar5+0x1c));
  }
  if (VI(piVar5+0xc) == 0) {
    VW(puVar4+0x500) = 8;
    if (VC((int)puVar7+8) == 0) {
      VW(puVar4+0x110) = 0;
      VW(puVar4+0x534) = VI(piVar5+0x18);
      VW(puVar4+0x538) = 1;
      VW(puVar4) = 1;
    }
  } else {
    iVar6 = piVar5;
    iVar2 = puVar4;
    VW(iVar2+0x304) = 4;
    uVar3 = 1;
    VW(VI(iVar6+0xc)+0xc0) = 1;
    VW(iVar2+0x304) = "(): EVENT_PUT_IN_GLASS_BOX_OPEN\n" /*=0xa0210*/;
    VW(iVar2+0x500) = 8;
    if (VI(iVar2+0x14c) != 0) {
      VW(iVar2+4) = 1;
      do { if (VI(iVar2+0x144) != 0) break; } while (VI(iVar2+0x124) == 0);
      VW(iVar2+0x14c) = 0;
      VW(iVar2+0x110) = 0;
      VW(iVar2+0x144) = 0;
      uVar3 = VI(iVar2+0x144);
    }
    k_timer_init(VI(iVar6+0xc)+0x80, ((uintptr_t)&rodata_84b87) /*=0x84b87*/, 0, uVar3);
    VW(VI(iVar6+0xc)+0xb4) = iVar6;
    k_timer_init(VI(iVar6+0xc)+0x20, ((uintptr_t)&tbl_84c57) /*=0x84c57*/, 0);
    VW(VI(iVar6+0xc)+0x54) = iVar6;
  }
  if ((int)(VI(puVar7+4) << 0x1e) >= 0) VW(puVar4+0x304) = 0x100;
  if ((VI(puVar7+4) << 0x1b) < 0) VW(puVar4+0x304) = 0x400000;
  VW(puVar4+0x544) = VI(piVar5+0x14);
  VW(puVar4+0x548) = 0;
  VW(puVar4+8) = 1;
  VW(puVar4+0xc) = 1;
  return iVar1;
}

