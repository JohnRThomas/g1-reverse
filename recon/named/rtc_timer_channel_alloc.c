/* readable reconstruction; identity: FUN_0006385c @ 0x0006385c
 * public-name: rtc_timer_channel_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_timer_channel_alloc                  <= FUN_0006385c @ 0x0006385c
 * address symbols (name @ address):
 *   nrf_rtc_timer_free_channels              @ 0x2000b2d4
 */
/* Reconstructed FUN_0006385c @ 0x6385c  (parity: 300/300 trials, PROVEN) */

unsigned int rtc_timer_channel_alloc(void)
{
  volatile unsigned int *addr = (volatile unsigned int *)0x2000b2d4UL;
  unsigned int val, idx, old;
  while (1) {
    val = *addr;
    if (val == 0) return 0xfffffff4;
    idx = 31 - __builtin_clz(val);
    old = __atomic_fetch_and(addr, ~(1u << (idx & 0xff)),
                             __ATOMIC_ACQ_REL);
    if ((int)((old >> (idx & 0xff)) << 0x1f) < 0) break;
  }
  return idx;
}
