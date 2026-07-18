/* net-core FUN_010298a8 @ 0x010298a8
 * Normalize controller mode flags to one supported mode.
 */
#include <stdint.h>

uint32_t FUN_010298a8(uint32_t mode)
{
    if (mode != 1u && mode != 2u) {
        mode &= 0x0cu;
        if (mode != 0u) {
            mode = 4u;
        }
    }
    return mode;
}
