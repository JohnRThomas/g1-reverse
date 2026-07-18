/* net-core FUN_0100d6e8 @ 0x100d6e8  (CFG-directed candidate) */

#include <stdint.h>
#include <stdbool.h>
/* Raw identity/back-map: FUN_0100d6e8 @ 0x0100d6e8. */
bool sdc_conn_recovery_window_update(uint32_t event_time, uint32_t reference_time,
                                     int32_t *window_start, int32_t *window_end)
{
    uint32_t threshold = event_time - 0x1d8u;
    uint32_t delta = reference_time < threshold ? 0u : reference_time - threshold;
    *window_end += (int32_t)(delta >> 1);
    *window_start -= (int32_t)(delta >> 1);
    return delta > 1u;
}
extern __typeof(sdc_conn_recovery_window_update) FUN_0100d6e8
    __attribute__((alias("sdc_conn_recovery_window_update")));
