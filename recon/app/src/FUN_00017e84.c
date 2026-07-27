/* Reconstructed FUN_00017e84 @ 0x17e84  (parity: 300/300 trials, PROVEN) */
extern unsigned int FUN_00019b2c(void);
extern long long FUN_00032ee4(void);
extern int FUN_000167a8(void);
extern void FUN_000723b8(unsigned,unsigned,unsigned,unsigned);
extern int FUN_0004f518(int,unsigned,unsigned);
extern void FUN_00072558(unsigned);
extern void DEBUG_PRINT(unsigned long, ...);
unsigned FUN_00017e84(unsigned param_1, unsigned param_2){
    int r6 = FUN_00019b2c();
    long long uVar3 = FUN_00032ee4();
    int r4;
    if ((int)uVar3 != 0) goto L_work;
    if (r6 == 0) goto L_dc;
    {
        int t = FUN_000167a8();
        if (*(char*)(t + 0xae3) != 0) goto L_dc;
        t = FUN_000167a8();
        if (*(int*)(t + 0x9b4) == 0) goto L_dc;
    }
L_work:
    FUN_000723b8(0x20006a1c, (unsigned)((unsigned long long)uVar3 >> 32), 0xffffffff, 0xffffffff);
    r4 = FUN_0004f518(0, param_1, param_2);
    FUN_00072558(0x20006a1c);
    if (r4 == 0) return 0;
    DEBUG_PRINT(0x9a155, r4, param_2);
    goto L_dc;
L_dc:
    r4 = -1;
    return (unsigned)r4;
}

