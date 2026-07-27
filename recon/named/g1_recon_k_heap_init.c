/* readable reconstruction; identity: FUN_000863aa @ 0x000863aa
 * public-name: g1_recon_k_heap_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_heap_init                            <= FUN_0004b3c8 @ 0x0004b3c8
 *   g1_recon_k_heap_init                     <= FUN_000863aa @ 0x000863aa
 */
/* Reconstructed FUN_000863aa @ 0x863aa. CFG_VERIFY_CALL_ARITIES=3 */
#include <stdint.h>
extern void sys_heap_init(unsigned long*, void*, unsigned long);

void g1_recon_k_heap_init(unsigned int *param_1, int param_2, int param_3)
{
    param_1[3] = (unsigned int)(param_1 + 3);
    param_1[4] = (unsigned int)(param_1 + 3);
    sys_heap_init(param_1, param_2, param_3);
}
