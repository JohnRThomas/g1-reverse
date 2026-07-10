/* Reconstructed FUN_00081626 @ 0x81626  (parity: 300/300 trials, PROVEN) */

extern void FUN_000815f6(int a, int *b, int *c, int d, unsigned int e);

int *FUN_00081626(int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
    int *piVar1;
    int *piVar2;
    int *piVar3;

    piVar1 = *(int **)(param_1 + 0x54);
    if (piVar1 != (int *)0) {
        piVar3 = (int *)0;
        piVar2 = piVar1;
        do {
            if (*(volatile unsigned char *)((int)piVar2 + 0xb8) == param_2) {
                if (param_3 == 0) {
                    return piVar2 + -2;
                }
                FUN_000815f6(param_1 + 0x54, (int*)piVar3, (int*)piVar2, param_1, param_4);
                return piVar2 + -2;
            }
            piVar1 = (int *)*piVar2;
            piVar3 = piVar2;
            piVar2 = piVar1;
        } while (piVar1 != (int *)0);
    }
    return piVar1;
}

