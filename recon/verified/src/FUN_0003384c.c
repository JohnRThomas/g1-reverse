/* Full owned-CFG reconstruction FUN_0003384c @ 0x3384c. */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t format, ...);
extern uint32_t FUN_0000ef12(uint32_t command);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00019c70(uintptr_t format, ...);
extern uint32_t FUN_00033730(void *transport, const void *name,
                             const void *payload, uint32_t reserved);
extern int FUN_00087036(uint32_t command, const void *name, uint32_t value);

/* G7-B2: both sinks are void; 0x338d4 pops straight to pc with the incoming
 * NULL still in r0 and every other exit is a tail call, so this function
 * computes no return value. */
void FUN_0003384c(const uint8_t *request)
{
    const uint32_t *commands = (const uint32_t *)0x000883c8u;
    uint32_t command_copy[9];
    unsigned int i;

    if (request == 0)
        return;

    for (i = 0; i < 9; ++i)
        command_copy[i] = commands[i];

    for (i = 0; i < 9; ++i) {
        uint32_t value = FUN_0000ef12(command_copy[i]);
        if (FUN_00087036(command_copy[i], request + 0x10, value) == 0) {
            if (*(volatile int *)0x20007554u == 0) {
                DEBUG_PRINT(0x000a7bf5u, 0x000a833eu,
                            0x137, request + 0x10);
                return;
            }
            FUN_00019c70(0x000a7bf5u, 0x000a833eu,
                         0x137, request + 0x10);
            return;
        }
    }

    FUN_00033730((void *)(FUN_000167a8() + 0x77c),
                 request + 0x10, request + 0x30, 0);
}
