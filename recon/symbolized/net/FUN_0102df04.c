#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102df04 @ 0x0102df04
 * public-name: FUN_0102df04
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_claim                          <= FUN_0102ce14 @ 0x0102ce14
 * address symbols (name @ address):
 *   g_net_periodic_work_obj                  @ 0x2100086c
 */
/* net-core FUN_0102df04 @ 0x102df04  (parity 300 trials PROVEN) */
/* FUN_0102df04: entry is a 2-instr tail-thunk (ldr r0,[pc,#4]; b.w 0x102ce14)
   -- immediate tail branch out of the function's own body. The harness's
   out-of-body hook treats this as a single oracle call whose result is
   returned directly (LR unchanged from entry). Model as one tail call. */
extern unsigned int mpsc_pbuf_claim(unsigned int a);
unsigned int FUN_0102df04(void)
{
  return mpsc_pbuf_claim(((unsigned long)&g_net_periodic_work_obj) /*=0x2100086c*/);
}
