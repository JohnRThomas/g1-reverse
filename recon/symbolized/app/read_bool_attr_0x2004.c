#include "g1_app_symbols.h"
/* named: read_bool_attr_0x2004 */
/* Reconstructed read_bool_attr_0x2004 @ 0x7ca24  (parity: 300/300 trials, PROVEN) */

extern int ipc_send_len_prefixed_packet_locked_retry(int,int,int,int,int);
void read_bool_attr_0x2004(int param_1, unsigned char *param_2)
{
    unsigned char stackbuf[4];
    *param_2 = 0;
    int iVar1 = ipc_send_len_prefixed_packet_locked_retry(param_1, 0x2004, (int)&stackbuf[3], 1, param_1);
    if (iVar1 == 0) {
        if (stackbuf[3] != 0) {
            *param_2 = 1;
        } else {
            *param_2 = 0;
        }
    }
}

