/* Reconstructed FUN_00056960 @ 0x56960  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00056654(unsigned int a);
extern void FUN_000566a4(unsigned int a);

void FUN_00056960(unsigned char param_1, void (*param_2)(unsigned int, unsigned int), unsigned int param_3)
{
    unsigned int iVar1;
    iVar1 = FUN_00056654(0x20006138UL);
    if (iVar1 != 0) {
        if ((param_1 & *(volatile unsigned char*)(iVar1 + 2)) != 0) {
            param_2(iVar1, param_3);
        }
        FUN_000566a4(iVar1);
    }
}

