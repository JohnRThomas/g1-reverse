#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004792c @ 0x0004792c
 * public-name: find_chinese_bitmap_by_unicode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   expand_bytes_via_lut32                   <= FUN_0004790c @ 0x0004790c
 *   find_chinese_bitmap_by_unicode           <= FUN_0004792c @ 0x0004792c
 *   find_chinese_bitmap_stub_zero            <= FUN_0007d84c @ 0x0007d84c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a1ce0                             @ 0x000a1ce0
 *   rodata_bbfee                             @ 0x000bbfee   [INLINED -- G6 literal batch]
 *   rodata_d74f4                             @ 0x000d74f4   [INLINED -- G6 literal batch]
 *   rodata_d750b                             @ 0x000d750b   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_chinese_glyph_bitmap_buf               @ 0x2001cf92
 */
/* Reconstructed FUN_0004792c @ 0x4792c */
#include <stdint.h>

extern void log_message(unsigned int, ...);
extern void debug_print(unsigned int, ...);
extern void *get_device_info(void);
extern unsigned int expand_bytes_via_lut32(void *, unsigned int, unsigned int);
extern unsigned int find_chinese_bitmap_stub_zero(unsigned int, unsigned int);
extern void memset_bytes(void *, int, unsigned int);

typedef int (*storage_callback)();

unsigned int find_chinese_bitmap_by_unicode(unsigned int codepoint, int16_t width, int16_t height)
{
    unsigned int bitmap_size = ((int)width * (int)height) & 0xffff;
    unsigned char bitmap[(bitmap_size + 7) & ~7U];
    unsigned char *result = bitmap;
    uint16_t dimensions[2];
    void *context;
    storage_callback callback;
    int status;

    if (codepoint - 0x20 < 0x60)
        return find_chinese_bitmap_stub_zero(codepoint & 0xff, bitmap_size);

    context = get_device_info();
    callback = *(storage_callback *)((unsigned char *)context + 0x1030);
    if (callback == 0) {
        result = 0;
    } else {
        context = get_device_info();
        callback = *(storage_callback *)((unsigned char *)context + 0x1030);
        context = get_device_info();
        status = callback(context, (codepoint - 0xa4) * 4 + 0x140000,
                          dimensions);
        if (status != 0) {
            if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                    log_message(((unsigned long)"%s(): read flash fail\n\n") /*=0xbbfee*/, ((unsigned long)"find_chinese_bitmap_by_unicode") /*=0xd750b*/);
                else
                    debug_print(((unsigned long)"%s(): read flash fail\n\n") /*=0xbbfee*/, ((unsigned long)"find_chinese_bitmap_by_unicode") /*=0xd750b*/);
            }
            return 0;
        }

        log_message(((unsigned long)"unicode=%x, offset=%d\n") /*=0xd74f4*/, dimensions[0], dimensions[1], 4);
        {
            unsigned int offset = (bitmap_size >> 2) * dimensions[1];
            if (bitmap_size == 0x1b0)
                offset += 0xcf120;

            memset_bytes(result, 0, bitmap_size);
            context = get_device_info();
            callback = *(storage_callback *)((unsigned char *)context + 0x1030);
            context = get_device_info();
            status = callback(context, offset + 0x200000,
                              result, bitmap_size >> 2);
            if (status != 0 && *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                    log_message(((unsigned long)&rodata_a1ce0) /*=0xa1ce0*/, ((unsigned long)"find_chinese_bitmap_by_unicode") /*=0xd750b*/, status);
                else
                    debug_print(((unsigned long)&rodata_a1ce0) /*=0xa1ce0*/, ((unsigned long)"find_chinese_bitmap_by_unicode") /*=0xd750b*/, status);
            }
        }
    }

    expand_bytes_via_lut32(result, bitmap_size, ((unsigned long)&g_chinese_glyph_bitmap_buf) /*=0x2001cf92*/);
    return ((unsigned long)&g_chinese_glyph_bitmap_buf) /*=0x2001cf92*/;
}
