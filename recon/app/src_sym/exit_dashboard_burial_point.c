/* Reconstructed exit_dashboard_burial_point @ 0x4aab0  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int FUN_0007dac0(void);
extern long long get_dashboard_sum_time(void);
extern unsigned int FUN_0007db50(void);
extern unsigned int DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int debug_print(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int exit_dashboard_burial_point(void)
{
    unsigned int r0v;
    unsigned int base;
    unsigned int uVar2;
    unsigned long long uVar4;
    unsigned int uVar3;

    base = get_device_info() + 0x1000;
    r0v = base;
    if (*(volatile unsigned char*)(base + 0x92) != 0) {
        uVar2 = FUN_0007dac0();
        r0v = uVar2;
        if (uVar2 < 7) {
            base = get_device_info() + 0x1000;
            *(volatile unsigned char*)(base + 0x92) = 0;
            uVar4 = (unsigned long long)get_dashboard_sum_time();
            r0v = (unsigned int)uVar4;
            uVar3 = (unsigned int)(uVar4 >> 32);
            r0v = FUN_0007db50();
            if (1 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
                if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                    base = get_device_info() + 0x1000;
                    r0v = DEBUG_PRINT(0xf03c4, 0xf0459, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                } else {
                    base = get_device_info() + 0x1000;
                    r0v = debug_print(0xf03c4, 0xf0459, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                }
            }
        }
    }
    return r0v;
}

