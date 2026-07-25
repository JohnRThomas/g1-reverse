/* readable reconstruction; identity: FUN_00052c40 @ 0x00052c40
 * public-name: sys_rand32_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   entropy_get_entropy_isr_call             <= FUN_00052bf8 @ 0x00052bf8
 *   sys_rand32_get                           <= FUN_00052c40 @ 0x00052c40
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   sys_clock_cycle_get_32                   <= FUN_00084c76 @ 0x00084c76
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   entropy_dev                              @ 0x00087b90
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2abf                             @ 0x000f2abf
 *   rodata_f2af8                             @ 0x000f2af8
 *   rodata_f2b15                             @ 0x000f2b15
 */
/* Reconstructed FUN_00052c40 @ 0x52c40  (parity: 300/300 trials, PROVEN) */

extern int entropy_get_entropy_isr_call(int*, int);
extern void assert_post_action(int,int);
extern void printk(int, ...);
extern int sys_clock_cycle_get_32(void);
extern int z_device_is_ready(int);

int sys_rand32_get(int param_1, int param_2)
{
    int local_c = param_2;
    int iVar2;
    iVar2 = z_device_is_ready(0x00087b90);
    if (iVar2 == 0) {
        printk(0x00099cbd, 0x000f2af8, 0x000f2abf, 0x15, param_1);
        printk(0x000f2b15, *(volatile int*)0x00087b90UL);
        assert_post_action(0x000f2abf, 0x15);
    }
    iVar2 = entropy_get_entropy_isr_call(&local_c, 4);
    if (iVar2 < 0) {
        local_c = sys_clock_cycle_get_32();
    }
    return local_c;
}
