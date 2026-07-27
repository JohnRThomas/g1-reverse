/* Reconstructed enqueue_dmic @ 0x2ec5c  (parity: 300/300 trials, PROVEN) */

extern void memcpy(void*, unsigned int, int);
extern void FUN_00072240(unsigned int, void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

int enqueue_dmic(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[204];

    memcpy(buf, 0x885cc, 200);
    if (*(volatile int*)(0x20007b7cUL /* device_info+0x1180 (k_msgq: dmic audio queue object) */ + 0x24) == 8) {
        FUN_00072240(0x20007b7cUL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0xa3f17, 0xa41e2, 8);
            } else {
                debug_print(0xa3f17, 0xa41e2, 8);
            }
        }
    }
    memcpy(buf, param_1, 200);
    iVar1 = FUN_000720d0(0x20007b7cUL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xa3f45, 0xa41e2);
        } else {
            debug_print(0xa3f45, 0xa41e2);
        }
    }
    return iVar1;
}

