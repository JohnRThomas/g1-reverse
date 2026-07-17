#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068a10 @ 0x00068a10
 * public-name: FUN_00068a10
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_884f0                             @ 0x000884f0
 *   rodata_8bbc0                             @ 0x0008bbc0
 *   rodata_8bbe0                             @ 0x0008bbe0
 */
/* Full reconstruction FUN_00068a10 @ 0x00068a10 (246-byte exact extent). */
#include <stdint.h>

uint32_t FUN_00068a10(int32_t profile, uint32_t count, const float *samples)
{
    if (count == 0) return 0;

    uint32_t selected = 0;
    uint32_t lane = 0;
    const int8_t *ranges = (const int8_t *)((unsigned long)&rodata_8bbe0) /*=0x8bbe0*/
        + (((count - 1u) + (uint32_t)profile * 4u) * 16u);

    do {
        int32_t first = ranges[lane * 4u];
        int32_t last = ranges[lane * 4u + 1u];
        float sum = samples[first];
        for (int32_t i = first + 1; i < last; ++i) sum += samples[i];
        int32_t scale = lane == 0 ? 20 : 10;
        lane = (lane + 1u) & 0xffu;
        if ((float)((int64_t)(last - first) * scale) <= sum) selected = lane;
    } while (lane < count);

    if (count <= selected) return selected;

    int32_t last = ranges[selected * 4u];
    int32_t width = *(const int32_t *)(((unsigned long)&rodata_8bbc0) /*=0x8bbc0*/
        + (((uint32_t)profile * 4u + selected) * 4u));
    float factor = *(const float *)(((unsigned long)&rodata_884f0) /*=0x884f0*/ + selected * 4u);
    int32_t cursor = last - width;
    if (width >= 0) {
        const float *older = samples + ((cursor + 1) - width);
        const float *newer = samples + cursor + 1;
        do {
            float new_value = *newer++;
            float old_value = *older++;
            ++cursor;
            if (new_value * factor < old_value) return selected;
        } while (cursor <= last);
    }
    return count;
}
