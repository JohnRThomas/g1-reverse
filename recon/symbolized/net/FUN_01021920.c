#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021920 @ 0x01021920
 * public-name: FUN_01021920
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_01021920 @ 0x1021920  (parity 300 trials PROVEN) */

typedef void (*code)(void);
void FUN_01021920(void)
{
    ((code)(*(volatile unsigned int*)(*(volatile unsigned int*)((unsigned long)&g_net_radio_ops_table_ptr) /*=0x21000530*/ + 4)))();
}
