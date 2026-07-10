#include "g1_app_symbols.h"
/* named: bt_smp_distribute_keys */
/* Reconstructed bt_smp_distribute_keys @ 0x5e1a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned undefined4;
extern unsigned bt_addr_le_str(int a);
extern int bt_security_err_lookup(int a);
extern int bt_rand(void *a, int b);
extern void bt_smp_send_pdu(int *a, int b, unsigned c);
extern void smp_pairing_complete(int *a, unsigned char b);
extern void bt_keys_add_type(int a, int b);
extern int net_buf_simple_add(int a, int b);
extern int atomic_test_bit(int *a, int b);
extern void FUN_00083074(unsigned a, int b, void *c);
extern unsigned atomic_set_bit(int a, unsigned b);
extern int smp_create_pdu(int *a, int b);
extern int atomic_test_and_clear_bit(int *a, int b);
extern void att_chan_reset(int *a);
extern void memcpy(int a, void *b, unsigned c);
extern void memset_bytes(int a, int b, int c);

void bt_smp_distribute_keys(int *param_1, int param_2)
{
    int iVar1, iVar3, iVar11;
    uint uVar2;
    undefined2 *puVar4;
    unsigned uVar5, uVar6;
    unsigned *puVar7, *puVar12;
    undefined1 uVar8;
    int *piVar9, *piVar10;
    undefined4 local_70, local_6c, uStack_68;
    undefined2 local_64;
    undefined4 local_50, local_4c;
    undefined4 local_44[4];
    undefined4 local_34, uStack_30;
    undefined2 local_2c;

    piVar10 = param_1 + -0x3b;
    piVar9 = param_1 + -0x3c;
    iVar11 = *param_1;
    iVar1 = atomic_test_and_clear_bit(piVar10, 1);
    if (iVar1 == 0) return;
    if (param_2 != 0) {
        iVar1 = atomic_test_bit(piVar10, 3);
        if (iVar1 == 0) return;
        iVar1 = bt_security_err_lookup(param_2);
        uVar2 = iVar1 - 1U & 0xff;
        if (uVar2 < 9) uVar8 = *(volatile undefined1 *)(((uintptr_t)&rodata_f5217) /*=0xf5217*/ + uVar2);
        else uVar8 = 0;
        atomic_set_bit((int)piVar10, 2);
        goto LAB_0005e1fa;
    }
    if (*(volatile char *)(iVar11 + 0xb) == '\0') return;
    iVar1 = atomic_test_bit(piVar10, 3);
    if (iVar1 == 0) {
        att_chan_reset(piVar9);
        return;
    }
    iVar1 = atomic_test_bit(piVar10, 5);
    if (iVar1 != 0) {
        if (((int)((uint)*(volatile unsigned char *)((int)param_1 - 8) << 0x1c) < 0) &&
            ((int)((uint)*(volatile unsigned char *)((int)param_1 - 7) << 0x1c) < 0)) {
            atomic_set_bit((int)piVar10, 0x11);
        }
        *(volatile unsigned char *)((int)param_1 - 8) &= 0xf7;
        *(volatile unsigned char *)((int)param_1 - 7) &= 0xf7;
    }
    uVar2 = (uint)*(volatile unsigned char *)((int)param_1 - 7);
    if ((int)(uVar2 << 0x1f) < 0) {
        uVar5 = 6;
LAB_0005e264:
        atomic_set_bit((int)piVar9, uVar5);
    } else {
        if ((int)(uVar2 << 0x1e) < 0) {
            uVar5 = 8;
            goto LAB_0005e264;
        }
        if ((int)(uVar2 << 0x1d) < 0) {
            uVar5 = 10;
            goto LAB_0005e264;
        }
    }
    uVar5 = atomic_set_bit((int)piVar10, 2);
    if (*(volatile int *)(*param_1 + 0xc0) == 0) {
        uStack_68 = bt_addr_le_str(*param_1 + 0x90);
        local_6c = "No keys space for %s" /*=0xf516d*/;
        local_64 = 0x200;
        local_70 = 0x01000003;
        FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1c40, &local_70);
        return;
    }
    iVar1 = atomic_test_bit((int *)uVar5, 5);
    if ((iVar1 == 0) && ((int)((uint)*(volatile unsigned char *)((int)param_1 - 8) << 0x1f) < 0)) {
        iVar11 = *(volatile int *)(*param_1 + 0xc0);
        iVar1 = bt_rand(local_44, 0x1a);
        uVar5 = "Unable to get random bytes" /*=0xf5182*/;
        if ((iVar1 == 0) && (iVar1 = smp_create_pdu(piVar9, 6), uVar5 = "Unable to allocate Encrypt Info buffer" /*=0xf519d*/, iVar1 != 0)) {
            iVar3 = net_buf_simple_add(iVar1 + 0xc, 0x10);
            memcpy(iVar3, local_44, *(volatile unsigned char *)(iVar11 + 0xc));
            uVar2 = (uint)*(volatile unsigned char *)(iVar11 + 0xc);
            if (uVar2 < 0x10) {
                memset_bytes(uVar2 + iVar3, 0, 0x10 - uVar2);
            }
            bt_smp_send_pdu(piVar9, iVar1, 0);
            iVar1 = smp_create_pdu(piVar9, 7);
            uVar5 = "Unable to allocate Central Ident buffer" /*=0xf51c4*/;
            if (iVar1 != 0) {
                puVar4 = (undefined2 *)net_buf_simple_add(iVar1 + 0xc, 10);
                *(undefined4 *)(puVar4 + 1) = local_34;
                *(undefined4 *)(puVar4 + 3) = uStack_30;
                *puVar4 = local_2c;
                bt_smp_send_pdu(piVar9, iVar1, ((uintptr_t)&tbl_5e3c0) /*=0x5e41d*/);
                iVar1 = atomic_test_bit(piVar10, 0xd);
                if (iVar1 != 0) {
                    bt_keys_add_type(iVar11, 1);
                    puVar7 = local_44;
                    puVar12 = (unsigned *)(iVar11 + 0x4a);
                    do {
                        uVar5 = *puVar7;
                        uVar6 = puVar7[1];
                        puVar7 = puVar7 + 2;
                        *puVar12 = uVar5;
                        puVar12[1] = uVar6;
                        puVar12 = puVar12 + 2;
                    } while (puVar7 != &local_34);
                    *(undefined4 *)(iVar11 + 0x40) = local_34;
                    *(undefined4 *)(iVar11 + 0x44) = uStack_30;
                    *(undefined2 *)(iVar11 + 0x48) = local_2c;
                }
                goto LAB_0005e2f2;
            }
        }
        local_50 = 2;
        local_4c = uVar5;
        FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1040, &local_50);
    }
LAB_0005e2f2:
    if ((short)param_1[-2] != 0) return;
    uVar8 = 0;
LAB_0005e1fa:
    smp_pairing_complete(piVar9, uVar8);
    return;
}

