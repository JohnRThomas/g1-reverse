/* Reconstructed FUN_0002c324 @ 0x2c324  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, unsigned b);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned a, unsigned b);
extern void FUN_0002bc2c(unsigned a, int b, int c);
extern unsigned FUN_0002c30c(unsigned a, int b);
extern int FUN_00033d58(int a);
extern int FUN_00034274(void);
extern void FUN_0003439c(void);
extern int FUN_00034410(void);
extern void FUN_0003443c(int a);
extern void FUN_0007ce40(void);
void FUN_0002c324(void){
    FUN_0007ce40();
    if (*(volatile int*)0x20007554 == 0){
        unsigned u = FUN_00034410();
        DEBUG_PRINT(0x000a26f7, u);
    } else {
        unsigned u = FUN_00034410();
        FUN_00019c70(0x000a26f7, u);
    }
    int iVar3 = FUN_00034410();
    if (iVar3 == 2 || FUN_00034410() == 4){
        FUN_00034274();
        int t = FUN_000167a8();
        unsigned uVar1 = FUN_0002c30c(*(volatile unsigned char*)(t + 0xfea), 0xf);
        t = FUN_000167a8();
        *(volatile unsigned char*)(t + 0xdb) = (unsigned char)uVar1;
    }
    int t = FUN_000167a8();
    unsigned char dd = *(volatile unsigned char*)(t + 0xdd);
    if (dd != 0){
        FUN_00033d58(1);
        FUN_0003439c();
        *(volatile unsigned char*)0x20018d9e = 1;
        return;
    }
    FUN_0003443c(0);
    t = FUN_000167a8();
    if (*(volatile unsigned char*)(t + 0xd5) == 1) return;
    t = FUN_000167a8();
    if (*(volatile unsigned char*)(t + 0xee4) != 2) return;
    t = FUN_000167a8();
    *(volatile unsigned char*)(t + 0xdb) = 0;
    t = FUN_000167a8();
    FUN_0002bc2c(0x000a2733, t, 1);
    return;
}

