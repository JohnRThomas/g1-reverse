/* Reconstructed FUN_000227d0 @ 0x227d0  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned a, unsigned b);
extern void FUN_00019c70(void);
extern int FUN_00022658(int a, int b, int c);
int FUN_000227d0(int param_1, int param_2, unsigned param_3){
    if (*(volatile int*)0x20007554UL == 0){
        DEBUG_PRINT(0x9e3db, param_3);
    } else {
        FUN_00019c70();
    }
    int iVar3 = 0;
    unsigned r6 = (((param_3 >> 12) + 1) & 0xff);
    int sl = (int)r6 - 1;
    int r4 = (short)(int)(param_3 - (sl << 12));
    unsigned uVar2 = 0;
    for(; (uVar2 & 0xff) < r6; uVar2++){
        int r2 = (sl <= (int)uVar2) ? r4 : 0x1000;
        int iVar1 = FUN_00022658(param_1 + (int)(uVar2*0x1000), param_2 + (int)(uVar2*0x1000), r2);
        iVar3 += iVar1;
    }
    return iVar3;
}

