/* readable reconstruction; identity: FUN_01025be0 @ 0x01025be0
 * public-name: FUN_01025be0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_driver_api_ptr                     @ 0x21000574
 */
/* net-core FUN_01025be0 @ 0x1025be0  (parity 300 trials PROVEN) */

int FUN_01025be0(void)
{
    volatile int * const p = (volatile int * const)0x21000574;
    int iVar1 = *p - 0x0103c780;
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
}
