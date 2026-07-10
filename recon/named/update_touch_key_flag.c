/* named: update_touch_key_flag */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_touch_key_flag @ 0x2c324  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, unsigned b);
extern int get_device_info(void);
extern void debug_print(unsigned a, unsigned b);
extern void trigger_screen_state_change(unsigned a, int b, int c);
extern unsigned get_message_type_param(unsigned a, int b);
extern int clear_timeout_message(int a);
extern int msg_count_dec(void);
extern void push_message_3439c(void);
extern int FUN_00034410(void);
extern void FUN_0003443c(int a);
extern void k_uptime_get_2(void);
void update_touch_key_flag(void){
    k_uptime_get_2();
    if (*(volatile int*)0x20007554 == 0){
        unsigned u = FUN_00034410();
        DEBUG_PRINT(0x000a26f7, u);
    } else {
        unsigned u = FUN_00034410();
        debug_print(0x000a26f7, u);
    }
    int iVar3 = FUN_00034410();
    if (iVar3 == 2 || FUN_00034410() == 4){
        msg_count_dec();
        int t = get_device_info();
        unsigned uVar1 = get_message_type_param(*(volatile unsigned char*)(t + 0xfea), 0xf);
        t = get_device_info();
        *(volatile unsigned char*)(t + 0xdb) = (unsigned char)uVar1;
    }
    int t = get_device_info();
    unsigned char dd = *(volatile unsigned char*)(t + 0xdd);
    if (dd != 0){
        clear_timeout_message(1);
        push_message_3439c();
        *(volatile unsigned char*)0x20018d9e = 1;
        return;
    }
    FUN_0003443c(0);
    t = get_device_info();
    if (*(volatile unsigned char*)(t + 0xd5) == 1) return;
    t = get_device_info();
    if (*(volatile unsigned char*)(t + 0xee4) != 2) return;
    t = get_device_info();
    *(volatile unsigned char*)(t + 0xdb) = 0;
    t = get_device_info();
    trigger_screen_state_change(0x000a2733, t, 1);
    return;
}

