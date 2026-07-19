#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005dce0 @ 0x0005dce0
 * public-name: bt_smp_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_error                                <= FUN_0005dc2c @ 0x0005dc2c
 *   bt_smp_recv                              <= FUN_0005dce0 @ 0x0005dce0
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   atomic_test_and_clear_bit                <= FUN_000831be @ 0x000831be
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_8b508                             @ 0x0008b508
 *   rodata_f4617                             @ 0x000f4617
 *   rodata_f4ff0                             @ 0x000f4ff0
 *   rodata_f500b                             @ 0x000f500b
 *   rodata_f503c                             @ 0x000f503c
 *   rodata_f505e                             @ 0x000f505e
 *   rodata_f5078                             @ 0x000f5078
 */
/* Reconstructed FUN_0005dce0 @ 0x5dce0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef int (* volatile codeptr)(int,int);
extern int smp_error(int,int);
extern int net_buf_simple_pull_5f594(int,int);
extern int atomic_test_bit(int,int);
extern int smp_log_message(int,int,void*);
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
        local_24 = ((unsigned long)&rodata_f4ff0) /*=0xf4ff0*/;
        local_28 = 2;
        smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1040, &local_28);
    } else {
        pbVar1 = (unsigned char *)net_buf_simple_pull_5f594(param_2 + 0xc, 1);
        iVar6 = param_1 + -0xf0;
        iVar2 = atomic_test_bit(param_1 + -0xec, 4);
        iVar4 = ((unsigned long)&rodata_8b508) /*=0x8b508*/;
        uVar3 = (unsigned int)*pbVar1;
        uVar5 = ((unsigned long)&rodata_f500b) /*=0xf500b*/;
        if ((iVar2 == 0) && (uVar5 = ((unsigned long)&rodata_f503c) /*=0xf503c*/, uVar3 < 0xf)) {
            if (*(volatile int *)(((unsigned long)&rodata_8b508) /*=0x8b508*/ + uVar3 * 8) == 0) {
                local_44 = ((unsigned long)&rodata_f505e) /*=0xf505e*/;
                local_48 = 3;
                uStack_40 = uVar3;
                smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1880, &local_48);
                iVar4 = 7;
            } else {
                iVar2 = atomic_test_and_clear_bit(iVar6);
                uVar3 = (unsigned int)*pbVar1;
                if (iVar2 == 0) {
                    local_44 = ((unsigned long)&rodata_f5078) /*=0xf5078*/;
                    local_48 = 3;
                    uStack_40 = uVar3;
                    smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1880, &local_48);
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
                    local_44 = ((unsigned long)&rodata_f4617) /*=0xf4617*/;
                    local_48 = 4;
                    uStack_40 = (unsigned int)*(unsigned short *)(param_2 + 0x10);
                    local_3c = uVar3;
                    smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x2040, &local_48);
                    iVar4 = 10;
                }
            }
            smp_error(iVar6, iVar4);
        } else {
            local_48 = 3;
            local_44 = uVar5;
            uStack_40 = uVar3;
            smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1880, &local_48);
        }
    }
    return 0;
}
