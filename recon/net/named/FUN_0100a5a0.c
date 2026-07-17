/* readable reconstruction; identity: FUN_0100a5a0 @ 0x0100a5a0
 * public-name: FUN_0100a5a0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_retry_handle                       @ 0x21000bc4
 */
/* net-core FUN_0100a5a0 @ 0x100a5a0  (parity 300 trials PROVEN) */

int FUN_0100a5a0(void)
{
    volatile int * const p = (volatile int * const)0x21000bc4;
    return *p;
}
