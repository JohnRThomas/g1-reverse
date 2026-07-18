/* readable reconstruction; identity: FUN_01028010 @ 0x01028010
 * public-name: FUN_01028010
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01028010 @ 0x01028010, exact executable extent 0x24. */
/*
 * Retained private-controller reconstruction.
 * Raw entry/backmap: FUN_01028010 @ 0x01028010, exact extent 0x24.
 */
#include <stdint.h>

extern uint16_t FUN_01027fa6(const void *link, uint8_t side);

#define controller_primary_slot_is_configured FUN_01028010

uint8_t controller_primary_slot_is_configured(const void *link)
{
    return FUN_01027fa6(link, 0u) != 0u;
}
