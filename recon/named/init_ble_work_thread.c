/* readable reconstruction; identity: FUN_0002201c @ 0x0002201c
 * public-name: init_ble_work_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_ble_work_thread                     <= FUN_0002201c @ 0x0002201c
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
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

/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int z_impl_k_thread_create(int,int,int,int,int,int,int,int,int,unsigned long long);
extern void kmutex_dlist_init(unsigned long);
extern void k_timer_init(int,int,int);

int init_ble_work_thread(int param_1)
{
    kmutex_dlist_init(0x20007574);
    k_timer_init(0x20003d28, 0x00019ff1, 0);
    z_impl_k_thread_create(0x20003d60, 0x2001e968, 0x3000, 0x21da9, param_1, 0, 0, (int)0xfffffff1, 0, 0ULL);
    return 0;
}
