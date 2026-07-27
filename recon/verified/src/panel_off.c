/* Reconstructed panel_off @ 0x46d2c. */
#include <stdint.h>

typedef void (*panel_callback_t)(void *panel);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0001655c(void);
extern void FUN_0002e8b4(void);
extern void FUN_00015fdc(void);

uint32_t panel_off(uint8_t *context)
{
    void *panel = context - 0x5c;

    *(void **)(context + 0x374) = panel;
    if (*(uint32_t *)(context - 0x48) != 0) {
        *(uint32_t *)(context + 0x35c) = 0;
        if (*(volatile int *)0x2000230cUL > 2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x000d721eu, 0x000d72d1u);
            } else {
                FUN_00019c70(0x000d721eu, 0x000d72d1u);
            }
        }
        if (FUN_0001655c() == 0)
            FUN_0002e8b4();
        ((panel_callback_t)*(uintptr_t *)(context - 0x58))(panel);
        FUN_00015fdc();
    }
    return 0;
}
