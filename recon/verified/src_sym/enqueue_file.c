/* Reconstructed enqueue_file @ 0x23514  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072240(unsigned int, void*, int, int);
extern void FUN_00086c1e(void*, unsigned int, unsigned int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

int enqueue_file(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned char buf[200];

    if (*(volatile int*)(0x200079a0UL /* device_info+0xFA4  (k_msgq: file-transfer queue object) */ + 0x24) == 0x1e) {
        FUN_00072240(0x200079a0UL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0x9e824, 0x9e8f6);
            } else {
                debug_print();
            }
        }
    }
    FUN_00086c1e(buf, param_1, param_2, 0xc9);
    buf[200-4] = (unsigned char)param_2;
    iVar1 = FUN_000720d0(0x200079a0UL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9e840, 0x9e8f6);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

