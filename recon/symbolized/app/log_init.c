#include "g1_app_symbols.h"
/* named: log_init */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
*/
/* Reconstructed log_init @ 0x4d678  (parity: 298/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d334(int);
extern int log_process(void);
extern int assert_post_action(int,int);
extern int printk(int,...);
void log_init(void){
  volatile uint8_t *pcVar1 = (volatile uint8_t*)((uintptr_t)&g_log_initialized_flag) /*=0x2001d44c*/;
  if(*pcVar1 == 0){
    FUN_0004d334(1);
    uint32_t piVar4 = ((uintptr_t)&tbl_880d8) /*=0x882a0*/;
    uint32_t piVar2 = ((uintptr_t)&__settings_handler_static_list_start) /*=0x882b0*/;
    while(1){
      if(piVar4 > piVar2){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "backend <= _log_backend_list_end" /*=0xf0cff*/, "WEST_TOPDIR/zephyr/subsys/logging/log_core.c" /*=0xf0cae*/, 0x188);
        printk("\tunexpected list end location\n" /*=0xf0d20*/);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/logging/log_core.c" /*=0xf0cae*/, 0x188);
      }
      if(piVar4 == piVar2) break;
      uint32_t e = *(volatile uint32_t*)(piVar4+4);
      if(*(volatile uint8_t*)(e+5) != 0){
        uint32_t f = *(volatile uint32_t*)(*(volatile uint32_t*)piVar4 + 8);
        ((void(*)(uint32_t))(uintptr_t)f)(piVar4);
      }
      piVar4 += 0x10;
    }
    int iVar3;
    do { iVar3 = log_process(); } while(iVar3 != 0);
    *pcVar1 = 1;
  }
}

