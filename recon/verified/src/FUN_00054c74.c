/* Reconstructed FUN_00054c74 @ 0x54c74  (parity: 300/300 trials, PROVEN) */
extern unsigned FUN_0000ef12(void);
extern int FUN_0000eefe(unsigned a, unsigned b);
extern void FUN_00086c04(unsigned a, unsigned b, unsigned c);
extern int FUN_00053098(int a, unsigned b);
extern void FUN_00080ea2(unsigned a, int b, void* c);
unsigned FUN_00054c74(unsigned param_1){
    unsigned uVar1 = FUN_0000ef12();
    unsigned uVar3;
    if (uVar1 < 0x1d){
        int iVar2 = FUN_0000eefe(0x2000216c, param_1);
        if (iVar2 != 0){
            FUN_00086c04(0x2000216c, param_1, uVar1);
            int base = 0x20002000 + 0x16c;
            *(volatile unsigned char*)(0x20002000UL + uVar1 + 0x16c) = 0;
            iVar2 = FUN_00053098(base, uVar1);
            if (iVar2 != 0){
                volatile unsigned local_18 = 2;
                volatile unsigned local_14 = 0xf33d4;
                (void)local_14;
                FUN_00080ea2(0x88138, 0x1080, (void*)&local_18);
            }
        }
        uVar3 = 0;
    } else uVar3 = 0xfffffff4;
    return uVar3;
}

