/* net-core FUN_01039bb0 @ 0x1039bb0  (parity 300 trials PROVEN) */

unsigned int FUN_01039bb0(void)
{
    __asm__ volatile(
        "eors r0, r0\n\t"
        "msr basepri, r0\n\t"
        "mov.w r0, #4\n\t"
        "svc #2\n\t"
    );
}

