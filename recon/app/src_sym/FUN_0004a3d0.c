/* Reconstructed FUN_0004a3d0 @ 0x4a3d0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void FUN_0004a3d0(int param_1, int param_2, int param_3, int param_4)
{
    volatile int *piVar1 = (volatile int*)0x20007554UL /* device_info.is_debug */;
    if (*piVar1 == 0) {
        DEBUG_PRINT(0x000f0229, param_2 + 0x10);
    } else {
        debug_print(0x000f0229, param_2 + 0x10);
    }
    if (*piVar1 == 0) {
        DEBUG_PRINT(0x000f024d, param_2 + 0x90);
    } else {
        debug_print(0x000f024d, param_2 + 0x90);
    }
    if (*piVar1 != 0) {
        debug_print(0x000f028c, *(volatile int*)(param_2+8), param_3, param_4);
        return;
    }
    DEBUG_PRINT(0x000f028c, *(volatile int*)(param_2+8), param_3, param_4);
}

