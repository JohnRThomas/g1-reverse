/* Reconstructed FUN_0007c670 @ 0x7c670  (parity: 300/300 trials, PROVEN) */

extern void pthread_attr_getstack(int param_1, int *param_2);

int FUN_0007c670(int param_1, int *param_2, int param_3)
{
    if (param_1 != 0) {
        if (param_2 == (int*)0) {
            param_1 = 0;
        } else {
            param_2[0] = 0;
            param_2[1] = 0;
            int iVar1 = *(volatile int*)((char*)param_1 + 0x14);
            if ((iVar1 == 0) || (*(volatile int*)((char*)iVar1 + 8) == 0)) {
                if (param_3 != 0) {
                    pthread_attr_getstack(param_1, param_2);
                }
            } else {
                void (*fp)(int) = (void(*)(int))*(volatile unsigned int*)((char*)iVar1 + 8);
                fp(iVar1);
            }
            param_1 = *param_2;
        }
    }
    return param_1;
}

