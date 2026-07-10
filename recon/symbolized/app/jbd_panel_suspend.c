#include "g1_app_symbols.h"
/* named: jbd_panel_suspend */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void projector_send_command(void);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    projector_send_command();
    return 0;
}

