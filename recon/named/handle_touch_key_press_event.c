/* named: handle_touch_key_press_event */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed handle_touch_key_press_event @ 0x2c3dc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a);
extern int get_device_info(void);
extern void debug_print(void);
extern unsigned esb_send_command_and_wait_ack(unsigned a, int b, int c);
extern void update_touch_key_flag(void);
extern int get_message_entry(int a);
extern unsigned char msg_content_recalc_unread(void);
extern void FUN_00072880(int a);
extern void thunk_FUN_00074844(unsigned a, int b);
unsigned handle_touch_key_press_event(void){
    volatile unsigned char *puVar1 = (volatile unsigned char*)0x20018d9f;
    *puVar1 = 1;
    unsigned sVar7 = 1000;
    for(;;){
        int iVar4 = get_message_entry(10);
        if (*(volatile unsigned char*)(iVar4 + 0x10) == 0) break;
        if (*(volatile unsigned char*)(iVar4 + 0xc) == 0) break;
        sVar7 = (sVar7 - 1) & 0xffff;
        thunk_FUN_00074844(0x21, 0);
        if (sVar7 == 0) break;
    }
    unsigned u5r = get_device_info();
    unsigned uVar6 = esb_send_command_and_wait_ack(u5r, 9, 0);
    unsigned uVar5;
    if (uVar6 < 2000){
        int t = get_device_info();
        if (*(volatile unsigned char*)(t + 0x105a) == 2){
            volatile unsigned char *pcVar2 = (volatile unsigned char*)0x20018d8d;
            int iVar4 = 0; int go446 = 0;
            for(;;){
                if (*pcVar2 != 0){ go446 = 1; break; }
                iVar4 = iVar4 + 1;
                thunk_FUN_00074844(0xccd, 0);
                if (iVar4 == 10) break;
            }
            if (!go446 && *pcVar2 == 0){ uVar5 = 0xffffffffu; goto out; }
            *pcVar2 = 0;
            int t2 = get_device_info();
            unsigned char u3 = msg_content_recalc_unread();
            *(volatile unsigned char*)(t2 + 0xdd) = u3;
            update_touch_key_flag();
            int t3 = get_device_info();
            FUN_00072880(t3 + 0x38);
            uVar5 = 0;
            goto out;
        }
    }
    if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x000a2748);
    else debug_print();
    uVar5 = 0xffffffffu;
out:
    *puVar1 = 0;
    return uVar5;
}

