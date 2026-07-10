#include "g1_app_symbols.h"
/* named: gatt_remove_peer_from_attr */
/* globals referenced:
//   0x20002a20  g_bt_gatt_sc_ccc             
*/
/* Reconstructed gatt_remove_peer_from_attr @ 0x5a3c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
typedef void (*fp)(int);
extern void ble_conn_unref(void);
extern int bt_conn_lookup_addr_le(int,void*);
extern void sc_clear(int);
extern int bt_addr_le_is_bonded(int,int);
extern int bt_conn_is_peer_addr_le(int,int,void*);
extern void FUN_000828da(void*,u32);
u32 gatt_remove_peer_from_attr(int param_1, u32 param_2, int param_3){
    if( (*(int*)(param_1+8) == ((uintptr_t)&tbl_5a458) /*=0x5a465*/)
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
                    if(puVar2 == (u8*)((uintptr_t)&g_bt_gatt_sc_ccc) /*=0x20002a20*/) sc_clear(param_3);
                    FUN_000828da(puVar3, ((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/);
                    *puVar2 = 0;
                    *(u16*)(puVar2+8) = 0;
                } else {
                    FUN_000828da(puVar3, param_3+0x90);
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

