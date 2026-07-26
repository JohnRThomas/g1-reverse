/* readable reconstruction; identity: FUN_00047260 @ 0x00047260
 * public-name: reflash_fb_data_to_lcd
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 * address symbols (name @ address):
 *   rodata_aa891                             @ 0x000aa891
 *   rodata_d7383                             @ 0x000d7383   [INLINED -- G6 literal batch]
 *   rodata_d7441                             @ 0x000d7441   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_projector_bus_lock                     @ 0x2000a060
 */
/* Reconstructed FUN_00047260 @ 0x47260  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_message(int,...);
extern int debug_print(int, int);
extern int k_mutex_lock(int,...);
extern int k_mutex_unlock(int,...);
extern long long get_projector_controller(void);
extern int delay_ms(int,...);
extern int projector_send_cmd_immediate(int,...);

unsigned reflash_fb_data_to_lcd(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
    unsigned char uVar1; int iVar2; unsigned uVar3; int iVar4; unsigned uVar5,uVar6;
    unsigned lock_arg;
    int iVar7,iVar8,iVar9,iVar10;
    unsigned char local_38[4]; unsigned local_34; unsigned local_30; unsigned char local_2c;

    local_38[0] = 0;
    {
        unsigned long long context_result = (unsigned long long)get_projector_controller();
        iVar2 = (int)context_result;
        lock_arg = (unsigned)(context_result >> 32);
    }
    if(*(int*)(iVar2+0x35c) == 0){
        if(0 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0){
                log_message(0x000aa891, ((unsigned long)"_reflash_fb_data_to_lcd"));
            } else { debug_print(0x000aa891, ((unsigned long)"_reflash_fb_data_to_lcd")); }
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
            volatile unsigned char *pixel = (volatile unsigned char *)iVar8;
            local_2c = *(unsigned char*)(iVar8+4);
            local_30 = *(unsigned*)(iVar10+iVar9);
            uVar6 = 0x0007fc00 & (unsigned)((param_2+param_4)*0x400);
            local_34 = uVar6 | uVar5;
            pixel[0] = 2;
            pixel[1] = (unsigned char)(uVar6>>0x10);
            pixel[2] = (unsigned char)(local_34>>8);
            pixel[3] = (unsigned char)uVar5;
            pixel[4] = 0xff;
            uVar1 = *(unsigned char*)(iVar8+iVar7);
            *(unsigned char*)(iVar8+iVar7) = 0;
            k_mutex_lock(0x2000a060, lock_arg, -1, -1);
            iVar4 = (*(int(**)(int,...))(*(int*)(iVar2+0x374)+8))(*(int*)(iVar2+0x374), iVar8, iVar7, (int)local_38, 1);
            k_mutex_unlock(0x2000a060);
            if(iVar4 != 0 && 0 < *(volatile int*)0x2000230c){
                if(*(volatile int*)0x20007554 == 0){
                    log_message(((unsigned long)"%s(): spi transfer error....\n"), ((unsigned long)"_reflash_fb_data_to_lcd"));
                } else { debug_print(((unsigned long)"%s(): spi transfer error....\n"), ((unsigned long)"_reflash_fb_data_to_lcd")); }
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
