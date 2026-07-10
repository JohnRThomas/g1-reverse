/* named: json_arr_encode */
/* Reconstructed json_arr_encode @ 0x7c898  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int ipc_send_len_prefixed_packet(int a, int b, int c, int d, int e, int f);
void json_arr_encode(unsigned int *param_1, int param_2, int param_3, int param_4) {
    unsigned short h = *(unsigned short*)((char*)param_1 + 8);
    ipc_send_len_prefixed_packet(*param_1, (int)(h | 4), param_2, param_3, param_4, param_2);
}

