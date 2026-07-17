/* net-core FUN_0101de10 @ 0x101de10  (CFG-directed candidate) */

#include <stdint.h>

extern void FUN_01008d00(uint32_t file_id, uint32_t line);
#define sdc_assertion_fail FUN_01008d00

uint32_t FUN_0101de10(uint32_t time_low, int32_t time_high,
                      uint32_t period, uint32_t unused,
                      uint32_t origin_low, int32_t origin_high)
{
    (void)unused;
    uint32_t delta_low = time_low - origin_low;
    int32_t delta_high = time_high - origin_high - (time_low < origin_low);
    uint64_t shifted = ((uint64_t)(uint32_t)delta_high << 32) | delta_low;
    shifted += 0x7fffffffULL;
    if (shifted > 0x00000000fffffffdULL)
        sdc_assertion_fail(0x37U, 0xbdU);

    if (delta_high < 0) {
        uint32_t remainder = (0U - delta_low) % period;
        if (remainder != 0)
            return period - remainder;
        return 0;
    }
    return delta_low % period;
}
