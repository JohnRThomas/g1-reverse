/* readable reconstruction; identity: FUN_01032680 @ 0x01032680
 * public-name: FUN_01032680
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_1032e41                           @ 0x01032e41
 *   rodata_103e386                           @ 0x0103e386
 */
/* net-core system workqueue initialization @ 0x01032680.
 * Raw/address back-map: FUN_01032680 / 0x01032680.
 */
#include <stdint.h>

extern void FUN_0103b512(void *);
extern uint32_t FUN_01035fa0(uint32_t, uint32_t, uint32_t, uint32_t,
                            uint32_t, uint32_t, uint32_t, uint32_t,
                            uint32_t, uint32_t, int32_t, int32_t);
extern uint32_t FUN_0103b156(uint32_t, const void *);

void FUN_01032680(void)
{
    FUN_0103b512((void *)0x21004988u);
    FUN_01035fa0(0x21004258u, 0x21008a00u, 0x388u, 0x01032e41u,
                 0, 0, 0, 10, 0, 0, 0, 0);
    FUN_0103b156(0x21004258u, (const void *)0x0103e386u);
}
