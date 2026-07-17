#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01024650 @ 0x01024650
 * public-name: FUN_01024650
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_link_state                         @ 0x21001bcc
 */
/* net-core FUN_01024650 @ 0x1024650  (parity 300 trials PROVEN) */

#include <stdbool.h>
bool FUN_01024650(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&g_net_link_state) /*=0x21001bcc*/;
    return (unsigned char)(*p - 2) < 2;
}
