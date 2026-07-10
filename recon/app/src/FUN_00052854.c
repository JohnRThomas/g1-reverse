/* Reconstructed FUN_00052854 @ 0x52854  (parity: 300/300 trials, PROVEN) */

extern int FUN_00080b32(int);
extern int* FUN_00080bfe(int);
extern int thunk_FUN_0005f24c(int);

int FUN_00052854(int param_1, int param_2)
{
    int iVar1 = FUN_00080b32(0x2000abac);
    if (iVar1 < 0) return iVar1;
    if (param_2 != 0) return iVar1;
    int *puVar2 = FUN_00080bfe(0x2000abac);
    *puVar2 = param_2;
    *(unsigned char*)((char*)puVar2+4) = (unsigned char)param_2;
    return thunk_FUN_0005f24c(0x2000abac);
}

