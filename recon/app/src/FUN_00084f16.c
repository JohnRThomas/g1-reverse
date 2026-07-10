/* Reconstructed FUN_00084f16 @ 0x84f16  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000ef12(int a);
void FUN_00084f16(int *param_1) {
    if (param_1 != (int*)0 && *param_1 != 0) {
        int iVar2 = param_1[2];
        int iVar1 = FUN_0000ef12(*param_1 + iVar2);
        param_1[2] = iVar2 + iVar1;
    }
}

