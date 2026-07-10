/* Reconstructed FUN_00034274 @ 0x34274  (parity: 300/300 trials, PROVEN) */
extern int FUN_000167a8(void);
extern void FUN_00033d58(int);
extern void DEBUG_PRINT(unsigned,int);
extern void FUN_00019c70(void);
extern unsigned char FUN_00033cf8(void);
unsigned char FUN_00034274(void){
    int iVar3 = FUN_000167a8();
    unsigned char bVar1 = *(unsigned char*)(iVar3 + 0xdd);
    if (bVar1 != 0){
        int r5 = bVar1 - 1;
        int r3 = r5 * 0x1b4 + 0x20007dac;
        if (*(int*)(r3 + 4) != 0){
            FUN_00033d58(1);
            unsigned char cVar4;
            if (r5 == 0) cVar4 = 0;
            else cVar4 = (unsigned char)(bVar1 - 2);
            *(volatile unsigned char*)0x2001a22aUL = cVar4;
            if (*(volatile int*)0x20007554UL == 0){
                DEBUG_PRINT(0xa8017, r5);
            } else {
                FUN_00019c70();
            }
            iVar3 = FUN_000167a8();
            unsigned char uVar2 = FUN_00033cf8();
            *(unsigned char*)(iVar3 + 0xdd) = uVar2;
        }
    }
    iVar3 = FUN_000167a8();
    return *(unsigned char*)(iVar3 + 0xdd);
}

