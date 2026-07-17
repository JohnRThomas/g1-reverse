/* net-core log-output formatter and hex-dump renderer @ 0x0102e4f4.
 * Raw/address back-map: FUN_0102e4f4 / 0x0102e4f4.
 */
#include <stdint.h>

extern int FUN_0102e460(uint32_t, const char *, ...);
extern void FUN_0102e484(uint32_t, uint32_t);
extern int FUN_0103966e(const void *, const void *, uint32_t, const void *);
extern void assert_print(const void *, const void *, uint32_t);
extern void FUN_01039bb0(const void *, uint32_t);
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
            assert_print((const void *)0x0103d2a7u,
                         (const void *)0x0103d6e1u, 0x1bf);
            FUN_01039bb0((const void *)0x0103d6e1u, 0x1bf);
        }

        uint32_t thread = FUN_0103a2c8();
        int count = thread ? FUN_0102e460(output,
                    (const char *)0x0103d715u, thread) : 0;

        if (flags & 2u) {
            if ((flags & 0x44u) == 0) {
                count += FUN_0102e460(output, (const char *)0x0103d719u,
                                      timestamp);
            } else {
                uint32_t frequency = *(volatile uint32_t *)0x21004674u;
                if (frequency != 0) {
                    uint32_t ticks = timestamp /
                                     *(volatile uint32_t *)0x21004670u;
                    uint32_t seconds = ticks / frequency;
                    uint32_t fractional = (ticks % frequency) * 1000u;
                    uint32_t millis = fractional / frequency;
                    uint32_t micros = ((fractional - frequency * millis) *
                                       1000u) / frequency;
                    count += FUN_0102e460(output,
                              (const char *)0x0103d722u,
                              seconds / 3600u, (seconds % 3600u) / 60u,
                              seconds % 60u, millis, micros);
                }
            }
        }

        if (flags & 1u) {
            const char *tag = *(const char **)(0x0103c924u + type * 4u);
            if (tag == 0)
                tag = (const char *)0x0103d710u;
            FUN_0102e460(output, (const char *)0x0103d73eu, tag);
        }

        if (flags & 8u) {
            const char *level_name =
                *(const char **)(0x0103c938u + type * 4u);
            prefix_count = FUN_0102e460(
                output, (const char *)0x0103d741u, level_name);
        } else {
            prefix_count = flags & 8u;
        }
        if (domain != 0)
            prefix_count += FUN_0102e460(
                output, (const char *)0x0103d747u, domain);
        if (level != 0)
            prefix_count += FUN_0102e460(
                output, (const char *)0x0103d74bu, level);
        count += (int)prefix_count;
        prefix_count = count;
        formatter = (const void *)0x0102eca1u;
    } else {
        if (level == 1)
            formatter = (const void *)0x0102eca1u;
        prefix_count = 0;
    }

    if (package != 0) {
        if (FUN_0103966e(formatter, (const void *)0x0103024du,
                         output, package) < 0) {
            assert_print((const void *)0x0103d2a7u,
                         (const void *)0x0103d6e1u, 0x219);
            FUN_01039bb0((const void *)0x0103d6e1u, 0x219);
        }
    }

    if (data_len != 0) {
        const char *blank = (const char *)0x0103e852u;
        const char *hex = (const char *)0x0103d750u;
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
                    FUN_0102e460(output, (const char *)0x0103e850u);
            }
            FUN_0102e460(output, (const char *)0x0103d756u);
            for (uint32_t i = 0; i < 16u; ++i) {
                uint32_t ch = data[i];
                if ((*(const uint8_t *)(0x0103ec11u + ch) & 0x97u) == 0)
                    ch = '.';
                FUN_0102e460(output, (const char *)0x0103d758u, ch);
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
            FUN_0102e460(output, (const char *)0x0103d73eu,
                         (const char *)0x0103d710u);
        FUN_0102e484(output, flags);
    }
    FUN_0103a344(output);
}
