/* readable reconstruction; identity: FUN_00023a54 @ 0x00023a54
 * public-name: spawn_flash_ops_and_brightness_threads
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_flash_ops_and_brightness_threads   <= FUN_00023a54 @ 0x00023a54
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   ADDR_flash_ops_thread_THUMB              @ 0x00023481
 *   ADDR_FUN_00023844_THUMB                  @ 0x00023845
 *   g_flash_ops_thread                       @ 0x20003e38
 *   g_brightness_thread                      @ 0x20003f10
 *   g_app_language_msgq                      @ 0x200079e4
 *   g_flash_ops_thread_stack                 @ 0x20021968
 *   g_brightness_thread_stack                @ 0x20022168
 */
/* Reconstructed FUN_00023a54 @ 0x23a54  (parity: 300/300 trials, PROVEN) */
extern void z_impl_k_sem_init(unsigned a, int b, int c);
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern void z_impl_k_thread_create(unsigned,unsigned,unsigned,unsigned,int,int,int,int,int,unsigned long long);
void spawn_flash_ops_and_brightness_threads(int param_1){
    z_impl_k_sem_init(0x200079e4, 0, 0x14);
    z_impl_k_thread_create(0x20003e38, 0x20021968, 0x800, 0x23481, param_1, 0, 0, 0xfffffff4, 0, 0ULL);
    z_impl_k_thread_create(0x20003f10, 0x20022168, 0x1400, 0x23845, param_1, 0, 0, 0xfffffff5, 0, 0ULL);
}
