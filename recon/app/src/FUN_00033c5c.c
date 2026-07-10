/* Reconstructed FUN_00033c5c @ 0x33c5c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086c78(int,int,int,int,int);
extern int FUN_000167a8(void);
extern void FUN_00033b0c(void);
extern void FUN_00033b4c(void);

void FUN_00033c5c(void)
{
    int iVar2;
    int iVar3 = 0;
    *(volatile unsigned char*)0x20018d8eUL = 1;
    iVar2 = 0x20007dac;
    do {
        iVar2 = FUN_00086c78(iVar2, 0, 0x1b4, iVar2, 0);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x1b4;
    } while (iVar3 != 0x14);
    *(volatile unsigned char*)0x2001a22bUL = 10;
    *(volatile unsigned char*)0x2001a22aUL = 0;
    iVar2 = FUN_000167a8();
    *(volatile unsigned char*)(iVar2 + 0xdd) = 0;
    FUN_00033b0c();
    FUN_00033b4c();
    *(volatile unsigned char*)0x20018d8eUL = 0;
}

