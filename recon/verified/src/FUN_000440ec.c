/* Full reconstruction of FUN_000440ec @ 0x440ec, exact extent 450 bytes.
 * Call arities are derived by target so optional calls cannot shift ordinal
 * metadata onto unrelated callees. */
#include <stdint.h>

extern int FUN_0007d446(void);
extern int FUN_000431a8(void);
extern void FUN_000432ec(void);
extern void FUN_000432d0(void);
extern uintptr_t FUN_000167a8(void);
extern void FUN_000471cc(uintptr_t, int, int, int, int, int);
extern unsigned FUN_00043e90(unsigned, uintptr_t, unsigned, int, int, int, int,
                            unsigned, unsigned, int, void *, int);
extern void FUN_000473c8(uintptr_t, uintptr_t, int, int, int, int, uint32_t);
extern void FUN_0007d5f2(uintptr_t, int, int, int, int, int, int);

static uintptr_t display(void) { return *(volatile uintptr_t *)0x2000a034u; }

void FUN_000440ec(int unused, uintptr_t text, int unused2, int left, int top,
                  int right, int bottom, unsigned rows, unsigned mask)
{
    (void)unused; (void)unused2;
    uint32_t glyphs[9];
    if (FUN_0007d446() <= 0x20) {
        int shifted_top = top + 0x1b;
        int shifted_bottom = bottom + 0x1b;
        if ((FUN_000431a8() & 2) != 0)
            FUN_000471cc(display(), 0, left, shifted_top, right, shifted_bottom);
        FUN_000432ec();
        FUN_00043e90(0, text, 0, left, shifted_top, right, shifted_bottom,
                     rows, mask, 0, 0, 0);
        FUN_000432d0();
        for (unsigned i = 0; i < 9; ++i) glyphs[i] = ((const uint32_t *)0x000883ecu)[i];
        for (unsigned i = 0; i < 9; ++i) {
            uintptr_t s = FUN_000167a8(); uintptr_t d = FUN_000167a8();
            FUN_000473c8(*(uint32_t *)(s + 0xeb4), *(uint32_t *)(d + 0xeb8),
                         left, top, right, bottom, glyphs[i]);
        }
        FUN_0007d5f2(display(), left, top, left, shifted_top, 0x1b, right - left);
        if ((FUN_000431a8() & 2) != 0)
            FUN_000471cc(display(), 0, left, bottom, right, shifted_bottom);
        return;
    }

    if (FUN_0007d446() > 0x20) {
        FUN_0007d5f2(display(), left, top - 0x1b, left, top, 0x1b, right - left);
        if ((FUN_000431a8() & 2) != 0)
            FUN_000471cc(display(), 0, left, top, right, bottom);
        FUN_000432ec();
        FUN_00043e90(0, text, 0, left, top, right, bottom, rows, mask, 0, 0, 0);
        FUN_000432d0();
        for (unsigned i = 0; i < 9; ++i) glyphs[i] = ((const uint32_t *)0x00088410u)[i];
        for (unsigned i = 0; i < 9; ++i) {
            uintptr_t s = FUN_000167a8(); uintptr_t d = FUN_000167a8();
            FUN_000473c8(*(uint32_t *)(s + 0xeb4), *(uint32_t *)(d + 0xeb8),
                         left, top, right, bottom, glyphs[i]);
        }
        if ((FUN_000431a8() & 2) != 0)
            FUN_000471cc(display(), 0, left, top, right, top);
    }
}
