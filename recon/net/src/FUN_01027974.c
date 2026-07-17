/* net-core FUN_01027974 @ 0x01027974
 * semantic name: controller_block_chain_records_init
 * back-map: raw identity FUN_01027974
 */
#include <stdint.h>

uint32_t FUN_01027974(void *storage, uint32_t header_size,
                      uint16_t block_count, uint32_t block_stride)
{
    uintptr_t cursor = (uintptr_t)storage + header_size;
    uint32_t total_size = header_size + block_stride;
    volatile uint16_t remaining = block_count;

    while ((uint16_t)(remaining = (uint16_t)(remaining - 1u)) != 0u) {
        if (storage != 0) {
            volatile uint32_t *words = (volatile uint32_t *)cursor;
            uintptr_t next = cursor + block_stride;

            words[0] = 0u;
            words[1] = 0u;
            *(volatile uint8_t *)(cursor + 8u) = 0u;
            words[0] = (uint32_t)next;
            cursor = next;
        }
        total_size += block_stride;
    }

    if (storage != 0) {
        volatile uint32_t *words = (volatile uint32_t *)cursor;

        words[0] = 0u;
        words[1] = 0u;
        *(volatile uint8_t *)(cursor + 8u) = 0u;
    }
    return total_size;
}
