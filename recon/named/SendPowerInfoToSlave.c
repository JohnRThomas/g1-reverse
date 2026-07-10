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
    iVar5 = k_msgq_put(0x2000392cUL, &local_30, 0, 0);
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
                DEBUG_PRINT(0x000ef519UL, 0x000ef6f2UL, uVar6);
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
                    DEBUG_PRINT(0x000ef553UL, 0x000ef6f2UL, (unsigned int)bVar2, (unsigned int)*(unsigned char*)(iVar5 + 0xfc1));
                } else {
                    iVar5 = (int)get_device_info();
                    uVar1 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)get_device_info();
                    debug_print(0x000ef553UL, 0x000ef6f2UL, uVar1, *(unsigned char*)(iVar5 + 0xfc1));
                }
            }
        }
    } else {
        DEBUG_PRINT(0x000ef058UL, 0x000ef6f2UL);
        uVar7 = 0xffffffffUL;
    }
    return uVar7;
}

