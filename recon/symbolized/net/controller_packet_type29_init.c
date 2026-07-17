#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01029bda @ 0x01029bda
 * public-name: controller_packet_type29_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_type29_init            <= FUN_01029bda @ 0x01029bda
 */
/* net-core FUN_01029bda @ 0x1029bda  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0101f924(void);
void controller_packet_type29_init(volatile uint8_t *packet)
{
    packet[3] = 0x1du;
    packet[4] = (uint8_t)FUN_0101f924();
}
