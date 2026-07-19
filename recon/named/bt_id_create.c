/* readable reconstruction; identity: FUN_00055204 @ 0x00055204
 * public-name: bt_id_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   id_find                                  <= FUN_00054ce8 @ 0x00054ce8
 *   bt_id_set_static_random_addr             <= FUN_00054d18 @ 0x00054d18
 *   bt_id_create                             <= FUN_00055204 @ 0x00055204
 *   bt_addr_le_eq                            <= FUN_00080fa4 @ 0x00080fa4
 *   ptr_read_u32                             <= FUN_00080fb4 @ 0x00080fb4
 *   bt_id_addr_update_thunk                  <= FUN_0008104a @ 0x0008104a
 * address symbols (name @ address):
 *   rodata_88150                             @ 0x00088150
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f3705                             @ 0x000f3705
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00055204 @ 0x55204  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int id_find(char*);
extern unsigned bt_id_set_static_random_addr(unsigned,char*);
extern int bt_addr_le_eq(char*,u32);
extern int ptr_read_u32(int);
extern void bt_id_addr_update_thunk(u32,int,void*);
unsigned bt_id_create(char* param_1, int param_2){
    u32 local_18[2];
    if(param_1 != 0){
        int fa = bt_addr_le_eq(param_1, 0x000f2b3a);
        if(fa == 0){
            if(*param_1 != 1 || (param_1[6] & 0xc0) != 0xc0){
                local_18[0] = 2; local_18[1] = 0x000f3705;
                bt_id_addr_update_thunk(0x00088150, 0x1040, local_18);
                return 0xffffffea;
            }
            int c = id_find(param_1);
            if(c >= 0) return 0xffffff88;
        }
    }
    if(param_2 != 0) return 0xffffffea;
    if(*(volatile char*)(0x20002000UL+7) == 1) return 0xfffffff4;
    int iVar3 = ptr_read_u32(0x20002000+0xd4);
    if((int)(iVar3 << 0x1f) < 0 || (param_1 != 0 && bt_addr_le_eq(param_1, 0x000f2b3a) == 0)){
        u8 bVar1 = *(volatile u8*)(0x20002000UL+7);
        *(volatile u8*)(0x20002000UL+7) = bVar1 + 1;
        unsigned uVar4 = bt_id_set_static_random_addr(bVar1, param_1);
        if(uVar4 != 0){
            *(volatile char*)(0x20002000UL+7) = *(volatile char*)(0x20002000UL+7) - 1;
            return uVar4;
        }
        return bVar1;
    }
    return 0xffffffea;
}
