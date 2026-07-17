/* readable reconstruction; identity: FUN_0101fc2c @ 0x0101fc2c
 * public-name: FUN_0101fc2c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ccm_op_status                      @ 0x210014d8
 */
/* net-core FUN_0101fc2c @ 0x101fc2c  (parity 300 trials PROVEN) */

void FUN_0101fc2c(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)0x210014d8;
    p[0] = 0;
    *(volatile unsigned short *)(p + 1) = 0x1000;
}
