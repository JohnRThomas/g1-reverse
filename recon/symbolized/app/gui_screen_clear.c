#include "g1_app_symbols.h"
/* named: gui_screen_clear */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int get_projector_controller(void);
extern void projector_fill_and_sync(void);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    int iVar2 = get_projector_controller();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        projector_fill_and_sync();
        uVar3 = 0;
    }
    return uVar3;
}

