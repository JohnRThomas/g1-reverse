#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000488bc @ 0x000488bc
 * public-name: SendPowerInfoToSlave
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef4fa                             @ 0x000ef4fa   [INLINED -- G6 literal batch]
 *   rodata_ef519                             @ 0x000ef519   [INLINED -- G6 literal batch]
 *   rodata_ef553                             @ 0x000ef553   [INLINED -- G6 literal batch]
 *   rodata_ef6f2                             @ 0x000ef6f2   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed SendPowerInfoToSlave @ 0x488bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int get_device_info(void);
extern int k_msgq_put(unsigned int, void*, int, int);
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
    unsigned char request[24];

    memset_bytes(&request[1], 0, 0x17);
    request[0] = 4;
    request[4] = (unsigned char)param_1;
    *(unsigned short *)&request[2] = 1;
    iVar5 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, request, 0, 0);
    piVar4 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    piVar3 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    if (iVar5 == 0) {
        uVar7 = 0;
        if (2 < *piVar3) {
            if (*piVar4 == 0) {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = ((unsigned long)"lower power") /*=0xef4fa*/;
                }
                log_message(((unsigned long)"%s(): send power infomation to slave . power status = %s\n") /*=0xef519*/, ((unsigned long)"SendPowerInfoToSlave") /*=0xef6f2*/, uVar6);
            } else {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = ((unsigned long)"lower power") /*=0xef4fa*/;
                }
                debug_print(((unsigned long)"%s(): send power infomation to slave . power status = %s\n") /*=0xef519*/, ((unsigned long)"SendPowerInfoToSlave") /*=0xef6f2*/, uVar6);
            }
            if (2 < *piVar3) {
                if (*piVar4 == 0) {
                    iVar5 = (int)get_device_info();
                    bVar2 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    log_message(((unsigned long)"%s(): GLOBAL->battery_info[0] = %d , GLOBAL->battery_info[1] = %d\n") /*=0xef553*/, ((unsigned long)"SendPowerInfoToSlave") /*=0xef6f2*/, (unsigned int)bVar2, (unsigned int)*(unsigned char*)(iVar5 + 0xfc1));
                } else {
                    iVar5 = (int)get_device_info();
                    uVar1 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    debug_print(((unsigned long)"%s(): GLOBAL->battery_info[0] = %d , GLOBAL->battery_info[1] = %d\n") /*=0xef553*/, ((unsigned long)"SendPowerInfoToSlave") /*=0xef6f2*/, uVar1, *(unsigned char*)(iVar5 + 0xfc1));
                }
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"SendPowerInfoToSlave") /*=0xef6f2*/);
        uVar7 = 0xffffffffUL;
    }
    return uVar7;
}
