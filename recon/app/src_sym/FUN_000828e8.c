/* Reconstructed FUN_000828e8 @ 0x828e8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00059e78(int);
typedef void (*fp_t)(unsigned int, void*, int);

void FUN_000828e8(unsigned int param_1, int param_2, unsigned int *param_3, unsigned int *param_4)
{
    unsigned int uVar1;
    if (param_4 != 0) {
        uVar1 = param_4[6];
        if (param_3 == 0) {
            *(unsigned int*)(param_2+8) = uVar1;
            if ((unsigned int*)(param_4+6) == *(unsigned int**)(param_2+0xc)) {
                *(unsigned int*)(param_2+0xc) = uVar1;
            }
        } else {
            *param_3 = uVar1;
            if ((unsigned int*)(param_4+6) == *(unsigned int**)(param_2+0xc)) {
                *(unsigned int**)(param_2+0xc) = param_3;
            }
        }
        param_4[6] = 0;
        fp_t fp = (fp_t)(*(unsigned int*)param_4);
        fp(param_1, param_4, 0);
    }
    if (*(int*)(param_2+8) != 0) return;
    FUN_00059e78(param_2);
}

