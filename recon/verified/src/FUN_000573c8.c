/* Reconstructed FUN_000573c8 @ 0x573c8
 * CFG_VERIFY_CALL_ARITIES=3
 * Readable identity: Bluetooth buffer-allocation failure logger.
 * Raw/address backmap: FUN_000573c8 @ 0x000573c8.
 */

#include <stdint.h>

extern void FUN_00081746(uint32_t source, uint32_t descriptor,
                         const void *package);

int FUN_000573c8(uint32_t buffer_type)
{
    const uint32_t log_package[3] = {
        3U,
        0x000f3ec2UL,
        buffer_type,
    };

    FUN_00081746(0x00088160UL, 0x1840U, log_package);
    return 0;
}
