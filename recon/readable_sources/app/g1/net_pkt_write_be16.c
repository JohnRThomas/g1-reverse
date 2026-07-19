#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d696 @ 0x0007d696
 * public-name: net_pkt_write_be16
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_pkt_write_be16                       <= FUN_0007d696 @ 0x0007d696
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 */
/* Reconstructed FUN_0007d696 @ 0x7d696  (parity: 300/300 trials, PROVEN) */

extern void projector_send_command(unsigned int, const void *, unsigned int);

void net_pkt_write_be16(unsigned int value)
{
    unsigned short big_endian =
        (unsigned short)((value << 8) | ((value >> 8) & 0xffu));
    projector_send_command(0x36, &big_endian, sizeof(big_endian));
}
