/* Reconstructed FUN_00032c0c @ 0x32c0c  (parity: 300/300 trials, PROVEN) */

extern long long k_uptime_get_4(void);

void FUN_00032c0c(void)
{
    long long lVar1 = k_uptime_get_4();
    *(volatile long long*)0x20004948UL = lVar1 + 10000;
}

