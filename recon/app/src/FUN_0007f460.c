/* Reconstructed FUN_0007f460 @ 0x7f460  (parity: 300/300 trials, PROVEN) */

extern int FUN_00080d3e(void*, int);

int FUN_0007f460(int *param_1, int param_2, int param_3)
{
    int iVar2;
    unsigned char b0; unsigned short h1;
    struct { unsigned char b0; unsigned char b1; unsigned short h1; } local;
    local.b0 = 0;
    local.h1 = 0x2800;
    iVar2 = FUN_00080d3e(&local, *param_1);
    if (iVar2 != 0) {
        struct { unsigned char b0; unsigned char b1; unsigned short h1; } local2;
        local2.b0 = 0;
        local2.h1 = 0x2801;
        iVar2 = FUN_00080d3e(&local2, *param_1);
        if (iVar2 != 0) return 0;
    }
    return *param_1 - 8;
}

