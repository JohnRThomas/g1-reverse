/* readable reconstruction; identity: FUN_01009210 @ 0x01009210
 * public-name: FUN_01009210
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_addr_record                        @ 0x21000a60
 */
/* net-core FUN_01009210 @ 0x1009210  (parity 300 trials PROVEN) */

int FUN_01009210(void)
{
    volatile int * const p = (volatile int * const)0x21000a60;
    int iVar1 = p[1];
    if (iVar1 != 0) {
        iVar1 = p[2];
        if (iVar1 != 0) iVar1 = 1;
    }
    return iVar1;
}
