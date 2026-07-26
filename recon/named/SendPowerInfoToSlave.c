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
extern void log_message(uint32_t, ...);
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
    unsigned char request[24];

    memset_bytes(&request[1], 0, 0x17);
    request[0] = 4;
    request[4] = (unsigned char)param_1;
    *(unsigned short *)&request[2] = 1;
    iVar5 = k_msgq_put(0x2000392cUL, request, 0, 0);
    piVar4 = (volatile int*)0x20007554UL;
    piVar3 = (volatile int*)0x2000230cUL;
    if (iVar5 == 0) {
        uVar7 = 0;
        if (2 < *piVar3) {
            if (*piVar4 == 0) {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = 0x000ef4faUL;
                }
                log_message(0x000ef519UL, 0x000ef6f2UL, uVar6);
            } else {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = 0x000ef4faUL;
                }
                debug_print(0x000ef519UL, 0x000ef6f2UL, uVar6);
            }
            if (2 < *piVar3) {
                if (*piVar4 == 0) {
                    iVar5 = (int)get_device_info();
                    bVar2 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    log_message(0x000ef553UL, 0x000ef6f2UL, (unsigned int)bVar2, (unsigned int)*(unsigned char*)(iVar5 + 0xfc1));
                } else {
                    iVar5 = (int)get_device_info();
                    uVar1 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    debug_print(0x000ef553UL, 0x000ef6f2UL, uVar1, *(unsigned char*)(iVar5 + 0xfc1));
                }
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n"), 0x000ef6f2UL);
        uVar7 = 0xffffffffUL;
    }
    return uVar7;
}
