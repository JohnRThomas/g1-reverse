/* Full reconstruction FUN_0002685c @ 0x2685c, exact extent 176 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=150 */
#include <stdint.h>
extern void DEBUG_PRINT(uintptr_t, ...);
extern void FUN_00019c70(uintptr_t, ...);
extern void FUN_00025528(void);
extern void FUN_0002ae84(void);
extern void FUN_0002aeb4(void);
extern void FUN_0002efc0(void);
extern void FUN_00032fd0(uint32_t);
extern uintptr_t FUN_0004c0a8(uint32_t);
extern void FUN_0007cb8e(uint32_t);
extern void fuel_gauge_update(uintptr_t, uint32_t);
extern void thunk_FUN_00074844(uint32_t, uint32_t);

void FUN_0002685c(uintptr_t context)
{
    volatile int *const log_level = (volatile int *)0x2000230cu;
    if (*log_level > 1) {
        if (*(volatile int *)0x20007554u)
            FUN_00019c70(0x0009fc8bu, 0x000a19e5u);
        else
            DEBUG_PRINT(0x0009fc8bu, 0x000a19e5u);
    }

    *(volatile uint16_t *)(context + 0xfc0) = 0;
    *(volatile uint16_t *)(context + 0xfc4) = 0x8000;
    uint32_t count = 0;
    for (;;) {
        if (*(volatile uint8_t *)(context + 1) == 1) {
            FUN_0002aeb4();
            FUN_00032fd0(0);
            FUN_0002efc0();
            if (count > 0x22) {
                if (*log_level > 0) {
                    if (*(volatile int *)0x20007554u)
                        FUN_00019c70(0x0009fc99u, 0x000a19e5u);
                    else
                        DEBUG_PRINT(0x0009fc99u, 0x000a19e5u);
                }
                for (;;) {
                    FUN_0007cb8e(500);
                    uintptr_t result = FUN_0004c0a8(1);
                    DEBUG_PRINT(result);
                }
            }
            ++count;
            thunk_FUN_00074844(0x28000, 0);
        } else {
            FUN_00025528();
            if (*(volatile uint8_t *)0x2000302cu == 0)
                FUN_0002aeb4();
            else if (*(volatile uint8_t *)0x20018d90u == 0)
                FUN_0002ae84();
            fuel_gauge_update(0x00087d70u, 0);
            thunk_FUN_00074844(0x8000, 0);
        }
    }
}
