/* Reconstructed FUN_00034dbc @ 0x34dbc. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00064b1c(int object);
extern int FUN_0008500c(void);
extern int FUN_00085020(int *);
extern int FUN_00085030(int object);
extern int FUN_0008503c(int, int);
extern int FUN_000850c8(void);
extern void FUN_00086c78(void *destination, int value, unsigned int count);
extern void FUN_0008705a(void *destination, const void *source,
                         unsigned int limit);

#define REPORT_ERROR(format_) do {                                      \
    if (*(volatile int *)0x20007554u == 0)                              \
        DEBUG_PRINT((format_));                                         \
    else                                                                \
        FUN_00019c70((format_));                                        \
} while (0)

uint32_t FUN_00034dbc(uint32_t request, uint32_t unused_2,
                      uint32_t unused_3)
{
    volatile uint8_t *const output = (volatile uint8_t *)0x2001a22cu;
    int root = FUN_0008500c();
    int object;
    uint32_t error_format;
    uint8_t item_count;
    uint8_t source_index;
    uint8_t output_index;
    (void)unused_2;
    (void)unused_3;

    if (root == 0) {
        if (*(volatile int *)0x20007554u == 0)
            DEBUG_PRINT(0x000a8604, request);
        else
            FUN_00019c70(0x000a8604, request);
        return 0;
    }

    FUN_00086c78((void *)output, 0, 0x15e2);
    object = FUN_0008503c(root, 0x000a862c);
    if (object == 0) { error_format = 0x000a8638; goto fail; }
    output[0] = (output[0] & 0xfeu) | (*(int *)(object + 0xc) == 2);

    object = FUN_0008503c(root, 0x000a864e);
    if (object == 0) { error_format = 0x000a8659; goto fail; }
    output[0] = (output[0] & 0xfdu) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 1);

    object = FUN_0008503c(root, 0x000a866e);
    if (object == 0) { error_format = 0x000a867e; goto fail; }
    output[0] = (output[0] & 0xf7u) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 3);

    object = FUN_0008503c(root, 0x000a869b);
    if (object == 0) { error_format = 0x000a86ab; goto fail; }
    output[0] = (output[0] & 0xfbu) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 2);

    object = FUN_0008503c(root, 0x0009e1b6);
    if (object == 0) { error_format = 0x000a86c8; goto fail; }
    {
        int nested = FUN_0008503c(object, 0x0009e235);
        if (nested == 0) { error_format = 0x000a86db; goto fail; }
        output[0] = (output[0] & 0xefu) |
                    ((uint32_t)(*(int *)(nested + 0xc) == 2) << 4);
    }

    object = FUN_0008503c(object, 0x000f3630);
    if (object == 0) { error_format = 0x000a86f4; goto fail; }

    if (FUN_000850c8() != 0) {
        item_count = (uint8_t)FUN_00085020(object);
        if (item_count > 99)
            item_count = 100;
        output[1] = item_count;
        output_index = 0;

        for (source_index = 0; source_index < output[1]; ++source_index) {
            int item = FUN_00085030(object);
            int name;
            int value;
            volatile uint8_t *record;

            if (item == 0) {
                REPORT_ERROR(0x000a870b);
                continue;
            }
            name = FUN_0008503c(item, 0x0009a1dd);
            if (name == 0) {
                REPORT_ERROR(0x000a8724);
                continue;
            }
            value = FUN_0008503c(item, 0x000f33e4);
            if (value == 0) {
                REPORT_ERROR(0x000a8739);
                continue;
            }

            record = output + (uint32_t)output_index * 0x38 + 2;
            FUN_00086c78((void *)record, 0, 0x28);
            FUN_00086c78((void *)(record + 0x28), 0, 0x10);
            FUN_0008705a((void *)record, *(const void **)(name + 0x10), 0x27);
            FUN_0008705a((void *)(record + 0x28),
                         *(const void **)(value + 0x10), 0x0f);
            output_index = (uint8_t)(output_index + 1);
        }
    }

    FUN_00064b1c(root);
    return 1;

fail:
    REPORT_ERROR(error_format);
    FUN_00064b1c(root);
    return 0;
}
