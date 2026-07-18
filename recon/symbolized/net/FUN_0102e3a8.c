#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e3a8 @ 0x0102e3a8
 * public-name: FUN_0102e3a8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d6b5                           @ 0x0103d6b5
 */
/* net-core static log-message package builder @ 0x0102e3a8.
 * Raw/address back-map: FUN_0102e3a8 / 0x0102e3a8.
 */
#include <stdint.h>

extern int FUN_0102bbec(void *, uint32_t, const void *, uint32_t, const void *);
extern void *FUN_0102def4(uint32_t);
extern void FUN_0103a2f8(void *, const void *, uint32_t, const void *);
extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t);

void FUN_0102e3a8(uint32_t domain, const void *source, uint32_t level,
                  const void *data, uint32_t data_len, const void *package,
                  uint32_t package_len, const void *package_arg)
{
    int converted_len;
    if (package_len == 0) {
        converted_len = 0;
    } else {
        converted_len = FUN_0102bbec(0, 0x10, package, package_len, package_arg);
        if (converted_len < 0) {
            assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                         (const void *)((unsigned long)&rodata_103d6b5) /*=0x103d6b5*/, 0x78);
            assert_post_action((const void *)((unsigned long)&rodata_103d6b5) /*=0x103d6b5*/, 0x78);
        }
    }

    uint32_t descriptor = ((domain & 7u) << 3) | ((level & 7u) << 6) |
                          (((uint32_t)converted_len << 9) & 0x000ffe00u) |
                          (data_len << 20);
    void *message = FUN_0102def4((data_len + 0x17u +
                                  (uint32_t)converted_len & ~7u) >> 2);
    if (message != 0 && package_len != 0) {
        if (FUN_0102bbec((uint8_t *)message + 0x10, (uint32_t)converted_len,
                         package, package_len, package_arg) < 0) {
            assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                         (const void *)((unsigned long)&rodata_103d6b5) /*=0x103d6b5*/, 0x92);
            assert_post_action((const void *)((unsigned long)&rodata_103d6b5) /*=0x103d6b5*/, 0x92);
        }
    }
    FUN_0103a2f8(message, source, descriptor, data);
}
