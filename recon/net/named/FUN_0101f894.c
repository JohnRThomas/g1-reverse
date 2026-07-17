/* readable reconstruction; identity: FUN_0101f894 @ 0x0101f894
 * public-name: FUN_0101f894
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_flags_bitmap64                     @ 0x21000020
 */
/* net-core FUN_0101f894 @ 0x101f894  (parity 300 trials PROVEN) */

#define DAT_0101f8ac ((unsigned int)0x21000020)

void FUN_0101f894(unsigned int param_1)
{
    unsigned int idx = param_1 >> 3;
    unsigned char bit = (unsigned char)(1 << (param_1 & 7));
    *(volatile unsigned char *)(DAT_0101f8ac + idx) = bit | *(volatile unsigned char *)(DAT_0101f8ac + idx);
    return;
}
