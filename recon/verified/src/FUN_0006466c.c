/* Reconstructed FUN_0006466c @ 0x6466c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00064640(int a);
extern int FUN_00084f2e(int a, int b);

typedef void (*fn0_t)(void);

int FUN_0006466c(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar2;
    if (param_1 != 0 && param_2 != 0 && param_3 != 0 && param_1 != param_3) {
        if (param_4 == 0) {
            param_2 = FUN_00064640(param_2);
            if (param_2 == 0) {
                return 0;
            }
            uVar2 = *(unsigned int *)(param_3 + 0xc) & 0xfffffdff;
        } else {
            uVar2 = *(unsigned int *)(param_3 + 0xc) | 0x200;
        }
        {
            int shifted = (*(int *)(param_3 + 0xc)) << 0x16;
            if (shifted >= 0 && *(int *)(param_3 + 0x20) != 0) {
                fn0_t f = *(volatile fn0_t *)0x20002bb0UL;
                f();
            }
        }
        *(int *)(param_3 + 0x20) = param_2;
        *(unsigned int *)(param_3 + 0xc) = uVar2;
        return FUN_00084f2e(param_1, param_3);
    }
    return 0;
}

