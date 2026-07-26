/* readable reconstruction; identity: FUN_0005c310 @ 0x0005c310
 * public-name: gatt_prepare_write_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_write                            <= FUN_0005c22c @ 0x0005c22c
 *   gatt_prepare_write_rsp                   <= FUN_0005c310 @ 0x0005c310
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   gatt_req_send                            <= FUN_00082aee @ 0x00082aee
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_82603                             @ 0x00082603
 *   ADDR_gatt_cancel_encode_THUMB            @ 0x0008278b
 *   ADDR_gatt_exec_encode_THUMB              @ 0x0008279d
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4cdd                             @ 0x000f4cdd   [INLINED -- G6 literal batch]
 *   rodata_f4cff                             @ 0x000f4cff   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005c310 @ 0x0005c310 (gatt_prepare_write_rsp).
 * Raw/address backmap: FUN_0005c310 @ 0x0005c310, extent 0x0000009c.
 */
#include <stdint.h>
extern void log_msg_create_3arg(uint32_t, uint32_t, const void *); /* logger */
extern int gatt_req_send(void *, void *, void *, void *, uint32_t, uint32_t);
extern int memcmp(const void *, const void *, uint32_t); /* memcmp */
extern int bt_gatt_write(void *, void *); /* bt_gatt_write */

struct write_params_recovered {
    void (*callback)(void *, uint8_t, void *);
    uint16_t handle;
    uint16_t offset;
    const uint8_t *data;
    uint16_t length;
};

void gatt_prepare_write_rsp(void *connection, const uint8_t *response,
                  uint16_t response_length, struct write_params_recovered *params)
{
    uint16_t payload_length = (uint16_t)(response_length - 4U);
    if (payload_length > params->length) {
        uint32_t package[2] = { 2U, 0x000f4cddU };
        log_msg_create_3arg(0x00088128U, 0x1040U, package);
        if (gatt_req_send(connection, (void *)0x00082603U, params,
                         (void *)0x0008278bU, 0x18U, 1U) != 0)
            params->callback(connection, 0x0eU, params);
        return;
    }
    int data_valid = memcmp(params->data, response + 4,
                                  payload_length) == 0;
    if (params->offset != *(const uint16_t *)(response + 2) || !data_valid) {
        uint32_t package[2] = { 2U, 0x000f4cffU };
        log_msg_create_3arg(0x00088128U, 0x1040U, package);
        if (gatt_req_send(connection, (void *)0x00082603U, params,
                         (void *)0x0008278bU, 0x18U, 1U) != 0)
            params->callback(connection, 0x0eU, params);
        return;
    }
    params->offset = (uint16_t)(params->offset + payload_length);
    params->data += payload_length;
    params->length = (uint16_t)(params->length - payload_length);
    int error;
    if (params->length == 0U)
        error = gatt_req_send(connection, (void *)0x00082603U, params,
                             (void *)0x0008279dU, 0x18U, 1U);
    else
        error = bt_gatt_write(connection, params);
    if (error != 0)
        params->callback(connection, 0x0eU, params);
}
