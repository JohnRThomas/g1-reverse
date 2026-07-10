/* named: sys_rand32_get */
/* globals referenced:
//   0x00087b90  entropy_dev                  
*/
/* Reconstructed sys_rand32_get @ 0x52c40  (parity: 300/300 trials, PROVEN) */

extern int entropy_get_entropy_isr_call(int*);
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
    iVar2 = entropy_get_entropy_isr_call(&local_c);
    if (iVar2 < 0) {
        local_c = sys_clock_cycle_get_32();
    }
    return local_c;
}

