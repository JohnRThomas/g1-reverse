/* Reconstructed jdb_panel_init @ 0x46fc0  (parity: 300/300 trials, PROVEN) */

extern void panel_init(void);
extern void set_brightness_to_panel_reg(void);
extern int spi_read_id(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int jdb_panel_init(unsigned char *param_1)
{
    *(unsigned int*)(param_1+0x374) = (unsigned int)(param_1 - 0x5c);
    panel_init();
    set_brightness_to_panel_reg();
    int iVar1 = spi_read_id();
    *(volatile unsigned int*)0x2000a074UL = iVar1;
    unsigned int uVar2;
    if (iVar1 == 0x4010) {
        uVar2 = 0;
        *(unsigned int*)(param_1+0x35c) = 1;
    } else {
        if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

