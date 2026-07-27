/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int FUN_0007d4ec(void);
extern void FUN_0007d6f4(void);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    int iVar2 = FUN_0007d4ec();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        FUN_0007d6f4();
        uVar3 = 0;
    }
    return uVar3;
}

