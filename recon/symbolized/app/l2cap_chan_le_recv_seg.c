#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057a04 @ 0x00057a04
 * public-name: l2cap_chan_le_recv_seg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_le_recv_seg                   <= FUN_00057a04 @ 0x00057a04
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_append_bytes                     <= FUN_0005f450 @ 0x0005f450
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_buf_frags_len                        <= FUN_00081616 @ 0x00081616
 *   gatt_send_service_changed_ind            <= FUN_00081b30 @ 0x00081b30
 * address symbols (name @ address):
 *   rodata_81699                             @ 0x00081699
 *   rodata_88160                             @ 0x00088160
 *   rodata_f4079                             @ 0x000f4079
 */
/* Reconstructed FUN_00057a04 @ 0x57a04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005774c(int,int);
extern int net_buf_unref(int);
extern short net_buf_append_bytes(int,int,int);
extern int assert_post_action(int,int);
extern int printk(int,int,int,int);
extern long long net_buf_frags_len(int);
extern int FUN_000816a2(int);
extern int FUN_00081746(int,int,void*);
extern int gatt_send_service_changed_ind(int);

void l2cap_chan_le_recv_seg(int param_1, int param_2)
{
    unsigned char bVar1;
    unsigned short uVar2;
    short sVar3;
    unsigned int uVar4;
    int iVar5;
    int extraout_r1;
    unsigned short uVar6;
    unsigned int uVar7;
    unsigned int local_48;
    int local_44, local_40, local_3c;
    int local_28;
    long long _r;

    _r = net_buf_frags_len(*(int *)(param_1 + 0x80));
    uVar2 = (unsigned short)_r;
    extraout_r1 = (int)((unsigned long long)_r >> 32);
    uVar6 = uVar2;
    if (uVar2 != 0) {
        uVar6 = *(unsigned short *)(extraout_r1 + 0x18);
    }
    if ((unsigned int)*(unsigned short *)(param_2 + 0x10) + (unsigned int)uVar2 <= (unsigned int)*(unsigned short *)(param_1 + 0x84)) {
        *(unsigned short *)(extraout_r1 + 0x18) = uVar6 + 1;
        local_40 = ((unsigned long)&rodata_81699) /*=0x81699*/;
        local_48 = 0;
        local_44 = 0;
        local_3c = param_1;
        (void)local_40; (void)local_44; (void)local_3c;
        sVar3 = net_buf_append_bytes(*(int *)(param_1 + 0x80), *(unsigned short *)(param_2 + 0x10), *(int *)(param_2 + 0xc));
        if (*(short *)(param_2 + 0x10) == sVar3) {
            uVar7 = *(unsigned int *)(param_1 + 0x80);
            uVar4 = (unsigned int)net_buf_frags_len(uVar7);
            if (*(unsigned short *)(param_1 + 0x84) <= uVar4) {
                bVar1 = *(unsigned char *)(param_1 + 0xb4);
                *(unsigned int *)(param_1 + 0x80) = 0;
                *(unsigned short *)(param_1 + 0x84) = 0;
                if (bVar1 == 3) {
                    iVar5 = FUN_000816a2(param_1 + 0x1c);
                    if (iVar5 == 0) {
                        iVar5 = (**(int (**)(int,int))(*(int *)(param_1 + 4) + 0x14))(param_1, uVar7);
                        if (iVar5 < 0) {
                            if (iVar5 == -0x77) {
                                return;
                            }
                            local_44 = ((unsigned long)&rodata_f4079) /*=0xf4079*/;
                            local_48 = (unsigned int)bVar1;
                            local_40 = iVar5;
                            FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1840, &local_48);
                            gatt_send_service_changed_ind(param_1);
                        } else if (*(char *)(param_1 + 0xb4) == '\x03') {
                            FUN_0005774c(param_1, 1);
                        }
                        net_buf_unref(uVar7);
                        return;
                    }
                    printk(0, 0, 0, 0x99c);
                    uVar7 = 0x99c;
                } else {
                    printk(0, 0, 0, 0x99b);
                    uVar7 = 0x99b;
                }
                assert_post_action(0, uVar7);
            }
            iVar5 = FUN_000816a2(param_1 + 0x1c);
            if (iVar5 != 0) {
                return;
            }
            FUN_0005774c(param_1, 1);
            return;
        }
    }
    local_28 = 2;
    FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1040, &local_28);
    gatt_send_service_changed_ind(param_1);
    return;
}
