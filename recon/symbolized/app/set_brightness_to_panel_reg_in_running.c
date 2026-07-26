#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047058 @ 0x00047058
 * public-name: set_brightness_to_panel_reg_in_running
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   panel_write_xy_reg_cached                <= FUN_00047028 @ 0x00047028
 *   set_brightness_to_panel_reg_in_running   <= FUN_00047058 @ 0x00047058
 *   thunk_FUN_0007d77c                       <= FUN_0007d63e @ 0x0007d63e
 *   projector_send_cmd1                      <= FUN_0007d642 @ 0x0007d642
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 * address symbols (name @ address):
 *   rodata_d7251                             @ 0x000d7251   [INLINED -- G6 literal batch]
 *   rodata_d72e9                             @ 0x000d72e9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00047058 @ 0x47058  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void log_message(uint32_t, ...);
extern int get_device_info(void);
extern void debug_print(uint32_t, ...);
extern void panel_write_xy_reg_cached(int,int);
extern void projector_send_cmd1(int,int);
extern void thunk_FUN_0007d77c(int);
extern void delay_ms(int);
void set_brightness_to_panel_reg_in_running(uint param_1){
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): set brightness level = %d\n") /*=0xd7251*/, ((unsigned long)"set_brightness_to_panel_reg_in_running") /*=0xd72e9*/, param_1,
                        *(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
        else
            debug_print(((unsigned long)"%s(): set brightness level = %d\n") /*=0xd7251*/, ((unsigned long)"set_brightness_to_panel_reg_in_running") /*=0xd72e9*/, param_1,
                         *(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
    }
    int iVar2=get_device_info();
    if(*(volatile int*)(iVar2+0xec8)==0) return;
    short sVar4=0; uint uVar5=0;
    if(param_1>5){
        iVar2=get_device_info();
        sVar4=(short)((*(volatile short*)(iVar2+0xed8)+1)*0x6f);
        uVar5=(param_1-6)&0xff;
    } else {
        iVar2=get_device_info();
        uint64_t uVar1=((uint64_t)*(volatile uint16_t*)(iVar2+0xed8)<<1)/9;
        int iv=(int)uVar1;
        int need96=(iv==0);
        if(!need96){
            int iVar3=get_device_info();
            if(*(volatile uint16_t*)(iVar3+0xed8)<6) need96=1;
            else{ iVar3=get_device_info();
                sVar4=(short)((short)(((int)(param_1*((uint)*(volatile uint16_t*)(iVar3+0xed8)-iv))/6)+(short)uVar1)*0x6f); }
        }
        if(need96){ iVar2=get_device_info();
            sVar4=(short)(((short)((param_1*0x6f)/6)+1)*(*(volatile short*)(iVar2+0xed8)+1)); }
        uVar5=0;
    }
    thunk_FUN_0007d77c(6); thunk_FUN_0007d77c(0xa9);
    panel_write_xy_reg_cached(sVar4,uVar5); projector_send_cmd1(0x31,4);
    thunk_FUN_0007d77c(0xa3); thunk_FUN_0007d77c(0x97);
    delay_ms(1);
}
