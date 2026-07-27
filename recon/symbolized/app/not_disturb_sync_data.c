#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0003ce04 @ 0x0003ce04
 * public-name: not_disturb_sync_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_a98de                             @ 0x000a98de   [INLINED -- G6 literal batch]
 *   rodata_a9935                             @ 0x000a9935   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed not_disturb_sync_data @ 0x3ce04  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern int get_device_info(void);
extern uint32_t esb_send_command_and_wait_ack(uint32_t a, uint32_t b, void* c, uint32_t d, void* e);
extern void memcpy(int, int, int);
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
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar2 = 0xa9909UL;
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
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar2 = ((unsigned long)"%s(): not_disturb SYNC TO Slave failed...\n") /*=0xa98de*/;
    }
    if (iVar3 == 0) {
        log_message(uVar2, ((unsigned long)"not_disturb_sync_data") /*=0xa9935*/);
    } else {
        debug_print(uVar2, ((unsigned long)"not_disturb_sync_data") /*=0xa9935*/);
    }
    return 0xffffffff;
}
