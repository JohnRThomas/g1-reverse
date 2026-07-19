#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055350 @ 0x00055350
 * public-name: hci_read_static_addresses
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   hci_read_static_addresses                <= FUN_00055350 @ 0x00055350
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_id_addr_update_thunk                  <= FUN_0008104a @ 0x0008104a
 * address symbols (name @ address):
 *   rodata_fc09                              @ 0x0000fc09
 *   rodata_88150                             @ 0x00088150
 *   rodata_f376a                             @ 0x000f376a
 *   rodata_f3796                             @ 0x000f3796
 *   rodata_f37b6                             @ 0x000f37b6
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00055350 @ 0x55350  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
extern int bt_hci_cmd_send_sync(int,int,void*);
extern void net_buf_unref(void*);
extern void bt_id_addr_update_thunk(u32,int,void*);
unsigned hci_read_static_addresses(int param_1, unsigned param_2){
    u32 local_34[5];
    u32 local_20[2];
    volatile u32 local_1c;
    int iVar1;
    local_1c = ((unsigned long)&rodata_f376a) /*=0xf376a*/;
    if( ((int)((u32)(*(volatile u8*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/+0xc2)) << 0x1f) < 0)
        && (iVar1 = bt_hci_cmd_send_sync(((unsigned long)&rodata_fc09) /*=0xfc09*/, 0, local_34), local_1c = ((unsigned long)&rodata_f3796) /*=0xf3796*/, iVar1 == 0) ){
        unsigned uVar5 = *(u8*)(*(int*)(local_34[0]+0xc)+1);
        u32* puVar4 = (u32*)(*(int*)(local_34[0]+0xc)+2);
        iVar1 = 0;
        if(param_2 <= uVar5) uVar5 = param_2;
        for(; iVar1 < (int)uVar5; iVar1++){
            u32* puVar2 = puVar4;
            u32* puVar6 = (u32*)(iVar1*0x16 + param_1);
            u32 *puVar3, *puVar7;
            do {
                puVar3 = puVar2+1;
                puVar7 = puVar6+1;
                *puVar6 = *puVar2;
                puVar2 = puVar3;
                puVar6 = puVar7;
            } while(puVar3 != puVar4+5);
            *(u16*)puVar7 = *(u16*)puVar3;
            puVar4 = (u32*)((int)puVar4 + 0x16);
        }
        net_buf_unref((void *)(uintptr_t)local_34[0]);
        if(uVar5 == 0){
            local_1c = ((unsigned long)&rodata_f37b6) /*=0xf37b6*/;
            local_20[0] = 2;
            bt_id_addr_update_thunk(((unsigned long)&rodata_88150) /*=0x88150*/, 0x1080, local_20);
        }
        return uVar5;
    } else {
        local_20[0] = 2;
        bt_id_addr_update_thunk(((unsigned long)&rodata_88150) /*=0x88150*/, 0x1080, local_20);
        return 0;
    }
}
