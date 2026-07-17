#include "g1_net_symbols.h"
/* net-core FUN_0100a50c @ 0x100a50c */
#include <stdint.h>

extern uint32_t FUN_01027662(uint32_t, uint32_t, uint32_t);
extern void FUN_010275d2(void *, uint16_t, uint32_t, uint32_t, uint32_t);

uint32_t FUN_0100a50c(void *raw_object, uint32_t raw_kind, uint32_t raw_bank)
{
    uint32_t kind = (uint32_t)raw_kind & 0xffu;
    uint32_t bank = (uint32_t)raw_bank & 0xffu;
    uint16_t handle = (uint16_t)FUN_01027662(bank, 0x2eu, kind);

    if (raw_object != 0) {
        FUN_010275d2(raw_object, handle, bank, 0x2eu, kind);
        *(void *volatile *)((unsigned long)&g_net_retry_handle) /*=0x21000bc4*/ = raw_object;
        *(volatile uint8_t *)((unsigned long)&g_net_retry_param2) /*=0x21000bc8*/ = (uint8_t)kind;
        *(volatile uint8_t *)((unsigned long)&g_sdc_last_cfg_param3) /*=0x21000bc9*/ = (uint8_t)bank;
    }
    return handle;
}
