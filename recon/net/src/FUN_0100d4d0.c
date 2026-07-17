/* net-core FUN_0100d4d0 @ 0x100d4d0  (CFG-directed candidate) */

#include <stdint.h>

extern int32_t FUN_01022f3c(void *request, uint32_t unit,
                            uint32_t arg2, uint32_t arg3);
extern void FUN_01008d00(uint32_t file_id, uint32_t line);

#define controller_timing_request_submit FUN_01022f3c
#define sdc_assertion_fail FUN_01008d00

uint32_t FUN_0100d4d0(void *request, uint32_t unit,
                      uint32_t arg2, uint32_t arg3)
{
    volatile uint32_t *fields = (volatile uint32_t *)request;
    uint32_t before_low = fields[4];
    uint32_t before_high = fields[5];

    if (controller_timing_request_submit(request, unit, arg2, arg3) == 0)
        sdc_assertion_fail(0x29U, 0x1d3U);

    if (unit == 0)
        return 0;

    uint32_t after_low = fields[4];
    uint32_t after_high = fields[5];
    uint32_t delta_low = after_low - before_low;
    int32_t delta_high = (int32_t)(after_high - before_high -
                                   (after_low < before_low));
    uint64_t delta = ((uint64_t)(uint32_t)delta_high << 32) | delta_low;
    if ((int64_t)delta < 1)
        return 0;
    if ((int64_t)delta > 0xfffffffeLL)
        sdc_assertion_fail(0x29U, 0x1ddU);

    uint32_t count = (delta_low + (unit - 1U)) / unit;
    uint32_t increment = count * unit;
    uint32_t scheduled_low = before_low + increment;
    fields[4] = scheduled_low;
    fields[5] = before_high + (scheduled_low < before_low);
    return count;
}
