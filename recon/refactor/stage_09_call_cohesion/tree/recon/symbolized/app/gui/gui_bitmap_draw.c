#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00043a68 @ 0x00043a68
 * public-name: gui_bitmap_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_bitmap_draw                          <= FUN_00043a68 @ 0x00043a68
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 * address symbols (name @ address):
 *   rodata_aa96d                             @ 0x000aa96d
 *   rodata_aacde                             @ 0x000aacde   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_00043a68 @ 0x43a68  (parity: 299/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
#include "../../../headers/g1_dedupe.h"
typedef unsigned uint; typedef unsigned char byte; typedef unsigned long long ulonglong;
extern int get_device_info(int,...);
extern int atomic_get_3_0(void);
extern int clean_fb_data(int,...);
extern int reflash_fb_data_to_lcd(int,...);

unsigned gui_bitmap_draw(uint param_1,int param_2,int param_3,int param_4,int param_5,byte param_6)
{
    uint uVar1; byte bVar2; int *piVar3; uint uVar4; int iVar5; uint uVar6; int iVar7,iVar8;
    uint uVar9; unsigned uVar10; byte *pbVar11; uint uVar12; int iVar13; ulonglong uVar14;
    unsigned local_2c[2];
    uVar9 = (uint)param_6;
    if((param_3 < (int)param_1) || (param_4 < param_2) || (0xf < uVar9)){
        if(*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) return 0xffffffff;
        iVar7 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar10 = ((unsigned long)&rodata_aa96d) /*=0xaa96d*/;
    } else {
        if((param_1 & 1) == 0){
            iVar7 = param_3;
            uVar14 = (ulonglong)atomic_get_3_0();
            piVar3 = (int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/;
            if((uVar14 & 2) != 0){
                clean_fb_data(*(volatile int *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, 0, param_1 - 2, param_2, iVar7 + 2, param_4);
            }
            uVar1 = (uint)((int)(param_3 - param_1) >> 3);
            iVar7 = *piVar3;
            iVar13 = 0;
            for(iVar8 = 0; iVar8 < param_4 - param_2; iVar8 = iVar8 + 1){
                pbVar11 = (byte*)(param_5 + iVar13);
                for(iVar5 = 0; iVar5 < (int)uVar1; iVar5 = iVar5 + 1){
                    bVar2 = *pbVar11;
                    uVar4 = 0;
                    local_2c[0] = 0;
                    uVar6 = 0;
                    do {
                        if((((int)(uint)bVar2 >> (uVar6 & 0xff)) & 1U) != 0){
                            if((uVar6 & 1U) != 0){ uVar4 = uVar4 | uVar9; }
                            else { uVar4 = uVar4 | ((uVar9 & 0xf) << 4); }
                        }
                        uVar12 = uVar6 + 1;
                        if((uVar12 & 1) == 0){
                            *(char*)((int)local_2c + ((int)uVar6 >> 1)) = (char)uVar4;
                            uVar4 = 0;
                        }
                        uVar6 = uVar12;
                    } while(uVar12 != 8);
                    *(unsigned*)(*(int*)(iVar7 + param_2*4 + iVar8*4) + iVar5*4 + (int)param_1/2) = local_2c[0];
                    pbVar11 = pbVar11 + 1;
                }
                iVar13 = iVar13 + (uVar1 & ~((int)(param_3 - param_1) >> 0x1f));
            }
            iVar7 = (int)atomic_get_3_0();
            if(((uint32_t)iVar7 & 2U) != 0){
                iVar7 = get_device_info(0);
                uVar10 = *(unsigned*)(iVar7 + 0xeb4);
                iVar7 = get_device_info(0);
                reflash_fb_data_to_lcd(uVar10, *(unsigned*)(iVar7+0xeb8), param_1-2, param_2, param_3+2, param_4);
                return 0;
            }
            return 0;
        }
        if(*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) return 0xffffffff;
        iVar7 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar10 = 0x000aa9a3;
    }
    G1_LOG_ROUTE(iVar7 == 0, uVar10, ((unsigned long)"gui_bitmap_draw") /*=0xaacde*/);
    return 0xffffffff;
}
