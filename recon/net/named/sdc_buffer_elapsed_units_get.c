/* readable reconstruction; identity: FUN_01026d3e @ 0x01026d3e
 * public-name: sdc_buffer_elapsed_units_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_buffer_elapsed_units_get             <= FUN_01026d3e @ 0x01026d3e
 */
/* net-core FUN_01026d3e @ 0x1026d3e  (CFG-directed candidate) */
#include <stdint.h>

extern uint32_t FUN_01026872(uint16_t link_value, uint8_t mode);

/* Raw back-map: FUN_01026d3e @ 0x01026d3e, exact extent 0x70 bytes. */
uint32_t sdc_buffer_elapsed_units_get(const uint8_t *state)
{
    uint16_t previous_raw = *(const uint16_t *)(state + 6);
    uint16_t current_raw = *(const uint16_t *)(state + 8);
    int32_t delta = (int32_t)(current_raw & 0x7fffu) -
                    (int32_t)(previous_raw & 0x7fffu);

    if ((int16_t)(previous_raw ^ current_raw) >= 0) {
        delta += *(const uint16_t *)(state + 2);
    }

    volatile uint16_t divisor =
        (uint16_t)FUN_01026872(*(const uint16_t *)state, state[0x13]);
    return (uint16_t)(delta / (int32_t)divisor);
}
