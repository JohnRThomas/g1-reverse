/* named: gui_set_active_canvas */
/* globals referenced:
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_set_active_canvas @ 0x431b4  (parity: 300/300 trials, PROVEN) */

unsigned int gui_set_active_canvas(unsigned int param_1)
{
    *(volatile unsigned int*)0x2000a034UL = param_1;
    return 0;
}

