#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002201c @ 0x0002201c
 * public-name: init_ble_work_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_ble_work_thread                     <= FUN_0002201c @ 0x0002201c
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 * address symbols (name @ address):
 *   rodata_19ff1                             @ 0x00019ff1
 *   ADDR_FUN_00021da8_THUMB                  @ 0x00021da9
 *   g_ble_work_timer                         @ 0x20003d28
 *   g_ble_work_thread                        @ 0x20003d60
 *   g_ble_work_queue                         @ 0x20007574
 *   g_ble_work_thread_stack                  @ 0x2001e968
 */
/* Reconstructed FUN_0002201c @ 0x2201c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00071eac(int,int,int,int,int,int,int,int,int);
extern void kmutex_dlist_init(int);
extern void k_timer_init(int,int,int);

int init_ble_work_thread(int param_1)
{
    kmutex_dlist_init(((unsigned long)&g_ble_work_queue) /*=0x20007574*/);
    k_timer_init(((unsigned long)&g_ble_work_timer) /*=0x20003d28*/, ((unsigned long)&rodata_19ff1) /*=0x19ff1*/, 0);
    FUN_00071eac(((unsigned long)&g_ble_work_thread) /*=0x20003d60*/, ((unsigned long)&g_ble_work_thread_stack) /*=0x2001e968*/, 0x3000, ADDR_FUN_00021da8_THUMB /*=0x21da9*/, param_1, 0, 0, (int)0xfffffff1, 0);
    return 0;
}
