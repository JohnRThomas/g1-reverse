/* readable reconstruction; identity: FUN_01024664 @ 0x01024664
 * public-name: FUN_01024664
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_link_state                         @ 0x21001bcc
 */
/* net-core FUN_01024664 @ 0x1024664  (parity 300 trials PROVEN) */

#include <stdbool.h>
bool FUN_01024664(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)0x21001bcc;
    return *p == 3;
}
