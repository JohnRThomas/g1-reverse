#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004396c @ 0x0004396c
 * public-name: gui_verticalLine_process_bar
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_verticalLine_process_bar             <= FUN_0004396c @ 0x0004396c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 * address symbols (name @ address):
 *   rodata_aa96d                             @ 0x000aa96d
 *   rodata_aacee                             @ 0x000aacee   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_0004396c @ 0x4396c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned int uint;
extern int get_device_info(void);
extern int64_t atomic_get_3_0(void);
extern void gui_bmp_bitmap_draw(int,int,int,int,int,int);
extern void clean_fb_data(int,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(int,int,int,int,int,int);
uint32_t gui_verticalLine_process_bar(uint param_1,int param_2,uint param_3,int param_4,uint32_t param_5,uint8_t param_6){
    uint32_t uVar1;
    if(param_1==param_3 && param_2<=param_4){
        uint uVar4=param_6;
        uint8_t uVar5=((param_1&1)==0)?0xf0:0xf;
        if(uVar4>99) uVar4=100;
        int64_t uVar6=atomic_get_3_0();
        if((uVar6&2)!=0) clean_fb_data(*(volatile int *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,0,param_1-6,(int)((uint64_t)uVar6>>32),param_1+6,param_4);
        int piVar3=*(volatile int *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/ + param_2*4;
        for(int i=0;i<param_4-param_2;i++){
            *(volatile uint8_t *)(*(volatile int *)piVar3 + (int)param_1/2)=uVar5;
            piVar3+=4;
        }
        int iVar2=(int)atomic_get_3_0();
        if((iVar2<<0x1e)<0){
            iVar2=get_device_info(); uint32_t u=*(volatile uint32_t *)(iVar2+0xeb4);
            iVar2=get_device_info();
            reflash_fb_data_to_lcd(u,*(volatile uint32_t *)(iVar2+0xeb8),param_1-6,param_2-0xe,param_3+6,param_4+0xe);
        }
        uVar1=0;
        gui_bmp_bitmap_draw(0x17,param_1-4,(int)(uVar4*((param_4-param_2)-0xd))/100+param_2,0,0,0);
    } else {
        if(*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/>1){
            if(*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) log_message(((unsigned long)&rodata_aa96d) /*=0xaa96d*/,((unsigned long)"gui_verticalLine_process_bar") /*=0xaacee*/,param_3,0,param_1,param_2,param_3);
            else debug_print(((unsigned long)&rodata_aa96d) /*=0xaa96d*/,((unsigned long)"gui_verticalLine_process_bar") /*=0xaacee*/,param_3,
                              *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/,
                              param_1,param_2,param_3);
        }
        uVar1=0xffffffff;
    }
    return uVar1;
}
