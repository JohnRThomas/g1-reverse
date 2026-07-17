/* readable reconstruction; identity: FUN_0100d5d0 @ 0x0100d5d0
 * public-name: FUN_0100d5d0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100d5d0 @ 0x100d5d0  (parity 300 trials PROVEN) */

unsigned int FUN_0100d5d0(unsigned int param_1)
{
  unsigned int hi;
  if ((param_1 - 0x3e8) > 0x1770) {
    hi = (unsigned int)(((unsigned long long)0xd1b71759u * param_1) >> 32);
    return (hi >> 10) & 0xffff;
  }
  hi = (unsigned int)(((unsigned long long)0x10624dd3u * param_1) >> 32);
  return (unsigned short)((hi >> 6) + 0xd00);
}
