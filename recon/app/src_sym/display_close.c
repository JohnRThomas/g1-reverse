/* Reconstructed display_close @ 0x497b0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
extern int FUN_000720d0(unsigned int a, void *b, int c, int d);
extern void memcpy(void *dst, void *src, unsigned int n);
extern void memset_bytes(void *dst, int val, int n);

unsigned int display_close(void *param_1, unsigned int param_2)
{
    unsigned char buf[24 + 4];
    int iVar1;

    memset_bytes(buf, 0, 0x18);
    if (param_2 < 0xb) {
        buf[0] = 3;
        if (param_1 != (void*)0) {
            memcpy(buf + 4, param_1, param_2);
            *(volatile unsigned short *)(buf + 2) = (unsigned short)param_2;
        }
        iVar1 = FUN_000720d0(0x200038c4U, buf, 0, 0);
        if (iVar1 == 0) {
            if (*(volatile int *)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ < 1) {
                return 0;
            }
            if (*(volatile int *)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ != 0) {
                debug_print();
                return 0;
            }
            DEBUG_PRINT(0xf0044U, 0xf018cU);
            return 0;
        }
        DEBUG_PRINT(0xef058U, 0xf018cU);
    } else if (0 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0xef01cU, 0xf018cU);
        } else {
            debug_print();
        }
    }
    return 0xffffffff;
}

