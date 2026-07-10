/* Reconstructed FUN_0004a4d0 @ 0x4a4d0  (parity: 300/300 trials, PROVEN) */

extern long long k_uptime_get_9(void);

void FUN_0004a4d0(long long *param_1)
{
  long long lVar1;
  lVar1 = k_uptime_get_9();
  *param_1 = (lVar1 - *(volatile long long*)0x20004df8UL) + *(volatile long long*)0x20004df0UL;
}

