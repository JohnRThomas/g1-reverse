/* Reconstructed FUN_0007d0c2 @ 0x7d0c2  (uncatalogued: Ghidra folded it into
 * the tail of read_rtc_counter_ms, 0x7d0aa; the next catalogued entry is
 * serial_data_read_dispatch at 0x7d0e8).  Code 0x7d0c2..0x7d0e8.
 *
 * Slot 3 of the ops table the shipped `.data` places at 0x20002408.
 *
 *   7d0c6  bic.w r4,r0,r0,asr #31         ; r4 = MAX(ms, 0)
 *   7d0c8..7d0d8  {r0,r1} = 999 + r4 * 0x8000  (smlal), {r2,r3} = 1000
 *   7d0dc  bl __aeabi_uldivmod            ; ticks = (MAX(ms,0)*32768+999)/1000
 *   7d0e4  b.w k_sleep                    ; tail call, k_timeout_t in r0:r1
 *
 * i.e. `k_sleep(K_MSEC(ms))` with CONFIG_SYS_CLOCK_TICKS_PER_SEC = 32768:
 * Zephyr 3.4's Z_TIMEOUT_MS(t) is k_ms_to_ticks_ceil64(MAX(t, 0)).
 */

typedef struct { long long ticks; } g1_k_timeout_t;
extern int k_sleep(g1_k_timeout_t timeout);

int FUN_0007d0c2(int param_1)
{
  g1_k_timeout_t t;
  int ms = param_1 < 0 ? 0 : param_1;

  t.ticks = (long long)(((unsigned long long)(unsigned int)ms * 32768ULL + 999ULL) / 1000ULL);
  return k_sleep(t);
}
