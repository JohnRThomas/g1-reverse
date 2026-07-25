#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021920 @ 0x01021920
 * public-name: FUN_01021920
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_01021920 @ 0x1021920  (parity 300 trials PROVEN)
 *
 * P4 iteration 27 CORRECTION -- see recon/net/src/FUN_01021920.c for the full
 * byte evidence.  The shipped thunk preserves r4 and tail-calls through ip
 * (push {r4}; ldr r4,=0x21000530; ldr r4,[r4]; ldr r4,[r4,#4]; mov ip,r4;
 * pop {r4}; bx ip) because r3 is a LIVE FOURTH ARGUMENT; its nine siblings at
 * 0x010218b4..0x01021914 use r3 as scratch and therefore have at most three
 * register arguments.  The previous `void FUN_01021920(void)` body compiled to
 * a tail call that clobbered r3 with the callee address.
 */

typedef long long (*g1_net_radio_ops_fn)(unsigned long, unsigned long,
                                         unsigned long, unsigned long);

long long FUN_01021920(unsigned long a0, unsigned long a1,
                       unsigned long a2, unsigned long a3)
{
    g1_net_radio_ops_fn *ops =
        *(g1_net_radio_ops_fn *volatile *)
            ((unsigned long)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    return ops[1](a0, a1, a2, a3);
}
