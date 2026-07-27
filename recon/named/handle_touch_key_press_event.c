struct k_sem;
/* readable reconstruction; identity: FUN_0002c3dc @ 0x0002c3dc
 * public-name: handle_touch_key_press_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   update_touch_key_flag                    <= FUN_0002c324 @ 0x0002c324
 *   handle_touch_key_press_event             <= FUN_0002c3dc @ 0x0002c3dc
 *   get_message_entry                        <= FUN_00033c4c @ 0x00033c4c
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_a2748                             @ 0x000a2748   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_new_notification_pending_flag          @ 0x20018d8d
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0002c3dc @ 0x2c3dc  (parity: 300/300 trials, PROVEN) */

extern unsigned long long get_device_info(void);
extern unsigned long long esb_send_command_and_wait_ack(unsigned a, int b, int c, int d);
extern void update_touch_key_flag(void);
extern int get_message_entry(int a);
extern unsigned char msg_content_recalc_unread(void);
extern void k_sem_give(struct k_sem *);
extern void FUN_0007ce5c(unsigned a, int b);
unsigned handle_touch_key_press_event(unsigned inherited_r0, unsigned inherited_r1,
                      unsigned inherited_r2, unsigned inherited_r3){
    volatile unsigned char *puVar1 = (volatile unsigned char*)0x20018d9f;
    *puVar1 = 1;
    unsigned sVar7 = 1000;
    for(;;){
        int iVar4 = get_message_entry(10);
        if (*(volatile unsigned char*)(iVar4 + 0x10) == 0) break;
        if (*(volatile unsigned char*)(iVar4 + 0xc) == 0) break;
        sVar7 = (sVar7 - 1) & 0xffff;
        FUN_0007ce5c(0x21, 0);
        if (sVar7 == 0) break;
    }
    unsigned long long residual = get_device_info();
    unsigned long long elapsed = esb_send_command_and_wait_ack((unsigned)residual, 9, 0, 0);
    unsigned uVar6 = (unsigned)elapsed;
    unsigned uVar5;
    if (uVar6 < 2000){
        residual = get_device_info();
        int t = (int)residual;
        if (*(volatile unsigned char*)(t + 0x105a) == 2){
            volatile unsigned char *pcVar2 = (volatile unsigned char*)0x20018d8d;
            int iVar4 = 0; int go446 = 0;
            for(;;){
                if (*pcVar2 != 0){ go446 = 1; break; }
                iVar4 = iVar4 + 1;
                FUN_0007ce5c(0xccd, 0);
                if (iVar4 == 10) break;
            }
            if (!go446 && *pcVar2 == 0){ uVar5 = 0xffffffffu; goto out; }
            *pcVar2 = 0;
            int t2 = (int)get_device_info();
            unsigned char u3 = msg_content_recalc_unread();
            *(volatile unsigned char*)(t2 + 0xdd) = u3;
            update_touch_key_flag();
            int t3 = (int)get_device_info();
            k_sem_give(t3 + 0x38);
            uVar5 = 0;
            goto out;
        }
    }
    if (*(volatile int*)0x20007554 == 0)
        log_message(((unsigned long)"#########timeout,should retry !"));
    else
        debug_print(((unsigned long)"#########timeout,should retry !"));
    uVar5 = 0xffffffffu;
out:
    *puVar1 = 0;
    (void)inherited_r0;
    (void)inherited_r1;
    (void)inherited_r2;
    (void)inherited_r3;
    return uVar5;
}
