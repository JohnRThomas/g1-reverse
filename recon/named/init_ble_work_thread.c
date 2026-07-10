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
    kmutex_dlist_init(0x20007574);
    k_timer_init(0x20003d28, 0x00019ff1, 0);
    FUN_00071eac(0x20003d60, 0x2001e968, 0x3000, 0x21da9, param_1, 0, 0, (int)0xfffffff1, 0);
    return 0;
}

