#include "g1_app_symbols.h"
/* named: k_aligned_alloc */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed k_aligned_alloc @ 0x75944  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int k_is_in_isr(void);
extern int* FUN_00075864(int,...);
int* k_aligned_alloc(unsigned p1, unsigned p2, unsigned p3, unsigned p4){
  int iVar2 = k_is_in_isr();
  int iVar3;
  if(iVar2==0){
    iVar3 = *(volatile int*)(*(volatile int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8)+0x88);
    if(iVar3==0) return 0;
  } else {
    iVar3 = ((uintptr_t)&g_k_aligned_alloc_isr_heap) /*=0x200037d8*/;
  }
  return FUN_00075864(iVar3, p1, p2);
}

