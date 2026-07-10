/* named: enable_ship_mode */
/* Reconstructed enable_ship_mode @ 0x167f4  (parity: 300/300 trials, PROVEN) */

extern void power_down_panel(void);
extern void power_down_imu_and_mic(void);
extern void app_msleep_thunk_a(unsigned int a);
extern int dev_write_reg3(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void DEBUG_PRINT(unsigned int a);

unsigned int enable_ship_mode(void)
{
    unsigned int format_string;
    power_down_panel();
    power_down_imu_and_mic();
    app_msleep_thunk_a(2000);
    int base = *(volatile int*)(0x00087d10UL + 4);
    unsigned int arg0 = *(volatile unsigned int*)(base + 0x1c);
    int iVar1 = dev_write_reg3(arg0, 0xb, 2, 1, 0);
    if (iVar1 < 0) {
        format_string = 0x0009973dUL;
    } else {
        format_string = 0x00099756UL;
    }
    DEBUG_PRINT(format_string);
    return 0;
}

