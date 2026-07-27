/* Reconstructed get_boot_seconds @ 0x4a51c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_9(void);
extern int __aeabi_ldivmod(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

int get_boot_seconds(void)
{
    unsigned long long uVar3 = k_uptime_get_9();
    (void)uVar3;
    int iVar1 = __aeabi_ldivmod();
    int iVar2 = *(volatile int*)0x2000a0b0UL;
    int diff = iVar1 - iVar2;
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return diff;
}

