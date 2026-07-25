/* Reconstructed FUN_000289b0 @ 0x289b0  (CFG-directed candidate) */

extern int FUN_000167a8(void);
extern void FUN_0002bd7c(int context);
extern void FUN_00047ab8(void);
extern void FUN_00049858(int);

void FUN_000289b0(void)
{
    int iVar2;
    FUN_00047ab8();
    iVar2 = FUN_000167a8();
    FUN_0002bd7c(iVar2);
    iVar2 = FUN_000167a8();
    *(unsigned char*)(iVar2 + 0xee4) = 1;
    FUN_00049858(3);
    iVar2 = FUN_000167a8();
    *(unsigned char*)(iVar2 + 0xd5) = 0;
    *(volatile unsigned char*)0x20018d8bUL = 0;
    return;
}
