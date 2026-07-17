#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01031814 @ 0x01031814
 * public-name: FUN_01031814
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01031814 @ 0x1031814  (parity 300 trials PROVEN) */
/* Raw bytes at 0x1031814 are just: ldr r0,[pc,#4] ; b.w 0x103657c
   (tail-branch to a shared handler far outside the declared 212-byte window,
   so the recon harness treats it as a single external call/oracle — model
   that faithfully instead of inlining the shared handler's logic.) */
extern unsigned int FUN_0103657c(unsigned int);

#define DAT_0103181c 0x210008ccu

unsigned int FUN_01031814(void)
{
  return FUN_0103657c(DAT_0103181c);
}
