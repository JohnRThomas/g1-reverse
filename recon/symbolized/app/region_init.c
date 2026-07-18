#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00050bf0 @ 0x00050bf0
 * public-name: region_init
 * durable-map: recon/catalogs/function_names_app.json
 */
/* region_init @ 0x00050bf0; raw FUN_00050bf0 */
#include <stdint.h>

struct arm_mpu_region_attr {
    uint32_t rbar;
    uint8_t mair_idx;
    uint8_t pad[3];
    uint32_t r_limit;
};

struct arm_mpu_region {
    uint32_t base;
    struct arm_mpu_region_attr attr;
};

void region_init(uint32_t index, const struct arm_mpu_region *region)
{
    *(volatile uint32_t *)0xe000ed98u = index;
    *(volatile uint32_t *)0xe000ed9cu =
        (region->base & 0xffffffe0u) | (region->attr.rbar & 0x1fu);
    *(volatile uint32_t *)0xe000eda0u =
        (region->attr.r_limit & 0xffffffe0u) |
        (((uint32_t)region->attr.mair_idx << 1) & 0x0eu) | 1u;
}
