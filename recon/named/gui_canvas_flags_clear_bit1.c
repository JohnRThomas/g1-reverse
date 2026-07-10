/* named: gui_canvas_flags_clear_bit1 */
/* globals referenced:
//   0x2000a030  g_gui_canvas_flags           
*/
/* Reconstructed gui_canvas_flags_clear_bit1 @ 0x432ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int gui_canvas_flags_clear_bit1(void)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a030UL;
    *p = *p & 0xfffffffdU;
    return 0;
}

