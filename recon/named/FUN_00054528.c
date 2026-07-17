/* readable reconstruction; identity: FUN_00054528 @ 0x00054528
 * public-name: FUN_00054528
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_or_create                <= FUN_000543d8 @ 0x000543d8
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   ble_notify_disconnected                  <= FUN_00056c78 @ 0x00056c78
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   le_conn_param_neg_reply                  <= FUN_00080f56 @ 0x00080f56
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2db7                             @ 0x000f2db7
 */
/* Reconstructed FUN_00054528 @ 0x54528 */
#include <stdint.h>

extern int bt_hci_cmd_create(int pool, int size);
extern void bt_hci_cmd_send_or_create(int queue, int packet);
extern void ble_conn_unref(int connection);
extern int ble_conn_lookup_masked(unsigned int identifier, int selector);
extern int ble_notify_disconnected(int connection, const void *fields);
extern uint16_t *net_buf_simple_add(int packet_data, int size);
extern void FUN_00080ea2(int source, int level, const void *record);
extern void le_conn_param_neg_reply(unsigned int identifier, int status);

struct diagnostic_record {
    unsigned int severity;
    unsigned int message;
    unsigned int identifier;
};

void FUN_00054528(int event)
{
    const uint8_t *source = *(const uint8_t **)(event + 0x0c);
    uint16_t identifier = *(const volatile uint16_t *)source;
    uint16_t fields[4];
    int connection;

    fields[0] = (uint16_t)(source[2] | (source[3] << 8));
    fields[1] = (uint16_t)(source[4] | (source[5] << 8));
    fields[2] = (uint16_t)(source[6] | (source[7] << 8));
    fields[3] = (uint16_t)(source[8] | (source[9] << 8));

    connection = ble_conn_lookup_masked(identifier, 1);
    if (connection == 0) {
        struct diagnostic_record diagnostic = {
            3, 0x000f2db7, identifier
        };

        FUN_00080ea2(0x00088138, 0x1840, &diagnostic);
        le_conn_param_neg_reply(identifier, 2);
        return;
    }

    if (ble_notify_disconnected(connection, fields) == 0) {
        le_conn_param_neg_reply(identifier, 0x1e);
    } else {
        int packet = bt_hci_cmd_create(0x2020, 0x0e);

        if (packet != 0) {
            volatile uint16_t *output = net_buf_simple_add(packet + 0x0c, 0x0e);

            output[0] = identifier;
            *(volatile uint32_t *)((volatile uint8_t *)output + 0x0a) = 0;
            output[1] = fields[0];
            output[2] = fields[1];
            output[3] = fields[2];
            output[4] = fields[3];
            bt_hci_cmd_send_or_create(0x2020, packet);
        }
    }

    ble_conn_unref(connection);
}
