/* readable reconstruction; identity: FUN_000361d8 @ 0x000361d8
 * public-name: FUN_000361d8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   find_chinese_bitmap_by_unicode           <= FUN_0004792c @ 0x0004792c
 *   float_to_ascii_signed_2dp                <= FUN_0004a300 @ 0x0004a300
 *   fb_blit_rows_wrap320                     <= FUN_0007d4f8 @ 0x0007d4f8
 * address symbols (name @ address):
 *   rodata_a8d20                             @ 0x000a8d20
 */
/* Full reconstruction FUN_000361d8 @ 0x000361d8 (190-byte exact extent). */
#include <stdint.h>

extern void *utf8_string_to_utf16(uintptr_t, uint16_t *);
extern uintptr_t find_chinese_bitmap_by_unicode(uint32_t, uint32_t, uint32_t);
extern void fb_blit_rows_wrap320(void *, uintptr_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern uint8_t *get_device_info(void);
extern int float_to_ascii_signed_2dp(uint32_t, void *);

int FUN_000361d8(void *destination)
{
    uint16_t count;
    uint8_t decoded[10] = {0};
    uint32_t groups[3];
    uint16_t *entries = utf8_string_to_utf16(0x000a8d20u, &count);

    for (uint32_t i = 0; i < count; ++i) {
        uintptr_t value = find_chinese_bitmap_by_unicode(entries[i], 12, 36);
        fb_blit_rows_wrap320((uint8_t *)destination + 36, value, 12, 36,
                     i * 12 + 6, 0);
    }

    uint8_t *state = get_device_info();
    groups[0] = *(uint32_t *)(state + 0xef);
    groups[1] = *(uint32_t *)(state + 0xf3);
    groups[2] = *(uint32_t *)(state + 0xf7);
    for (uint32_t group = 0; group < 3; ++group) {
        int n = float_to_ascii_signed_2dp(groups[group], decoded);
        uint32_t row = (group + 1) * 30;
        for (int i = 0; i < n; ++i) {
            uintptr_t value = find_chinese_bitmap_by_unicode(decoded[i], 12, 36);
            fb_blit_rows_wrap320((uint8_t *)destination + 36, value, 12, 36,
                         (uint32_t)i * 12 + 6, row);
        }
    }
    return 0;
}
