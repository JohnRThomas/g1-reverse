#include "g1_app_symbols.h"
/* named: init_ble_work_thread */
/* globals referenced:
//   0x20007574  g_ble_work_queue             
*/
/* Reconstructed init_ble_work_thread @ 0x2201c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00071eac(int,int,int,int,int,int,int,int,int);
extern void kmutex_dlist_init(int);
extern void k_timer_init(int,int,int);

int init_ble_work_thread(int param_1)
{
    kmutex_dlist_init(((uintptr_t)&g_ble_work_queue) /*=0x20007574*/);
    k_timer_init(((uintptr_t)&g_ble_work_timer) /*=0x20003d28*/, ((uintptr_t)&tbl_19fcc) /*=0x19ff1*/, 0);
    FUN_00071eac(((uintptr_t)&g_ble_work_thread) /*=0x20003d60*/, ((uintptr_t)&g_ble_work_thread_stack) /*=0x2001e968*/, 0x3000, ((uintptr_t)&tbl_21d54) /*=0x21da9*/, param_1, 0, 0, (int)0xfffffff1, 0);
    return 0;
}

