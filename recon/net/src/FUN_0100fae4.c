/* CPUNET controller timing-state finisher @ 0x0100fae4.
 * Raw back-map: FUN_0100fae4@0x0100fae4; true executable extent 0x20. */
#include <stdint.h>

extern void controller_timing_snapshot_enqueue(uint16_t handle,
                                               void *timing_snapshot,
                                               void *queue_node);

void FUN_0100fae4(const uint8_t *owner)
{
    uint8_t *connection = *(uint8_t *const *)(owner + 4);

    if (connection[0x64] == 1) {
        connection[0x64] = 2;
        return;
    }

    controller_timing_snapshot_enqueue(*(uint16_t *)connection,
                                       connection + 0x30,
                                       connection + 0x1ce);
}
