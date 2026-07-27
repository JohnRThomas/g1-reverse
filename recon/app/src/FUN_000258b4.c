/* Reconstructed FUN_000258b4 @ 0x000258b4, extent 0x000000a0.
 * Readable identity: transport_parameters_read.
 * Raw/address backmap: transport_parameters_read <= FUN_000258b4 @ 0x000258b4.
 */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00025788(uint32_t transport, uint32_t key,
                        void *value, uint32_t length);

int FUN_000258b4(uint32_t transport, uint32_t *value, uint32_t *result_value)
{
    uint8_t status = 0U;
    uint32_t received = 0U;
    int result;

    if (transport == 0U || value == 0 || result_value == 0)
        return -1;
    result = FUN_00025788(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        DEBUG_PRINT(0x0009f2f8UL);
        return -2;
    }
    if ((status & 5U) != 5U)
        return -3;
    result = FUN_00025788(transport, 0x2007U, &received, 1U);
    if (result != 0) {
        DEBUG_PRINT(0x0009f32dUL);
        return -4;
    }
    *result_value = received;
    result = FUN_00025788(transport, 0x2008U, value, 0xffU);
    if (result != 0) {
        DEBUG_PRINT(0x0009f361UL);
        return -5;
    }
    return 0;
}
