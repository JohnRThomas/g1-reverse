/* Reconstructed FUN_00084dea @ 0x84dea  (parity: 300/300 trials, PROVEN) */
extern int FUN_0007efaa(unsigned,unsigned,void*,unsigned);
extern unsigned FUN_0007f000(void);
extern unsigned FUN_0007f012(unsigned);
extern void FUN_00086c1e(void*,unsigned,int,int);
extern void FUN_00086c78(void*,unsigned,unsigned);
int FUN_00084dea(unsigned param_1, unsigned param_2, unsigned param_3, int param_4){
    unsigned auStack_28[3];
    auStack_28[0]=param_1; auStack_28[1]=param_2; auStack_28[2]=param_3;
    unsigned i = FUN_0007f000();
    unsigned uVar3 = ((unsigned)(param_4 - 1) + i) & (unsigned)(-(int)i);
    if (uVar3 < 9){
        unsigned uVar2 = FUN_0007f012(param_1);
        FUN_00086c1e(auStack_28, param_3, param_4, 8);
        FUN_00086c78((char*)auStack_28 + param_4, uVar2, uVar3 - (unsigned)param_4);
        int iVar1 = FUN_0007efaa(param_1, param_2, auStack_28, uVar3);
        if (iVar1 != 0) return 1;
        return iVar1;
    }
    return -1;
}

