#include "g1_net_symbols.h"
/* net-core FUN_0102ee28 @ 0x102ee28  (parity 300 trials PROVEN) */
extern void FUN_0103a3d6(unsigned int, unsigned int, void*);

#define DAT_0102ef34 ((uintptr_t)&rodata_103d8fb) /*=0x103d8fb*/
#define DAT_0102ef38 ((uintptr_t)&rodata_103c0c4) /*=0x103c0c4*/
#define DAT_0102ef3c 0xe000ed00u
#define PTR_s_I_Channel_0102ef40 "I Channel" /*=0x103d911*/
#define PTR_s_013000_0102ef44 "013000" /*=0x103d922*/
#define PTR_s_rte_0102ef48 "rte" /*=0x103d935*/
#define PTR_s_ivers_timer_nrf_rtc_timer_c_0102ef4c "ivers/timer/nrf_rtc_timer.c" /*=0x103d94e*/
#define PTR_s_imer_c_0102ef50 "imer.c" /*=0x103d963*/
#define PTR_s_al_error_0102ef54 "al_error" /*=0x103d97e*/

unsigned int FUN_0102ee28(int param_1, unsigned char *param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int local_40;
  unsigned int local_3c;
  unsigned int uStack_38;
  unsigned int local_20;
  unsigned int local_1c;

  local_1c = DAT_0102ef34;
  local_20 = 2;
  FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
  if (*(volatile int *)(DAT_0102ef3c + 0x28) << 0x13 < 0) {
    local_20 = 2;
    local_1c = PTR_s_I_Channel_0102ef40;
    FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
    uVar2 = 0x17;
  } else {
    uVar2 = 0x16;
  }
  if (*(volatile int *)(DAT_0102ef3c + 0x28) << 0x14 < 0) {
    local_1c = PTR_s_013000_0102ef44;
    local_20 = 2;
    FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
    uVar2 = 0x18;
  }
  iVar1 = DAT_0102ef3c;
  if (*(volatile int *)(DAT_0102ef3c + 0x28) << 0x16 < 0) {
    local_1c = PTR_s_rte_0102ef48;
    local_20 = 2;
    FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
    if (*(volatile int *)(iVar1 + 0x28) << 0x10 < 0) {
      local_3c = PTR_s_ivers_timer_nrf_rtc_timer_c_0102ef4c;
      local_40 = 3;
      uStack_38 = *(volatile unsigned int *)(iVar1 + 0x38);
      FUN_0103a3d6(DAT_0102ef38, 0x1840, &local_40);
      if (param_1 != 0) {
        *(volatile unsigned int *)(iVar1 + 0x28) =
            *(volatile unsigned int *)(iVar1 + 0x28) & 0xffff7fff;
      }
    }
    uVar2 = 0x19;
  }
  if (*(volatile int *)(DAT_0102ef3c + 0x28) << 0x15 < 0) {
    local_1c = PTR_s_imer_c_0102ef50;
    local_20 = 2;
    FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
    uVar2 = 0x1a;
  }
  if (*(volatile int *)(DAT_0102ef3c + 0x28) << 0x17 < 0) {
    local_1c = PTR_s_al_error_0102ef54;
    local_20 = 2;
    FUN_0103a3d6(DAT_0102ef38, 0x1040, &local_20);
    uVar2 = 0x1b;
  }
  *(volatile unsigned int *)(DAT_0102ef3c + 0x28) =
      *(volatile unsigned int *)(DAT_0102ef3c + 0x28) | 0xff00;
  *param_2 = 0;
  return uVar2;
}

