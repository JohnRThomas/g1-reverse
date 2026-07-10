#include "g1_app_symbols.h"
/* named: projector_send_cmd1 */
/* Reconstructed projector_send_cmd1 @ 0x7d642  (parity: 300/300 trials, PROVEN) */

extern void projector_send_command(unsigned int, unsigned char*, unsigned int, unsigned int, unsigned int, unsigned int);

void projector_send_cmd1(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int stackword = ((param_2 & 0xFFu) << 24) | (param_2 & 0x00FFFFFFu);
    unsigned char *p = ((unsigned char*)&stackword) + 3;
    projector_send_command(param_1, p, 1, param_4, param_1, stackword);
}

