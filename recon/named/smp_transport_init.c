/* named: smp_transport_init */
/* Reconstructed smp_transport_init @ 0x526f4  (parity: 300/300 trials, PROVEN) */

extern void k_work_init(int a, unsigned int b);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00080b28(void);
extern void z_impl_k_queue_init(int a);

unsigned int smp_transport_init(int param_1)
{
    if (*(volatile int *)(param_1 + 0x2c) == 0) {
        printk(0x00099cbdUL, 0x000f293bUL, 0x000f2901UL, 0x92);
        printk(0x000f2963UL, 0, 0, 0);
        assert_post_action(0x000f2901UL, 0x92);
    }
    FUN_00080b28();
    k_work_init(param_1, 0x00080ab5UL);
    z_impl_k_queue_init(param_1 + 0x10);
    return 0;
}

