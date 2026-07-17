/* readable reconstruction; identity: FUN_01034b18 @ 0x01034b18
 * public-name: FUN_01034b18
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_4100a308                             @ 0x4100a308
 */
/* net-core FUN_01034b18 @ 0x1034b18 */
#include <stdint.h>
extern int FUN_010344d4(void);
extern int FUN_01034508(uint32_t);
extern uint32_t FUN_01034520(uint32_t);
extern void FUN_0103a9be(uint32_t, uint32_t);

void FUN_01034b18(uint32_t context)
{
    if (FUN_010344d4() != 0 && FUN_01034508(context) == 0) {
        uint32_t index = FUN_01034520(context);
        *(volatile uint32_t *)0x4100a308 = 1u << index;
        volatile uint32_t *control =
            (volatile uint32_t *)(0x4100a510 + index * 4);
        *control &= ~3u;
        return;
    }
    FUN_0103a9be(context, 0);
}
