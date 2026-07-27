/* Reconstructed not_disturb_sync_data @ 0x3ce04  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern void DEBUG_PRINT(unsigned long, ...);
extern uint32_t get_device_info(void);
extern void debug_print(unsigned long, ...);
extern uint32_t FUN_00027448(uint32_t a, uint32_t b, void* c, uint32_t d, void* e);
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
        uVar4 = FUN_00027448(uVar2, 0xd, &local_14, (p2 + 1) & 0xff, param_1);
        if (uVar4 < 2000) {
            return 0;
        }
        if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */;
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
        if (*(volatile int*)0x2000230cUL < 1) {
            return 0xffffffff;
        }
        iVar3 = *(volatile uint32_t*)0x20007554UL;
        uVar2 = 0xa98deUL;
    }
    if (iVar3 == 0) {
        DEBUG_PRINT(uVar2, 0xa9935UL);
    } else {
        debug_print(uVar2, 0xa9935UL);
    }
    return 0xffffffff;
}

