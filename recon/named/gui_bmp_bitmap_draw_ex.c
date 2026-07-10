/* named: gui_bmp_bitmap_draw_ex */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_bmp_bitmap_draw_ex @ 0x435d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(void);
extern int atomic_get_3_0(void);
extern int resource_manger_get(int,...);
extern int clean_fb_data(int,...);
extern int reflash_fb_data_to_lcd(int,...);
extern int fb_blit_rows_copy(int,...);
extern int memcpy(int,...);

unsigned int gui_bmp_bitmap_draw_ex(unsigned int param_1, int param_2, int param_3, int param_4, unsigned char param_5)
{
    int iVar3;
    unsigned int uVar5;
    int local_24, local_20;
    unsigned int local_1c;

    if (param_5 == 0) {
        if (*(volatile int*)0x2000230cUL < 2) return 0xffffffff;
        iVar3 = *(volatile int*)0x20007554UL;
        uVar5 = 0x000aa923;
    } else {
        iVar3 = resource_manger_get(4, param_1, &local_24, &local_20, &local_1c, 0);
        if (iVar3 >= 0) {
            int cnt = local_20 * (local_24 / 2);
            memcpy(param_4, local_1c, cnt);
            for (int i = 0; i < cnt; i++) {
                unsigned char *p = (unsigned char*)(intptr_t)(param_4) + i;
                if (*p != 0) *p = *p & param_5;
            }
            unsigned int m = atomic_get_3_0();
            if ((m & 2) != 0) {
                clean_fb_data(*(volatile uint32_t*)0x2000a034UL, 0, param_2, param_3, local_24 + 2 + param_2, local_20 + param_3);
            }
            fb_blit_rows_copy(*(volatile uint32_t*)0x2000a034UL, param_4, local_24 / 2, local_20, param_2, param_3);
            iVar3 = atomic_get_3_0();
            if ((iVar3 << 0x1e) < 0) {
                int r = get_device_info();
                unsigned int v = *(volatile uint32_t*)(intptr_t)(r + 0xeb4);
                r = get_device_info();
                reflash_fb_data_to_lcd(v, *(volatile uint32_t*)(intptr_t)(r + 0xeb8), param_2, param_3, local_24 + 2 + param_2, local_20 + param_3);
            }
            return 0;
        }
        if (*(volatile int*)0x2000230cUL < 2) return 0xffffffff;
        iVar3 = *(volatile int*)0x20007554UL;
        uVar5 = 0x000aa8eb;
    }
    if (iVar3 == 0) {
        DEBUG_PRINT(uVar5, 0x000aadb9);
    } else {
        debug_print();
    }
    return 0xffffffff;
}

