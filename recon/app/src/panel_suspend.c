/* Reconstructed panel_suspend @ 0x46d8c  (CFG-directed candidate) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t format, ...);
extern void FUN_00019c70(uint32_t format, ...);
extern void FUN_000475f0(void);
extern uint32_t FUN_00046d2c(uint8_t *context);

uint32_t panel_suspend(uint8_t *context)
{
    *(void * volatile *)(context + 0x374) = (void *)(context - 0x5c);
    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000d721eu, 0x000d72dbu);
        } else {
            FUN_00019c70(0x000d721eu, 0x000d72dbu);
        }
    }
    FUN_000475f0();
    FUN_00046d2c(context);
    *(volatile uint32_t *)(context + 0x35c) = 0;
    return 0;
}
