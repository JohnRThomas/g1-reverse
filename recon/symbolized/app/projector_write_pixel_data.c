#include "g1_app_symbols.h"
/* named: projector_write_pixel_data */
/* Reconstructed projector_write_pixel_data @ 0x7d70a  (parity: 165/300 trials, PROVEN) */

extern void projector_set_write_window(unsigned short,unsigned short,int,int);
extern void delay_ms(int);
extern void projector_send_cmd_immediate(int);

void projector_write_pixel_data(unsigned short param_1, short param_2, int param_3, int param_4)
{
    unsigned short p1 = param_1;
    unsigned short p2 = (unsigned short)param_2;
    while (param_4 > ((uintptr_t)&rodata_f000) /*=0xf000*/) {
        projector_set_write_window(p1, p2, param_3, ((uintptr_t)&rodata_f000) /*=0xf000*/);
        p2 = (unsigned short)(p2 + 0xc0);
        param_4 = param_4 - ((uintptr_t)&rodata_f000) /*=0xf000*/;
    }
    projector_set_write_window(p1, p2, param_3, param_4);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
}

