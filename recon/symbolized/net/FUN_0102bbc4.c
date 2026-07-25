#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102bbc4 @ 0x0102bbc4
 * public-name: FUN_0102bbc4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102bbc4 @ 0x102bbc4  (CFG-directed candidate) */
/* net-core FUN_0102bbc4 @ 0x102bbc4
 * ESB transport transition reached from the cpunet-hw-id IPC handler's
 * sub-command 8.  Both callees take exactly one argument, so the reviewed ABI
 * is declared: CFG_VERIFY_CALL_ARITIES=1,1
 */
#include <stdint.h>
extern void FUN_0102b758(uint32_t transition);
extern int FUN_0102b900(uint32_t value);

void FUN_0102bbc4(void)
{
    *(volatile uint8_t *)G1N_21004fa5 = 1u;
    FUN_0102b758(1u);
    FUN_0102b900(3u);
}
