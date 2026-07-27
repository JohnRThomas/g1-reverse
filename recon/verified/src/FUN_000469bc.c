/* Full reconstruction of FUN_000469bc @ 0x469bc, exact extent 430 bytes.
 * Call arities are derived by target because optional logging and cache
 * refresh calls do not have stable ordinals. */
#include <stdint.h>

extern uintptr_t FUN_000167a8(void);
extern void FUN_000431c0(void);
extern int FUN_00023ee0(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern uintptr_t FUN_0007d4b2(unsigned id);
extern void FUN_00043484(int, int, int, int, int, int);
extern unsigned FUN_00043e90(unsigned, uintptr_t, unsigned, int, int, int, int,
                            unsigned, unsigned, int, void *, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

static __attribute__((always_inline)) inline void draw_pair(uintptr_t text, int x, unsigned second_id)
{
    int y0 = FUN_0007d3ee();
    int x0 = FUN_0007d446();
    int y1 = FUN_0007d3ee();
    int x1 = FUN_0007d446();
    FUN_00043e90(0, text, 0, x + y0, x0 + 0x3c, y1 + 0x240,
                 x1 + 0x57, 1, 0, 0, 0, 0);

    x = (FUN_00023ee0() == 6)
        ? (second_id == 5 ? 0x78 : 0x22)
        : (second_id == 5 ? 0x9e : 0x6e);
    text = FUN_0007d4b2(second_id);
    y0 = FUN_0007d3ee(); x0 = FUN_0007d446();
    y1 = FUN_0007d3ee(); x1 = FUN_0007d446();
    FUN_00043e90(0, text, 0, x + y0, x0 + 0x71, y1 + 0x240,
                 x1 + 0x8c, 1, 0, 0, 0, 0);
}

unsigned FUN_000469bc(void)
{
    uintptr_t state = FUN_000167a8();
    uint8_t mode = *(volatile uint8_t *)(state + 0xf0);
    volatile uint8_t *cached_mode = (volatile uint8_t *)0x2001cf91u;

    if (mode >= 2) {
        if (*(volatile int *)0x2000230cu > 0) {
            if (*(volatile int *)0x20007554u == 0)
                DEBUG_PRINT(0x000d7173u, 0x000d71f9u);
            else
                FUN_00019c70(0x000d7173u, 0x000d71f9u);
        }
        return UINT32_MAX;
    }
    if (*cached_mode != mode) {
        FUN_000431c0();
        *cached_mode = *(volatile uint8_t *)(state + 0xf0);
    }

    int y = FUN_0007d3ee();
    int x = FUN_0007d446();
    FUN_00043484(0x7c, y + 0x52, x + 0x65, 0, 0, 0);

    if (*(volatile int8_t *)(state + 0xf0) == 1) {
        int first_x = (FUN_00023ee0() == 6) ? 0xb6 : 0xba;
        draw_pair(FUN_0007d4b2(4), first_x, 5);
    } else {
        int first_x = (FUN_00023ee0() == 6) ? 0xd0 : 0xc0;
        draw_pair(FUN_0007d4b2(2), first_x, 3);
    }
    return 0;
}
