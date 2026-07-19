#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083766 @ 0x00083766
 * public-name: net_buf_push_le16
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   net_buf_push_le16                        <= FUN_00083766 @ 0x00083766
 */
/* Reconstructed FUN_00083766 @ 0x83766  (parity: 300/300 trials, PROVEN) */

extern unsigned char *net_buf_simple_add(unsigned int a, unsigned int b);

void net_buf_push_le16(unsigned int param_1, unsigned int param_2)
{
    unsigned char *puVar1 = net_buf_simple_add(param_1, 2);
    puVar1[0] = (unsigned char)param_2;
    puVar1[1] = (unsigned char)(param_2 >> 8);
}
