/* Reconstructed panel_resume @ 0x46f20  (CFG-directed candidate) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00047638(uint8_t *context);
extern uint32_t FUN_00047724(void);
extern void FUN_00046dd8(uint8_t *context);
extern void FUN_00046e3c(uint32_t level);

int32_t panel_resume(uint8_t *context)
{
    int32_t state;

    *(void * volatile *)(context + 0x374) = (void *)(context - 0x5c);
    if ((*(volatile uint16_t *)(context + 0x4f0) & 0x100u) == 0)
        return -1;
    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000d7272u, 0x000d72c4u);
        } else {
            FUN_00019c70(0x000d7272u, 0x000d72c4u);
        }
    }
    state = *(volatile int32_t *)(context + 0x35c);
    if (state != 0)
        return -1;
    if (*(volatile uint32_t *)(*(void * volatile *)(context + 0x374) + 0x14) == 0) {
        FUN_00046dd8(context);
        FUN_00046e3c(*(volatile uint8_t *)(context + 0x369));
        return state;
    }
    FUN_00047638(context);
    if (FUN_00047724() != 0x4010u) {
        if (*(volatile int *)0x2000230cUL > 0) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x000d728du, 0x000d72c4u);
            } else {
                FUN_00019c70(0x000d728du, 0x000d72c4u);
            }
        }
    }
    *(volatile int32_t *)(context + 0x35c) = 1;
    return state;
}
