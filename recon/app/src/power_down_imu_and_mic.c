/* Reconstructed power_down_imu_and_mic @ 0x160b4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

unsigned int power_down_imu_and_mic(void)
{
    int iVar1 = FUN_00083dc8();
    (void)iVar1;
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL;
    if (flag == 0) {
        DEBUG_PRINT();
    } else {
        FUN_00019c70();
    }
    return 0;
}

