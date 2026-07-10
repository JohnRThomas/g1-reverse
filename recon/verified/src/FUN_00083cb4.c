/* Reconstructed FUN_00083cb4 @ 0x83cb4  (parity: 300/300 trials, PROVEN) */

extern int FUN_0008638c(unsigned int);

unsigned int FUN_00083cb4(void *param_1)
{
    int iVar1;
    unsigned int uVar2;
    int *p = *(volatile int**)((char*)param_1 + 4);
    iVar1 = FUN_0008638c(*(volatile unsigned int*)((char*)p + 4));
    if (iVar1 == 0) {
        uVar2 = 0xffffffed;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

