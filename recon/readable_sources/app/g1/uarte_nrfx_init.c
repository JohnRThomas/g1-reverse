#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_nrfx_data__param_0312            [param_0312; library]
 * Raw function identity: 0x00062d9c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00062d9c @ 0x00062d9c
 * public-name: uarte_nrfx_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 *   arch_irq_priority_set                    <= FUN_0005010c @ 0x0005010c
 *   uarte_nrfx_configure                     <= FUN_00062ad8 @ 0x00062ad8
 *   uarte_nrfx_init                          <= FUN_00062d9c @ 0x00062d9c
 *   nrfx_gppi_channels_enable                <= FUN_00064f30 @ 0x00064f30
 *   flag32_channel_alloc_wrapper             <= FUN_0006540c @ 0x0006540c
 *   pinctrl_apply_state                      <= FUN_00084b14 @ 0x00084b14
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 * address symbols (name @ address):
 *   ADDR_flowctl_schedule_next_send_THUMB    @ 0x00084b87
 *   rodata_84c57                             @ 0x00084c57
 *   rodata_88290                             @ 0x00088290
 *   rodata_a0210                             @ 0x000a0210
 *   rodata_f6607                             @ 0x000f6607
 */
/* Reconstructed FUN_00062d9c @ 0x62d9c  (parity: 300/300 trials, PROVEN) */
extern void z_log_msg_runtime_create(int,int,void*,int);
extern void arch_irq_enable(int);
extern void arch_irq_priority_set(int,int,int);
extern int  uarte_nrfx_configure(int,int);
extern void nrfx_gppi_channels_enable(int);
extern int  flag32_channel_alloc_wrapper(int);
extern int  pinctrl_apply_state(int,int);
extern void nrfx_gppi_channel_endpoints_setup(int,int,int);
extern void k_timer_init(int,int,int,...);
#define VI(a) (*(volatile int*)(a))
#define VW(a) (*(volatile int*)(a))
#define VC(a) (*(volatile char*)(a))

int uarte_nrfx_init(int param_1){
  int iVar1,iVar2,iVar6,uVar3;
  int puVar7 = VI(param_1+4);
  int piVar5 = VI(param_1+0x10);
  int puVar4 = VI(puVar7);
  arch_irq_priority_set(8,1,0);
  arch_irq_enable(8);
  VW(puVar4+0x500) = 0;
  VW(piVar5) = param_1;
  iVar1 = pinctrl_apply_state(VI(puVar7+0xc), 0);
  if (iVar1 < 0) return iVar1;
  iVar1 = uarte_nrfx_configure(param_1, piVar5+4);
  if (iVar1 != 0) return iVar1;
  if (((unsigned)VI(puVar7+4) & 2U) != 0) {
    iVar2 = flag32_channel_alloc_wrapper(piVar5+0x1c);
    if (iVar2 != 0x0bad0000) {
      struct { unsigned severity; unsigned message; } diagnostic = {
        2, ((unsigned long)&rodata_f6607) /*=0xf6607*/
      };
      z_log_msg_runtime_create(((unsigned long)&rodata_88290) /*=0x88290*/,0x1040,&diagnostic,0);
      return -5;
    }
    nrfx_gppi_channel_endpoints_setup(
        VC(piVar5+0x1c), puVar4+0x120, puVar4+0xc);
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
    VW(iVar2+0x304) = ((unsigned long)&rodata_a0210) /*=0xa0210*/;
    VW(iVar2+0x500) = 8;
    if (VI(iVar2+0x14c) != 0) {
      VW(iVar2+4) = 1;
      do { if (VI(iVar2+0x144) != 0) break; } while (VI(iVar2+0x124) == 0);
      VW(iVar2+0x14c) = 0;
      VW(iVar2+0x110) = 0;
      VW(iVar2+0x144) = 0;
      uVar3 = VI(iVar2+0x144);
    }
    k_timer_init(VI(iVar6+0xc)+0x80, ADDR_flowctl_schedule_next_send_THUMB /*=0x84b87*/, 0, uVar3);
    VW(VI(iVar6+0xc)+0xb4) = iVar6;
    k_timer_init(VI(iVar6+0xc)+0x20, ((unsigned long)&rodata_84c57) /*=0x84c57*/, 0);
    VW(VI(iVar6+0xc)+0x54) = iVar6;
  }
  if (((unsigned)VI(puVar7+4) & 2U) == 0) VW(puVar4+0x304) = 0x100;
  if (((unsigned)VI(puVar7+4) & 0x10U) != 0) VW(puVar4+0x304) = 0x400000;
  VW(puVar4+0x544) = VI(piVar5+0x14);
  VW(puVar4+0x548) = 0;
  VW(puVar4+8) = 1;
  VW(puVar4+0xc) = 1;
  return iVar1;
}
