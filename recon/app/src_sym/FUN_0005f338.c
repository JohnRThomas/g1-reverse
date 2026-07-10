/* Reconstructed FUN_0005f338 @ 0x5f338  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* FUN_0005f304(void*);
extern void assert_post_action(void);
extern void printk(void);

void FUN_0005f338(int *param_1, int *param_2)
{
    if (param_1 == 0) {
        printk();
        assert_post_action();
        return;
    }
    if (param_2 != 0) {
        int *iVar3 = *(volatile int**)((char*)param_1 + 4);
        if (iVar3 != 0) {
            int *iVar1 = (int*)FUN_0005f304(param_2);
            *(volatile int**)((char*)iVar1 + 4) = iVar3;
        }
        *(volatile int**)((char*)param_1 + 4) = param_2;
        return;
    }
    printk();
    assert_post_action();
}
