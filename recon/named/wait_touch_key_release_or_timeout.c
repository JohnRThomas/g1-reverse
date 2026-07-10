/* named: wait_touch_key_release_or_timeout */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed wait_touch_key_release_or_timeout @ 0x2c2b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00034410(void);
extern int is_msg_expiration(void);
extern int debug_print(void);
extern int sync_message_signal_to_slave(int);
extern int msg_count_dec(void);
extern int get_device_info(void);
extern int FUN_0003443c(int);
extern void DEBUG_PRINT(int,...);
void wait_touch_key_release_or_timeout(void){
  volatile int *piVar1 = (volatile int*)0x20007554UL;
  while(FUN_00034410()==5 && is_msg_expiration()==2){
    if(*piVar1==0){
      DEBUG_PRINT(0x000a26cbUL);
    } else {
      debug_print();
    }
    int iVar2 = sync_message_signal_to_slave(2);
    if(iVar2 <= 3000){
      msg_count_dec();
      int r = get_device_info();
      if(*(volatile uint8_t*)(r+0xdd)==0){
        FUN_0003443c(0);
        return;
      }
      FUN_0003443c(6);
    }
  }
}

