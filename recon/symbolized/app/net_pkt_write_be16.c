#include "g1_app_symbols.h"
/* named: net_pkt_write_be16 */
/* Reconstructed net_pkt_write_be16 @ 0x7d696  (parity: 300/300 trials, PROVEN) */

extern int projector_send_command(int a, void*b, int c, int d, int e);
void net_pkt_write_be16(unsigned int param_1, int param_2, int param_3, int param_4) {
    unsigned short local_c = (unsigned short)(((param_1 & 0xff) << 8) | ((param_1 >> 8) & 0xff));
    projector_send_command(0x36, &local_c, 2, param_4, (int)param_1);
}

