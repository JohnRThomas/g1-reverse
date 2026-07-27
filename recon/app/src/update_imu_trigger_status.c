/* Reconstructed update_imu_trigger_status @ 0x2bcbc  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int update_imu_trigger_status(unsigned int param_1, int param_2, int param_3)
{
    unsigned int uVar2;

    if (*(volatile int*)(param_2 + 0xee8) == param_3) {
        uVar2 = 0xffffffff;
    } else {
        *(volatile int*)(param_2 + 0xee8) = param_3;
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa24a9, 0xa2530, param_1, param_3);
            } else {
                FUN_00019c70(0xa24a9, 0xa2530, param_1, param_3);
            }
        }
        if ((*(volatile unsigned char*)(param_2 + 0xfea) == 0xa) && (param_3 != 0) &&
            (*(volatile unsigned char*)(param_2 + 0xb0c) == 0)) {
            if (2 < *(volatile int*)0x2000230cUL) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0xa24c3, 0xa2530, 0, 0);
                } else {
                    FUN_00019c70(0xa24c3, 0xa2530, 0, 0);
                }
            }
            *(volatile unsigned char*)(param_2 + 0xfe9) = 1;
            FUN_00072880(param_2 + 0xaf4);
        }
        uVar2 = 0;
    }
    return uVar2;
}

