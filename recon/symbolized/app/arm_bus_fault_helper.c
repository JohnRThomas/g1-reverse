#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00050558 @ 0x00050558
 * public-name: arm_bus_fault_helper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_bus_fault_helper                     <= FUN_00050558 @ 0x00050558
 * address symbols (name @ address):
 *   rodata_88258                             @ 0x00088258
 *   rodata_f1c82                             @ 0x000f1c82
 *   rodata_f1ce2                             @ 0x000f1ce2
 *   rodata_f1df9                             @ 0x000f1df9
 *   rodata_f1e0f                             @ 0x000f1e0f
 *   rodata_f1e20                             @ 0x000f1e20
 *   rodata_f1e39                             @ 0x000f1e39
 *   rodata_f1e4e                             @ 0x000f1e4e
 *   rodata_f1e69                             @ 0x000f1e69
 */
/* Reconstructed FUN_00050558 @ 0x50558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00080780(uint32_t sink, uint32_t format, const void *record);

struct fault_message {
    uint32_t severity;
    uint32_t message;
};

struct fault_message_with_value {
    uint32_t severity;
    uint32_t message;
    uint32_t value;
};

int arm_bus_fault_helper(int param_1, unsigned char *param_2)
{
    int uVar2;
    struct fault_message message;

    message.severity = 2;
    message.message = ((unsigned long)&rodata_f1df9) /*=0xf1df9*/;
    FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x13 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1e0f) /*=0xf1e0f*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        uVar2 = 0x17;
    } else {
        uVar2 = 0x16;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x14 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1c82) /*=0xf1c82*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        uVar2 = 0x18;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x16 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1e20) /*=0xf1e20*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        if (*(volatile int *)(0xe000ed00 + 0x28) << 0x10 < 0) {
            struct fault_message_with_value detail;
            detail.severity = 3;
            detail.message = ((unsigned long)&rodata_f1e39) /*=0xf1e39*/;
            detail.value = *(volatile uint32_t *)(0xe000ed00 + 0x38);
            FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1840, &detail);
            if (param_1 != 0) {
                *(volatile unsigned int *)(0xe000ed00 + 0x28) = *(volatile unsigned int *)(0xe000ed00 + 0x28) & 0xffff7fff;
            }
        }
        uVar2 = 0x19;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x15 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1e4e) /*=0xf1e4e*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        uVar2 = 0x1a;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x17 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1e69) /*=0xf1e69*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        uVar2 = 0x1b;
    } else if (*(volatile int *)(0xe000ed00 + 0x28) << 0x12 < 0) {
        message.severity = 2;
        message.message = ((unsigned long)&rodata_f1ce2) /*=0xf1ce2*/;
        FUN_00080780(((unsigned long)&rodata_88258) /*=0x88258*/, 0x1040, &message);
        uVar2 = 0x1c;
    }
    *(volatile unsigned int *)(0xe000ed00 + 0x28) = *(volatile unsigned int *)(0xe000ed00 + 0x28) | 0xff00;
    *param_2 = 0;
    return uVar2;
}
