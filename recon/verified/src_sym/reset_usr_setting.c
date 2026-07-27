/* Reconstructed reset_usr_setting @ 0x22ddc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void FUN_00032ef0(unsigned int);
extern void FUN_0007c28e(void *a, unsigned int b);

unsigned int reset_usr_setting(char *param_1)
{
    if (2 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
            DEBUG_PRINT(0x9e5f3U, 0x9e7b7U);
        } else {
            debug_print(0x9e5f3U, 0x9e7b7U);
        }
    }
    *(volatile unsigned char *)(param_1 + 0xfea) = 10;
    *(volatile unsigned char *)(param_1 + 0xed5) = 0x15;
    *(volatile unsigned int *)(param_1 + 0xf6c) = 400;
    *(volatile unsigned char *)(param_1 + 0xf60) = 1;
    *(volatile unsigned char *)(param_1 + 0xf98) = 1;
    *(volatile unsigned char *)(param_1 + 0x108d) = 1;
    *(volatile unsigned char *)(param_1 + 0x1070) = 0;
    *(volatile unsigned char *)(param_1 + 0xec0) = 3;
    *(volatile unsigned int *)(param_1 + 0x1069) = 0xffffffff;
    *(volatile unsigned int *)(param_1 + 0x106c) = 0xffffffff;
    *(volatile unsigned short *)(param_1 + 0xef4) = 0x114;
    *(volatile unsigned char *)(param_1 + 0x108f) = 0;
    *(volatile unsigned short *)(param_1 + 0x1090) = 0;
    FUN_00032ef0(0);
    *(volatile unsigned char *)(param_1 + 0xec1) = 3;
    *(volatile unsigned int *)(param_1 + 0xf68) = 0;
    FUN_0007c28e(param_1, 0);
    return 0;
}

