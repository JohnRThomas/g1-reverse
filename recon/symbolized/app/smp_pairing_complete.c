#include "g1_app_symbols.h"
/* named: smp_pairing_complete */
/* Reconstructed smp_pairing_complete @ 0x5daf0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ble_notify_remote_info_available(int,int,int);
extern int FUN_0005d964(int);
extern int bt_keys_clear(int);
extern int bt_keys_store(int);
extern int atomic_test_bit(int,int);
extern int FUN_00083074(int,int,void*);
extern int att_chan_reset(int);

void smp_pairing_complete(int param_1, int param_2)
{
    int iVar1;
    unsigned char uVar2;
    unsigned int uVar3;
    int *piVar4;
    void (*pcVar5)(int,int);
    uint32_t *puVar6;
    int iVar7;
    int iVar8;
    uint32_t *puVar9;
    int local_20, local_1c;

    iVar7 = *(int *)(param_1 + 0xf0);
    iVar8 = param_1 + 4;
    if (*(char *)(iVar7 + 0xd) == '\a') {
        if (param_2 == 0) {
            iVar8 = atomic_test_bit(iVar8, 0xd);
            if (iVar8 != 0) {
                bt_keys_store(*(uint32_t *)(iVar7 + 0xc0));
            }
            puVar6 = (uint32_t *)*(void * volatile *)((uintptr_t)&g_bt_conn_auth_info_cb_list) /*=0x2000ad20*/;
            if (puVar6 != (uint32_t *)0x0) {
                puVar9 = (uint32_t *)*puVar6;
                if (puVar9 != (uint32_t *)0x0) {
                    puVar9 = puVar9 + -3;
                }
                pcVar5 = (void (*)(int,int))puVar6[-3];
                if (pcVar5 == 0) goto LAB_0005dba4;
                do {
                    (*pcVar5)(iVar7, iVar8);
LAB_0005dba4:
                    if (puVar9 == (uint32_t *)0x0) break;
                    do {
                        pcVar5 = (void (*)(int,int))*puVar9;
                        if (puVar9[3] == 0) {
                            puVar9 = (uint32_t *)0x0;
                            if (pcVar5 == 0) goto LAB_0005dbba;
                            break;
                        }
                        puVar9 = (uint32_t *)(puVar9[3] + -0xc);
                    } while (pcVar5 == 0);
                } while (1);
            }
            goto LAB_0005dbba;
        }
        uVar3 = param_2 - 1U & 0xff;
        if (uVar3 < 0xf) goto LAB_0005db1a;
        uVar3 = 9;
    } else {
        local_1c = "Not connected!" /*=0xf4f89*/;
        local_20 = 2;
        FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1080, &local_20);
        uVar3 = 7;
LAB_0005db1a:
        uVar3 = (unsigned int)*(volatile unsigned char *)(((uintptr_t)&rodata_f5220) /*=0xf5220*/ + uVar3);
    }
    if ((*(int *)(iVar7 + 0xc0) != 0) &&
        ((*(char *)(*(int *)(iVar7 + 0xc0) + 0xc) == '\0' ||
          (iVar1 = atomic_test_bit(iVar8, 2), iVar1 != 0)))) {
        bt_keys_clear(*(uint32_t *)(iVar7 + 0xc0));
        *(uint32_t *)(iVar7 + 0xc0) = 0;
    }
    iVar1 = atomic_test_bit(iVar8, 2);
    if (iVar1 == 0) {
        if (uVar3 < 8) {
            uVar2 = *(volatile unsigned char *)(((uintptr_t)&rodata_f520f) /*=0xf520f*/ + uVar3);
        } else {
            uVar2 = 0x1f;
        }
        ble_notify_remote_info_available(iVar7, uVar2, uVar3);
    }
    iVar8 = atomic_test_bit(iVar8, 3);
    if ((iVar8 != 0) && (piVar4 = (int *)*(void * volatile *)((uintptr_t)&g_bt_conn_auth_info_cb_list) /*=0x2000ad20*/, piVar4 != (int *)0x0)) {
        iVar8 = *piVar4;
        if (iVar8 != 0) {
            iVar8 = iVar8 + -0xc;
        }
        pcVar5 = (void (*)(int,int))piVar4[-2];
        if (pcVar5 != 0) goto LAB_0005dbf8;
        while (iVar8 != 0) {
            do {
                pcVar5 = *(void (**)(int,int))(iVar8 + 4);
                if (*(int *)(iVar8 + 0xc) == 0) {
                    iVar8 = 0;
                    if (pcVar5 == 0) goto LAB_0005dbba;
                    break;
                }
                iVar8 = *(int *)(iVar8 + 0xc) + -0xc;
            } while (pcVar5 == 0);
LAB_0005dbf8:
            (*pcVar5)(iVar7, uVar3);
        }
    }
LAB_0005dbba:
    att_chan_reset(param_1);
    if ((*(char *)(iVar7 + 0xd) == '\a') && (*(char *)(iVar7 + 9) != *(char *)(iVar7 + 10))) {
        FUN_0005d964(iVar7);
        return;
    }
    return;
}

