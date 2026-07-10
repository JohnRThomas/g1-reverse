/* Reconstructed FUN_00059690 @ 0x59690  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_000826e0(unsigned a, int b);
extern void FUN_000864e8(unsigned a);
extern void FUN_00086502(unsigned a, int b);
extern void FUN_00059cb4(void);
extern void FUN_000732d4(unsigned a, unsigned b);
extern void FUN_000531cc(unsigned a, unsigned b, int c, int d);
extern void FUN_00057330(unsigned a);
void FUN_00059690(void){
    FUN_000864e8(0x20003a28);
    int iVar4 = 0; int iVar5 = 0x2000add4;
    do { iVar4 = iVar4 + 1; FUN_00086502(0x20003a28, iVar5); iVar5 += 0x14; } while (iVar4 != 10);
    unsigned long long uVar6 = FUN_000826e0(0x2000af04, 1);
    unsigned r4 = (unsigned)uVar6 & (unsigned)(uVar6>>32);
    if (r4 != 0) return;
    FUN_00059cb4();
    *(volatile unsigned*)0x2000af10 = r4;
    *(volatile unsigned*)0x2000af14 = r4;
    FUN_000732d4(0x200063a0, 0x00082cb3);
    FUN_000531cc(0x200063a0, 0, 0x148, 0);
    FUN_000732d4(0x20006418, 0x0005b4bd);
    FUN_000826e0(0x20006448, 2);
    FUN_000732d4(0x20006350, 0x00082fa7);
    FUN_00057330(0x200029f8);
    int iv4 = *(volatile int*)0x2000ad1c;
    *(volatile int*)0x2000ad1c = 0x200029d4;
    *(volatile int*)(0x200029d4+0x20) = iv4;
    return;
}

