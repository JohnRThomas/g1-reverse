/* readable reconstruction; identity: FUN_0100e5f4 @ 0x0100e5f4
 * public-name: FUN_0100e5f4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e5f4 @ 0x100e5f4  (CFG-directed candidate) */
void FUN_0100e5f4(unsigned char *p, unsigned int value)
{
    *p = (unsigned char)((*p & 0xdfu) | ((value << 5) & 0x20u));
}
