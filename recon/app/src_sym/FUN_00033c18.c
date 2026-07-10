/* Reconstructed FUN_00033c18 @ 0x33c18  (parity: 300/300 trials, PROVEN) */

int FUN_00033c18(int param_1)
{
    int iVar1 = 10;
    volatile int *piVar2 = *(volatile int**)0x33c44UL;
    while ((*(volatile char*)((int)piVar2+8) == 0) ||
           (*(volatile char*)((int)piVar2+6) != 0) ||
           (piVar2[0] != param_1)) {
        iVar1 = iVar1 + 1;
        piVar2 = (volatile int*)((char*)piVar2 + 0x1b4);
        if (iVar1 == 0x14) {
            return 0;
        }
    }
    return iVar1 * 0x1b4 + *(volatile int*)0x33c48UL;
}

