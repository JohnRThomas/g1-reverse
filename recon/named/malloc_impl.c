/* readable reconstruction; identity: FUN_000868c2 @ 0x000868c2
 * public-name: malloc_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_aligned_alloc                          <= FUN_000758cc @ 0x000758cc
 *   malloc_impl                              <= FUN_000868c2 @ 0x000868c2
 */
/* Reconstructed FUN_000868c2 @ 0x868c2  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int k_aligned_alloc(int,int);
int malloc_impl(int param_1){
  return k_aligned_alloc(4, param_1);
}
