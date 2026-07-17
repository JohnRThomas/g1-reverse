#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000187e8 @ 0x000187e8
 * public-name: gatt_discover
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   gatt_dm_start                            <= FUN_0004ed8c @ 0x0004ed8c
 *   atomic_and                               <= FUN_0007c08e @ 0x0007c08e
 * address symbols (name @ address):
 *   rodata_88388                             @ 0x00088388
 *   rodata_88a0c                             @ 0x00088a0c
 *   rodata_9a65b                             @ 0x0009a65b
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 *   g_ancs_client                            @ 0x20006ae8
 */
/* Reconstructed FUN_000187e8 @ 0x187e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int get_device_info(void);
extern int is_battery_critical(void);
extern int atomic_and(u32,u32);
extern int gatt_dm_start(u32,void*,u32,u32);
extern void DEBUG_PRINT(u32,int);
void gatt_discover(u32 param_1, int param_2){
    volatile u32* puVar1 = (volatile u32*)((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/;
    char* pcVar2 = (char*)(uintptr_t)get_device_info();
    if(*pcVar2 == 2){
        int iVar3 = is_battery_critical();
        if(iVar3 != 1){
            u32 uVar7 = *puVar1;
            *puVar1 = uVar7 | 1;
            if((uVar7 & 1) == 0){
                u32 v = *puVar1;
                int go_tail = 0;
                if((int)(v << 0x1e) < 0){
                    go_tail = 1;
                } else if(param_2 != 0){
                    iVar3 = atomic_and(((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/, 0xfffffffb);
                    if((int)(iVar3 << 0x1d) >= 0) go_tail = 1;
                }
                if(go_tail){
                    atomic_and(((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/, 0xfffffffe);
                    return;
                }
                u32 local_2c[5];
                u32* src = (u32*)((unsigned long)&rodata_88388) /*=0x88388*/;
                for(int i=0;i<4;i++) local_2c[i] = src[i];
                *(u8*)&local_2c[4] = *(u8*)(src+4);
                iVar3 = gatt_dm_start(param_1, local_2c, ((unsigned long)&rodata_88a0c) /*=0x88a0c*/, ((unsigned long)&g_ancs_client) /*=0x20006ae8*/);
                if(iVar3 != 0){
                    DEBUG_PRINT(((unsigned long)&rodata_9a65b) /*=0x9a65b*/, iVar3);
                    atomic_and(((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/, 0xfffffffe);
                }
            }
        }
    }
}
