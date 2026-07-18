/* CPUNET payload-time budget helper @ 0x0100f5b4.
 * Raw back-map: FUN_0100f5b4=controller_payload_time_get;
 * true executable extent 0x16. */
#include <stdint.h>

uint32_t FUN_0100f5b4(const uint32_t *timing, uint32_t overhead)
{
    uint32_t total = *timing;
    uint32_t reserved = overhead + 0x9cu;

    return total > reserved ? (total - reserved) >> 1 : 0u;
}
