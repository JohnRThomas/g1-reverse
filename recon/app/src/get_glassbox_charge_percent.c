/* Reconstructed get_glassbox_charge_percent @ 0x327c4. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

uint8_t get_glassbox_charge_percent(void)
{
    uint8_t percent = *(volatile uint8_t *)0x20019ef4UL & 0x7f;

    if (2 < *(volatile int *)0x2000230cUL) {
        if (*(volatile uint32_t *)0x20007554UL == 0)
            DEBUG_PRINT(0x000a742dUL, 0x000a7735UL, percent);
        else
            FUN_00019c70(0x000a742dUL, 0x000a7735UL, percent);
    }
    /* The firmware deliberately reloads after the diagnostic call.  The
       status byte is volatile and may be updated while the logger runs. */
    return *(volatile uint8_t *)0x20019ef4UL & 0x7f;
}
