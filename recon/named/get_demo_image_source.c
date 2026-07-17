/* readable reconstruction; identity: FUN_00036820 @ 0x00036820
 * public-name: get_demo_image_source
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   pixelto4bithex                           <= FUN_0003678c @ 0x0003678c
 *   get_demo_image_source                    <= FUN_00036820 @ 0x00036820
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   heap_free                                <= FUN_00076d7c @ 0x00076d7c
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8d69                             @ 0x000a8d69
 *   rodata_a8d7f                             @ 0x000a8d7f
 *   rodata_a8da5                             @ 0x000a8da5
 *   rodata_a8da8                             @ 0x000a8da8
 *   rodata_a8dc1                             @ 0x000a8dc1
 *   rodata_a8dde                             @ 0x000a8dde
 *   rodata_a8e02                             @ 0x000a8e02
 *   g_pixel4bit_bitpos                       @ 0x20009fc4
 *   g_pixel4bit_row_buf_off                  @ 0x20009fc8
 *   g_pixel4bit_row_buf                      @ 0x20009fcc
 */
/* Reconstructed FUN_00036820 @ 0x36820. */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t format, ...);
extern uintptr_t get_device_info(void);
extern void pixelto4bithex(unsigned int inverted_byte, int glyph_width);
extern void *malloc(unsigned int size);
extern void heap_free(void *allocation);
extern void printf(uint32_t message);
extern int FUN_0007d1c8(const void *field);
extern void memcpy(uintptr_t destination, int source, unsigned int size);
extern void memset_bytes(void *destination, int value, unsigned int size);
extern int FUN_00087036(const void *header, uint32_t descriptor, unsigned int count);

typedef int (*read_callback_t)(uintptr_t context, uint32_t address,
                               void *destination, unsigned int size);

static read_callback_t get_read_callback(void)
{
    return *(read_callback_t *)(get_device_info() + 0x1030u);
}

static uintptr_t get_read_context(void)
{
    return get_device_info();
}

void get_demo_image_source(unsigned int mode)
{
    uint8_t *buffer = (uint8_t *)malloc(0x50u);
    if (buffer == 0) {
        DEBUG_PRINT(0x000a8d69u, 0x000a8e02u, 0xd3u);
        return;
    }

    memset_bytes(buffer, 0, 0x50u);
    if (mode > 4u) {
        DEBUG_PRINT(0x000a8ddeu, mode);
        mode = 0;
    }

    read_callback_t read = get_read_callback();
    uintptr_t context = get_read_context();
    uint32_t address = mode * 0x3ebeu + 0x00180000u;
    if (read(context, address, buffer, 0x50u) != 0) {
        DEBUG_PRINT(0x000a8d7fu, 0x000a8e02u, 0xdfu);
        heap_free(buffer);
        return;
    }

    uint8_t header[14];
    for (unsigned int i = 0; i < sizeof(header); ++i)
        header[i] = buffer[i];

    if (FUN_00087036(header, 0x000a8da5u, 2u) != 0) {
        DEBUG_PRINT(0x000a8da8u);
        heap_free(buffer);
        return;
    }

    uint8_t metadata[40];
    for (unsigned int i = 0; i < sizeof(metadata); ++i)
        metadata[i] = buffer[14u + i];

    int first_offset = FUN_0007d1c8(header + 10);
    int glyph_width = FUN_0007d1c8(metadata + 4);
    int row_count = FUN_0007d1c8(metadata + 8);
    uint16_t format = (uint16_t)metadata[14] |
                      (uint16_t)((uint16_t)metadata[15] << 8);

    if (format != 1u) {
        printf(0x000a8dc1u);
        heap_free(buffer);
        return;
    }

    int row_bytes = glyph_width + 7;
    *(volatile int *)0x20009fc4 = 0;
    if (row_bytes < 0)
        row_bytes = glyph_width + 14;
    row_bytes >>= 3;

    *(volatile int *)0x20009fc8 = 0;
    int row_words = glyph_width + 31;
    if (row_words < 0)
        row_words = glyph_width + 62;
    row_words >>= 5;

    address += (uint32_t)first_offset +
               (uint32_t)((row_count - 1) * row_words * 4);

    for (int row = 0; row < row_count; ++row) {
        *(volatile int *)0x20009fc4 = 0;
        memset_bytes(buffer, 0, 0x50u);
        read = get_read_callback();
        context = get_read_context();
        if (read(context, address, buffer, (unsigned int)row_bytes) != 0) {
            DEBUG_PRINT(0x000a8d7fu, 0x000a8e02u, 0x103u);
            heap_free(buffer);
            return;
        }

        for (int column = 0; column < row_bytes; ++column)
            pixelto4bithex((unsigned int)(uint8_t)~buffer[column], glyph_width);

        int rendered = *(volatile int *)0x20009fcc;
        if (rendered != 0) {
            *(volatile int *)0x20009fc8 = 0;
            uintptr_t device = get_device_info();
            uintptr_t destination = *(volatile uintptr_t *)(device +
                                      0x0b90u + (unsigned int)row * 4u);
            memcpy(destination, rendered, 0x140u);
        }
        address -= (uint32_t)(row_words * 4);
    }

    heap_free(buffer);
}
