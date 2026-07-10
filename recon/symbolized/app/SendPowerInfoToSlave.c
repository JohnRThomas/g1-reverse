#include "g1_app_symbols.h"
/* named: SendPowerInfoToSlave */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed SendPowerInfoToSlave @ 0x488bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int k_msgq_put(uint32_t, void*, int, int);
extern void memset_bytes(void*, int, int);

unsigned int SendPowerInfoToSlave(int param_1)
{
    unsigned char uVar1;
    unsigned char bVar2;
    volatile int *piVar3;
    volatile int *piVar4;
    int iVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned char local_30;
    unsigned char uStack_2f;
    unsigned short local_2e;
    unsigned char local_2c;

    memset_bytes(&uStack_2f, 0, 0x17);
    local_30 = 4;
    local_2c = (unsigned char)param_1;
    local_2e = 1;
    iVar5 = k_msgq_put(((uintptr_t)&g_dashboard_response_msgq) /*=0x2000392c*/, &local_30, 0, 0);
    piVar4 = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    piVar3 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    if (iVar5 == 0) {
        uVar7 = 0;
        if (2 < *piVar3) {
            if (*piVar4 == 0) {
                uVar6 = "battery value > 20" /*=0xef506*/;
                if (param_1 == 1) {
                    uVar6 = "lower power" /*=0xef4fa*/;
                }
                DEBUG_PRINT("%s(): send power infomation to slave . power status = %s\n" /*=0xef519*/, "SendPowerInfoToSlave" /*=0xef6f2*/, uVar6);
            } else {
                uVar6 = "battery value > 20" /*=0xef506*/;
                if (param_1 == 1) {
                    uVar6 = "lower power" /*=0xef4fa*/;
                }
                debug_print("%s(): send power infomation to slave . power status = %s\n" /*=0xef519*/, "SendPowerInfoToSlave" /*=0xef6f2*/, uVar6);
            }
            if (2 < *piVar3) {
                if (*piVar4 == 0) {
                    iVar5 = (int)get_device_info();
                    bVar2 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    DEBUG_PRINT("%s(): GLOBAL->battery_info[0] = %d , GLOBAL->battery_info[1] = %d\n" /*=0xef553*/, "SendPowerInfoToSlave" /*=0xef6f2*/, (unsigned int)bVar2, (unsigned int)*(unsigned char*)(iVar5 + 0xfc1));
                } else {
                    iVar5 = (int)get_device_info();
                    uVar1 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    debug_print("%s(): GLOBAL->battery_info[0] = %d , GLOBAL->battery_info[1] = %d\n" /*=0xef553*/, "SendPowerInfoToSlave" /*=0xef6f2*/, uVar1, *(unsigned char*)(iVar5 + 0xfc1));
                }
            }
        }
    } else {
        DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "SendPowerInfoToSlave" /*=0xef6f2*/);
        uVar7 = 0xffffffffUL;
    }
    return uVar7;
}

