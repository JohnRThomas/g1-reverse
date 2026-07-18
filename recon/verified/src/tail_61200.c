/* Compiler-outlined cold error path of Zephyr flash_nrf_read @ 0x00061200.
 * Raw/address back-map: tail_61200 / 0x00061200.
 */
#include <stddef.h>
#include <stdint.h>

struct flash_address_log_record_raw {
    uint32_t count;
    uint32_t format;
    int32_t address;
    size_t length;
};

extern void FUN_0004d944(uintptr_t source, uint32_t level,
                         const void *record, uint32_t reserved);

#define log_output_record               FUN_0004d944 /* 0x0004d944 */
int flash_nrf_read_invalid_address(int32_t address, size_t length)
{
    const struct flash_address_log_record_raw diagnostic = {
        4,
        0x000f5d81,
        address,
        length,
    };

    log_output_record(0x000881b0, 0x2040, &diagnostic, 0);
    return -22;
}
