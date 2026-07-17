/* Reconstructed dmic_record_start @ 0x3b78c */

#include <stdint.h>

extern uint8_t *FUN_000167a8(void);
extern void DEBUG_PRINT(uint32_t format, uint32_t argument);
extern void FUN_00019c70(uint32_t format, uint32_t argument, ...);
extern void FUN_0002f688(void);
extern void FUN_0002f764(void);
extern void FUN_00072880(void *event);

void dmic_record_start(void)
{
    uint8_t *device = FUN_000167a8();
    device[0x1059] = 4;

    if (*(volatile int32_t *)0x2000230cUL > 2) {
        if (*(volatile uint32_t *)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009d30bUL, 0x000a9843UL);
        } else {
            FUN_00019c70(0x0009d30bUL, 0x000a9843UL);
        }
    }

    FUN_0002f688();
    FUN_0002f764();
    (void)__atomic_exchange_n((uint32_t *)0x20007b78UL, 1,
                              __ATOMIC_SEQ_CST);

    device = FUN_000167a8();
    *(uint32_t *)(device + 0x104c) = 0x1d;
    device = FUN_000167a8();
    FUN_00072880(device + 0x68);
}
