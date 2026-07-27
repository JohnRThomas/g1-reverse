/* Reconstructed FUN_0004792c @ 0x4792c */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void *FUN_000167a8(void);
extern unsigned int FUN_0004790c(void *, unsigned int, unsigned int);
extern unsigned int FUN_0007d84c(unsigned int, unsigned int);
extern void FUN_00086c78(void *, int, unsigned int);

typedef int (*storage_callback)();

unsigned int FUN_0004792c(unsigned int codepoint, int16_t width, int16_t height)
{
    unsigned int bitmap_size = ((int)width * (int)height) & 0xffff;
    unsigned char bitmap[(bitmap_size + 7) & ~7U];
    unsigned char *result = bitmap;
    uint16_t dimensions[2];
    void *context;
    storage_callback callback;
    int status;

    if (codepoint - 0x20 < 0x60)
        return FUN_0007d84c(codepoint & 0xff, bitmap_size);

    context = FUN_000167a8();
    callback = *(storage_callback *)((unsigned char *)context + 0x1030);
    if (callback == 0) {
        result = 0;
    } else {
        context = FUN_000167a8();
        callback = *(storage_callback *)((unsigned char *)context + 0x1030);
        context = FUN_000167a8();
        status = callback(context, (codepoint - 0xa4) * 4 + 0x140000,
                          dimensions);
        if (status != 0) {
            if (*(volatile int *)0x2000230c > 0) {
                if (*(volatile int *)0x20007554 == 0)
                    DEBUG_PRINT(0x000bbfee, 0x000d750b);
                else
                    FUN_00019c70(0x000bbfee, 0x000d750b);
            }
            return 0;
        }

        DEBUG_PRINT(0x000d74f4, dimensions[0], dimensions[1], 4);
        {
            unsigned int offset = (bitmap_size >> 2) * dimensions[1];
            if (bitmap_size == 0x1b0)
                offset += 0xcf120;

            FUN_00086c78(result, 0, bitmap_size);
            context = FUN_000167a8();
            callback = *(storage_callback *)((unsigned char *)context + 0x1030);
            context = FUN_000167a8();
            status = callback(context, offset + 0x200000,
                              result, bitmap_size >> 2);
            if (status != 0 && *(volatile int *)0x2000230c > 0) {
                if (*(volatile int *)0x20007554 == 0)
                    DEBUG_PRINT(0x000a1ce0, 0x000d750b, status);
                else
                    FUN_00019c70(0x000a1ce0, 0x000d750b, status);
            }
        }
    }

    FUN_0004790c(result, bitmap_size, 0x2001cf92);
    return 0x2001cf92;
}
