#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000473c8 @ 0x000473c8
 * public-name: reflash_fb_data_to_lcd_ex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   reflash_fb_data_to_lcd_ex                <= FUN_000473c8 @ 0x000473c8
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 * address symbols (name @ address):
 *   rodata_aa891                             @ 0x000aa891
 *   rodata_d7383                             @ 0x000d7383
 *   rodata_d7426                             @ 0x000d7426
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_projector_bus_lock                     @ 0x2000a060
 */
/* Reconstructed FUN_000473c8 @ 0x473c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned long long u64;
extern long long DEBUG_PRINT(int,...);
extern long long debug_print(int,...);
extern int k_mutex_lock(int,...);
extern int k_mutex_unlock(int,...);
extern int get_projector_controller(int,...);
extern int delay_ms(int,...);
extern int projector_send_cmd_immediate(int,...);

unsigned reflash_fb_data_to_lcd_ex(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)
{
    unsigned char uVar1; int iVar2; unsigned uVar3; int iVar4; unsigned uVar5,uVar6;
    int iVar7,iVar8,iVar9,iVar10;
    unsigned char local_38[4]; unsigned local_34; unsigned local_30; unsigned char local_2c;

    local_38[0] = 0;
    iVar2 = get_projector_controller(0);
    if(*(int*)(iVar2+0x35c) == 0){
        if(0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ DEBUG_PRINT(((unsigned long)&rodata_aa891) /*=0xaa891*/,((unsigned long)&rodata_d7426) /*=0xd7426*/); }
            else { debug_print(((unsigned long)&rodata_aa891) /*=0xaa891*/, ((unsigned long)&rodata_d7426) /*=0xd7426*/); }
        }
        uVar3 = 0xffffffff;
    } else {
        uVar3 = 0x140;
        if(199 < param_6) param_6 = 200;
        if(0x27f < param_5) param_5 = 0x280;
        iVar9 = (5 - param_3/2) + param_5/2;
        uVar5 = (param_3 + param_1) & 0x3ff;
        for(; param_4 <= param_6; param_4 = param_4 + 1){
            iVar10 = *(int*)(iVar2+0x344);
            iVar8 = param_4*0x140 + param_7*0x140 + param_3/2 - 5;
            iVar7 = iVar10 + iVar8;
            volatile unsigned char *pixel = (volatile unsigned char *)iVar7;
            local_2c = *(unsigned char*)(iVar7+4);
            local_30 = *(unsigned*)(iVar10+iVar8);
            uVar6 = 0x0007fc00 & (unsigned)((param_4+param_2)*0x400);
            local_34 = uVar6 | uVar5;
            pixel[0] = 2;
            pixel[1] = (unsigned char)(uVar6>>0x10);
            pixel[2] = (unsigned char)(local_34>>8);
            pixel[3] = (unsigned char)uVar5;
            pixel[4] = 0xff;
            uVar1 = *(unsigned char*)(iVar7+iVar9);
            *(unsigned char*)(iVar7+iVar9) = 0;
            k_mutex_lock(((unsigned long)&g_projector_bus_lock) /*=0x2000a060*/, uVar3, 0xffffffff, 0xffffffff);
            long long ret = (*(long long(**)(int,...))(*(int*)(iVar2+0x374)+8))(*(int*)(iVar2+0x374), iVar7, iVar9, (int)local_38, 1);
            iVar4 = (int)ret;
            k_mutex_unlock(((unsigned long)&g_projector_bus_lock) /*=0x2000a060*/);
            uVar3 = (unsigned)((u64)ret >> 32);
            if(iVar4 != 0 && 0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
                if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                    uVar3 = (unsigned)((u64)DEBUG_PRINT(((unsigned long)&rodata_d7383) /*=0xd7383*/,((unsigned long)&rodata_d7426) /*=0xd7426*/) >> 32);
                } else {
                    uVar3 = (unsigned)((u64)debug_print(((unsigned long)&rodata_d7383) /*=0xd7383*/, ((unsigned long)&rodata_d7426) /*=0xd7426*/) >> 32);
                }
            }
            *(unsigned char*)(iVar7+iVar9) = uVar1;
            *(unsigned*)(iVar10+iVar8) = local_30;
            *(unsigned char*)(iVar7+4) = local_2c;
        }
        projector_send_cmd_immediate(0x97);
        delay_ms(1);
        uVar3 = 0;
    }
    return uVar3;
}
