/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void FUN_0007d82e(void);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    FUN_0007d82e();
    return 0;
}

