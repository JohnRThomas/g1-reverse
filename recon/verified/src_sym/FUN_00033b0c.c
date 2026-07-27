/* Reconstructed FUN_00033b0c @ 0x33b0c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void FUN_00033b0c(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int format_string = 0xa7d1cUL;
    volatile int *piVar1 = (volatile int*)0x20007554UL /* device_info.is_debug  (device_info_t+0xB58) */;
    volatile unsigned int *puVar3 = (volatile unsigned int*)0x20007dacUL /* device_info_t+0x13B0  (message/display region) */;
    int iVar2 = 0;
    do {
        if (*piVar1 == 0) {
            DEBUG_PRINT(format_string, iVar2, puVar3[2], puVar3[1], puVar3[0], param_2, param_3);
        } else {
            debug_print(format_string, iVar2, puVar3[2], puVar3[1], puVar3[0], param_2, param_3);
        }
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 0x6d;
    } while (iVar2 != 10);
}

