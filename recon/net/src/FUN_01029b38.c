/* CPUNET private state predicate @ 0x01029b38.
 * Raw back-map: FUN_01029b38@0x01029b38; extent 0x16. */
#include <stdint.h>

extern unsigned controller_state_mode_is_invalid(const void *state); /* FUN_01029b24 */

unsigned FUN_01029b38(const uint8_t *state)
{
    if (state[0x10] == 1)
        return 1;
    return controller_state_mode_is_invalid(state) & 1u;
}
