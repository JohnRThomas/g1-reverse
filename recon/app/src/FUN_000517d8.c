/* Reconstructed FUN_000517d8 @ 0x517d8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0005169c(void);
extern int FUN_0004e048(unsigned a, void*b);
extern int FUN_0007ef80(unsigned a, int b, unsigned c, unsigned d);
extern void FUN_0007ef7e(unsigned a);
extern void FUN_0008096a(unsigned a, unsigned b, void*c);
int FUN_000517d8(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned local_1c; unsigned s[4]; int iVar1;
    unsigned long long uVar2 = FUN_0005169c();
    unsigned uStack_28 = (unsigned)uVar2;
    if ((int)uStack_28 < 0){ iVar1 = 0xe; }
    else {
        int local_24 = FUN_0004e048(uStack_28 & 0xff, &local_1c);
        if (local_24 == 0){
            iVar1 = FUN_0007ef80(local_1c, (int)(uVar2>>32), param_3, param_4);
            FUN_0007ef7e(local_1c);
            if (iVar1 != 0){
                s[1] = 0x000f26c4; s[0] = 3; s[2] = (unsigned)iVar1;
                FUN_0008096a(0x00088208, 0x1840, s);
                iVar1 = 0xb;
            }
        } else {
            s[1] = 0x000f25fb; s[0] = 4;
            FUN_0008096a(0x00088208, 0x2040, s);
            iVar1 = 10;
        }
    }
    return iVar1;
}

