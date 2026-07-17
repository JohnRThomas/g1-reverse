/* Reconstructed FUN_0002c3dc @ 0x2c3dc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned);
extern unsigned long long FUN_000167a8(void);
extern void FUN_00019c70(unsigned);
extern unsigned long long FUN_00027448(unsigned a, int b, int c, int d);
extern void FUN_0002c324(void);
extern int FUN_00033c4c(int a);
extern unsigned char FUN_00033cf8(void);
extern void FUN_00072880(int a);
extern void FUN_0007ce5c(unsigned a, int b);
unsigned FUN_0002c3dc(unsigned inherited_r0, unsigned inherited_r1,
                      unsigned inherited_r2, unsigned inherited_r3){
    volatile unsigned char *puVar1 = (volatile unsigned char*)0x20018d9f;
    *puVar1 = 1;
    unsigned sVar7 = 1000;
    for(;;){
        int iVar4 = FUN_00033c4c(10);
        if (*(volatile unsigned char*)(iVar4 + 0x10) == 0) break;
        if (*(volatile unsigned char*)(iVar4 + 0xc) == 0) break;
        sVar7 = (sVar7 - 1) & 0xffff;
        FUN_0007ce5c(0x21, 0);
        if (sVar7 == 0) break;
    }
    unsigned long long residual = FUN_000167a8();
    unsigned long long elapsed = FUN_00027448((unsigned)residual, 9, 0, 0);
    unsigned uVar6 = (unsigned)elapsed;
    unsigned uVar5;
    if (uVar6 < 2000){
        residual = FUN_000167a8();
        int t = (int)residual;
        if (*(volatile unsigned char*)(t + 0x105a) == 2){
            volatile unsigned char *pcVar2 = (volatile unsigned char*)0x20018d8d;
            int iVar4 = 0; int go446 = 0;
            for(;;){
                if (*pcVar2 != 0){ go446 = 1; break; }
                iVar4 = iVar4 + 1;
                FUN_0007ce5c(0xccd, 0);
                if (iVar4 == 10) break;
            }
            if (!go446 && *pcVar2 == 0){ uVar5 = 0xffffffffu; goto out; }
            *pcVar2 = 0;
            int t2 = (int)FUN_000167a8();
            unsigned char u3 = FUN_00033cf8();
            *(volatile unsigned char*)(t2 + 0xdd) = u3;
            FUN_0002c324();
            int t3 = (int)FUN_000167a8();
            FUN_00072880(t3 + 0x38);
            uVar5 = 0;
            goto out;
        }
    }
    if (*(volatile int*)0x20007554 == 0)
        DEBUG_PRINT(0x000a2748);
    else
        FUN_00019c70(0x000a2748);
    uVar5 = 0xffffffffu;
out:
    *puVar1 = 0;
    (void)inherited_r0;
    (void)inherited_r1;
    (void)inherited_r2;
    (void)inherited_r3;
    return uVar5;
}
