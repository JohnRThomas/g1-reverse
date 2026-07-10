/* named: vsnprintf_impl */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed vsnprintf_impl @ 0x77c30  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0008712e(int a, int b, int c, int d, int e, int f, int g);
void vsnprintf_impl(int param_1, int param_2, int param_3, int param_4) {
    FUN_0008712e(*(volatile int*)0x20002d20UL, param_1, param_2, param_3, param_4, param_2, param_3);
}

