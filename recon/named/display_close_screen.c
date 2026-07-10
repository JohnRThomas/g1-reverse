/* named: display_close_screen */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_close_screen @ 0x49858  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(void);
extern int set_dashboard_close_pending_flag(void);
extern int display_close(void*,int);
extern int mutex_unlock_syscall_handler(void);
extern int memset_bytes(int,int,int);
int display_close_screen(int param_1, uint32_t param_2){
  uint8_t loc[4];
  *(volatile uint16_t*)(loc) = 1;
  loc[1] = (uint8_t)param_1;
  if(param_1 != 0){
    if(*(volatile int*)0x2000230cUL > 0){
      if(*(volatile int*)0x20007554UL == 0){
        DEBUG_PRINT(0x000f006d, 0x000f0177, param_1, 0, param_1);
      } else {
        debug_print();
      }
    }
    if(param_1 == 4){
      set_dashboard_close_pending_flag();
    }
    display_close(loc, 2);
    mutex_unlock_syscall_handler();
    int iVar1 = get_device_info();
    memset_bytes(iVar1 + 0xef, 0, 0x5dc);
  }
  return 0;
}

