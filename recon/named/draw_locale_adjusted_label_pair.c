/* readable reconstruction; identity: FUN_0003f2a8 @ 0x0003f2a8
 * public-name: draw_locale_adjusted_label_pair
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   draw_locale_adjusted_label_pair          <= FUN_0003f2a8 @ 0x0003f2a8
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_a9da3                             @ 0x000a9da3
 *   rodata_aa02b                             @ 0x000aa02b
 *   rodata_aa056                             @ 0x000aa056
 */
/* Reconstructed FUN_0003f2a8 @ 0x3f2a8  full 0xca-byte body */
#include <stdint.h>

extern int FUN_00023ee0(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern void gui_utf_draw(int, uint32_t, int, int, int, int, int,
                         int, int, int, int, int);

void draw_locale_adjusted_label_pair(void)
{
    int a, b, c, d;
    uint32_t format;

    if (FUN_00023ee0() == 6) {
        a = device_info_text_width_get();
        b = device_info_text_height_get_clamped();
        c = device_info_text_width_get();
        d = device_info_text_height_get_clamped();
        gui_utf_draw(0, UINT32_C(0x000aa056), 0,
                     a + 0xa8, b + 0x37, c + 0x23a, d + 0x52,
                     1, 0, 0, 0, 0);

        a = device_info_text_width_get();
        b = device_info_text_height_get_clamped();
        c = device_info_text_width_get();
        d = device_info_text_height_get_clamped();
        a += 0xb4;
        b += 0x52;
        c += 0x23a;
        d += 0x6d;
        format = UINT32_C(0x000a9da3);
    } else {
        a = device_info_text_width_get();
        b = device_info_text_height_get_clamped();
        c = device_info_text_width_get();
        d = device_info_text_height_get_clamped();
        a += 0x58;
        b += 0x37;
        c += 0x23a;
        d += 0x88;
        format = UINT32_C(0x000aa02b);
    }

    gui_utf_draw(0, format, 0, a, b, c, d, 1, 0, 0, 0, 0);
}
