#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e4f4 @ 0x0102e4f4
 * public-name: FUN_0102e4f4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 * address symbols (name @ address):
 *   rodata_102eca1                           @ 0x0102eca1
 *   rodata_103024d                           @ 0x0103024d
 *   rodata_103c924                           @ 0x0103c924
 *   rodata_103c938                           @ 0x0103c938
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d6e1                           @ 0x0103d6e1
 *   rodata_103d710                           @ 0x0103d710
 *   rodata_103d715                           @ 0x0103d715
 *   rodata_103d719                           @ 0x0103d719
 *   rodata_103d722                           @ 0x0103d722
 *   rodata_103d73e                           @ 0x0103d73e
 *   rodata_103d741                           @ 0x0103d741
 *   rodata_103d747                           @ 0x0103d747
 *   rodata_103d74b                           @ 0x0103d74b
 *   rodata_103d750                           @ 0x0103d750
 *   rodata_103d756                           @ 0x0103d756
 *   rodata_103d758                           @ 0x0103d758
 *   rodata_103e850                           @ 0x0103e850
 *   rodata_103e852                           @ 0x0103e852
 *   rodata_103ec11                           @ 0x0103ec11
 *   g_21004670                               @ 0x21004670
 *   g_21004674                               @ 0x21004674
 */
/* net-core log-output formatter and hex-dump renderer @ 0x0102e4f4.
 * Raw/address back-map: FUN_0102e4f4 / 0x0102e4f4.
 */
#include <stdint.h>
#include "../../headers/g1_dedupe.h"

extern int FUN_0102e460(uint32_t, const char *, ...);
extern void FUN_0102e484(uint32_t, uint32_t);
extern int FUN_0103966e(const void *, const void *, uint32_t, const void *);
extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t);
extern uint32_t FUN_0103a2c8(void);
extern void FUN_0103a344(uint32_t);

