/* FUN_010280d8 @ 0x010280d8: zero-option wrapper around the private helper. */
#include <stdint.h>

extern uint32_t FUN_01028034(uint32_t argument, uint32_t option);

uint32_t controller_private_option_zero(uint32_t argument)
{
    return FUN_01028034(argument, 0u);
}

/* Raw identity/back-map: FUN_010280d8 @ 0x010280d8, true extent 0x1a. */
extern __typeof(controller_private_option_zero) FUN_010280d8
    __attribute__((alias("controller_private_option_zero")));
