#include "g1_app_symbols.h"
/* named: some_module_sem_init */
/* globals referenced:
//   0x20007b1c  g_some_module_sem            
//   0x20018d8a  g_some_module_init_done_flag 
*/
/* Reconstructed some_module_sem_init @ 0x2953c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int z_impl_k_sem_init(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void some_module_sem_init(void)
{
    int iVar1 = z_impl_k_sem_init(((uintptr_t)&g_some_module_sem) /*=0x20007b1c*/, 0, 5, 0, 0);
    if (iVar1 == 0) {
        *(volatile uint8_t *)((uintptr_t)&g_some_module_init_done_flag) /*=0x20018d8a*/ = 1;
    }
}