void FUN_0102e4f4(uint32_t output, uint32_t timestamp, int32_t domain,
                  int32_t level, uint32_t unused, uint8_t type,
                  const void *package, const uint8_t *data,
                  uint32_t data_len, uint32_t flags)
{
    (void)unused;
    int32_t prefix_count = 0;
    const void *formatter = (const void *)0x0103ab5fu;

    if (type != 0) {
        if (type > 4) {
            G1_NET_ASSERT_FAIL(((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, (const void *)((unsigned long)&rodata_103d6e1) /*=0x103d6e1*/, 0x1bf), ((const void *)((unsigned long)&rodata_103d6e1) /*=0x103d6e1*/, 0x1bf));
        }

        uint32_t thread = FUN_0103a2c8();
        int count = thread ? FUN_0102e460(output,
                    (const char *)((unsigned long)&rodata_103d715) /*=0x103d715*/, thread) : 0;

        if (flags & 2u) {
            if ((flags & 0x44u) == 0) {
                count += FUN_0102e460(output, (const char *)((unsigned long)&rodata_103d719) /*=0x103d719*/,
                                      timestamp);
            } else {
                uint32_t frequency = *(volatile uint32_t *)((unsigned long)&g_21004674) /*=0x21004674*/;
                if (frequency != 0) {
                    uint32_t ticks = timestamp /
                                     *(volatile uint32_t *)((unsigned long)&g_21004670) /*=0x21004670*/;
                    uint32_t seconds = ticks / frequency;
                    uint32_t fractional = (ticks % frequency) * 1000u;
                    uint32_t millis = fractional / frequency;
                    uint32_t micros = ((fractional - frequency * millis) *
                                       1000u) / frequency;
                    count += FUN_0102e460(output,
                              (const char *)((unsigned long)&rodata_103d722) /*=0x103d722*/,
                              seconds / 3600u, (seconds % 3600u) / 60u,
                              seconds % 60u, millis, micros);
                }
            }
        }

        if (flags & 1u) {
            const char *tag = *(const char **)(((unsigned long)&rodata_103c924) /*=0x103c924*/ + type * 4u);
            if (tag == 0)
                tag = (const char *)((unsigned long)&rodata_103d710) /*=0x103d710*/;
            FUN_0102e460(output, (const char *)((unsigned long)&rodata_103d73e) /*=0x103d73e*/, tag);
        }

        if (flags & 8u) {
            const char *level_name =
                *(const char **)(((unsigned long)&rodata_103c938) /*=0x103c938*/ + type * 4u);
            prefix_count = FUN_0102e460(
                output, (const char *)((unsigned long)&rodata_103d741) /*=0x103d741*/, level_name);
        } else {
            prefix_count = flags & 8u;
        }
        if (domain != 0)
            prefix_count += FUN_0102e460(
                output, (const char *)((unsigned long)&rodata_103d747) /*=0x103d747*/, domain);
        if (level != 0)
            prefix_count += FUN_0102e460(
                output, (const char *)((unsigned long)&rodata_103d74b) /*=0x103d74b*/, level);
        count += (int)prefix_count;
        prefix_count = count;
        formatter = (const void *)((unsigned long)&rodata_102eca1) /*=0x102eca1*/;
    } else {
        if (level == 1)
            formatter = (const void *)((unsigned long)&rodata_102eca1) /*=0x102eca1*/;
        prefix_count = 0;
    }

    if (package != 0) {
        if (FUN_0103966e(formatter, (const void *)((unsigned long)&rodata_103024d) /*=0x103024d*/,
                         output, package) < 0) {
            G1_NET_ASSERT_FAIL(((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, (const void *)((unsigned long)&rodata_103d6e1) /*=0x103d6e1*/, 0x219), ((const void *)((unsigned long)&rodata_103d6e1) /*=0x103d6e1*/, 0x219));
        }
    }

    if (data_len != 0) {
        const char *blank = (const char *)((unsigned long)&rodata_103e852) /*=0x103e852*/;
        const char *hex = (const char *)((unsigned long)&rodata_103d750) /*=0x103d750*/;
        while (data_len != 0) {
            uint32_t chunk = data_len > 16u ? 16u : data_len;
            FUN_0102e484(output, flags);
            for (int32_t i = 0; i < prefix_count; ++i)
                FUN_0102e460(output, blank);
            FUN_0102e460(output, hex, data[0]);
            for (uint32_t i = 1; i < 16u; ++i) {
                if ((i & 7u) == 0)
                    FUN_0102e460(output, blank);
                if (i < chunk)
                    FUN_0102e460(output, hex, data[i]);
                else
                    FUN_0102e460(output, (const char *)((unsigned long)&rodata_103e850) /*=0x103e850*/);
            }
            FUN_0102e460(output, (const char *)((unsigned long)&rodata_103d756) /*=0x103d756*/);
            for (uint32_t i = 0; i < 16u; ++i) {
                uint32_t ch = data[i];
                if ((*(const uint8_t *)(((unsigned long)&rodata_103ec11) /*=0x103ec11*/ + ch) & 0x97u) == 0)
                    ch = '.';
                FUN_0102e460(output, (const char *)((unsigned long)&rodata_103d758) /*=0x103d758*/, ch);
                if (i + 1u != 16u && ((i + 1u) & 7u) == 0)
                    FUN_0102e460(output, blank);
                if (i + 1u >= chunk && i + 1u != 16u)
                    FUN_0102e460(output, blank);
            }
            data += chunk;
            data_len -= chunk;
        }
    }

    if (type != 0) {
        if (flags & 1u)
            FUN_0102e460(output, (const char *)((unsigned long)&rodata_103d73e) /*=0x103d73e*/,
                         (const char *)((unsigned long)&rodata_103d710) /*=0x103d710*/);
        FUN_0102e484(output, flags);
    }
    FUN_0103a344(output);
}
