#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055534 @ 0x00055534
 * public-name: hci_set_ad
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   hci_set_ad                               <= FUN_00055534 @ 0x00055534
 * address symbols (name @ address):
 *   rodata_880f8                             @ 0x000880f8
 *   rodata_f3804                             @ 0x000f3804   [INLINED -- G6 literal batch]
 */
/* Reconstructed hci_set_ad @ 0x00055534 (FUN_00055534; NCS 2.5.1 adv.c). */
#include <stddef.h>
#include <stdint.h>

struct bt_data_record {
    uint8_t type;
    uint8_t data_len;
    const uint8_t *data;
};
struct bt_ad {
    const struct bt_data_record *data;
    size_t len;
};
struct log_record {
    uint32_t count;
    const char *message;
};

extern void *bt_hci_cmd_create(uint16_t opcode, uint32_t payload_size); /* FUN_00053cd4 */
extern uint8_t *net_buf_simple_add(void *simple, uint32_t length); /* FUN_0005f5d0 */
extern void memset_bytes(void*, int, int); /* FUN_00086c78 */
extern void memcpy(int, int, int); /* FUN_00086c04 */
extern void net_buf_unref(int); /* FUN_0005f24c */
extern int bt_hci_cmd_send_sync(uint16_t opcode, void *buffer, void *response);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
#define bt_hci_cmd_send_sync bt_hci_cmd_send_sync
#define log_message z_log_msg_runtime_create
#define hci_set_ad hci_set_ad

int hci_set_ad(uint16_t opcode, const struct bt_ad *ad, size_t ad_len)
{
    void *buffer = bt_hci_cmd_create(opcode, 0x20u);
    if (buffer == 0) {
        return -105;
    }

    uint8_t *set_data = net_buf_simple_add((uint8_t *)buffer + 0x0c, 0x20u);
    memset_bytes(set_data, 0u, 0x20u);
    uint8_t used = 0u;

    for (size_t i = 0; i < ad_len; ++i) {
        for (size_t j = 0; j < ad[i].len; ++j) {
            const struct bt_data_record *entry = &ad[i].data[j];
            uint32_t length = entry->data_len;
            uint8_t type = entry->type;
            uint32_t value_offset = (uint32_t)used + 2u;

            if (length + value_offset > 0x1fu) {
                length = 0x1fu - value_offset;
                if (type != 9u || (int32_t)length < 1) {
                    struct log_record record = {
                        2u, (const char *)((unsigned long)"Too big advertising data") /*=0xf3804*/
                    };
                    log_message((const void *)((unsigned long)&rodata_880f8) /*=0x880f8*/, 0x1040u,
                                &record, 0u);
                    net_buf_unref(buffer);
                    return -22;
                }
                type = 8u;
            }

            set_data[(uint8_t)(used + 1u)] = (uint8_t)length + 1u;
            set_data[(uint8_t)(used + 2u)] = type;
            memcpy(set_data + (uint8_t)value_offset + 1u,
                   entry->data, (uint8_t)length);
            used = (uint8_t)(used + (uint8_t)length + 2u);
        }
    }

    set_data[0] = used;
    return bt_hci_cmd_send_sync(opcode, buffer, 0);
}
