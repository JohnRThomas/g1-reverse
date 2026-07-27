/* Reconstructed display_DelayClose @ 0x498c0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *dst, int val, unsigned int len);
extern int FUN_000720d0(void *obj, void *msg, unsigned int a, unsigned int b);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int display_DelayClose(unsigned int param_1)
{
    unsigned char buf[0x18];
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 4;
    *(unsigned short *)(buf + 2) = 4;
    *(unsigned int *)(buf + 4) = param_1;

    void *obj = (void *)0x200038c4UL;
    int iVar1 = FUN_000720d0(obj, buf, 0, 0);
    unsigned int uVar2;

    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int *)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
            if (*(volatile int *)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0xf008cU, 0xf0164U);
            } else {
                debug_print(0xf008cU, 0xf0164U);
            }
        }
    } else {
        DEBUG_PRINT(0xef058U, 0xf0164U);
        uVar2 = 0xffffffffU;
    }
    return uVar2;
}

