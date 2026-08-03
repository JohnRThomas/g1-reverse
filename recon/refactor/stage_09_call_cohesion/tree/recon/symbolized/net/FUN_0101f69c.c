#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f69c @ 0x0101f69c
 * public-name: FUN_0101f69c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_101ec69                           @ 0x0101ec69
 *   g_net_ble_conn_role_cfg                  @ 0x21001208
 */
/* net-core FUN_0101f69c @ 0x101f69c  (parity 300 trials PROVEN) */

extern void FUN_0101f894(int);
extern void FUN_010161e8(void);
#define DAT_0101f6b0 ((unsigned int)((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/)
#define DAT_0101f6b4 ((unsigned int)((unsigned long)&rodata_101ec69) /*=0x101ec69*/)

void FUN_0101f69c(void)
{
    FUN_0101f894(5);
    FUN_010161e8();
    *(volatile unsigned int *)(DAT_0101f6b0 + 0x24) = DAT_0101f6b4;
    return;
}
