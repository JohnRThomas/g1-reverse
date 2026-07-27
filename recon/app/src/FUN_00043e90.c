/* Full reconstruction of FUN_00043e90 @ 0x43e90, exact extent 574 bytes.
 * CFG_VERIFY_CALL_ARITIES=2,2,4 */
#include <stdint.h>

typedef unsigned (*render_callback_t)(unsigned, uintptr_t, int, int, int);
extern uint16_t *FUN_000478d8(uintptr_t text, uint16_t *count);
extern int FUN_000431a8(void);
extern int FUN_0007d860(uint16_t character);
extern int FUN_0004588c(int font, uint16_t character, int *width,
                        int *height, uintptr_t *bitmap, int flags);
extern void FUN_00086c1e(void *dst, uintptr_t src, int bytes, int limit);
extern int FUN_00043e58(uint16_t current, uint16_t next);
extern void FUN_0007d53a(uintptr_t display, const void *bitmap, int half_width,
                         int height, int x, int y);
extern uintptr_t FUN_000167a8(void);
extern void FUN_000471cc(uintptr_t, int, int, int, int, int);
extern void FUN_00047260(uintptr_t, uintptr_t, int, int, int, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned FUN_00043e90(unsigned unused, uintptr_t text, int font,
                      int left, int top, int right, int bottom,
                      unsigned max_lines, unsigned mask_before,
                      int callback_mode, render_callback_t callback,
                      int suppress_default)
{
    (void)unused;
    uint16_t count = 0;
    uint16_t *characters = FUN_000478d8(text, &count);
    int glyph_width = 0, glyph_height = 0;
    uintptr_t glyph_bitmap = 0;
    uint8_t pixels[680];

    if (callback_mode != 0) {
        if (callback != 0) goto invoke_callback;
        return 0;
    }
    if (callback != 0) {
invoke_callback:
        if (*(volatile int *)0x2000230cu > 1) {
            if (*(volatile int *)0x20007554u == 0)
                DEBUG_PRINT(0x000aaa7fu, 0x000aadacu);
            else
                FUN_00019c70(0x000aaa7fu, 0x000aadacu);
        }
        return callback(0, text, font, left, top);
    }
    if (suppress_default != 0) return 0;

    if ((FUN_000431a8() & 2) != 0)
        FUN_000471cc(*(volatile uintptr_t *)0x2000a034u, 0,
                     left, top, right, bottom);

    unsigned line = 0, y_offset = 0, line_x = 0, x_advance = 0;
    for (unsigned index = 0; index < count; ++index, ++characters) {
        uint16_t ch = characters[0];
        int classification = FUN_0007d860(ch);
        if (classification == 0) {
            int rc = FUN_0004588c(font, ch, &glyph_width, &glyph_height,
                                  &glyph_bitmap, 0);
            if (rc < 0) {
                if (*(volatile int *)0x2000230cu > 1) {
                    if (*(volatile int *)0x20007554u == 0)
                        DEBUG_PRINT(0x000aaa58u, 0x000aadacu, ch);
                    else
                        FUN_00019c70(0x000aaa58u, 0x000aadacu, ch);
                }
                continue;
            }

            int half_width = (glyph_width + (glyph_width < 0)) / 2;
            int bytes = glyph_height * half_width;
            FUN_00086c1e(pixels, glyph_bitmap, bytes, 0x2a4);
            if (index < mask_before) {
                for (int i = 0; i < bytes; ++i)
                    pixels[i] &= *(volatile uint8_t *)0x200034f6u;
            }

            int spacing = FUN_00043e58(characters[0], characters[1]);
            unsigned candidate = x_advance + (unsigned)glyph_width + (unsigned)spacing;
            if ((unsigned)(right - left) < candidate) {
                y_offset += (unsigned)glyph_height;
                if (font == 0) ++y_offset;
                if (++line >= max_lines || (unsigned)(bottom - top) <= y_offset)
                    break;
                FUN_0007d53a(*(volatile uintptr_t *)0x2000a034u, pixels,
                             half_width, glyph_height, left, top + (int)y_offset);
                x_advance = (unsigned)glyph_width +
                            (unsigned)FUN_00043e58(characters[0], characters[1]);
                line_x = x_advance;
            } else {
                FUN_0007d53a(*(volatile uintptr_t *)0x2000a034u, pixels,
                             half_width, glyph_height, left + (int)line_x,
                             top + (int)y_offset);
                line_x += (unsigned)glyph_width +
                          (unsigned)FUN_00043e58(characters[0], characters[1]);
                x_advance = line_x;
            }
        } else if (classification == -1 && (ch == '\r' || ch == '\n')) {
            if (glyph_height == 0)
                y_offset += (font == 0) ? 0x1b : 0x1a;
            else {
                y_offset += (unsigned)glyph_height;
                if (font == 0) ++y_offset;
            }
            if (++line >= max_lines || (unsigned)(bottom - top) <= y_offset)
                break;
            line_x = x_advance = 0;
        }
    }

    if ((FUN_000431a8() & 2) != 0) {
        uintptr_t state = FUN_000167a8();
        uintptr_t display = *(uint32_t *)(state + 0xeb4);
        state = FUN_000167a8();
        FUN_00047260(display, *(uint32_t *)(state + 0xeb8),
                     left, top, right, bottom);
    }
    return 0;
}
