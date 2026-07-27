/* readable reconstruction; identity: FUN_00043d78 @ 0x00043d78
 * public-name: gui_4bit_bitmap_override
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   fb_blit_rows_or                          <= FUN_0007d586 @ 0x0007d586
 * address symbols (name @ address):
 *   rodata_aa8eb                             @ 0x000aa8eb
 *   rodata_aaa01                             @ 0x000aaa01   [INLINED -- G6 literal batch]
 *   rodata_aacaf                             @ 0x000aacaf   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed gui_4bit_bitmap_override @ 0x43d78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int get_device_info(void);
extern int atomic_get_3_0(void);
extern long resource_manger_get(unsigned long, unsigned long, long*, long*, unsigned long*, unsigned long);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, unsigned int, unsigned int, int, int);
extern void fb_blit_rows_or(int, int, int, int, int, int);

unsigned int gui_4bit_bitmap_override(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int uVar2;
    int local_1c = 0;
    int local_18 = 0;
    uint32_t local_14 = 0;

    if ((param_2 < 0x281) && (param_3 < 0x1e1)) {
        iVar1 = resource_manger_get(4, param_1, &local_1c, &local_18, &local_14, 0);
        if (-1 < iVar1) {
            fb_blit_rows_or(*(volatile uint32_t*)0x2000a034UL, local_14, local_1c, local_18, param_2, param_3);
            iVar1 = atomic_get_3_0();
            if ((iVar1 << 0x1e) < 0) {
                iVar1 = (int)(intptr_t)get_device_info();
                uVar2 = *(uint32_t*)(intptr_t)(iVar1 + 0xeb4);
                iVar1 = (int)(intptr_t)get_device_info();
                reflash_fb_data_to_lcd(uVar2, *(uint32_t*)(intptr_t)(iVar1 + 0xeb8), param_2, param_3, local_1c + param_2, local_18 + param_3);
            }
            return 0;
        }
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0) {
                log_message(0x000aa8ebUL, 0x000aacafUL);
            } else {
                debug_print(0x000aa8ebUL, 0x000aacafUL);
            }
        }
    } else if (0 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            log_message(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        } else {
            debug_print(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        }
    }
    return 0xffffffffUL;
}
