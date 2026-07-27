#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a3c4 @ 0x0005a3c4
 * public-name: gatt_remove_peer_from_attr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_addr_le                   <= FUN_00056e74 @ 0x00056e74
 *   sc_clear                                 <= FUN_0005a090 @ 0x0005a090
 *   gatt_remove_peer_from_attr               <= FUN_0005a3c4 @ 0x0005a3c4
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   bt_conn_is_peer_addr_le                  <= FUN_000814e6 @ 0x000814e6
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   ADDR_gatt_ccc_write_THUMB                @ 0x0005a465
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_bt_gatt_sc_ccc                         @ 0x20002a20
 */
/* Reconstructed FUN_0005a3c4 @ 0x5a3c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
typedef void (*fp)(int);
extern void ble_conn_unref(void);
extern int bt_conn_lookup_addr_le(int, void*);
extern void sc_clear(int);
extern int bt_addr_le_is_bonded(unsigned char, const void*);
extern int bt_conn_is_peer_addr_le(int,int,void*);
extern void bt_addr_le_copy_828da(void*, const void*);
u32 gatt_remove_peer_from_attr(int param_1, u32 param_2, int param_3){
    if( (*(int*)(param_1+8) == ADDR_gatt_ccc_write_THUMB /*=0x5a465*/)
        && (({u8* puVar2 = *(u8**)(param_1+0xc); *(short*)(puVar2+10) != 0;})) ){
        u8* puVar2 = *(u8**)(param_1+0xc);
        if(*(short*)(puVar2+8) != 0){
            u8* puVar3 = puVar2+1;
            int iVar1 = bt_conn_is_peer_addr_le(param_3, *puVar2, puVar3);
            if(iVar1 == 0){
                iVar1 = bt_conn_lookup_addr_le(*puVar2, puVar3);
                if(iVar1 != 0){
                    if(*(char*)(iVar1+0xd) == 7){ ble_conn_unref(); return 1; }
                    ble_conn_unref();
                }
            } else {
                iVar1 = bt_addr_le_is_bonded(*(u8*)(param_3+8), param_3+0x90);
                if(iVar1 == 0){
                    if(puVar2 == (u8*)((unsigned long)&g_bt_gatt_sc_ccc) /*=0x20002a20*/) sc_clear(param_3);
                    bt_addr_le_copy_828da(puVar3, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
                    *puVar2 = 0;
                    *(u16*)(puVar2+8) = 0;
                } else {
                    bt_addr_le_copy_828da(puVar3, param_3+0x90);
                }
            }
        }
        *(u16*)(puVar2+10) = 0;
        if(*(fp*)(puVar2+0xc) != 0){
            (*(fp*)(puVar2+0xc))(param_1);
        }
    }
    return 1;
}
