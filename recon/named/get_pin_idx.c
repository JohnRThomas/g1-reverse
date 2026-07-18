/* readable reconstruction; identity: FUN_00065434 @ 0x00065434
 * public-name: get_pin_idx
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f6ba7                             @ 0x000f6ba7
 */
/* Reconstructed get_pin_idx @ 0x65434  (CFG-directed candidate) */
#include <stdint.h>
uint8_t get_pin_idx(uint32_t pin) {
    const volatile uint8_t *port_offset = (const volatile uint8_t *)0x000f6ba7u;
    return (uint8_t)(port_offset[pin >> 5] + (pin & 0x1fu));
}
