/* Reconstructed FUN_0004f198 @ 0x4f198  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005c22c(unsigned int, void*, unsigned int, void*, unsigned int);
extern void FUN_0007f5d8(volatile int *, int);

int FUN_0004f198(unsigned int *param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
    char *base = (char*)param_1;
    *(volatile unsigned short*)(base + 0x20) = param_2;
    *(volatile unsigned int*)(base + 0x14) = 0x7f5efUL;
    unsigned short v8 = *(volatile unsigned short*)(base + 8);
    *(volatile unsigned int*)(base + 0x24) = param_3;
    *(volatile unsigned short*)(base + 0x18) = v8;
    *(volatile unsigned short*)(base + 0x1a) = 0;
    *(volatile unsigned int*)(base + 0x1c) = (unsigned int)(base + 0x28);
    int iVar2 = FUN_0005c22c(*(volatile unsigned int*)base, base + 0x14, param_3, base + 0x28, param_4);
    if (iVar2 != 0) {
        FUN_0007f5d8(base + 4, 2);
    }
    return iVar2;
}

