/* Reconstructed FUN_00054828 @ 0x54828  (parity: 300/300 trials, PROVEN) */
extern void FUN_00053530(int);
extern int FUN_00080e14(unsigned);
extern void FUN_00054784(int);
extern void FUN_0005f24c(int);
extern void FUN_00080ea2(unsigned,int,void*);
unsigned FUN_00054828(int param_1){
    unsigned char uStack_18 = *(unsigned char*)(param_1 + 0x18);
    if (uStack_18 == 1){
        int r3 = *(int*)(param_1 + 0xc);
        int iVar1 = FUN_00080e14(*(unsigned char*)r3);
        if ((int)((unsigned)iVar1 << 31) < 0) FUN_00054784(param_1);
        if ((int)((unsigned)iVar1 << 30) >= 0) return 0;
    } else if (uStack_18 != 3){
        volatile unsigned local[8];
        local[4]=3; local[5]=0xf3191;
        FUN_00080ea2(0x88138, 0x1840, (void*)&local[4]);
        FUN_0005f24c(param_1);
        return 0xffffffea;
    }
    FUN_00053530(param_1);
    return 0;
}

