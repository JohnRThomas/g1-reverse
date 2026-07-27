/* readable reconstruction; identity: FUN_0005e1a8 @ 0x0005e1a8
 * public-name: bt_smp_distribute_keys
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_str                           <= FUN_00052cdc @ 0x00052cdc
 *   bt_security_err_lookup                   <= FUN_00054250 @ 0x00054250
 *   bt_rand                                  <= FUN_00055cb4 @ 0x00055cb4
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   bt_smp_distribute_keys                   <= FUN_0005e1a8 @ 0x0005e1a8
 *   bt_keys_add_type                         <= FUN_0005e9a0 @ 0x0005e9a0
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 *   atomic_test_and_clear_bit                <= FUN_000831be @ 0x000831be
 *   att_chan_reset                           <= FUN_00083204 @ 0x00083204
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_5e41d                             @ 0x0005e41d
 *   rodata_88180                             @ 0x00088180
 *   rodata_f516d                             @ 0x000f516d
 *   rodata_f5182                             @ 0x000f5182
 *   rodata_f519d                             @ 0x000f519d
 *   rodata_f51c4                             @ 0x000f51c4
 */
/* Reconstructed FUN_0005e1a8 @ 0x5e1a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned undefined4;
extern unsigned int bt_addr_le_str(const void *);
extern unsigned char bt_security_err_lookup(unsigned int);
extern int bt_rand(void *, int);
extern void bt_smp_send_pdu(int, unsigned int, unsigned int);
extern void smp_pairing_complete(int, unsigned int);
extern void bt_keys_add_type(int a, int b);
extern int net_buf_simple_add(int a, int b);
extern int atomic_test_bit(int, int);
extern void smp_log_message(unsigned a, int b, void *c);
extern unsigned atomic_set_bit(int a, unsigned b);
extern int smp_create_pdu(int, int);
extern int atomic_test_and_clear_bit(int *a, int b);
extern void att_chan_reset(int *a);
extern void memcpy(int, int, int);
extern void memset_bytes(void*, int, int);

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
        if (uVar2 < 9) uVar8 = *(volatile undefined1 *)(0xf5217 + uVar2);
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
        local_6c = 0xf516d;
        local_64 = 0x200;
        local_70 = 0x01000003;
        smp_log_message(0x88180, 0x1c40, &local_70);
        return;
    }
    iVar1 = atomic_test_bit((int *)uVar5, 5);
    if ((iVar1 == 0) && ((int)((uint)*(volatile unsigned char *)((int)param_1 - 8) << 0x1f) < 0)) {
        iVar11 = *(volatile int *)(*param_1 + 0xc0);
        iVar1 = bt_rand(local_44, 0x1a);
        uVar5 = 0xf5182;
        if ((iVar1 == 0) && (iVar1 = smp_create_pdu(piVar9, 6), uVar5 = 0xf519d, iVar1 != 0)) {
            iVar3 = net_buf_simple_add(iVar1 + 0xc, 0x10);
            memcpy(iVar3, local_44, *(volatile unsigned char *)(iVar11 + 0xc));
            uVar2 = (uint)*(volatile unsigned char *)(iVar11 + 0xc);
            if (uVar2 < 0x10) {
                memset_bytes(uVar2 + iVar3, 0, 0x10 - uVar2);
            }
            bt_smp_send_pdu(piVar9, iVar1, 0);
            iVar1 = smp_create_pdu(piVar9, 7);
            uVar5 = 0xf51c4;
            if (iVar1 != 0) {
                puVar4 = (undefined2 *)net_buf_simple_add(iVar1 + 0xc, 10);
                *(undefined4 *)(puVar4 + 1) = local_34;
                *(undefined4 *)(puVar4 + 3) = uStack_30;
                *puVar4 = local_2c;
                bt_smp_send_pdu(piVar9, iVar1, 0x5e41d);
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
        smp_log_message(0x88180, 0x1040, &local_50);
    }
LAB_0005e2f2:
    if ((short)param_1[-2] != 0) return;
    uVar8 = 0;
LAB_0005e1fa:
    smp_pairing_complete(piVar9, uVar8);
    return;
}
