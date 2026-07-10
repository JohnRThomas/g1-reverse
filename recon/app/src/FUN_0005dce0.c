/* Reconstructed FUN_0005dce0 @ 0x5dce0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef int (* volatile codeptr)(int,int);
extern int FUN_0005dc2c(int,int);
extern int FUN_0005f594(int,int);
extern int FUN_00082ff6(int,int);
extern int FUN_00083074(int,int,void*);
extern int FUN_000831be(int);

int FUN_0005dce0(int param_1, int param_2)
{
    unsigned char *pbVar1;
    int iVar2;
    unsigned int uVar3;
    int iVar4;
    int uVar5;
    int iVar6;
    int local_48, local_44;
    unsigned int uStack_40, local_3c;
    int local_28, local_24;

    if (*(short *)(param_2 + 0x10) == 0) {
        local_24 = 0x000f4ff0;
        local_28 = 2;
        FUN_00083074(0x00088180, 0x1040, &local_28);
    } else {
        pbVar1 = (unsigned char *)FUN_0005f594(param_2 + 0xc, 1);
        iVar6 = param_1 + -0xf0;
        iVar2 = FUN_00082ff6(param_1 + -0xec, 4);
        iVar4 = 0x0008b508;
        uVar3 = (unsigned int)*pbVar1;
        uVar5 = 0x000f500b;
        if ((iVar2 == 0) && (uVar5 = 0x000f503c, uVar3 < 0xf)) {
            if (*(volatile int *)(0x0008b508 + uVar3 * 8) == 0) {
                local_44 = 0x000f505e;
                local_48 = 3;
                uStack_40 = uVar3;
                FUN_00083074(0x00088180, 0x1880, &local_48);
                iVar4 = 7;
            } else {
                iVar2 = FUN_000831be(iVar6);
                uVar3 = (unsigned int)*pbVar1;
                if (iVar2 == 0) {
                    local_44 = 0x000f5078;
                    local_48 = 3;
                    uStack_40 = uVar3;
                    FUN_00083074(0x00088180, 0x1880, &local_48);
                    iVar4 = FUN_00082ff6(param_1 + -0xec, 3);
                    if (iVar4 == 0) {
                        return 0;
                    }
                    iVar4 = 8;
                } else if ((unsigned int)*(volatile unsigned char *)(iVar4 + uVar3 * 8 + 4) == (unsigned int)*(unsigned short *)(param_2 + 0x10)) {
                    iVar4 = (*(codeptr *)(iVar4 + uVar3 * 8))(iVar6, param_2);
                    if (iVar4 == 0) {
                        return 0;
                    }
                } else {
                    local_44 = 0x000f4617;
                    local_48 = 4;
                    uStack_40 = (unsigned int)*(unsigned short *)(param_2 + 0x10);
                    local_3c = uVar3;
                    FUN_00083074(0x00088180, 0x2040, &local_48);
                    iVar4 = 10;
                }
            }
            FUN_0005dc2c(iVar6, iVar4);
        } else {
            local_48 = 3;
            local_44 = uVar5;
            uStack_40 = uVar3;
            FUN_00083074(0x00088180, 0x1880, &local_48);
        }
    }
    return 0;
}

