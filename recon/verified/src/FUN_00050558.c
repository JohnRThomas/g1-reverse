/* Reconstructed FUN_00050558 @ 0x50558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
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

int FUN_00050558(int param_1, unsigned char *param_2)
{
    volatile uint32_t *const scb_cfsr =
        (volatile uint32_t *)G1_SCB_CFSR; /* raw backmap: 0xe000ed00 + 0x28 */
    volatile uint32_t *const scb_bfar =
        (volatile uint32_t *)G1_SCB_BFAR; /* raw backmap: 0xe000ed00 + 0x38 */
    int uVar2;
    struct fault_message message;

    message.severity = 2;
    message.message = 0x000f1df9;
    FUN_00080780(0x00088258, 0x1040, &message);
    if ((int32_t)(*scb_cfsr << 0x13) < 0) {
        message.severity = 2;
        message.message = 0x000f1e0f;
        FUN_00080780(0x00088258, 0x1040, &message);
        uVar2 = 0x17;
    } else {
        uVar2 = 0x16;
    }
    if ((int32_t)(*scb_cfsr << 0x14) < 0) {
        message.severity = 2;
        message.message = 0x000f1c82;
        FUN_00080780(0x00088258, 0x1040, &message);
        uVar2 = 0x18;
    }
    if ((int32_t)(*scb_cfsr << 0x16) < 0) {
        uint32_t fault_address;

        message.severity = 2;
        message.message = 0x000f1e20;
        FUN_00080780(0x00088258, 0x1040, &message);

        /*
         * The firmware samples BFAR before re-reading CFSR.BFARVALID.  BFAR
         * is sampled even when BFARVALID is clear; this ordered MMIO read is
         * architecturally observable and must not be folded into the branch.
         */
        fault_address = *scb_bfar;
        if ((int32_t)(*scb_cfsr << 0x10) < 0) {
            struct fault_message_with_value detail;
            detail.severity = 3;
            detail.message = 0x000f1e39;
            detail.value = fault_address;
            FUN_00080780(0x00088258, 0x1840, &detail);
            if (param_1 != 0) {
                *scb_cfsr = *scb_cfsr & 0xffff7fff;
            }
        }
        uVar2 = 0x19;
    }
    if ((int32_t)(*scb_cfsr << 0x15) < 0) {
        message.severity = 2;
        message.message = 0x000f1e4e;
        FUN_00080780(0x00088258, 0x1040, &message);
        uVar2 = 0x1a;
    }
    if ((int32_t)(*scb_cfsr << 0x17) < 0) {
        message.severity = 2;
        message.message = 0x000f1e69;
        FUN_00080780(0x00088258, 0x1040, &message);
        uVar2 = 0x1b;
    } else if ((int32_t)(*scb_cfsr << 0x12) < 0) {
        message.severity = 2;
        message.message = 0x000f1ce2;
        FUN_00080780(0x00088258, 0x1040, &message);
        uVar2 = 0x1c;
    }
    *scb_cfsr = *scb_cfsr | 0xff00;
    *param_2 = 0;
    return uVar2;
}
