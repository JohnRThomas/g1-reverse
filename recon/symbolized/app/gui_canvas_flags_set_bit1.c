#include "g1_app_symbols.h"
/* named: gui_canvas_flags_set_bit1 */
/* globals referenced:
//   0x2000a030  g_gui_canvas_flags           
*/
/* Reconstructed gui_canvas_flags_set_bit1 @ 0x432d0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int gui_canvas_flags_set_bit1(void)
{
    volatile uint32_t *p = (volatile uint32_t *)((uintptr_t)&g_gui_canvas_flags) /*=0x2000a030*/;
    *p = *p | 2;
    return 0;
}

