#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000548b8 @ 0x000548b8
 * public-name: bt_dev_show_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_dev_show_info                         <= FUN_000548b8 @ 0x000548b8
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   rodata_f31a5                             @ 0x000f31a5
 *   rodata_f31a9                             @ 0x000f31a9   [INLINED -- G6 literal batch]
 *   rodata_f31b8                             @ 0x000f31b8   [INLINED -- G6 literal batch]
 *   rodata_f31c9                             @ 0x000f31c9   [INLINED -- G6 literal batch]
 *   rodata_f3207                             @ 0x000f3207   [INLINED -- G6 literal batch]
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_000548b8 @ 0x000548b8. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern unsigned int bt_addr_le_str(const void *); /* FUN_00052cdc */
extern uint32_t version_string(uint32_t version); /* FUN_00053344 */
extern int atomic_or(volatile long*, long); /* FUN_00080e6a */
/* FUN_00080ea2 */

struct five_word_log_record {
    uint32_t argument_count;
    uint32_t format;
    uint32_t argument0;
    uint32_t argument1;
    uint32_t argument2;
};

struct address_log_record {
    uint32_t argument_count;
    uint32_t format;
    uint32_t index;
    uint32_t address;
    uint16_t kind;
};

struct version_log_record {
    uint32_t argument_count;
    uint32_t format;
    uint32_t version_string;
    uint32_t version;
    uint32_t revision;
    uint32_t build;
    uint16_t kind;
};

struct controller_version_log_record {
    uint32_t argument_count;
    uint32_t format;
    uint32_t version_string;
    uint32_t version;
    uint32_t revision;
    uint16_t kind;
};

void bt_dev_show_info(void)
{
    const uint8_t *const controller = (const uint8_t *)((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    uint8_t address_count = controller[7];

    atomic_or((uint32_t *)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/, 4);

    struct five_word_log_record identity = {
        .argument_count = 0x02000004u,
        .format = ((unsigned long)"Identity%s: %s") /*=0xf31a9*/,
        .argument0 = address_count > 1 ? ((unsigned long)&rodata_f31a5) /*=0xf31a5*/ : ((unsigned long)&rodata_a8ea0) /*=0xa8ea0*/,
        .argument1 = bt_addr_le_str(controller),
        .argument2 = 0x03010200u,
    };

    log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x28c0u, &identity);

    for (uint32_t index = 1; index < address_count; ++index) {
        struct address_log_record address = {
            .argument_count = 0x01000004u,
            .format = ((unsigned long)"Identity[%d]: %s") /*=0xf31b8*/,
            .index = index,
            .address = bt_addr_le_str(controller + index * 7u),
            .kind = 0x0301u,
        };
        log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x24c0u, &address);
    }

    uint8_t host_version = controller[0x70];
    struct version_log_record host = {
        .argument_count = 0x01000006u,
        .format = ((unsigned long)"HCI: version %s (0x%02x) revision 0x%04x, manufacturer 0x%04x") /*=0xf31c9*/,
        .version_string = version_string(host_version),
        .version = host_version,
        .revision = *(const uint16_t *)(controller + 0x72),
        .build = *(const uint16_t *)(controller + 0x76),
        .kind = 0x0200u,
    };
    log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x34c0u, &host);

    uint8_t controller_version = controller[0x71];
    struct controller_version_log_record radio = {
        .argument_count = 0x01000005u,
        .format = ((unsigned long)"LMP: version %s (0x%02x) subver 0x%04x") /*=0xf3207*/,
        .version_string = version_string(controller_version),
        .version = controller_version,
        .revision = *(const uint16_t *)(controller + 0x74),
        .kind = 0x0200u,
    };
    log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x2cc0u, &radio);
}
