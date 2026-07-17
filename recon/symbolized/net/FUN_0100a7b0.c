#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a7b0 @ 0x0100a7b0
 * public-name: FUN_0100a7b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a7b0 @ 0x100a7b0  (parity 300 trials PROVEN) */

extern void FUN_0100a718(void);
extern void FUN_0100a760(void);
#define DAT_0100a7c8 ((unsigned int)0x4100f000)

void FUN_0100a7b0(void)
{
    FUN_0100a718();
    FUN_0100a760();
    *(volatile unsigned int *)(DAT_0100a7c8 + 0x508) = 0x1ff8;
    return;
}
