#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c3d0 @ 0x0007c3d0
 * public-name: pt_write_frame_type3
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   packet_transport_write_frame             <= FUN_00024e60 @ 0x00024e60
 *   pt_write_frame_type3                     <= FUN_0007c3d0 @ 0x0007c3d0
 */
/* Reconstructed FUN_0007c3d0 @ 0x7c3d0.
 * Complete ten-byte argument-shuffling tail wrapper; 0x7c3da starts the next
 * function.  Bit zero in 0x24e61 selects Thumb state for the 0x24e60 target. */
extern int packet_transport_write_frame(unsigned type, unsigned first, unsigned second);

int pt_write_frame_type3(unsigned first, unsigned second)
{
    return packet_transport_write_frame(3, first, second);
}
