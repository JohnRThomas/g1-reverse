/* Reconstructed FUN_00073d1c @ 0x73d1c  (parity: 300/300 trials, PROVEN) */

extern void FUN_000737d8(int a);
extern void FUN_00073cdc(unsigned a, int* b);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned a,unsigned b);
void FUN_00073d1c(int *param_1){
    volatile unsigned char *p = (volatile unsigned char*)param_1;
    if ((signed char)p[0xd] < 0){
        p[0xd] = p[0xd] & 0x7f;
        FUN_00073cdc(0x2000b464, param_1);
    }
    p[0xd] = p[0xd] | 0x80;
    int iVar1 = 0x2000b448;
    if ((unsigned)param_1 == 0x20006720u){
        FUN_0007e2fa(0x00099cbd,0x000f84d6,0x000f82f4,0xc1);
        FUN_0007e2ec(0x000f82f4,0xc1);
    }
    volatile int *puVar3 = (volatile int*)(iVar1 + 0x1c);
    volatile int *puVar4 = (volatile int*)*puVar3;
    volatile int *puVar2 = (volatile int*)*(volatile int*)(iVar1 + 0x20);
    if (puVar4 == puVar3) puVar4 = 0;
    for (; puVar4 != 0; puVar4 = (volatile int*)*puVar4){
        signed char a = (signed char)p[0xe];
        signed char b2 = (signed char)((volatile unsigned char*)puVar4)[0xe];
        if (a != b2 && a < b2){
            volatile int *t = (volatile int*)puVar4[1];
            ((volatile int*)param_1)[0] = (int)puVar4;
            ((volatile int*)param_1)[1] = (int)t;
            *t = (int)param_1;
            puVar4[1] = (int)param_1;
            goto done;
        }
        if (puVar2 == puVar4) break;
    }
    ((volatile int*)param_1)[0] = (int)puVar3;
    ((volatile int*)param_1)[1] = (int)puVar2;
    *puVar2 = (int)param_1;
    *(volatile int*)(iVar1 + 0x20) = (int)param_1;
done:
    FUN_000737d8(*(volatile int*)(iVar1 + 8) == (int)param_1);
}

