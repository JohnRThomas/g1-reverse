/* Full reconstruction of gui_string_draw @ 0x455cc (280 bytes). */
#include <stdint.h>

extern int FUN_0000ef12(const uint8_t *s);
extern uint32_t FUN_000431a8(void);
extern uintptr_t FUN_000167a8(void);
extern void FUN_000471cc(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void FUN_00047260(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern int FUN_0004588c(uint32_t, uint32_t, int32_t *, int32_t *, uint32_t *, uint32_t);
extern void FUN_0007d53a(uint32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t);
extern int FUN_00043e58(uint32_t, uint32_t);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

int gui_string_draw(uint32_t font, const uint8_t *text, int32_t x, uint32_t y,
                    uint32_t arg5, uint32_t arg6, int32_t *width_out)
{
    int32_t glyph_width = 0, glyph_height = 0;
    uint32_t bitmap = 0;
    int length = FUN_0000ef12(text);
    int32_t cursor = x;

    if (FUN_000431a8() & 2u)
        FUN_000471cc(*(volatile uint32_t *)0x2000a034u, 0, x, y, arg5, arg6);

    for (const uint8_t *p = text; p != text + length; ++p) {
        if (*p < 0x20u) {
            if (*(volatile int32_t *)0x2000230cu > 0) {
                if (*(volatile uint32_t *)0x20007554u == 0)
                    DEBUG_PRINT(0x000aac83u, 0x000aac9fu);
                else
                    FUN_00019c70(0x000aac83u, 0x000aac9fu);
            }
            continue;
        }

        if (FUN_0004588c(font, *p, &glyph_width, &glyph_height, &bitmap, 0) != 0 || bitmap == 0) {
            if (*(volatile int32_t *)0x2000230cu > 1) {
                if (*(volatile uint32_t *)0x20007554u == 0)
                    DEBUG_PRINT(0x000aac62u, 0x000aac9fu);
                else
                    FUN_00019c70(0x000aac62u, 0x000aac9fu);
            }
            continue;
        }

        FUN_0007d53a(*(volatile uint32_t *)0x2000a034u, bitmap,
                     (glyph_width + (glyph_width < 0)) / 2, glyph_height,
                     cursor, y);
        if ((uint32_t)(*p - 0x20u) <= 0x5eu && font == 3)
            cursor += glyph_width + 3;
        else
            cursor += glyph_width + FUN_00043e58(*p, p[1]);
    }

    if (FUN_000431a8() & 2u) {
        uintptr_t state = FUN_000167a8();
        uint32_t left = *(volatile uint32_t *)(state + 0xeb4);
        state = FUN_000167a8();
        FUN_00047260(left, *(volatile uint32_t *)(state + 0xeb8), x, y, arg5, arg6);
    }
    if (width_out)
        *width_out = cursor - x;
    return 0;
}
