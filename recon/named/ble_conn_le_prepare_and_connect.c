/* named: ble_conn_le_prepare_and_connect */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed ble_conn_le_prepare_and_connect @ 0x55734  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char undefined1;
extern void FUN_0004d944(unsigned a, int b, void *c, int d);
extern int bt_hci_cmd_create(int a, int b);
extern int FUN_00053d70(int a, int b, int c);
extern int FUN_00055454(undefined1 *a, unsigned b, int c, int d);
extern int FUN_00055614(void *a);
extern int ble_conn_addr_resolve_or_create(undefined1 *a, int *b);
extern void ble_conn_unref(int a);
extern void ble_conn_set_state(int a, int b);
extern int FUN_00081130(void *a);
extern int get_adv_channel_map(unsigned a, unsigned b);
extern unsigned long long FUN_0008117a(void *a);
extern void atomic_and_1(unsigned a);
extern void FUN_00081196(int a, unsigned b);
extern void FUN_000811a4(undefined1 *a, int b, uint c);
extern int le_adv_update(undefined1 *a, unsigned b, unsigned c, int d, unsigned e, int f, int g);
extern int get_adv_name_type_param(void *a);
extern int bt_le_adv_set_enable_legacy(undefined1 *a, int b);
extern void net_buf_simple_push_mem(int a, void *b, int c);

int ble_conn_le_prepare_and_connect(undefined1 *param_1, int param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 param_6)
{
    int iVar1, iVar2, iVar6, iVar8;
    undefined1 uVar4;
    uint uVar5;
    undefined1 *puVar3, *puVar7;
    unsigned long long uVar9;
    int local_54;

    iVar8 = *(volatile int *)(param_2 + 0x10);
    iVar6 = iVar8;
    if (iVar8 != 0) iVar6 = 1;
    local_54 = 0;
    uVar9 = FUN_0008117a((void *)0x200020d4);
    puVar3 = (undefined1 *)(unsigned)(uVar9 >> 0x20);
    if (-1 < (int)((unsigned)uVar9) << 0x1d) return -0xb;
    iVar1 = FUN_00055614(puVar3);
    if ((iVar1 == 0) || (iVar1 = FUN_00081130(puVar3), iVar1 == 0)) return -0x16;
    puVar7 = param_1 + 0x10;
    iVar2 = FUN_0008117a(puVar7);
    if (iVar2 << 0x18 < 0) return -0x78;
    get_adv_channel_map(*(volatile unsigned *)(puVar3 + 4), 0xffffdfff);
    atomic_and_1(0x200020d4);
    uVar4 = *puVar3;
    *param_1 = uVar4;
    *(volatile undefined1 *)(0x20002000 + 0x6f) = uVar4;
    iVar6 = FUN_00055454(param_1, *(volatile unsigned *)(puVar3 + 4), iVar6, 0);
    if (iVar6 != 0) return iVar6;
    int iVar1b = 0;
    if (iVar8 == 0) {
        FUN_00081196((int)(param_1 + 9), 0xf2b3a);
        iVar6 = get_adv_name_type_param(puVar3);
        uVar5 = *(volatile uint *)(puVar3 + 4);
        if (-1 < (int)(uVar5 << 0x1f)) goto LAB_000557f6;
    } else {
        FUN_00081196((int)(param_1 + 9), *(volatile unsigned *)(puVar3 + 0x10));
        iVar6 = get_adv_name_type_param(puVar3);
        uVar5 = *(volatile uint *)(puVar3 + 4);
        if ((int)(uVar5 << 0x1f) < 0) {
            FUN_00081196(0, *(volatile unsigned *)(puVar3 + 0x10));
            iVar1b = 0;
        } else {
LAB_000557f6:
            if ((((int)(uVar5 << 0x16) < 0) || (param_5 != 0)) || (iVar6 == 2)) {
                ;
            } else {
                iVar1b = 0;
            }
        }
    }
    iVar2 = bt_hci_cmd_create(0x2006, 0xf);
    if (iVar2 == 0) return -0x69;
    net_buf_simple_push_mem(iVar2 + 0xc, (void *)0, 0xf);
    iVar2 = FUN_00053d70(0x2006, iVar2, 0);
    if (iVar2 != 0) return iVar2;
    if ((iVar8 == 0) &&
        (iVar2 = le_adv_update(param_1, param_3, param_4, param_5, param_6, iVar1b, iVar6), iVar2 != 0)) {
        return iVar2;
    }
    if ((*(volatile int *)(puVar3 + 4) << 0x1f < 0) && (iVar2 = ble_conn_addr_resolve_or_create(param_1, &local_54), iVar2 != 0)) {
        if (iVar2 != -0xc) return iVar2;
        if (iVar8 != 0) return -0xc;
        if (*(volatile int *)(puVar3 + 4) << 0x1e < 0) return -0xc;
    } else {
        iVar2 = bt_le_adv_set_enable_legacy(param_1, 1);
        if (iVar2 != 0) {
            FUN_0004d944(0x880f8, 0x1040, (void *)0, 0);
            iVar6 = local_54;
            if (local_54 == 0) return iVar2;
            ble_conn_set_state(local_54, 0);
            ble_conn_unref(iVar6);
            return iVar2;
        }
        if (local_54 != 0) ble_conn_unref(local_54);
        uVar5 = 0;
        if (iVar8 != 0) goto LAB_0005590e;
    }
    uVar5 = ((*(volatile uint *)(puVar3 + 4) ^ 2) << 0x1e) >> 0x1f;
LAB_0005590e:
    FUN_000811a4(puVar7, 0xe, uVar5);
    FUN_000811a4(puVar7, 8, iVar6 == 1);
    FUN_000811a4(puVar7, 9, iVar6 == 2);
    FUN_000811a4(puVar7, 10, *(volatile uint *)(puVar3 + 4) & 1);
    FUN_000811a4(puVar7, 0xb, iVar1b);
    FUN_000811a4(puVar7, 0xd, (uint)(*(volatile int *)(puVar3 + 4) << 0x1d) >> 0x1f);
    return 0;
}

