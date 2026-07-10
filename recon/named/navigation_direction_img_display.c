/* named: navigation_direction_img_display */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed navigation_direction_img_display @ 0x3dff8  (parity: 300/300 trials, PROVEN) */

extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern void gui_bmp_bitmap_draw(int a, int b, int c, int d, int e, int f, int g);
extern void debug_print(void);
extern void DEBUG_PRINT(int a, int b);

void navigation_direction_img_display(int param_1, int param_2, int param_3)
{
    unsigned int uVar1;
    int iVar2;

    if ((unsigned int)(param_1 - 1) < 0x23) {
        uVar1 = device_info_text_width_get();
        iVar2 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(param_1 + 0x55, uVar1, iVar2 + 0x39, 0, 0, 0, param_3);
    } else if (1 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL != 0) {
            debug_print();
        } else {
            DEBUG_PRINT(0xa9e91, 0xaa466);
        }
    }
}

