/* Reconstructed trigger_screen_state_change @ 0x2bc2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int trigger_screen_state_change(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    if ((unsigned int)(*(volatile unsigned char*)(param_2 + 0xfe8)) == param_3) {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa2470, 0xa254a, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                FUN_00019c70(0xa2470, 0xa254a, param_1,
                             *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            }
        }
        param_3 = 0xffffffff;
    } else {
        if (param_3 == 0) {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 0;
        } else {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 1;
            FUN_00072880(param_2 + 0x50);
        }
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa2486, 0xa254a, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                FUN_00019c70(0xa2486, 0xa254a, param_1,
                             *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            }
        }
    }
    return param_3;
}
