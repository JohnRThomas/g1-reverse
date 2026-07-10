#include "g1_app_symbols.h"
/* named: local_store_write */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed local_store_write @ 0x22168  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern void DEBUG_PRINT(u32,u32,u32,u32);
extern void debug_print(u32,u32,u32,u32);
extern int settings_save_one(void*,u32,u32);
extern void memset_bytes(void*,int,int);
extern void __strcat_chk(void*,u32,int);
u32 local_store_write(u32 param_1, u32 param_2, u32 param_3){
    u32 local_98[8];
    u8 auStack_7c[100];
    u32* src = (u32*)"ar_glass_userdata_settings/" /*=0x9e145*/;
    u32* dst = local_98;
    do { u32 a=src[0],b=src[1]; src+=2; dst[0]=a; dst[1]=b; dst+=2; } while(src != (u32*)"ar_glass_userdata_settings/" /*=0x9e145*/ + 6);
    *dst = *src;
    memset_bytes(auStack_7c, 0, 100);
    __strcat_chk(local_98, param_1, 0x80);
    int iVar2 = settings_save_one(local_98, param_2, param_3);
    u32 uVar1;
    if(iVar2 == 0){
        if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 3) return 0;
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar1 = "%s(): save success:[%s], len=%d\n" /*=0x9e187*/;
    } else {
        if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) return 0;
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar1 = "%s(): failed to store key: %s --- %d\n" /*=0x9e161*/;
    }
    if(iVar2 == 0){
        DEBUG_PRINT(uVar1, "local_store_write" /*=0x9e553*/, param_1, param_3);
    } else {
        debug_print(uVar1, "local_store_write" /*=0x9e553*/, param_1, param_3);
    }
    return 0;
}

