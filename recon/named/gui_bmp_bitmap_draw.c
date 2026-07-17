/* readable reconstruction; identity: FUN_00043484 @ 0x00043484
 * public-name: gui_bmp_bitmap_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   load_icon_bitmap_expanded                <= FUN_00047a4c @ 0x00047a4c
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 * address symbols (name @ address):
 *   rodata_aa8eb                             @ 0x000aa8eb
 *   rodata_aadd0                             @ 0x000aadd0
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_00043484 @ 0x43484  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int, ...);
extern int get_device_info(void);
extern int debug_print(int, ...);
extern long long atomic_get_3_0(void);
extern int resource_manger_get(int,int,void*,void*,void*,int);
extern int clean_fb_data(int,int,int,int,int,int);
extern int reflash_fb_data_to_lcd(int,int,int,int,int,int);
extern int load_icon_bitmap_expanded(int,int);
extern int fb_blit_rows_copy(int,int,int,int,int,int);

int gui_bmp_bitmap_draw(unsigned int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    volatile uint32_t *puVar1 = (volatile uint32_t *)0x2000a034;
    int iVar2;
    unsigned int uVar3;
    int iVar4, iVar5;
    int uVar6;
    unsigned long long uVar7;
    int local_24;
    int local_20, local_1c;
    volatile int *g5c0 = (volatile int *)0x2000230c;
    volatile int *g5c4 = (volatile int *)0x20007554;

    if (((param_4 == 0) && (param_5 == 0)) && (param_6 == 0)) {
        local_20 = param_6;
        local_1c = param_6;
        if (param_1 - 0x16 < 0x67) {
            iVar2 = resource_manger_get(4, param_1, &local_20, &local_1c, &local_24, 0);
            if (iVar2 < 0) {
                if (1 < *g5c0) {
                    if (*g5c4 == 0) {
                        DEBUG_PRINT(0x000aa8eb, 0x000aadd0);
                    } else {
                        debug_print(0);
                    }
                }
                return 0xffffffff;
            }
            uVar3 = (unsigned int)atomic_get_3_0();
            if ((uVar3 & 2) != 0) {
                clean_fb_data((int)*puVar1, 0, param_2, param_3, local_20 + 2 + param_2, local_1c + param_3);
            }
            fb_blit_rows_copy((int)*puVar1, local_24, local_20 / 2, local_1c, param_2, param_3);
            iVar2 = (int)atomic_get_3_0();
            if (-1 < iVar2 << 0x1e) {
                return 0;
            }
            iVar2 = get_device_info();
            uVar6 = *(int *)(iVar2 + 0xeb4);
            iVar2 = get_device_info();
            iVar4 = local_1c + param_3;
            iVar5 = local_20 + 2 + param_2;
        } else {
            uVar7 = (unsigned long long)atomic_get_3_0();
            iVar2 = (int)(uVar7 >> 0x20);
            if ((uVar7 & 2) != 0) {
                clean_fb_data((int)*puVar1, 0, iVar2, param_3, iVar2 + 0x18, param_3 + 0x18);
            }
            local_24 = load_icon_bitmap_expanded(param_1 & 0xff, 0x120);
            fb_blit_rows_copy((int)*puVar1, local_24, 0xc, 0x18, param_2, param_3);
            iVar2 = (int)atomic_get_3_0();
            if (-1 < iVar2 << 0x1e) {
                return 0;
            }
            iVar2 = get_device_info();
            uVar6 = *(int *)(iVar2 + 0xeb4);
            iVar2 = get_device_info();
            iVar4 = param_3 + 0x18;
            iVar5 = param_2 + 0x18;
        }
        reflash_fb_data_to_lcd(uVar6, *(int *)(iVar2 + 0xeb8), param_2, param_3, iVar5, iVar4);
    }
    return 0;
}
