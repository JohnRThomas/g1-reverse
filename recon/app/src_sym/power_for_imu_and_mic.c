/* Reconstructed power_for_imu_and_mic @ 0x15f80  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int power_for_imu_and_mic(void)
{
    int iVar1 = FUN_00083dc8();
    (void)iVar1;
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */;
    if (flag == 0) {
        DEBUG_PRINT();
    } else {
        debug_print();
    }
    return 0;
}

