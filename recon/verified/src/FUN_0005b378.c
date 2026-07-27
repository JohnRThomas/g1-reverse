/* Reconstructed FUN_0005b378 @ 0x5b378  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005a9f4(int a0);
extern int FUN_0005aa84(int a0,int a1,int a2,int a3,int a4,int a5,void *a6);
extern int FUN_0005b270(int a0,int a1,int *a2);
extern void FUN_0007e2ec(int a0,int a1);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00080d3e(int a0,void *a1);
extern int FUN_0008270c(int a0);
extern int FUN_00082c0e(void);

int FUN_0005b378(int param_1,int *param_2)
{
    unsigned char local_28[2];
    unsigned short local_26;
    unsigned int *local_24;
    unsigned short local_20;
    unsigned int local_1c;
    unsigned short local_18;
    int *local_14;
    int iVar1;
    int uVar2;

    if (param_2 == (int*)0) {
        FUN_0007e2fa(0x00099cbd, 0x000f4b3d, 0x000f46b8, 0xbc4);
        FUN_0007e2fa(0x000f4a0a, 0, 0, 0);
        uVar2 = 0xbc4;
        FUN_0007e2ec(0x000f46b8, uVar2);
        return 0;
    } else {
        if ((param_2[1] != 0) || (param_2[0] != 0)) {
            iVar1 = FUN_0008270c(0x200020d4);
            if (-1 < (int)((unsigned int)iVar1 << 0x1d)) {
                return 0xfffffff5;
            }
            if ((param_1 != 0) && (*(unsigned char*)(param_1 + 0xd) != 7)) {
                return 0xffffff80;
            }
            local_24 = (unsigned int*)param_2[1];
            iVar1 = FUN_0005a9f4(param_2[1]);
            local_20 = (unsigned short)iVar1;
            if (param_2[0] == 0) {
                if (iVar1 != 0) goto LAB_0005b40a;
                return 0xfffffffe;
            } else {
                local_24 = (unsigned int*)0;
                FUN_0005aa84(iVar1,0xffff,param_2[0],0,1,0x000825fb,&local_24);
                if (local_24 != (unsigned int*)0) {
                    param_2[1] = (int)local_24;
LAB_0005b40a:
                    local_28[0] = 0;
                    local_26 = 0x2803;
                    iVar1 = FUN_00080d3e(*local_24, local_28);
                    if (iVar1 == 0) {
                        if (-1 < (int)((unsigned int)(*(unsigned char*)(local_24[3] + 6)) << 0x1a)) {
                            return 0xffffffea;
                        }
                        local_20 = (unsigned short)FUN_00082c0e();
                    }
                    if (param_1 != 0) {
                        *(unsigned char*)((int)param_2 + 0x16) = 1;
                        uVar2 = FUN_0005b270(param_1, local_20, param_2);
                        return uVar2;
                    }
                    local_1c = 0xffffff80;
                    local_18 = 2;
                    local_26 = 0x2902;
                    *(unsigned char*)((int)param_2 + 0x16) = 0;
                    local_28[0] = 0;
                    local_14 = param_2;
                    FUN_0005aa84(local_20,0xffff,(int)local_28,0,1,0x0005b891,&local_24);
                    return local_1c;
                }
                return 0xfffffffe;
            }
        }
        FUN_0007e2fa(0x00099cbd, 0x000f4b44, 0x000f46b8, 0xbc5);
        FUN_0007e2fa(0x000f4a0a, 0, 0, 0);
        uVar2 = 0xbc5;
        FUN_0007e2ec(0x000f46b8, uVar2);
        return 0;
    }
}

