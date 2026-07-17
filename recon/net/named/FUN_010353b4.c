/* readable reconstruction; identity: FUN_010353b4 @ 0x010353b4
 * public-name: FUN_010353b4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103e867                           @ 0x0103e867
 *   g_net_debug_trace_level                  @ 0x21004b04
 *   g_net_debug_trace_cb                     @ 0x21004b08
 */
/* net-core FUN_010353b4 @ 0x10353b4  (parity 300 trials PROVEN) */

typedef void (*fp3_t)(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b522(int param_1);

void FUN_010353b4(int param_1)
{
  if (param_1 != 0) {
    if ((*(volatile short *)(param_1 + 0x24) != *(volatile short *)(param_1 + 0xa)) &&
        (3 < *(volatile unsigned char *)0x21004b04u) &&
        (*(volatile fp3_t *)0x21004b08u != (fp3_t)0)) {
      (*(volatile fp3_t *)0x21004b08u)(4, 0x0103e867u, *(volatile unsigned int *)(param_1 + 4));
    }
    FUN_0103b522(param_1);
    return;
  }
  return;
}
