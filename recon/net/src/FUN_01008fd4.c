/* net-core FUN_01008fd4 @ 0x1008fd4  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int32_t FUN_01009210(void);
extern uint8_t FUN_010257e4(int32_t a);
extern void FUN_01008a58(uint32_t a, int32_t b);
extern void FUN_0101fc14(void);
extern void FUN_0101f818(uint8_t a, int32_t b);
extern void FUN_01008d7c(void);

int32_t FUN_01008fd4(int32_t param_1, uint32_t param_2)
{
    if (param_1 == 0 || param_2 == 0 || (param_2 & 7) != 0) {
        return (int32_t)0xffffffea;
    }

    int32_t r0 = FUN_01009210();
    if (r0 == 0) {
        return -1;
    }

    int32_t iVar1 = 0x21000a30;
    uint8_t v = FUN_010257e4(param_1);
    *(volatile uint8_t *)(iVar1 + 0x2e) = v;

    FUN_01008a58(param_2, 0);
    FUN_0101fc14();

    uint8_t a = *(volatile uint8_t *)(iVar1 + 0x2e);
    int32_t b = *(volatile int32_t *)(iVar1 + 0x24);
    FUN_0101f818(a, b);

    FUN_01008d7c();
    *(volatile uint8_t *)(iVar1 + 0x2c) = 1;
    return 0;
}

