/* named: gatt_discover */
/* globals referenced:
//   0x20006ab4  g_gatt_discovery_flags       
//   0x20006ae8  g_ancs_client                
*/
/* Reconstructed gatt_discover @ 0x187e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int get_device_info(void);
extern int is_battery_critical(void);
extern int atomic_and(u32,u32);
extern int gatt_dm_start(u32,void*,u32,u32);
extern void DEBUG_PRINT(u32,int);
void gatt_discover(u32 param_1, int param_2){
    volatile u32* puVar1 = (volatile u32*)0x20006ab4UL;
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
                    iVar3 = atomic_and(0x20006ab4, 0xfffffffb);
                    if((int)(iVar3 << 0x1d) >= 0) go_tail = 1;
                }
                if(go_tail){
                    atomic_and(0x20006ab4, 0xfffffffe);
                    return;
                }
                u32 local_2c[5];
                u32* src = (u32*)0x00088388;
                for(int i=0;i<4;i++) local_2c[i] = src[i];
                *(u8*)&local_2c[4] = *(u8*)(src+4);
                iVar3 = gatt_dm_start(param_1, local_2c, 0x00088a0c, 0x20006ae8);
                if(iVar3 != 0){
                    DEBUG_PRINT(0x0009a65b, iVar3);
                    atomic_and(0x20006ab4, 0xfffffffe);
                }
            }
        }
    }
}

