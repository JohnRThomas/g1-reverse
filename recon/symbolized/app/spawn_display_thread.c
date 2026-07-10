#include "g1_app_symbols.h"
/* named: spawn_display_thread */
/* globals referenced:
//   0x2000a09c  g_display_thread_id          [g_obj_2000a018.f_84]
*/
/* Reconstructed spawn_display_thread @ 0x49638  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00071eac(unsigned int, unsigned int, int, unsigned int, unsigned int, int, int, int, int);

unsigned int spawn_display_thread(unsigned int param_1)
{
    unsigned int uVar1 = FUN_00071eac(((uintptr_t)&g_display_thread) /*=0x20004d18*/, ((uintptr_t)&g_display_thread_stack_buf) /*=0x20028e68*/, 0x1400, ((uintptr_t)&tbl_48fc4) /*=0x49091*/, param_1, 0, 0, 0xfffffff2, 0);
    *(volatile unsigned int*)((uintptr_t)&g_display_thread_id) /*=0x2000a09c*/ = uVar1;
    return 0;
}

