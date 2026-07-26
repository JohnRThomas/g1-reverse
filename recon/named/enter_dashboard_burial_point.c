/* readable reconstruction; identity: FUN_0004a9ec @ 0x0004a9ec
 * public-name: enter_dashboard_burial_point
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   enter_dashboard_burial_point             <= FUN_0004a9ec @ 0x0004a9ec
 *   k_uptime_get_10                          <= FUN_0007daa4 @ 0x0007daa4
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 * address symbols (name @ address):
 *   rodata_f038d                             @ 0x000f038d   [INLINED -- G6 literal batch]
 *   rodata_f0475                             @ 0x000f0475   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004a9ec @ 0x4a9ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int get_device_info(void);
extern unsigned get_current_burial_point_type(void);
extern unsigned long long k_uptime_get_10(void);

void enter_dashboard_burial_point(void){
    int iVar1 = get_device_info();
    if (*(char*)(iVar1+0x1092) != 1){
        unsigned uVar2 = get_current_burial_point_type();
        if (uVar2 < 7){
            iVar1=get_device_info(); *(char*)(iVar1+0x1092)=1;
            iVar1=get_device_info(); *(char*)(iVar1+0x1093)=(char)uVar2;
            iVar1=get_device_info(); *(unsigned long long*)(iVar1+0x1094)=k_uptime_get_10();
            iVar1=get_device_info(); { int a = (int)(uVar2*0xc) + iVar1; *(int*)(a+0x113a) += 1; }
            iVar1=get_device_info(); *(int*)(iVar1+0x10d6) += 1;
            if (1 < *(int*)0x2000230c){
                if (*(int*)0x20007554 != 0){
                    iVar1=get_device_info();
                    debug_print(((unsigned long)"%s(): [enter_dashboard_burial_point] start_time is %d\n"),((unsigned long)"enter_dashboard_burial_point"),*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                    return;
                }
                iVar1=get_device_info();
                log_message(((unsigned long)"%s(): [enter_dashboard_burial_point] start_time is %d\n"),((unsigned long)"enter_dashboard_burial_point"),*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                return;
            }
        }
    }
}
