#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024d74 @ 0x00024d74
 * public-name: st25dv_read_reg_pair
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_read_reg_pair                     <= FUN_00024d74 @ 0x00024d74
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 * address symbols (name @ address):
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024d74 @ 0x24d74  (parity: 300/300 trials, PROVEN) */

extern int ipc_send_len_prefixed_packet_locked_retry(unsigned int, int, int, int, unsigned int);

int st25dv_read_reg_pair(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = ipc_send_len_prefixed_packet_locked_retry(*(volatile unsigned int*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/, 0, param_1, 4, param_4);
    if (*(volatile char*)(param_1+2) == 0) {
        if (iVar2 != 0) return -1;
        iVar2 = ipc_send_len_prefixed_packet_locked_retry(*(volatile unsigned int*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/, 4, param_1 + 4, 4, param_4);
    }
    if (iVar2 != 0) iVar2 = 1;
    return -iVar2;
}
