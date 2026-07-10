#include "g1_app_symbols.h"
/* named: panel_on */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed panel_on @ 0x46dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int power_for_panel(void);
extern int get_ambient_light_sensor_ready_flag(void);
extern int debug_print(void);
extern int opt3007_chip_init(void);
extern int panel_init(void);
int panel_on(int param_1){
  *(volatile int*)(param_1+0x374) = param_1 - 0x5c;
  if(*(volatile int*)(param_1-0x48)==0){
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2){
      if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
        DEBUG_PRINT("%s(): panel_on enter!\n" /*=0xd723a*/, "panel_on" /*=0xd72bb*/);
      } else {
        debug_print();
      }
    }
    power_for_panel();
    void (*fp)(int) = *(void(* volatile*)(int))(param_1-0x5c);
    fp(*(volatile int*)(param_1+0x374));
    panel_init();
    *(volatile int*)(param_1+0x35c) = 1;
    int iVar1 = get_ambient_light_sensor_ready_flag();
    if(iVar1==0){
      opt3007_chip_init();
    }
  }
  return 0;
}

