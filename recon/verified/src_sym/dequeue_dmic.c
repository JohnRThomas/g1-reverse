/* Reconstructed dequeue_dmic @ 0x2ed00  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int FUN_00072240(void);
extern void memcpy(void);

int dequeue_dmic(unsigned int param_1)
{
    memcpy();
    int iVar1 = FUN_00072240();
    if (iVar1 == 0) {
        memcpy();
    } else if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 0) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return iVar1;
}

