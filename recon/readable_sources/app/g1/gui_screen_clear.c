#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000431c0 @ 0x000431c0
 * public-name: gui_screen_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   projector_fill_and_sync                  <= FUN_0007d6f4 @ 0x0007d6f4
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_aa86c                             @ 0x000aa86c
 *   rodata_aa891                             @ 0x000aa891
 *   rodata_aae0f                             @ 0x000aae0f
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int message, unsigned int function);
extern void debug_print(void);
extern int get_projector_controller(void);
extern void projector_fill_and_sync(int clear_value);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_aa86c) /*=0xaa86c*/, ((unsigned long)&rodata_aae0f) /*=0xaae0f*/);
        } else {
            debug_print();
        }
    }
    int iVar2 = get_projector_controller();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_aa891) /*=0xaa891*/, ((unsigned long)&rodata_aae0f) /*=0xaae0f*/);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        projector_fill_and_sync(0);
        uVar3 = 0;
    }
    return uVar3;
}
