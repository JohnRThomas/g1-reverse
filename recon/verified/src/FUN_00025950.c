/* Reconstructed FUN_00025950 @ 0x00025950, extent 0x0000007c.
 * Readable identity: transport_parameters_write.
 * Raw/address backmap: transport_parameters_write <= FUN_00025950 @ 0x00025950.
 */
#include <stdint.h>

extern int DEBUG_PRINT(uintptr_t format, ...);
extern int FUN_00025788(uint32_t transport, uint32_t key,
                        void *value, uint32_t length);
extern int FUN_000256dc(uint32_t transport, uint32_t key,
                        const void *value, uint32_t length);

int FUN_00025950(uint32_t transport, const void *value, uint32_t length)
{
    uint8_t status = 0U;
    int result;

    if (transport == 0U || value == 0 || length == 0U)
        return -1;
    result = FUN_00025788(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        DEBUG_PRINT(0x0009f2f8UL);
        return -2;
    }
    if ((status & 6U) != 0U) {
        DEBUG_PRINT(0x0009f396UL);
        return -3;
    }
    result = FUN_000256dc(transport, 0x2008U, value, length);
    if (result != 0) {
        DEBUG_PRINT(0x0009f3caUL);
        return -3;
    }
    status = 1U;
    result = FUN_00025788(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        DEBUG_PRINT(0x0009f2f8UL);
        return -2;
    }
    return 0;
}
