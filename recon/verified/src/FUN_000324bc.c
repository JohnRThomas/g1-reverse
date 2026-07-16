/* Full reconstruction FUN_000324bc @ 0x000324bc (320-byte exact extent). CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>

extern void FUN_00086c78(void *, uint32_t, uint32_t);
extern uint64_t FUN_00086534(void *, uint32_t, uint32_t);
extern uint64_t FUN_00072908(void *, uint32_t, uint32_t, uint32_t);
extern int FUN_0008638c(void *);
extern void DEBUG_PRINT(uintptr_t, ...);
extern void FUN_00019c70(uintptr_t, ...);
extern uint8_t *FUN_000167a8(void);
extern int FUN_0007d120(void *, uint32_t, void *, uint32_t);
extern void FUN_0007d14a(uint32_t);

struct message { uint32_t tag; uint16_t code; uint8_t data[204]; };

void FUN_000324bc(void)
{
    struct message message;
    uint8_t *gate = (uint8_t *)0x20007bd4u;
    uint8_t *object = (uint8_t *)0x00087bf0u;
    uint32_t failures = 0;
    message.tag = 0;
    FUN_00086c78(&message.code, 0, 0xca);
    uint64_t inherited = FUN_00086534(gate, 0, 1);
    for (;;) {
        inherited = FUN_00072908(gate, (uint32_t)(inherited >> 32),
                                 0xffffffffu, 0xffffffffu);
        message.tag = 0x01f1a55au;
        if (!FUN_0008638c(object)) {
            if (*(volatile int *)0x2000230cu > 0) {
                if (!*(volatile int *)0x20007554u)
                    DEBUG_PRINT(0x000a40e6u, 0x000a759eu, *(uint32_t *)object);
                else FUN_00019c70(0x000a40e6u, 0x000a759eu, *(uint32_t *)object);
            }
            message.code = 0xca00u;
            uint8_t *state = FUN_000167a8();
            ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
        } else {
            uint8_t *state = FUN_000167a8();
            if (*(uint32_t *)(state + 0x1030)) {
                uint32_t page = 0;
                for (;;) {
                    uint32_t address = *(volatile uint32_t *)0x20002420u + page * 200u;
                    DEBUG_PRINT(0x000a73e2u, address, page);
                    if (FUN_0007d120(object, address, message.data, 200)) {
                        DEBUG_PRINT(0x0009e2dau);
                        message.code = (uint16_t)(0xca00u | (uint8_t)page);
                        state = FUN_000167a8();
                        ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
                        break;
                    }
                    message.code = (uint8_t)page;
                    uint32_t erased = 0;
                    for (uint32_t i = 0; i < 20; ++i) erased += message.data[i] == 0xffu;
                    if (erased == 20 || address > 0x410000u) {
                        message.code = 0x0100u;
                        state = FUN_000167a8();
                        ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
                        break;
                    }
                    state = FUN_000167a8();
                    int sent = ((int (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 0xce);
                    if (sent < 0) {
                        failures = (failures + 1u) & 0xffu;
                        if (failures > 9) {
                            if (*(volatile int *)0x2000230cu > 0) {
                                if (!*(volatile int *)0x20007554u)
                                    DEBUG_PRINT(0x0009b45eu, 0x000a759eu, failures);
                                else FUN_00019c70(0x0009b45eu, 0x000a759eu, failures);
                            }
                            failures = 0;
                            break;
                        }
                    } else page = (page + 1u) & 0xffffu;
                    FUN_0007d14a(20);
                }
            }
        }
        FUN_00086c78(&message, 0, 0xce);
    }
}
