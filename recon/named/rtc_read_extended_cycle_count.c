/* readable reconstruction; identity: FUN_00063610 @ 0x00063610
 * public-name: rtc_read_extended_cycle_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_read_extended_cycle_count            <= FUN_00063610 @ 0x00063610
 * address symbols (name @ address):
 *   g_rtc_cycle_range_minmax                 @ 0x200066b8
 *   g_uptime_ref_tick_hi                     @ 0x200066bc
 *   g_uptime_tick_overflow_state             @ 0x2000b2dc
 *   REG_50015504                             @ 0x50015504
 */
/* Reconstructed FUN_00063610 @ 0x63610  (parity: 300/300 trials, PROVEN) */

unsigned long long rtc_read_extended_cycle_count(void)
{
  unsigned int counterVal = *(volatile unsigned int *)0x2000b2dcUL;
  unsigned int uVar1 = counterVal >> 8;
  unsigned int shifted = counterVal << 24;
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
  unsigned int uVar3 = *(volatile unsigned int *)0x50015504UL;
  unsigned int uVar2 = uVar3 + shifted;
  unsigned int carry1 = (uVar2 < uVar3) ? 1 : 0;
  uVar1 = uVar1 + carry1;
  if (uVar3 < 0x100000) {
    unsigned int lo = *(volatile unsigned int *)0x200066b8UL;
    unsigned int hi = *(volatile unsigned int *)0x200066bcUL;
    unsigned long long a = ((unsigned long long)uVar1 << 32) | uVar2;
    unsigned long long b = ((unsigned long long)hi << 32) | lo;
    if (a < b) {
      unsigned int old = uVar2;
      uVar2 = uVar2 + 0x1000000;
      unsigned int carry2 = (uVar2 < old) ? 1 : 0;
      uVar1 = uVar1 + carry2;
    }
  }
  return ((unsigned long long)uVar1 << 32) | uVar2;
}
