#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057cc4 @ 0x00057cc4
 * public-name: bt_l2cap_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_recv                            <= FUN_00057cc4 @ 0x00057cc4
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   k_work_submit                            <= FUN_00072fdc @ 0x00072fdc
 *   bt_l2cap_le_lookup_rx_cid                <= FUN_00081aca @ 0x00081aca
 *   gatt_send_service_changed_ind            <= FUN_00081b30 @ 0x00081b30
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 */
/* Reconstructed FUN_00057cc4 @ 0x57cc4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00057b60(int);
extern void net_buf_put(int,int);
extern void net_buf_unref(int);
extern int  net_buf_simple_pull_5f594(int,int);
extern void k_work_submit(int);
extern int  FUN_000816a2(int);
extern void FUN_00081746(int,int,void*);
extern int  bt_l2cap_le_lookup_rx_cid(uint32_t,uint16_t);
extern void gatt_send_service_changed_ind(void);
typedef void (*fp_t)(int,int);
void bt_l2cap_recv(uint32_t param_1, int param_2, int param_3){
    uint32_t stackbuf[8];
    if (*(volatile uint16_t*)(param_2+0x10) < 4){
        FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1040, stackbuf);
        net_buf_unref(param_2); return;
    }
    int iVar1 = net_buf_simple_pull_5f594(param_2+0xc, 4);
    iVar1 = bt_l2cap_le_lookup_rx_cid(param_1, *(volatile uint16_t*)(iVar1+2));
    if (iVar1 == 0){
        FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1880, stackbuf);
        net_buf_unref(param_2); return;
    }
    if ((uint16_t)(*(volatile uint16_t*)(iVar1+0x14) - 0x40) > 0x3f){
        (*(volatile fp_t*)(*(volatile int*)(iVar1+4)+0x14))(iVar1, param_2);
        net_buf_unref(param_2); return;
    }
    if (param_3 == 0){
        gatt_send_service_changed_ind();
        net_buf_unref(param_2); return;
    }
    if (*(volatile uint8_t*)(iVar1+0xb4) != 4){
        int iVar2 = FUN_000816a2(iVar1+0x10);
        if ((iVar2 << 0x1e) >= 0){
            if ((uint16_t)(*(volatile uint16_t*)(iVar1+0xb6) - 0x80) <= 0x7f){
                net_buf_put(iVar1+0x98, param_2);
                k_work_submit(iVar1+0x88); return;
            }
            FUN_00057b60(iVar1);
            net_buf_unref(param_2); return;
        }
    }
    FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1080, stackbuf);
    net_buf_unref(param_2); return;
}
