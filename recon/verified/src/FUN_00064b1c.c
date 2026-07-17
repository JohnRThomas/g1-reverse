/* Reconstructed FUN_00064b1c @ 0x64b1c  (parity: 300/300 trials, PROVEN) */

typedef void (*fp1_t)(volatile int*);

void FUN_00064b1c(volatile int *param_1)
{
    volatile int *base = (volatile int*)0x20002bacUL;
    while (param_1 != 0) {
        int iVar2 = param_1[0];
        int cond1 = (param_1[3] << 0x17) >= 0;
        if (cond1) {
            if (param_1[2] != 0) {
                FUN_00064b1c((volatile int*)param_1[2]);
                cond1 = (param_1[3] << 0x17) >= 0;
            }
            if (cond1) {
                if (param_1[4] != 0) {
                    fp1_t release = (fp1_t)(*(volatile int*)((char*)base + 4));
                    release((volatile int *)param_1[4]);
                }
            }
        }
        if ((param_1[3] << 0x16) >= 0 && param_1[8] != 0) {
            fp1_t release = (fp1_t)(*(volatile int*)((char*)base + 4));
            release((volatile int *)param_1[8]);
        }
        {
            fp1_t fp3 = (fp1_t)(*(volatile int*)((char*)base + 4));
            fp3(param_1);
        }
        param_1 = (volatile int*)iVar2;
    }
}
