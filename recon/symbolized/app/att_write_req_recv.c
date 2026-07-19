#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082282 @ 0x00082282
 * public-name: att_write_req_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_notify_or_indicate                  <= FUN_00058c34 @ 0x00058c34
 *   att_write_req_recv                       <= FUN_00082282 @ 0x00082282
 *   net_buf_simple_pull_le16                 <= FUN_00083718 @ 0x00083718
 */
/* Reconstructed FUN_00082282 @ 0x82282  (parity: 300/300 trials, PROVEN) */

extern unsigned int net_buf_simple_pull_le16(int);
extern void gatt_notify_or_indicate(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void att_write_req_recv(unsigned int param_1, int param_2)
{
    unsigned int uVar1;
    uVar1 = net_buf_simple_pull_le16(param_2 + 0xc);
    gatt_notify_or_indicate(param_1, 0x12, 0x13, uVar1, 0, *(unsigned int*)(param_2 + 0xc), *(unsigned short*)(param_2 + 0x10));
    return;
}
