/* readable reconstruction; identity: FUN_0007c898 @ 0x0007c898
 * public-name: json_arr_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet             <= FUN_00025740 @ 0x00025740
 *   json_arr_encode                          <= FUN_0007c898 @ 0x0007c898
 */
/* Reconstructed FUN_0007c898 @ 0x7c898  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int ipc_send_len_prefixed_packet(int a, int b, int c, int d, int e, int f);
void json_arr_encode(unsigned int *param_1, int param_2, int param_3, int param_4) {
    unsigned short h = *(unsigned short*)((char*)param_1 + 8);
    ipc_send_len_prefixed_packet(*param_1, (int)(h | 4), param_2, param_3, param_4, param_2);
}
