/* Reconstructed FUN_00052000 @ 0x52000  (parity: 300/300 trials, PROVEN) */

extern int FUN_0008633e(int, void*);
extern int thunk_FUN_00086320(int, unsigned int);

unsigned int FUN_00052000(int param_1)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int local_10;
    unsigned int local_c;
    local_10 = 0xa24e0U;
    local_c = 3;
    iVar1 = FUN_0008633e(param_1 + 4, &local_10);
    if (iVar1 == 0 ||
        (iVar1 = thunk_FUN_00086320(param_1 + 4, *(volatile unsigned int*)(0x2000ab7cUL + 4)), iVar1 == 0)) {
        uVar2 = 7;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

