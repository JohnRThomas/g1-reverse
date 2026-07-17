/* Reconstructed FUN_00083cfc @ 0x83cfc  (parity: 300/300 trials, PROVEN) */

extern void FUN_00067884(int a);
extern void FUN_000678d0(int a);
extern int FUN_00083cde(unsigned int a, int b, unsigned int c, unsigned int d);

int FUN_00083cfc(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 4);
    if (param_2 != 0) {
        if (param_2 == 1) {
            iVar1 = FUN_00083cde(*(unsigned int *)(iVar2 + 0x20), 0,
                                 param_3, param_4);
            if (-1 < iVar1) {
                FUN_00067884(iVar2);
            }
        } else {
            iVar1 = -0x86;
        }
        return iVar1;
    }
    FUN_000678d0(iVar2);
    iVar2 = FUN_00083cde(*(unsigned int *)(iVar2 + 0x20), 1, param_3, param_4);
    return iVar2;
}
