#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01014884 @ 0x01014884
 * public-name: FUN_01014884
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_01014884 @ 0x1014884 */

extern void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_01014884(unsigned int unused_1, unsigned int unused_2,
                  unsigned int arg_3, unsigned int arg_4)
{
    for (;;)
        sdc_assertion_fail(0x31, 0x8ed, arg_3, arg_4);
}
