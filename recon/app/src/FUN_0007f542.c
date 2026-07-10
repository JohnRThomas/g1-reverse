/* Reconstructed FUN_0007f542 @ 0x7f542  (parity: 300/300 trials, PROVEN) */

extern unsigned int* FUN_0007f51a(void);
extern int FUN_00080d3e(void*, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int* FUN_0007f542(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned short uVar1;
    unsigned int *puVar2;
    int iVar3;
    unsigned int local_c;
    local_c = param_2;
    puVar2 = FUN_0007f51a();
    if (puVar2 != (unsigned int*)0) {
        uVar1 = (unsigned short)local_c;
        local_c = (0x2803U << 16) | (uVar1 & 0xff00U);
        iVar3 = FUN_00080d3e(&local_c, *puVar2, param_3, 0x2803U, param_1);
        if (iVar3 != 0) {
            return puVar2;
        }
    }
    return (unsigned int*)0;
}

