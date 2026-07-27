/* Reconstructed power_for_imu_and_mic @ 0x15f80  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(unsigned int,unsigned int,unsigned int,unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int power_for_imu_and_mic(void)
{
    int iVar1 = FUN_00083dc8(
        *(volatile unsigned int *)(*(volatile unsigned int *)(0x00087ce0 + 4) + 0x1c),
        8, 2, 1);
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL;
    if (flag == 0) {
        DEBUG_PRINT(iVar1 < 0 ? 0x0009945a : 0x00099476, 0x00099c28);
    } else {
        FUN_00019c70(iVar1 < 0 ? 0x0009945a : 0x00099476, 0x00099c28);
    }
    return 0;
}
