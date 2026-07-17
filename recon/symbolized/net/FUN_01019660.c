#include "g1_net_symbols.h"
/* Reconstructed net-core setup routine @ 0x01019660. */
#include <stdint.h>

extern void FUN_01008d00(uint32_t, uint32_t);
extern void *FUN_0100a5a0(void);
extern uint32_t FUN_0100a5b4(void);
extern void FUN_0100ef88(void *, const void *, uint32_t);
extern uint32_t FUN_01026d3e(void *);
extern uint32_t FUN_01026f32(void *, uint16_t, uint32_t);
extern uint8_t *FUN_010270d2(void *);
extern void FUN_0102714a(void *, void *, void *);

void FUN_01019660(void)
{
    uint16_t auxiliary;
    void *handle;
    void *controller = FUN_0100a5a0();
    uint8_t *entry;
    uint8_t initial_flag;

    FUN_0102714a(controller, &handle, &auxiliary);
    entry = FUN_010270d2(handle);
    initial_flag = entry[0x1f];

    if (initial_flag == 0) {
        if (FUN_01026d3e(controller) == 1)
            return;
        if (FUN_01026f32(controller, (uint16_t)FUN_0100a5b4(), 1) == 0) {
            FUN_01008d00(0x33, 0x2ba);
            return;
        }
        if (FUN_01026d3e(controller) == 0) {
            FUN_01008d00(0x33, 0x2be);
            FUN_01008d00(0x33, 0x2ba);
            return;
        }
        entry[8] = initial_flag;
        FUN_0100ef88(entry, (const void *)0x01019a9d, 6);
    } else if (FUN_01026d3e(controller) == 0) {
        FUN_01008d00(0x33, 0x2be);
        FUN_01008d00(0x33, 0x2ba);
        return;
    }

    *(volatile uint16_t *)((unsigned long)&g_2100109c) /*=0x2100109c*/ = 0;
}
