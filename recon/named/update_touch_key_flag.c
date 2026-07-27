/* readable reconstruction; identity: FUN_0002c324 @ 0x0002c324
 * public-name: update_touch_key_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   get_message_type_param                   <= FUN_0002c30c @ 0x0002c30c
 *   update_touch_key_flag                    <= FUN_0002c324 @ 0x0002c324
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   msg_count_dec                            <= FUN_00034274 @ 0x00034274
 *   push_message_3439c                       <= FUN_0003439c @ 0x0003439c
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   k_uptime_get_2                           <= FUN_0007ce40 @ 0x0007ce40
 * address symbols (name @ address):
 *   rodata_a26f7                             @ 0x000a26f7   [INLINED -- G6 literal batch]
 *   rodata_a2733                             @ 0x000a2733
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_pending_message_flag                   @ 0x20018d9e
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0002c324 @ 0x2c324  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void trigger_screen_state_change(unsigned a, int b, int c);
extern unsigned get_message_type_param(unsigned a, int b);
extern int clear_timeout_message(int a);
extern int msg_count_dec(void);
extern void push_message_3439c(void);
extern unsigned long get_message_pending_state(void);
extern void set_message_pending_state(int a);
extern void k_uptime_get_2(void);
void update_touch_key_flag(void){
    k_uptime_get_2();
    if (*(volatile int*)0x20007554 == 0){
        unsigned u = get_message_pending_state();
        log_message(((unsigned long)"[csh_debug_msg] set touch key flag get_msg_show_state() %d\n"), u);
    } else {
        unsigned u = get_message_pending_state();
        debug_print(((unsigned long)"[csh_debug_msg] set touch key flag get_msg_show_state() %d\n"), u);
    }
    int iVar3 = get_message_pending_state();
    if (iVar3 == 2 || get_message_pending_state() == 4){
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
    set_message_pending_state(0);
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
