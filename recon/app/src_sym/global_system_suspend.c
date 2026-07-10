/* Reconstructed global_system_suspend @ 0x2bd7c  (parity: 296/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt, unsigned int a1, unsigned int a2, unsigned int a3);
extern void debug_print(void);
typedef void (*fn2_t)(unsigned int);

unsigned int global_system_suspend(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char *)param_1;
    if ((*(base + 0xfe6) & 0xfb) == 0) {
        *(base + 0xfe6) = 2;
        if (*(volatile int *)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 1) {
            if (*(volatile int *)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0xa24ebU, 0xa251aU, param_3, 0U);
            } else {
                debug_print();
            }
        }
        /* param_1 == device_info; +0xB6C == device_info.projector_controller.
           vtable dispatch: projector_controller->suspend (method ptr @+0xB70) */
        fn2_t fn = *(fn2_t *)(base + 0xb70);
        fn((unsigned int)((unsigned char *)param_1 + 0xb6c));
        if (*(volatile int *)0x2000230cUL > 1) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0xa24f9U, 0xa251aU, param_3, 0U);
            } else {
                debug_print();
            }
        }
        *(base + 0xfe6) = 1;
    }
    return 0;
}

