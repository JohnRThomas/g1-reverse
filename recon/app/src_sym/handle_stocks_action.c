/* Reconstructed handle_stocks_action @ 0x371e8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int handle_stocks_action(unsigned char param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(volatile unsigned char*)(0x20004950UL+5) = param_1;
    *(volatile unsigned char*)0x2001b814UL = param_1;
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return 0;
}

