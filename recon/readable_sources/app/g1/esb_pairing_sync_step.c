#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000275fc @ 0x000275fc
 * public-name: esb_pairing_sync_step
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   esb_pairing_sync_step                    <= FUN_000275fc @ 0x000275fc
 *   stage_pending_message_for_resend         <= FUN_00033b88 @ 0x00033b88
 *   set_message_pool_entry_status            <= FUN_00033bf0 @ 0x00033bf0
 *   confirm_message                          <= FUN_00034524 @ 0x00034524
 * address symbols (name @ address):
 *   g_esb_notify_sync_retry_cnt              @ 0x20018d82
 *   g_esb_notify_sync_substate               @ 0x20018d98
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 */
/* Reconstructed FUN_000275fc @ 0x275fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int get_device_info(void);
extern void esb_send_command_and_wait_ack(int,int,int,int);
extern int stage_pending_message_for_resend(void);
extern void set_message_pool_entry_status(int,int);
extern void confirm_message(int);
extern int sync_to_slave(int,int,int,int);
void esb_pairing_sync_step(void){
    int iVar3=get_device_info();
    if(((uint)*(volatile uint8_t*)(iVar3+0xe4)<<0x1d)&0x80000000u) return;
    iVar3=get_device_info();
    uint8_t r5=*(volatile uint8_t*)(iVar3+0x6de)&4;
    if(r5!=0) return;
    int r4=stage_pending_message_for_resend();
    if(r4==0) return;
    char* pcVar4=(char*)get_device_info();
    if(*(volatile char*)pcVar4==1){
        int8_t d=*(volatile int8_t*)(r4+0xd);
        if(d==1){
            *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/=(uint8_t)d;
            int u=get_device_info();
            int r6=sync_to_slave(u,0xa,r4+8,4);
            if(r6>2999) return;
            set_message_pool_entry_status(*(volatile uint8_t*)(r4+0xc),2);
            return;
        }
        if(d!=3) return;
        int u=get_device_info();
        int r6=sync_to_slave(u,0xb,r4+8,4);
        if(r6>2999) return;
        set_message_pool_entry_status(*(volatile uint8_t*)(r4+0xc),4);
        confirm_message(*(volatile int*)(r4+8));
        *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/=r5;
        return;
    } else {
        uint8_t r5b=*(volatile uint8_t*)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/;
        if(r5b!=0) return;
        int8_t r6b=*(volatile int8_t*)(r4+0xd);
        if(r6b==0){
            *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/=1;
            int u=get_device_info();
            esb_send_command_and_wait_ack(u,0xb,r4,0xda);
            *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_retry_cnt) /*=0x20018d82*/=(uint8_t)r6b;
            return;
        }
        if(r6b!=2) return;
        uint8_t r3c=(uint8_t)(*(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_retry_cnt) /*=0x20018d82*/+1);
        *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_retry_cnt) /*=0x20018d82*/=r3c;
        if(r3c<=9){
            int u=get_device_info();
            esb_send_command_and_wait_ack(u,0xc,r4+0xda,0xda);
            return;
        }
        int c=*(volatile uint8_t*)(r4+0xc);
        *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_retry_cnt) /*=0x20018d82*/=r5b;
        set_message_pool_entry_status(c,r5b);
        *(volatile uint8_t*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/=r5b;
        return;
    }
}
