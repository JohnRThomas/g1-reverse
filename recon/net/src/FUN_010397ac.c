/* net-core FUN_010397ac @ 0x10397ac  (parity 300 trials PROVEN) */

unsigned int FUN_010397ac(int param_1, int param_2)
{
    int iVar1;
    if (*(volatile unsigned int *)(param_1 + 8) < 0x8000) {
        iVar1 = 4;
    } else {
        iVar1 = 8;
    }
    return (unsigned int)((param_2 - iVar1) - param_1) >> 3;
}

