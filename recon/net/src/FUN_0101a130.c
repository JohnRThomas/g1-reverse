/* net-core FUN_0101a130 @ 0x101a130  (CFG-directed candidate) */

#include <stdint.h>
extern int FUN_01025d28(void);
extern int controller_radio_work_pending(void);
extern void FUN_01021908(int8_t *state);
extern void FUN_01021914(int8_t *state);

uint32_t radio_slot_margin_get(void)
{
    uint32_t active_margin;
    uint32_t idle_margin;
    int8_t first_state;
    int8_t second_state;

    if (FUN_01025d28() != 0) {
        active_margin = 0x15cu;
        idle_margin = 0x152u;
    } else if (controller_radio_work_pending() != 0) {
        active_margin = 0x153u;
        idle_margin = 0x149u;
    } else {
        active_margin = 0x144u;
        idle_margin = 0x13au;
    }

    FUN_01021908(&first_state);
    FUN_01021914(&second_state);
    return (first_state != 0 || second_state != 0) ? active_margin : idle_margin;
}
