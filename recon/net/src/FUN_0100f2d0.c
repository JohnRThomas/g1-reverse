/* net-core FUN_0100f2d0 @ 0x100f2d0  (CFG-directed candidate) */
/* Role: controller_packet_result_prepare. Back-map: FUN_0100f2d0. */
#include <stdint.h>
extern void FUN_0100eec8(void *node, uintptr_t callback);

void FUN_0100f2d0(uint16_t packet_kind, const void *timing_record,
                  void *work_node)
{
    const uint8_t *src = (const uint8_t *)timing_record;
    volatile uint8_t *dst = (volatile uint8_t *)work_node;
    *(volatile uint16_t *)(dst + 0x09) = packet_kind;
    *(volatile uint16_t *)(dst + 0x0b) = *(const uint16_t *)(src + 0x14);
    *(volatile uint16_t *)(dst + 0x0d) = *(const uint16_t *)(src + 0x16);
    *(volatile uint16_t *)(dst + 0x0f) = *(const uint16_t *)(src + 0x18);
    *(volatile uint16_t *)(dst + 0x11) = *(const uint16_t *)(src + 0x1a);
    FUN_0100eec8(work_node, 0x0100f805u); /* controller_work_enqueue_packet_result */
}
