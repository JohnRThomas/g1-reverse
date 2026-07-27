#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a464 @ 0x0005a464
 * public-name: gatt_ccc_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ccc_match_conn_cfg                       <= FUN_00059c48 @ 0x00059c48
 *   gatt_delayed_store_enqueue               <= FUN_00059d24 @ 0x00059d24
 *   gatt_ccc_write                           <= FUN_0005a464 @ 0x0005a464
 *   gatt_ccc_changed                         <= FUN_000825c0 @ 0x000825c0
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f486f                             @ 0x000f486f
 */
/* Reconstructed FUN_0005a464 @ 0x5a464  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ccc_match_conn_cfg(int,int);
extern void gatt_delayed_store_enqueue(int,int,int);
extern void gatt_ccc_changed(int,int);
extern void bt_addr_le_copy_828da(void*, const void*);
extern void log_msg_create_3arg(uint32_t,int,void*);

int gatt_ccc_write(int param_1, int param_2, uint16_t *param_3, int param_4, short param_5){
    int iVar5 = *(volatile int*)(param_2+0xc);
    uint32_t local_28, local_24;
    if (param_5 == 0){
        if ((uint32_t)(param_4 - 1) < 2){
            uint16_t uVar4 = (uint16_t)(uint8_t)*(volatile uint8_t*)param_3;
            if (param_4 != 1) uVar4 = *(volatile uint16_t*)param_3;
            volatile uint8_t *puVar2 = (volatile uint8_t*)ccc_match_conn_cfg(param_1, iVar5);
            if (puVar2 == 0){
                if (uVar4 == 0) return param_4;
                puVar2 = (volatile uint8_t*)ccc_match_conn_cfg(0, iVar5);
                if (puVar2 == 0){
                    local_24 = ((unsigned long)&rodata_f486f) /*=0xf486f*/; local_28 = 2;
                    log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1080, &local_28);
                    return -0x11;
                }
                bt_addr_le_copy_828da((void*)(puVar2+1), param_1+0x90);
                *puVar2 = *(volatile uint8_t*)(param_1+8);
            }
            {
                volatile uint32_t *cp = (volatile uint32_t*)(iVar5+0x10);
                if (*cp != 0){
                    int iVar3 = ((int(*)(int,int,uint16_t))(*cp))(param_1,param_2,uVar4);
                    if (iVar3 < 0) return iVar3;
                    if ((uint32_t)(iVar3 - 1) > 1) return -0xe;
                }
            }
            uint16_t uVar1 = *(volatile uint16_t*)(puVar2+8);
            *(volatile uint16_t*)(puVar2+8) = uVar4;
            if (*(volatile uint16_t*)(iVar5+10) != uVar4) gatt_ccc_changed(param_2, iVar5);
            if (uVar1 != uVar4) gatt_delayed_store_enqueue(*(volatile uint8_t*)(param_1+8), param_1+0x90, 0);
            if (uVar4 == 0){
                bt_addr_le_copy_828da((void*)(puVar2+1), ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
                *puVar2 = 0;
                *(volatile uint16_t*)(puVar2+8) = 0;
            }
        } else param_4 = -0xd;
    } else param_4 = -7;
    return param_4;
}
