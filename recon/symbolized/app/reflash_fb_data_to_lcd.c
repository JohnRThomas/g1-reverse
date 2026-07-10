#include "g1_app_symbols.h"
/* named: reflash_fb_data_to_lcd */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a060  g_projector_bus_lock         
*/
/* Reconstructed reflash_fb_data_to_lcd @ 0x47260  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int debug_print(void);
extern int k_mutex_lock(int,...);
extern int k_mutex_unlock(int,...);
extern int get_projector_controller(void);
extern int delay_ms(int,...);
extern int projector_send_cmd_immediate(int,...);

unsigned reflash_fb_data_to_lcd(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
    unsigned char uVar1; int iVar2; unsigned uVar3; int iVar4; unsigned uVar5,uVar6;
    int iVar7,iVar8,iVar9,iVar10;
    unsigned char local_38[4]; unsigned local_34; unsigned local_30; unsigned char local_2c;

    local_38[0] = 0;
    iVar2 = get_projector_controller();
    if(*(int*)(iVar2+0x35c) == 0){
        if(0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
            if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                DEBUG_PRINT("%s(): c->init_done = 0,init failed, can't write data!\n" /*=0xaa891*/, "_reflash_fb_data_to_lcd" /*=0xd7441*/);
            } else { debug_print(); }
        }
        uVar3 = 0xffffffff;
    } else {
        if(199 < param_6) param_6 = 200;
        if(0x27f < param_5) param_5 = 0x280;
        iVar7 = (5 - param_3/2) + param_5/2;
        uVar5 = (param_3 + param_1) & 0x3ff;
        for(; param_4 <= param_6; param_4 = param_4 + 1){
            iVar10 = *(int*)(iVar2+0x344);
            iVar9 = param_4*0x140 + param_3/2 - 5;
            iVar8 = iVar10 + iVar9;
            local_2c = *(unsigned char*)(iVar8+4);
            local_30 = *(unsigned*)(iVar10+iVar9);
            uVar6 = ((uintptr_t)&rodata_7fc00) /*=0x7fc00*/ & (unsigned)((param_2+param_4)*0x400);
            local_34 = uVar6 | uVar5;
            *(unsigned char*)(iVar10+iVar9) = 2;
            *(char*)(iVar8+1) = (char)(uVar6>>0x10);
            *(char*)(iVar8+2) = (char)(local_34>>8);
            *(char*)(iVar8+3) = (char)uVar5;
            *(unsigned char*)(iVar8+4) = 0xff;
            uVar1 = *(unsigned char*)(iVar8+iVar7);
            *(unsigned char*)(iVar8+iVar7) = 0;
            k_mutex_lock(((uintptr_t)&g_projector_bus_lock) /*=0x2000a060*/);
            iVar4 = (*(int(**)(int,...))(*(int*)(iVar2+0x374)+8))(*(int*)(iVar2+0x374), iVar8, iVar7, (int)local_38, 1);
            k_mutex_unlock(((uintptr_t)&g_projector_bus_lock) /*=0x2000a060*/);
            if(iVar4 != 0 && 0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
                if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                    DEBUG_PRINT("%s(): spi transfer error....\n" /*=0xd7383*/, "_reflash_fb_data_to_lcd" /*=0xd7441*/);
                } else { debug_print(); }
            }
            *(unsigned char*)(iVar8+iVar7) = uVar1;
            *(unsigned*)(iVar10+iVar9) = local_30;
            *(unsigned char*)(iVar8+4) = local_2c;
        }
        projector_send_cmd_immediate(0x97);
        delay_ms(1);
        uVar3 = 0;
    }
    return uVar3;
}

