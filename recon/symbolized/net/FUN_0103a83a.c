#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a83a @ 0x0103a83a
 * public-name: FUN_0103a83a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a83a @ 0x103a83a  (P4 iteration 24; parity 300/300 trials, 0 mismatches) */
/* CPUNET RADIO IRQ 0x19 trampoline @ 0x0103a83a.
 * Raw back-map: FUN_0103a83a@0x0103a83a; true extent 4 -- a single
 * `b.w 0x010350a4` tail branch.  FUN_010333b4 installs it as the RUNTIME
 * Thumb pointer 0x0103b03b (= analysis 0x0103a83a | 1).
 */
extern void FUN_010350a4(void);

void FUN_0103a83a(void)
{
    FUN_010350a4();
}
