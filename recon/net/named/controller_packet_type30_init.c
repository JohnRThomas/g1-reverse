/* readable reconstruction; identity: FUN_01029bea @ 0x01029bea
 * public-name: controller_packet_type30_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_type30_init            <= FUN_01029bea @ 0x01029bea
 */
/* net-core FUN_01029bea @ 0x1029bea  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0101f924(void);
void controller_packet_type30_init(volatile uint8_t *packet)
{
    packet[3] = 0x1eu;
    packet[4] = (uint8_t)FUN_0101f924();
}
