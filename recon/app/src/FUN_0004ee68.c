/* Reconstructed FUN_0004ee68 @ 0x4ee68  (parity: 300/300 trials, PROVEN) */
extern int FUN_0004ed3c(int a0, void *a1);
extern int FUN_0007f460(void);
extern int FUN_0007f4c8(int a0);
extern int FUN_0007f4d2(void);
extern int FUN_0007f570(int a0, int a1, void *a2);
extern int FUN_00080d3e(int a0, void *a1);

int FUN_0004ee68(int param_1, int *param_2)
{
    unsigned char buf[24];
    int *puVar1;
    int uVar9;
    int iVar3a, iVar3b, iVar3c, iVar3d, iVar3e, iVar3f, iVar4a, iVar4b;

    FUN_0007f4d2();
    puVar1 = (int*)(long)FUN_0007f460();
    uVar9 = *puVar1;
    iVar3a = FUN_00080d3e(uVar9, buf);
    if (iVar3a == 0) {
        param_2[0]=0; param_2[1]=0; param_2[2]=0; param_2[3]=0;
        *(unsigned short*)(param_2+4) = 0;
        iVar3a = FUN_0004ed3c(param_1, buf);
        if (iVar3a != 0) {
            iVar3b = FUN_0007f570(param_1, iVar3a, buf);
            if (iVar3b != 0) {
                *(unsigned short*)((char*)param_2+8) = *(unsigned short*)(iVar3b+4);
                iVar3c = FUN_0004ed3c(param_1, buf);
                if (iVar3c != 0) {
                    iVar4a = FUN_0007f570(param_1, iVar3c, buf);
                    if (iVar4a != 0) {
                        *(unsigned short*)((char*)param_2+10) = *(unsigned short*)(iVar4a+4);
                        iVar3d = FUN_0007f570(param_1, iVar3c, buf);
                        if (iVar3d != 0) {
                            *(unsigned short*)((char*)param_2+12) = *(unsigned short*)(iVar3d+4);
                            iVar3e = FUN_0004ed3c(param_1, buf);
                            if (iVar3e != 0) {
                                iVar4b = FUN_0007f570(param_1, iVar3e, buf);
                                if (iVar4b != 0) {
                                    *(unsigned short*)((char*)param_2+14) = *(unsigned short*)(iVar4b+4);
                                    iVar3f = FUN_0007f570(param_1, iVar3e, buf);
                                    if (iVar3f != 0) {
                                        *(unsigned short*)((char*)param_2+16) = *(unsigned short*)(iVar3f+4);
                                        uVar9 = FUN_0007f4c8(param_1);
                                        param_2[0] = uVar9;
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        uVar9 = 0xffffffea;
    } else {
        uVar9 = 0xffffff7a;
    }
    return uVar9;
}

