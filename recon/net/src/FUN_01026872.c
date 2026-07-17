/* net-core FUN_01026872 @ 0x01026872, exact Thumb extent 0x2a bytes. */
#include <stdint.h>

extern uint16_t controller_packet_overhead_span_get(uint8_t packet_mode); /* FUN_01026856 */

/* Return the complete encoded stride: link/payload units plus mode overhead. */
uint16_t FUN_01026872(uint16_t link_units, uint8_t packet_mode)
{
    volatile uint8_t narrowed_mode = packet_mode;
    return (uint16_t)(link_units +
                      controller_packet_overhead_span_get(narrowed_mode));
}
