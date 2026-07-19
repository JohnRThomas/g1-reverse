/* readable reconstruction; identity: FUN_00025e2c @ 0x00025e2c
 * public-name: SendDashboardLockInfoToApp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   send_response_data_to_msgqueue           <= FUN_00047b1c @ 0x00047b1c
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   read_volatile_u32_a                      <= FUN_0007ca4e @ 0x0007ca4e
 * address symbols (name @ address):
 *   rodata_9f73d                             @ 0x0009f73d
 *   rodata_9fa9c                             @ 0x0009fa9c
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dashboard_lock_sent_flags              @ 0x2000756c
 *   g_dashboard_lock_ready_flags             @ 0x20007570
 *   g_dashboard_reset_pending_flags          @ 0x20007aa0
 */
/* Reconstructed SendDashboardLockInfoToApp @ 0x25e2c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int log_message(int,...);
extern int debug_print(void);
extern int send_response_data_to_msgqueue(void*,...);
extern int send_response_data_to_ble(void);
extern int read_volatile_u32_a(int,...);
void SendDashboardLockInfoToApp(unsigned p1, unsigned p2, unsigned p3){
  volatile unsigned buf[3];
  buf[0]=p1; buf[1]=p2; buf[2]=p3;
  int iVar1 = read_volatile_u32_a(0x20007570);
  if((iVar1<<0x1e)<0){
    iVar1 = read_volatile_u32_a(0x20007aa0);
    if(-1 < (iVar1<<0x1e)){
      iVar1 = read_volatile_u32_a(0x2000756c);
      unsigned bit = (unsigned)(iVar1>>1)&1u;
      if(-1 < (iVar1<<0x1e)){
        iVar1 = read_volatile_u32_a(0x20007570);
        if((iVar1<<0x1e)<0){
          buf[0]=bit;
          *(volatile uint16_t*)&buf[0] = 0x650;
          *(volatile uint16_t*)((char*)&buf[1]) = 0x101;
          if(*(volatile int*)0x2000230c > 2){
            if(*(volatile int*)0x20007554==0){
              log_message(0x9f73d,0x9fa9c,1);
            } else {
              debug_print();
            }
          }
          send_response_data_to_msgqueue((void*)buf,6);
          send_response_data_to_ble();
          *(volatile uint32_t*)0x2000756c |= 2u;
        }
      }
    }
  }
}
