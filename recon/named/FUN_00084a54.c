/* readable reconstruction; identity: FUN_00084a54 @ 0x00084a54
 * public-name: FUN_00084a54
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00084a54 @ 0x84a54, exact extent 106 bytes. */
#include <stdint.h>

extern void *memset_bytes(void *destination, uint32_t value, uint32_t length);

uint32_t FUN_00084a54(uintptr_t *context_ref, uint8_t *buffer, uint32_t length)
{
    volatile uint8_t *state = (volatile uint8_t *)(uintptr_t)*context_ref;
    uint32_t generation = *(volatile uint32_t *)(state + 0x53cu);
    uint8_t *validation_buffer;
    uintptr_t fallback[2];

    if (buffer == 0) {
        fallback[0] = (uintptr_t)context_ref;
        fallback[1] = 0;
        buffer = (uint8_t *)fallback;
        validation_buffer = 0;
        length = 5u;
    } else {
        validation_buffer = memset_bytes(buffer, 0u, length);
        buffer = validation_buffer;
    }

    *(volatile uint8_t **)(state + 0x534u) = buffer;
    *(volatile uint32_t *)(state + 0x538u) = length;
    *(volatile uint32_t *)(state + 0x110u) = 0;
    *(volatile uint32_t *)(state + 0x2cu) = 1;
    while (*(volatile uint32_t *)(state + 0x110u) == 0)
        ;
    *(volatile uint32_t *)(state + 0x110u) = 0;

    uint32_t current_generation = *(volatile uint32_t *)(state + 0x53cu);
    if (validation_buffer != 0 && generation == current_generation) {
        uint8_t *end = validation_buffer + length;
        for (uint8_t *p = validation_buffer; p != end; ++p) {
            if (*p != 0)
                return current_generation & 0xffu;
        }
        return 0;
    }
    return current_generation & 0xffu;
}
