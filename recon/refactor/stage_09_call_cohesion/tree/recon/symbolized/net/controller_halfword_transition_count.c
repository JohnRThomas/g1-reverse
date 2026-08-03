#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f748 @ 0x0100f748
 * public-name: controller_halfword_transition_count
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_halfword_transition_count     <= FUN_0100f748 @ 0x0100f748
 */
/* net-core FUN_0100f748 @ 0x100f748  (CFG-directed candidate) */
/* Role: transition count over a signed 16-bit controller word. Back-map: FUN_0100f748. */
#include <stdint.h>
uint32_t controller_halfword_transition_count(uint32_t value)
{
    uint32_t folded = value ^ (uint32_t)(uint16_t)((int16_t)value >> 1);
    folded = (folded & 0x5555u) + ((folded >> 1) & 0x5555u);
    folded = (folded & 0x3333u) + ((folded >> 2) & 0x3333u);
    folded = (folded & 0x0f0fu) + ((folded >> 4) & 0x0f0fu);
    return (folded + (folded >> 8)) & 0xffu;
}
