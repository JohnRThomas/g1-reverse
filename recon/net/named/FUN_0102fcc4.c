/* readable reconstruction; identity: FUN_0102fcc4 @ 0x0102fcc4
 * public-name: FUN_0102fcc4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_047fc                              @ 0x210047fc
 */
/* net-core FUN_0102fcc4 @ 0x102fcc4  (parity 300 trials PROVEN) */

extern void FUN_0102ff54(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_0102fcc4(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned int * const p = (volatile unsigned int * const)0x210047fc;
    FUN_0102ff54(*p, param_1, param_3, (unsigned int)p);
    return 0;
}
