/* net-core FUN_0102689c @ 0x0102689c, exact Thumb extent 0x32 bytes. */
#include <stdint.h>

extern uint16_t FUN_01026872(uint16_t link_units, uint8_t packet_mode);
#define controller_encoded_stride_get FUN_01026872 /* raw back-map: 0x01026872 */
#define controller_encoded_stride_scale FUN_0102689c /* raw back-map: 0x0102689c */

/* Scale one encoded packet stride, retaining the controller's 16-bit ABI. */
uint16_t controller_encoded_stride_scale(uint16_t link_units,
                                         uint8_t packet_mode,
                                         uint16_t stride_count)
{
    /* The private ABI does not require unused upper argument bits to be
     * canonical, so mirror the firmware's explicit STRH/STRB narrowing. */
    volatile uint16_t narrowed_link_units = link_units;
    volatile uint8_t narrowed_packet_mode = packet_mode;
    volatile uint16_t narrowed_stride_count = stride_count;
    uint16_t encoded_stride =
        controller_encoded_stride_get(narrowed_link_units,
                                      narrowed_packet_mode);

    return (uint16_t)((uint32_t)encoded_stride *
                      (uint32_t)narrowed_stride_count);
}
