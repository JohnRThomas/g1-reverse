#include "g1_app_symbols.h"
/* named: not_disturb_sync_data */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed not_disturb_sync_data @ 0x3ce04  (parity: 300/300 trials, PROVEN) */


extern void DEBUG_PRINT(uint32_t a, uint32_t b);
extern uint32_t get_device_info(void);
extern void debug_print(void);
extern uint32_t esb_send_command_and_wait_ack(uint32_t a, uint32_t b, void* c, uint32_t d, void* e);
extern void memcpy(uint32_t dst, void* src, uint32_t len);
extern uint32_t sync_to_slave(uint32_t a, uint32_t b, void* c, uint32_t d);

uint32_t not_disturb_sync_data(uint8_t *param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t local_14;
    uint32_t uStack_10;
    uint8_t *pcVar1;
    uint32_t uVar2;
    uint32_t iVar3;
    uint32_t uVar4;
    uint32_t p2 = param_2;

    if (param_1 == (uint8_t*)0) {
        return 0xffffffff;
    }
    local_14 = param_2;
    uStack_10 = param_3;
    pcVar1 = (uint8_t*)get_device_info();
    if (*pcVar1 != 1) {
        local_14 = (local_14 & 0xFFFF0000UL) | 5UL;
        if (param_2 != 0) {
            p2 = 1;
            local_14 = (local_14 & 0xFFFF0000UL) | (((uint32_t)(*param_1)) << 8) | 5UL;
        }
        uVar2 = get_device_info();
        uVar4 = esb_send_command_and_wait_ack(uVar2, 0xd, &local_14, (p2 + 1) & 0xff, param_1);
        if (uVar4 < 2000) {
            return 0;
        }
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar2 = "%s(): not_disturb SYNC TO master failed...\n" /*=0xa9909*/;
    } else {
        local_14 = 5;
        if (p2 < 4) {
            if (p2 != 0) {
                memcpy((uint32_t)&local_14 + 1, param_1, p2);
            }
        } else {
            p2 = 3;
            memcpy((uint32_t)&local_14 + 1, param_1, p2);
        }
        uVar2 = get_device_info();
        iVar3 = sync_to_slave(uVar2, 6, &local_14, (p2+1) & 0xff);
        if (iVar3 < 5000) {
            return 0;
        }
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar2 = "%s(): not_disturb SYNC TO Slave failed...\n" /*=0xa98de*/;
    }
    if (iVar3 == 0) {
        DEBUG_PRINT(uVar2, "not_disturb_sync_data" /*=0xa9935*/);
    } else {
        debug_print();
    }
    return 0xffffffff;
}

