/* Full ABI-faithful reconstruction indicate_sc_cb @ 0x18a38. */
#include <stdint.h>

extern void FUN_000187e8(uint32_t connection, uint32_t enabled);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);
extern void DEBUG_PRINT(unsigned long, ...);

void indicate_sc_cb(const uint32_t *connection_ref, uint32_t security_level,
                    int32_t error)
{
    uint8_t attempt;

    (void)security_level;
    if (error != 0)
        return;

    attempt = (uint8_t)(*(volatile uint8_t *)0x2000ff70u + 1u);
    *(volatile uint8_t *)0x2000ff70u = attempt;
    if (attempt < 5u) {
        *(volatile uint32_t *)0x20006ab4u |= 4u;
        FUN_000187e8(*connection_ref, 1u);
        return;
    }

    *(volatile uint8_t *)0x2000ff70u = 0;
    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a8f9u, 0x0009b1dau);
        else
            FUN_00019c70(0x0009a8f9u, 0x0009b1dau);
    }

    FUN_00056a68(*connection_ref, 0x13u);
}
