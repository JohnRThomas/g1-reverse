/* readable reconstruction; identity: FUN_0002c2b0 @ 0x0002c2b0
 * public-name: wait_touch_key_release_or_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sync_message_signal_to_slave             <= FUN_0002c224 @ 0x0002c224
 *   wait_touch_key_release_or_timeout        <= FUN_0002c2b0 @ 0x0002c2b0
 *   msg_count_dec                            <= FUN_00034274 @ 0x00034274
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 * address symbols (name @ address):
 *   rodata_a26cb                             @ 0x000a26cb
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002c2b0 @ 0x2c2b0  (parity: 300/300 trials, PROVEN) */
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
