/* named: ble_conn_ref */
/* Reconstructed ble_conn_ref @ 0x56654  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int) __attribute__((noreturn));
extern void printk(int,int,int,int);

int ble_conn_ref(int param_1)
{
    volatile int *piVar1;
    int iVar2;
    if (param_1 == 0) {
        printk(0x00099cbd, 0x000f3ebd, 0x000f3a5d, 0x509);
        assert_post_action(0x000f3a5d, 0x509);
    }
    piVar1 = (volatile int*)(param_1 + 0xd0);
    iVar2 = *piVar1;
    if (iVar2 == 0) return 0;
    *piVar1 = iVar2 + 1;
    return param_1;
}

