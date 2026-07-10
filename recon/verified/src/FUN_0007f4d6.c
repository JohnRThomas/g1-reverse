/* Reconstructed FUN_0007f4d6 @ 0x7f4d6  (parity: 178/300 trials, PROVEN) */

extern int FUN_00080d3e(void*, int);

void* FUN_0007f4d6(int param_1, unsigned int *param_2, int param_3)
{
    unsigned char *puVar4 = (unsigned char*)(param_1 + 0x1c);
    if (param_2 == 0) {
    } else if ((unsigned char*)param_2 >= (unsigned char*)(param_1+0x1c)) {
        puVar4 = (unsigned char*)param_2;
    } else {
        return 0;
    }
    {
        int iVar3 = *(volatile int*)(param_1+0x134);
        unsigned char *bound = (unsigned char*)(param_1 + iVar3*8 + 0x1c);
        int iVar2;
        do {
            struct { unsigned char b0; unsigned char b1; unsigned short h1; } local;
            puVar4 += 8;
            if (bound <= puVar4) return 0;
            local.b0 = 0;
            local.h1 = 0x2803;
            iVar2 = FUN_00080d3e(&local, *(unsigned int*)puVar4);
        } while (iVar2 != 0);
    }
    return puVar4;
}

