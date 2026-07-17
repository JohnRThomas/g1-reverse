/* readable reconstruction; identity: FUN_00034dbc @ 0x00034dbc
 * public-name: parse_whitelist_json
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   parse_whitelist_json                     <= FUN_00034dbc @ 0x00034dbc
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   sllist_count_nodes                       <= FUN_00085020 @ 0x00085020
 *   sllist_node_at_index                     <= FUN_00085030 @ 0x00085030
 *   sllist_find_by_name_ci                   <= FUN_0008503c @ 0x0008503c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_9e1b6                             @ 0x0009e1b6
 *   rodata_9e235                             @ 0x0009e235
 *   rodata_a8604                             @ 0x000a8604
 *   rodata_a862c                             @ 0x000a862c
 *   rodata_a8638                             @ 0x000a8638
 *   rodata_a864e                             @ 0x000a864e
 *   rodata_a866e                             @ 0x000a866e
 *   rodata_a869b                             @ 0x000a869b
 *   rodata_a870b                             @ 0x000a870b
 *   rodata_f33e4                             @ 0x000f33e4
 *   rodata_f3630                             @ 0x000f3630
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed FUN_00034dbc @ 0x34dbc. */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern void cjson_delete(int object);
extern int FUN_0008500c(void);
extern unsigned int sllist_count_nodes(int object);
extern int sllist_node_at_index(int object);
extern int sllist_find_by_name_ci(int object, uint32_t key);
extern int FUN_000850c8(void);
extern void memset_bytes(void *destination, int value, unsigned int count);
extern void strncpy_zero_pad(void *destination, const void *source,
                         unsigned int limit);

#define REPORT_ERROR(format_) do {                                      \
    if (*(volatile int *)0x20007554u == 0)                              \
        log_message((format_));                                         \
    else                                                                \
        debug_print((format_));                                        \
} while (0)

uint32_t parse_whitelist_json(uint32_t request, uint32_t unused_2,
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
            log_message(0x000a8604, request);
        else
            debug_print(0x000a8604, request);
        return 0;
    }

    memset_bytes((void *)output, 0, 0x15e2);
    object = sllist_find_by_name_ci(root, 0x000a862c);
    if (object == 0) { error_format = 0x000a8638; goto fail; }
    output[0] = (output[0] & 0xfeu) | (*(int *)(object + 0xc) == 2);

    object = sllist_find_by_name_ci(root, 0x000a864e);
    if (object == 0) { error_format = 0x000a8659; goto fail; }
    output[0] = (output[0] & 0xfdu) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 1);

    object = sllist_find_by_name_ci(root, 0x000a866e);
    if (object == 0) { error_format = 0x000a867e; goto fail; }
    output[0] = (output[0] & 0xf7u) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 3);

    object = sllist_find_by_name_ci(root, 0x000a869b);
    if (object == 0) { error_format = 0x000a86ab; goto fail; }
    output[0] = (output[0] & 0xfbu) |
                ((uint32_t)(*(int *)(object + 0xc) == 2) << 2);

    object = sllist_find_by_name_ci(root, 0x0009e1b6);
    if (object == 0) { error_format = 0x000a86c8; goto fail; }
    {
        int nested = sllist_find_by_name_ci(object, 0x0009e235);
        if (nested == 0) { error_format = 0x000a86db; goto fail; }
        output[0] = (output[0] & 0xefu) |
                    ((uint32_t)(*(int *)(nested + 0xc) == 2) << 4);
    }

    object = sllist_find_by_name_ci(object, 0x000f3630);
    if (object == 0) { error_format = 0x000a86f4; goto fail; }

    if (FUN_000850c8() != 0) {
        item_count = (uint8_t)sllist_count_nodes(object);
        if (item_count > 99)
            item_count = 100;
        output[1] = item_count;
        output_index = 0;

        for (source_index = 0; source_index < output[1]; ++source_index) {
            int item = sllist_node_at_index(object);
            int name;
            int value;
            volatile uint8_t *record;

            if (item == 0) {
                REPORT_ERROR(0x000a870b);
                continue;
            }
            name = sllist_find_by_name_ci(item, 0x0009a1dd);
            if (name == 0) {
                REPORT_ERROR(0x000a8724);
                continue;
            }
            value = sllist_find_by_name_ci(item, 0x000f33e4);
            if (value == 0) {
                REPORT_ERROR(0x000a8739);
                continue;
            }

            record = output + (uint32_t)output_index * 0x38 + 2;
            memset_bytes((void *)record, 0, 0x28);
            memset_bytes((void *)(record + 0x28), 0, 0x10);
            strncpy_zero_pad((void *)record, *(const void **)(name + 0x10), 0x27);
            strncpy_zero_pad((void *)(record + 0x28),
                         *(const void **)(value + 0x10), 0x0f);
            output_index = (uint8_t)(output_index + 1);
        }
    }

    cjson_delete(root);
    return 1;

fail:
    REPORT_ERROR(error_format);
    cjson_delete(root);
    return 0;
}
