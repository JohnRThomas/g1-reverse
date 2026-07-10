/* named: arm_timeout_10s */
/* globals referenced:
//   0x20004948  g_deadline_10s               
*/
/* Reconstructed arm_timeout_10s @ 0x32c0c  (parity: 300/300 trials, PROVEN) */

extern long long k_uptime_get_4(void);

void arm_timeout_10s(void)
{
    long long lVar1 = k_uptime_get_4();
    *(volatile long long*)0x20004948UL = lVar1 + 10000;
}

