/* readable reconstruction; identity: FUN_0100bc1c @ 0x0100bc1c
 * public-name: controller_status_defaults_reset
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_status_defaults_reset         <= FUN_0100bc1c @ 0x0100bc1c
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_status_defaults_reset @ 0x0100bc1c.
 * Raw/address backmaps:
 *   FUN_0100bc1c@0x0100bc1c
 *   memory_fill = FUN_01025a84@0x01025a84
 *   controller_state = 0x21000d18
 */
#include <stddef.h>
#include <stdint.h>
#define controller_status_defaults_reset controller_status_defaults_reset

struct controller_status_defaults {
    uint8_t prefix[0x18a];
    volatile uint8_t first;
    volatile uint8_t second;
    volatile uint16_t duration;
};

extern struct controller_status_defaults *
FUN_01025a84(void *destination, int value, size_t length);
#define memory_fill FUN_01025a84

void controller_status_defaults_reset(void)
{
    struct controller_status_defaults *status =
        memory_fill((void *)0x21000d18u, 0, 0x18au);

    status->first = 0;
    status->second = 0;
    status->duration = 900u;
}
