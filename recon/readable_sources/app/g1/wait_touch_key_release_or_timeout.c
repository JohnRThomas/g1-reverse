#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002c2b0 @ 0x0002c2b0
 * public-name: wait_touch_key_release_or_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sync_message_signal_to_slave             <= FUN_0002c224 @ 0x0002c224
 *   wait_touch_key_release_or_timeout        <= FUN_0002c2b0 @ 0x0002c2b0
 *   msg_count_dec                            <= FUN_00034274 @ 0x00034274
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 * address symbols (name @ address):
 *   rodata_a26cb                             @ 0x000a26cb   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002c2b0 @ 0x2c2b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_message_pending_state(void);
extern int is_msg_expiration(void);
extern int debug_print(void);
extern int sync_message_signal_to_slave(int);
extern int msg_count_dec(void);
extern int get_device_info(void);
extern int set_message_pending_state(int);
extern void log_message(int,...);
void wait_touch_key_release_or_timeout(void){
  volatile int *piVar1 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  while(get_message_pending_state()==5 && is_msg_expiration()==2){
    if(*piVar1==0){
      log_message(((unsigned long)"[csh_debug_msg] check showing msg timeout \n") /*=0xa26cb*/);
    } else {
      debug_print();
    }
    int iVar2 = sync_message_signal_to_slave(2);
    if(iVar2 <= 3000){
      msg_count_dec();
      int r = get_device_info();
      if(*(volatile uint8_t*)(r+0xdd)==0){
        set_message_pending_state(0);
        return;
      }
      set_message_pending_state(6);
    }
  }
}
