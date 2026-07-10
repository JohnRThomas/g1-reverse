#include "g1_app_symbols.h"
/* named: FUN_000440ec */
/* Reconstructed FUN_000440ec @ 0x440ec  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(int,...);
extern int atomic_get_3_0(int,...);
extern int gui_canvas_flags_set_bit1(int,...);
extern int gui_canvas_flags_clear_bit1(int,...);
extern int gui_utf_draw(int,...);
extern int clean_fb_data(int,...);
extern int reflash_fb_data_to_lcd_ex(int,...);
extern int device_info_text_height_get_clamped(int,...);
extern int fb_blit_rows_halved(int,...);

void FUN_000440ec(int param_1, int param_2, int param_3, int param_4, int param_5,
                  int param_6, int param_7, int param_8, int param_9)
{
    int iVar3, iVar4;
    volatile int sink;

    iVar3 = device_info_text_height_get_clamped(0);
    if (iVar3 < 0x21) {
        iVar3 = atomic_get_3_0(0);
        if ((iVar3 << 0x1e) < 0) clean_fb_data(0);
        gui_canvas_flags_clear_bit1(0);
        gui_utf_draw(0);
        gui_canvas_flags_set_bit1(0);
        iVar3 = 0;
        do {
            iVar4 = get_device_info(0);
            sink = *(volatile int *)(iVar4 + 0xeb4);
            iVar4 = get_device_info(0);
            sink = *(volatile int *)(iVar4 + 0xeb8);
            iVar3 = iVar3 + 1;
            reflash_fb_data_to_lcd_ex(0);
        } while (iVar3 != 9);
        fb_blit_rows_halved(0);
        iVar3 = atomic_get_3_0(0);
        if ((iVar3 << 0x1e) < 0) { clean_fb_data(0); return; }
    } else {
        iVar3 = device_info_text_height_get_clamped(0);
        if (0x20 < iVar3) {
            fb_blit_rows_halved(0);
            iVar3 = atomic_get_3_0(0);
            if ((iVar3 << 0x1e) < 0) clean_fb_data(0);
            gui_canvas_flags_clear_bit1(0);
            gui_utf_draw(0);
            gui_canvas_flags_set_bit1(0);
            iVar3 = 0;
            do {
                iVar4 = get_device_info(0);
                sink = *(volatile int *)(iVar4 + 0xeb4);
                iVar4 = get_device_info(0);
                sink = *(volatile int *)(iVar4 + 0xeb8);
                iVar3 = iVar3 + 1;
                reflash_fb_data_to_lcd_ex(0);
            } while (iVar3 != 9);
            iVar3 = atomic_get_3_0(0);
            if ((iVar3 << 0x1e) < 0) { clean_fb_data(0); return; }
        }
    }
    (void)sink;
}

