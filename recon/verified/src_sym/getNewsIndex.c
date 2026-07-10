/* Reconstructed getNewsIndex @ 0x3719c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(unsigned int a, unsigned int b);

unsigned char getNewsIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */;
    unsigned char b = *(volatile unsigned char*)0x2001b814UL;
    base[5] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95abUL);
        } else {
            debug_print(0x000a8ff3UL, 0x000a95abUL);
        }
    }
    return base[5];
}

