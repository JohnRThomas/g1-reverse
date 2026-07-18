/* Reconstructed flash_write_close_ate_marker @ 0x00084e44.
 * Raw/address back-map: FUN_00084e44 / 0x00084e44.
 */
#include <stdint.h>

#define flash_write_padded_entry FUN_00084dea
extern int flash_write_padded_entry(uintptr_t peripheral, uint32_t destination,
                                    const void *source, uint32_t length);

#define flash_write_close_ate_marker FUN_00084e44
void flash_write_close_ate_marker(uintptr_t peripheral, uint32_t destination,
                                  uint8_t marker)
{
    (void)flash_write_padded_entry(peripheral, destination, &marker, 1u);
}
