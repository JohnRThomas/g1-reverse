/* Reconstructed enqueue_ancs @ 0x18bb4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern void FUN_00072240(unsigned int, void*, int, int);
extern void memcpy(void*, unsigned int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

int enqueue_ancs(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[436];

    memset_bytes(buf, 0, 0x1b4);
    if (*(volatile int*)(0x20006a6cUL /* device_info+0x070  (k_msgq: ANCS notification queue object) */ + 0x10) == 0) {
        iVar1 = 1;
    } else {
        if (*(volatile int*)(0x20006a6cUL + 0x24) == 10) {
            FUN_00072240(0x20006a6cUL, buf, 0, 0);
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0x9a964, 0, 0);
            } else {
                debug_print(0x9a964, 0, 0);
            }
        }
        memcpy(buf, param_1, 0x1b4);
        iVar1 = FUN_000720d0(0x20006a6cUL, buf, 0, 0);
        if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */)) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9a981, 0x9b19d);
            } else {
                debug_print(0x9a981, 0x9b19d);
            }
        }
    }
    return iVar1;
}

