/* Reconstructed is_msg_expiration @ 0x3444c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *get_device_info(void);
extern void debug_print(unsigned long, ...);
extern unsigned int get_timestamp(void);
extern void FUN_0007d230(unsigned int);

unsigned int is_msg_expiration(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned char *pbVar1;
    int iVar2;
    char *pcVar3;
    unsigned int uVar4;
    int iVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned int uVar8;

    iVar2 = (int)(intptr_t)get_device_info();
    if (*(char*)(intptr_t)(iVar2 + 0x108f) != 0) {
        pcVar3 = (char*)get_device_info();
        if (*pcVar3 == 1) {
            iVar2 = (int)(intptr_t)get_device_info();
            FUN_0007d230(**(unsigned int**)(intptr_t)(iVar2 + 0xfec));
        }
    }
    iVar2 = 0x20007dac /* device_info+0x13B0 */;
    pbVar1 = (unsigned char*)0x2001a22aUL;
    iVar5 = (int)(*pbVar1) * 0x1b4 + iVar2;
    uVar6 = (unsigned int)*(unsigned char*)(intptr_t)(iVar5 + 0xf);
    if ((uVar6 != 0) && ((uVar6 = *(unsigned int*)(intptr_t)(iVar5 + 4)) != 0)) {
        uVar6 = get_timestamp();
        uVar7 = (unsigned int)*pbVar1;
        iVar5 = *(int*)(intptr_t)(uVar7 * 0x1b4 + iVar2 + 4);
        if (iVar5 + 10U < uVar6) {
            if (0 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
                if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                    uVar4 = get_timestamp();
                    DEBUG_PRINT(0x000a80e3UL, 0x000a820fUL, uVar7, iVar5, uVar4, param_2, param_3);
                } else {
                    uVar4 = get_timestamp();
                    debug_print(0x000a80e3UL, 0x000a820fUL, uVar7, iVar5, uVar4, param_2, param_3);
                }
            }
            uVar6 = 2;
        } else {
            uVar6 = 1;
        }
    }
    uVar8 = *(unsigned int*)(intptr_t)((unsigned int)*pbVar1 * 0x1b4 + iVar2 + 4);
    uVar7 = get_timestamp();
    if (uVar7 < uVar8) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8146UL);
        } else {
            debug_print(0x000a8146UL);
        }
        uVar6 = 2;
    }
    return uVar6;
}

