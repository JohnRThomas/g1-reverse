#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083740 @ 0x00083740
 * public-name: net_buf_simple_add_mem
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00083740 @ 0x83740  (parity: 300/300 trials, PROVEN) */

extern int net_buf_simple_add(int a, int b);
extern void memcpy(int a, int b, int c, int d);
void net_buf_simple_add_mem(int param_1, int param_2, int param_3, int param_4) {
    int uVar1 = net_buf_simple_add(param_1, param_3);
    memcpy(uVar1, param_2, param_3, param_4);
}
