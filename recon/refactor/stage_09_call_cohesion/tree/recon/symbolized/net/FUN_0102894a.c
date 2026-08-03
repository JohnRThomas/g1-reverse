#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102894a @ 0x0102894a
 * public-name: FUN_0102894a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102894a @ 0x0102894a
 * Dispatch a compact controller command record.
 */
#include <stdint.h>

extern uint32_t FUN_010283b8(void);
extern void FUN_01028296(uint32_t type, const uint8_t *payload,
                         uint32_t context, uint32_t caller_context);
extern uint32_t FUN_01010834(void);
extern void FUN_0100bc44(void);

uint32_t FUN_0102894a(const uint8_t *command, uint32_t unused,
                      uint32_t context, uint32_t caller_context)
{
    uint32_t busy = FUN_010283b8();
    uint8_t type;
    (void)unused;

    if (busy != 0u) {
        return 0x0cu;
    }
    type = command[0];
    if (type <= 1u) {
        FUN_01028296(type, command + 1u, context, caller_context);
        return FUN_01010834() == 0u ? 0x12u : 0u;
    }
    if (type == 0xffu) {
        FUN_0100bc44();
        return 0u;
    }
    return 0x12u;
}
