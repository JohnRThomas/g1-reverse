#include "g1_app_symbols.h"
/* named: bt_smp_recv */
/* Reconstructed bt_smp_recv @ 0x5dce0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef int (* volatile codeptr)(int,int);
extern int smp_error(int,int);
extern int net_buf_simple_pull_5f594(int,int);
extern int atomic_test_bit(int,int);
extern int FUN_00083074(int,int,void*);
extern int atomic_test_and_clear_bit(int);

int bt_smp_recv(int param_1, int param_2)
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
        local_24 = "Too small SMP PDU received" /*=0xf4ff0*/;
        local_28 = 2;
        FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1040, &local_28);
    } else {
        pbVar1 = (unsigned char *)net_buf_simple_pull_5f594(param_2 + 0xc, 1);
        iVar6 = param_1 + -0xf0;
        iVar2 = atomic_test_bit(param_1 + -0xec, 4);
        iVar4 = ((uintptr_t)&tbl_8b508) /*=0x8b508*/;
        uVar3 = (unsigned int)*pbVar1;
        uVar5 = "SMP command (code 0x%02x) received after timeout" /*=0xf500b*/;
        if ((iVar2 == 0) && (uVar5 = "Received reserved SMP code 0x%02x" /*=0xf503c*/, uVar3 < 0xf)) {
            if (*(volatile int *)(((uintptr_t)&tbl_8b508) /*=0x8b508*/ + uVar3 * 8) == 0) {
                local_44 = "Unhandled SMP code 0x%02x" /*=0xf505e*/;
                local_48 = 3;
                uStack_40 = uVar3;
                FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1880, &local_48);
                iVar4 = 7;
            } else {
                iVar2 = atomic_test_and_clear_bit(iVar6);
                uVar3 = (unsigned int)*pbVar1;
                if (iVar2 == 0) {
                    local_44 = "Unexpected SMP code 0x%02x" /*=0xf5078*/;
                    local_48 = 3;
                    uStack_40 = uVar3;
                    FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1880, &local_48);
                    iVar4 = atomic_test_bit(param_1 + -0xec, 3);
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
                    local_44 = "Invalid len %u for code 0x%02x" /*=0xf4617*/;
                    local_48 = 4;
                    uStack_40 = (unsigned int)*(unsigned short *)(param_2 + 0x10);
                    local_3c = uVar3;
                    FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x2040, &local_48);
                    iVar4 = 10;
                }
            }
            smp_error(iVar6, iVar4);
        } else {
            local_48 = 3;
            local_44 = uVar5;
            uStack_40 = uVar3;
            FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1880, &local_48);
        }
    }
    return 0;
}

