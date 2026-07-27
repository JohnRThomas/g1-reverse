/* Full ABI-faithful reconstruction check_bonded_addr @ 0x183e4. */
#include <stdint.h>

extern void FUN_00018334(const void *connection, char description[36]);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

void check_bonded_addr(const void *connection)
{
    char description[36];

    FUN_00018334(connection, description);
    ++*(volatile uint32_t *)0x20007514u;
    *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006ab8u + 0x367u) = 0;

    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a46fu, 0x0009b108u, description);
        else
            FUN_00019c70(0x0009a46fu, 0x0009b108u, description);
    }
}
