/* Reconstructed getAppLanguageInfofromFlash @ 0x23d0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int z_device_is_ready(uint32_t);

unsigned char getAppLanguageInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile int *piVar1;
    volatile unsigned int *puVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;
    unsigned char uVar6;
    int iVar7;

    piVar1 = (volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */;
    unsigned int local_14 = param_2;

    if (2 < *piVar1) {
        if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT(0x0009e9bfUL, 0x0009ed2eUL, param_3, 0, param_1);
        } else {
            debug_print(0x0009e9bfUL, 0x0009ed2eUL, param_3, 0, param_1);
        }
    }
    puVar2 = (volatile unsigned int*)0x00087bf0UL;
    iVar3 = z_device_is_ready(0x00087bf0UL);
    if (iVar3 == 0) {
        if (0 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009e9eaUL, 0x0009ed2eUL, *puVar2, 0, param_1);
            } else {
                debug_print(0x0009e9eaUL, 0x0009ed2eUL, *puVar2, 0, param_1);
            }
        }
        uVar6 = 0xff;
    } else {
        local_14 = local_14 & 0xff000000UL;
        char *p1 = (char*)get_device_info();
        void *pcVar8 = *(void**)(p1 + 0x1030);   /* device_info+0x1030 stored flash-read fn ptr */
        void *r1arg = get_device_info();
        int (*fn)(void*, unsigned int, void*, int) = (int(*)(void*, unsigned int, void*, int))pcVar8;
        /* equivalent: flash_read(dev=device_info, 0x13e000, &local_14, 3) */
        iVar5 = fn(r1arg, 0x13e000, &local_14, 3);
        iVar3 = 0x20018462;
        iVar7 = *piVar1;
        if (iVar5 == 0) {
            if ((char)local_14 == -0x56) {
                uVar6 = (unsigned char)(local_14 >> 8);
            } else {
                uVar6 = 2;
            }
            *(unsigned char*)(intptr_t)(0x20018462 + 1) = uVar6;
            if (3 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea37UL, 0x0009ed2eUL, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                } else {
                    debug_print(0x0009ea37UL, 0x0009ed2eUL, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                }
            }
            uVar6 = *(unsigned char*)(intptr_t)(iVar3 + 1);
        } else {
            if (0 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea0aUL, 0x0009ed2eUL, 0x13e000UL);
                } else {
                    debug_print(0x0009ea0aUL, 0x0009ed2eUL, 0x13e000UL);
                }
            }
            uVar6 = 0;
        }
    }
    return uVar6;
}

