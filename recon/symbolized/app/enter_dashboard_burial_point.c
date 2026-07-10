#include "g1_app_symbols.h"
/* named: enter_dashboard_burial_point */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed enter_dashboard_burial_point @ 0x4a9ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern unsigned get_current_burial_point_type(void);
extern unsigned long long k_uptime_get_10(void);
extern void debug_print(unsigned,unsigned,unsigned,unsigned);
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,unsigned);

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
            if (1 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
                if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0){
                    iVar1=get_device_info();
                    debug_print("%s(): [enter_dashboard_burial_point] start_time is %d\n" /*=0xf038d*/,"enter_dashboard_burial_point" /*=0xf0475*/,*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                    return;
                }
                iVar1=get_device_info();
                DEBUG_PRINT("%s(): [enter_dashboard_burial_point] start_time is %d\n" /*=0xf038d*/,"enter_dashboard_burial_point" /*=0xf0475*/,*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                return;
            }
        }
    }
}

