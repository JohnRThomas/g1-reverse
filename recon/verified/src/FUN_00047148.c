/* Reconstructed FUN_00047148 @ 0x47148  (parity: 300/300 trials, PROVEN) */
extern void FUN_000864c2(unsigned);
extern int FUN_00076d6c(unsigned);
void FUN_00047148(int* param_1){
    FUN_000864c2(0x2000a060);
    param_1[0] = 0x46fc1;
    param_1[1] = 0x46d8d;
    param_1[2] = 0x46f21;
    param_1[3] = 0x46d2d;
    param_1[4] = 0x46dd9;
    param_1[5] = 0x35775;
    param_1[6] = 0x7d4d7;
    param_1[7] = 0x7d4cb;
    param_1[8] = 0x46ce9;
    int iVar1 = FUN_00076d6c(0xfa08);
    int iVar3 = iVar1 + 5;
    param_1[0xd1] = iVar3;
    int* piVar2 = param_1 + 8;
    do {
        piVar2 = piVar2 + 1;
        *piVar2 = iVar3;
        iVar3 = iVar3 + 0x140;
    } while (iVar3 != iVar1 + 0xfa05);
    param_1[0xd4] = 64000;
}

