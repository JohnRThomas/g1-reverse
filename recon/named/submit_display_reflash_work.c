/* named: submit_display_reflash_work */
/* globals referenced:
//   0x2000a09c  g_display_thread_id          [g_obj_2000a018.f_84]
//   0x2001d446  g_display_reflash_pending    
*/
/* Reconstructed submit_display_reflash_work @ 0x4904c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00074554(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void submit_display_reflash_work(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a09cUL;
    FUN_00074554(*p, 0xfffffff0U, param_3, (unsigned int)(uintptr_t)p, param_4);
    *(volatile uint8_t *)0x2001d446UL = 1;
}

