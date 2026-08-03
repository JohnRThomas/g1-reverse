#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000435d4 @ 0x000435d4
 * public-name: gui_bmp_bitmap_draw_ex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_aa8eb                             @ 0x000aa8eb
 *   rodata_aa923                             @ 0x000aa923
 *   rodata_aadb9                             @ 0x000aadb9   [INLINED -- refactor stage 01]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed gui_bmp_bitmap_draw_ex @ 0x435d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
#include "../../../headers/g1_dedupe.h"
#include "g1_gui.h"
extern int get_device_info(void);
extern int atomic_get_3_0(void);
extern long resource_manger_get(unsigned long, unsigned long, long*, long*, unsigned long*, unsigned long);
extern int clean_fb_data(int,...);
extern int reflash_fb_data_to_lcd(int,...);
extern void memcpy(int, int, int);

unsigned int gui_bmp_bitmap_draw_ex(unsigned int param_1, int param_2, int param_3, int param_4, unsigned char param_5)
{
    int iVar3;
    unsigned int uVar5;
    struct {
        int width;
        int height;
        unsigned int data_offset;
    } metadata;

    if (param_5 == 0) {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) return 0xffffffff;
        iVar3 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar5 = ((unsigned long)&rodata_aa923) /*=0xaa923*/;
    } else {
        iVar3 = resource_manger_get(4, param_1, &metadata.width,
                            &metadata.height, &metadata.data_offset, 0);
        if (iVar3 >= 0) {
            int cnt = metadata.height * (metadata.width / 2);
            memcpy(param_4, metadata.data_offset, cnt);
            for (int i = 0; i < cnt; i++) {
                unsigned char *p = (unsigned char*)(intptr_t)(param_4) + i;
                if (*p != 0) *p = *p & param_5;
            }
            unsigned int m = atomic_get_3_0();
            if ((m & 2) != 0) {
                clean_fb_data(*(volatile uint32_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, 0, param_2,
                             param_3, metadata.width + 2 + param_2,
                             metadata.height + param_3);
            }
            fb_blit_rows_copy(*(volatile uint32_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, param_4,
                         metadata.width / 2, metadata.height,
                         param_2, param_3);
            iVar3 = atomic_get_3_0();
            if ((iVar3 << 0x1e) < 0) {
                int r = get_device_info();
                unsigned int v = *(volatile uint32_t *)(intptr_t)(r + 0xeb4);
                r = get_device_info();
                reflash_fb_data_to_lcd(v, *(volatile uint32_t *)(intptr_t)(r + 0xeb8),
                             param_2, param_3,
                             metadata.width + 2 + param_2,
                             metadata.height + param_3);
            }
            return 0;
        }
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) return 0xffffffff;
        iVar3 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar5 = ((unsigned long)&rodata_aa8eb) /*=0xaa8eb*/;
    }
    G1_LOG_ROUTE(iVar3 == 0, uVar5, ((unsigned long)"gui_bmp_bitmap_draw_ex") /*=0xaadb9*/);
    return 0xffffffff;
}
