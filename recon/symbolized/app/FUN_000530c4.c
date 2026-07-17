#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000530c4 @ 0x000530c4
 * public-name: FUN_000530c4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_set_name_internal                     <= FUN_00054c74 @ 0x00054c74
 *   bt_setup_public_id_addr                  <= FUN_00055330 @ 0x00055330
 * address symbols (name @ address):
 *   rodata_88178                             @ 0x00088178
 *   rodata_9ac7c                             @ 0x0009ac7c
 *   rodata_f2c8c                             @ 0x000f2c8c
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_000530c4 @ 0x530c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_0004d944(u32,int,void*,int);
extern void FUN_000530b4(void);
extern void FUN_000548b8(void);
extern void bt_set_name_internal(u32);
extern int bt_setup_public_id_addr(void);
extern int FUN_000553f8(void);
int FUN_000530c4(void){
    volatile u32* puVar1 = (volatile u32*)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/;
    u32 r3 = *puVar1;
    if((r3 & 1) == 0) return 0;
    if(*(volatile u8*)(((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/ + 0x98) == 0){
        bt_set_name_internal(((unsigned long)&rodata_9ac7c) /*=0x9ac7c*/);
    }
    int iVar2;
    if(*(volatile u8*)(((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/ - 0xcd) == 0){
        iVar2 = bt_setup_public_id_addr();
        if(iVar2 != 0) goto RS;
        if(*(volatile u8*)(((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/ - 0xcd) == 0){
            iVar2 = FUN_000553f8();
            if(iVar2 != 0) goto RS;
        }
    }
    {
        u32 v = *puVar1;
        if((int)(v << 0x1d) >= 0) FUN_000548b8();
        u32 uVar3 = __atomic_fetch_and((u32 *)puVar1, 0xfffeffffu,
                                      __ATOMIC_ACQ_REL);
        if((int)(uVar3 << 0xf) < 0) FUN_000530b4();
    }
    return 0;
RS: ;
    u32 local[2];
    local[0] = 2;
    local[1] = ((unsigned long)&rodata_f2c8c) /*=0xf2c8c*/;
    FUN_0004d944(((unsigned long)&rodata_88178) /*=0x88178*/, 0x1040, local, 0);
    return iVar2;
}
