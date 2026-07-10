/* named: ble_conn_unref */
/* Reconstructed ble_conn_unref @ 0x566a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int printk(int, ...);
extern int assert_post_action(int,int);
extern int FUN_00055aac(int);

void ble_conn_unref(int param_1)
{
    int *piVar4 = (int *)(param_1 + 0xd0);
    int iVar3 = *piVar4;
    *piVar4 = iVar3 - 1;
    if (iVar3 < 1) {
        printk(0, 0, 0, 0x525);
        printk(0);
        assert_post_action(0, 0x525);
    }
    if ((*(short *)(param_1 + 2) == 0x101) && (*piVar4 == 0)) {
        FUN_00055aac(param_1);
    }
    return;
}

