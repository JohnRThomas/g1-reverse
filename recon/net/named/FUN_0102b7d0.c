/* readable reconstruction; identity: FUN_0102b7d0 @ 0x0102b7d0
 * public-name: FUN_0102b7d0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_evt_callback_fn                    @ 0x2100463c
 *   g_net_evt_notify_disabled_flag           @ 0x21004fa5
 *   g_net_evt_last_notified_state            @ 0x21004fa6
 */
/* net-core FUN_0102b7d0 @ 0x102b7d0  (parity 300 trials PROVEN) */

typedef void (*fptr_t)(int);
void FUN_0102b7d0(int param_1)
{
  volatile unsigned char *A = (volatile unsigned char*)0x21004fa5;
  volatile unsigned char *B = (volatile unsigned char*)0x21004fa6;
  fptr_t *Cp = (fptr_t*)0x2100463c;
  if (*A == 0) {
    if (param_1 == 0) {
      if (*B != 0) {
        (*Cp)(1);
        *B = 0;
      }
    } else if (*B == 0) {
      (*Cp)(0);
      *B = 1;
    }
  }
}
