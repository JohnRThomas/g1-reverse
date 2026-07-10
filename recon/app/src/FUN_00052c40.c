/* Reconstructed FUN_00052c40 @ 0x52c40  (parity: 300/300 trials, PROVEN) */

extern int FUN_00052bf8(int*);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int, ...);
extern int FUN_00084c76(void);
extern int FUN_0008638c(int);

int FUN_00052c40(int param_1, int param_2)
{
    int local_c = param_2;
    int iVar2;
    iVar2 = FUN_0008638c(0x00087b90);
    if (iVar2 == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f2af8, 0x000f2abf, 0x15, param_1);
        FUN_0007e2fa(0x000f2b15, *(volatile int*)0x00087b90UL);
        FUN_0007e2ec(0x000f2abf, 0x15);
    }
    iVar2 = FUN_00052bf8(&local_c);
    if (iVar2 < 0) {
        local_c = FUN_00084c76();
    }
    return local_c;
}

