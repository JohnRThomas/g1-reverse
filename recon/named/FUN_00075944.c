/* readable reconstruction; identity: FUN_00075944 @ 0x00075944
 * public-name: FUN_00075944
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_heap_aligned_alloc                     <= FUN_00075864 @ 0x00075864
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   g_zephyr_kernel                          @ 0x2000b448
 */
/* Reconstructed FUN_00075944 @ 0x75944  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int k_is_in_isr(void);
extern int* z_heap_aligned_alloc(int,...);
int* FUN_00075944(unsigned p1, unsigned p2, unsigned p3, unsigned p4){
  int iVar2 = k_is_in_isr();
  int iVar3;
  if(iVar2==0){
    iVar3 = *(volatile int*)(*(volatile int*)(0x2000b448+8)+0x88);
    if(iVar3==0) return 0;
  } else {
    iVar3 = 0x200037d8;
  }
  return z_heap_aligned_alloc(iVar3, p1, p2);
}
