#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021838 @ 0x01021838
 * public-name: FUN_01021838
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01021838 @ 0x1021838 — true CFG extent 30 bytes (ends 0x1021856) */
#include <stdint.h>

extern void FUN_01021800(void);
extern void FUN_010217cc(void);

void FUN_01021838(int32_t param_1)
{
    volatile uint8_t * const g = (uint8_t *)G1N_21001670;

    FUN_01021800();
    *(volatile uint8_t *)(param_1 + 0x80) = 0;
    g[10] = g[10] - 1;
    FUN_010217cc();
}
