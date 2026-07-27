#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025528 @ 0x00025528
 * public-name: handle_box_placement_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   box_placement_animation_step             <= FUN_0000fcf0 @ 0x0000fcf0
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   st25dv_mailbox_set_enabled               <= FUN_00024cc8 @ 0x00024cc8
 *   st25dv_write_control_and_ack             <= FUN_00024f40 @ 0x00024f40
 *   process_box_event                        <= FUN_000254d8 @ 0x000254d8
 *   handle_box_placement_event               <= FUN_00025528 @ 0x00025528
 *   periodic_check_run                       <= FUN_0003271c @ 0x0003271c
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   send_box_event_ipc                       <= FUN_0007c9f2 @ 0x0007c9f2
 *   ipc_send_byte_cmd2002                    <= FUN_0007c9fe @ 0x0007c9fe
 * address symbols (name @ address):
 *   rodata_50100                             @ 0x00050100
 *   g_box_event_state_buf                    @ 0x20002380
 *   g_box_mailbox_synced_flag                @ 0x200079fc
 *   g_box_field_timer_cfg_buf                @ 0x20007a2c
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00025528 @ 0x25528  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void box_placement_animation_step(unsigned char*);
extern int get_device_info(void);
extern int st25dv_mailbox_set_enabled(int);
extern int st25dv_write_control_and_ack(int);
extern int process_box_event(volatile void*, volatile void*, int, volatile void*, uint32_t, uint32_t);
extern void periodic_check_run(void);
extern int is_battery_critical(void);
extern int send_box_event_ipc(uint32_t, void*);
extern int ipc_send_byte_cmd2002(uint32_t, uint32_t);

uint32_t handle_box_placement_event(uint32_t param_1, uint32_t param_2) {
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_box_mailbox_synced_flag) /*=0x200079fc*/;
    volatile uint32_t *g_a44 = (volatile uint32_t*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/;
    volatile uint8_t *b = (volatile uint8_t*)((unsigned long)&g_box_event_state_buf) /*=0x20002380*/;
    uint8_t local7 = 0;
    uint32_t uVar6 = param_2;
    int iVar4;
    int8_t cVar5;
    periodic_check_run();
    if (*piVar1 == 0) {
        iVar4 = st25dv_mailbox_set_enabled(1);
        if (iVar4 < 0) return 0;
        iVar4 = send_box_event_ipc(*g_a44, (void*)&local7);
        if (iVar4 == 0) {
            local7 = local7 & 0xfe;
            ipc_send_byte_cmd2002(*g_a44, local7);
        }
        st25dv_write_control_and_ack(0xff);
        iVar4 = st25dv_mailbox_set_enabled(0);
        if (iVar4 < 0) return 0;
        *piVar1 = 1;
    }
    cVar5 = *(volatile int8_t*)(b+5);
    if (cVar5 == 1) {
        *(volatile uint32_t*)(b+0) = 1;
        *(volatile uint8_t*)(b+4) = 1;
        cVar5 = 0;
        *(volatile uint32_t*)(b+8) = 0x09010000UL;
        *(volatile uint32_t*)(b+0xc) = 0x0a031e09UL;
        *(volatile uint16_t*)(b+6) = 0;
        *(volatile uint32_t*)(b+0x10) = ((unsigned long)&rodata_50100) /*=0x50100*/;
        *(volatile uint32_t*)(b+0x14) = 0;
        *(volatile uint16_t*)(b+0x1c) = 0x200;
        *(volatile uint16_t*)(b+0x2e) = 0x101;
        *(volatile uint32_t*)(b+0x30) = 0xa0a;
        *(volatile uint32_t*)(b+0x34) = 0x0f000000UL;
        *(volatile uint16_t*)(b+0x18) = 0;
        *(volatile uint8_t*)(b+0x1e) = 0;
        *(volatile uint8_t*)(b+0x25) = 0;
        *(volatile uint8_t*)(b+0x27) = 0;
        *(volatile uint32_t*)(b+0x28) = 0;
        *(volatile uint8_t*)(b+0x2c) = 0;
        *(volatile uint8_t*)(b+0x38) = 0;
        *(volatile uint8_t*)(b+0x3a) = 0;
    }
    process_box_event((volatile void*)((unsigned long)&g_box_field_timer_cfg_buf) /*=0x20007a2c*/, b, cVar5, b, param_1, uVar6);
    iVar4 = is_battery_critical();
    if ((iVar4 != 0) || (iVar4 = get_device_info(), 0x1d < *(volatile uint8_t*)(iVar4 + 0xfc0))) {
        box_placement_animation_step(b);
    }
    return 0;
}
