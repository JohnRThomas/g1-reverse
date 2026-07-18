/* readable reconstruction; identity: FUN_000526f4 @ 0x000526f4
 * public-name: smp_transport_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_transport_init                       <= FUN_000526f4 @ 0x000526f4
 *   k_work_init                              <= FUN_00072e50 @ 0x00072e50
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   smp_reassembly_init                      <= FUN_00080b28 @ 0x00080b28
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 * address symbols (name @ address):
 *   ADDR_smp_handle_reqs_THUMB               @ 0x00080ab5
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2901                             @ 0x000f2901
 *   rodata_f293b                             @ 0x000f293b
 *   rodata_f2963                             @ 0x000f2963
 */
/* Reconstructed FUN_000526f4 @ 0x526f4  (parity: 300/300 trials, PROVEN) */

extern void k_work_init(int a, unsigned int b);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, ...);
extern void smp_reassembly_init(void);
#define z_impl_k_queue_init z_impl_k_queue_init
extern void z_impl_k_queue_init(void *queue);

unsigned int smp_transport_init(int param_1)
{
    if (*(volatile int *)(param_1 + 0x2c) == 0) {
        printk(0x00099cbdUL, 0x000f293bUL, 0x000f2901UL, 0x92);
        printk(0x000f2963UL);
        assert_post_action(0x000f2901UL, 0x92);
    }
    smp_reassembly_init();
    k_work_init(param_1, 0x00080ab5UL);
    z_impl_k_queue_init((void *)(param_1 + 0x10));
    return 0;
}
