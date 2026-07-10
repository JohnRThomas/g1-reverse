#include "g1_app_symbols.h"
/* named: FUN_00019ac0 */
/* Reconstructed FUN_00019ac0 @ 0x19ac0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern void ancs_discover_start(void);
extern void ancs_cancel_timers(void);
extern void FUN_00072880(int);
int FUN_00019ac0(int param_1){
  int iVar1;
  ancs_cancel_timers();
  if(param_1==0){
    iVar1=get_device_info();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=1) return 0;
    iVar1=get_device_info();
    *(volatile uint8_t*)(iVar1+0x1070)=0;
  } else {
    if(*(volatile uint32_t*)((uintptr_t)&g_ancs_conn) /*=0x20007518*/==0) return 0;
    ancs_discover_start();
    iVar1=get_device_info();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=0) return 0;
    iVar1=get_device_info();
    *(volatile uint8_t*)(iVar1+0x1070)=1;
  }
  iVar1=get_device_info();
  *(volatile uint32_t*)(iVar1+0x104c)=0;
  iVar1=get_device_info();
  FUN_00072880(iVar1+0x80);
  return 0;
}

