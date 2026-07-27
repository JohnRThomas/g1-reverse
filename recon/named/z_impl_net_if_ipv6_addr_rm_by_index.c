/* readable reconstruction; identity: FUN_00080c8c @ 0x00080c8c
 * public-name: z_impl_net_if_ipv6_addr_rm_by_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   active_transfer_conn_match               <= FUN_000527dc @ 0x000527dc
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_net_if_ipv6_addr_rm_by_index      <= FUN_00080c8c @ 0x00080c8c
 */
/* Reconstructed FUN_00080c8c @ 0x80c8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t active_transfer_conn_match(unsigned long);
extern void k_sem_give(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

void z_impl_net_if_ipv6_addr_rm_by_index(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    uint64_t uVar1 = active_transfer_conn_match(param_1);
    unsigned int lo = (unsigned int)uVar1;
    unsigned int hi = (unsigned int)(uVar1 >> 32);
    if ((int)lo != 0) {
        k_sem_give(lo + 0x6c, hi, param_3, param_4);
    }
}
