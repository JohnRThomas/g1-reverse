#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e888 @ 0x0101e888
 * public-name: FUN_0101e888
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 */
/* net-core FUN_0101e888 @ 0x101e888  (parity 300 trials PROVEN) */

extern void FUN_0101e828(void);
void FUN_0101e888(void)
{
    volatile unsigned int * const p = (volatile unsigned int * const)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
    p[2] = 0xea6;
    p[3] = 0x1d4c;
    FUN_0101e828();
}
