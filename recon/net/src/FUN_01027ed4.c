/* FUN_01027ed4 @ 0x01027ed4: fixed-mode wrapper around the private helper. */
#include <stdint.h>

extern uint32_t FUN_01027e1c(uint32_t first, uint32_t second, uint32_t mode);

uint32_t controller_private_mode_one(uint32_t first, uint32_t second)
{
    return FUN_01027e1c(first, second, 1u);
}

/* Raw identity/back-map: FUN_01027ed4 @ 0x01027ed4, true extent 0x1e. */
extern __typeof(controller_private_mode_one) FUN_01027ed4
    __attribute__((alias("controller_private_mode_one")));
