/* named: power_down_imu_and_mic */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed power_down_imu_and_mic @ 0x160b4  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int power_down_imu_and_mic(void)
{
    int iVar1 = dev_write_reg3();
    (void)iVar1;
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL;
    if (flag == 0) {
        DEBUG_PRINT();
    } else {
        debug_print();
    }
    return 0;
}

