/* Reconstructed FUN_00052c40 @ 0x52c40  (parity: 300/300 trials, PROVEN) */

extern int FUN_00052bf8(int*);
extern void assert_post_action(int,int);
extern void printk(unsigned long, ...);
extern int FUN_00084c76(void);
extern int z_device_is_ready(int);

int FUN_00052c40(int param_1, int param_2)
{
    int local_c = param_2;
    int iVar2;
    iVar2 = z_device_is_ready(0x00087b90);
    if (iVar2 == 0) {
        printk(0x00099cbd, 0x000f2af8, 0x000f2abf, 0x15, param_1);
        printk(0x000f2b15, *(volatile int*)0x00087b90UL);
        assert_post_action(0x000f2abf, 0x15);
    }
    iVar2 = FUN_00052bf8(&local_c);
    if (iVar2 < 0) {
        local_c = FUN_00084c76();
    }
    return local_c;
}

