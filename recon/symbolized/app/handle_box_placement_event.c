#include "g1_app_symbols.h"
/* named: handle_box_placement_event */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed handle_box_placement_event @ 0x25528  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0000fcf0(volatile void*);
extern int get_device_info(void);
extern int st25dv_mailbox_set_enabled(int);
extern int st25dv_write_control_and_ack(int);
extern int process_box_event(volatile void*, volatile void*, int, volatile void*, uint32_t, uint32_t);
extern int FUN_0003271c(void);
extern int is_battery_critical(void);
extern int FUN_0007c9f2(uint32_t, void*);
extern int FUN_0007c9fe(uint32_t);

uint32_t handle_box_placement_event(uint32_t param_1, uint32_t param_2) {
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_box_mailbox_synced_flag) /*=0x200079fc*/;
    volatile uint32_t *g_a44 = (volatile uint32_t*)((uintptr_t)&g_st25dv_dev) /*=0x20007a44*/;
    volatile uint8_t *b = (volatile uint8_t*)((uintptr_t)&g_box_event_state_buf) /*=0x20002380*/;
    uint8_t local7 = 0;
    uint32_t uVar6 = param_2;
    int iVar4;
    int8_t cVar5;
    FUN_0003271c();
    if (*piVar1 == 0) {
        iVar4 = st25dv_mailbox_set_enabled(1);
        if (iVar4 < 0) return 0;
        iVar4 = FUN_0007c9f2(*g_a44, (void*)&local7);
        if (iVar4 == 0) {
            local7 = local7 & 0xfe;
            FUN_0007c9fe(*g_a44);
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
        *(volatile uint32_t*)(b+0x10) = ((uintptr_t)&tbl_50090) /*=0x50100*/;
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
    process_box_event((volatile void*)((uintptr_t)&g_box_field_timer_cfg_buf) /*=0x20007a2c*/, b, cVar5, b, param_1, uVar6);
    iVar4 = is_battery_critical();
    if ((iVar4 != 0) || (iVar4 = get_device_info(), 0x1d < *(volatile uint8_t*)(iVar4 + 0xfc0))) {
        FUN_0000fcf0(b);
    }
    return 0;
}

