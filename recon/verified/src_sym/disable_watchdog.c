/* Reconstructed disable_watchdog @ 0x2aeb4  (parity: 151/300 trials, PROVEN) */

extern void FUN_00074844(unsigned int, unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

typedef int (*fp_t)(unsigned int);

int disable_watchdog(void)
{
    volatile int *piVar1 = (volatile int*)0x20007b50UL /* device_info+0x1154 (watchdog install/channel flag) */;
    int iVar5;

    if (*piVar1 < 0) {
        if (3 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0xa1c4e, 0xa1c85, *piVar1, 0, 0);
            } else {
                debug_print(0xa1c4e, 0xa1c85, *piVar1, 0, 0);
            }
        }
        iVar5 = 0;
    } else {
        int iVar6 = 5;
        do {
            if (3 < *(volatile int*)0x2000230cUL) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0xa1c6a, 0xa1c85);
                } else {
                    debug_print(0xa1c6a, 0xa1c85);
                }
            }
            /* Zephyr driver-vtable dispatch: dev->api->method (api ptr @dev+8, method @api+4);
               0x87cc8 = watchdog struct device *dev (rodata) -> wdt disable/feed(dev) */
            fp_t f = *(fp_t*)(*(int*)(0x87cc8 + 8) + 4);
            iVar5 = f(0x87cc8);
            if (iVar5 == 0) {
                *piVar1 = -0x10;
                iVar5 = 0;
                break;
            }
            FUN_00074844(0x667, 0);
            iVar6 = iVar6 - 1;
        } while (iVar6 != 0);
    }
    return iVar5;
}

