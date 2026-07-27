/* readable reconstruction; identity: FUN_00054444 @ 0x00054444
 * public-name: bt_hci_le_ltk_request
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_or_create                <= FUN_000543d8 @ 0x000543d8
 *   bt_hci_le_ltk_request                    <= FUN_00054444 @ 0x00054444
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   bt_smp_request_ltk                       <= FUN_00083370 @ 0x00083370
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2db7                             @ 0x000f2db7
 *   rodata_f3125                             @ 0x000f3125   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_00054444 @ 0x00054444 (214-byte exact extent). */
#include <stdint.h>

extern void *ble_conn_lookup_masked(uint32_t, uint32_t);
extern int bt_smp_request_ltk(void *, uint32_t, uint32_t, uint32_t, uint32_t, void *);
extern void *bt_hci_cmd_create(uint32_t, uint32_t);
extern void *net_buf_simple_add(void *, uint32_t);
extern void bt_hci_cmd_send_or_create(uint32_t, void *);
extern void ble_conn_unref(int);
extern void bt_log_forward_3arg(uintptr_t, uint32_t, const void *);

struct log3 { uint32_t count, format, value; };

void bt_hci_le_ltk_request(const void *event)
{
    const uint8_t *p = *(const uint8_t * const *)((const uint8_t *)event + 12);
    uint16_t handle = *(const uint16_t *)p;
    uint32_t parameters[4];
    void *connection = ble_conn_lookup_masked(handle, 1);
    if (!connection) {
        struct log3 r = {3, 0x000f2db7u, handle};
        bt_log_forward_3arg(0x00088138u, 0x1840u, &r);
        return;
    }
    uint32_t diversifier = *(const uint16_t *)(p + 10);
    int enhanced = bt_smp_request_ltk(connection, diversifier,
                                *(const uint32_t *)(p + 2), *(const uint32_t *)(p + 6),
                                diversifier, parameters);
    void *command;
    uint32_t opcode;
    if (enhanced) {
        opcode = 0x201au;
        command = bt_hci_cmd_create(opcode, 18);
        if (command) {
            uint8_t *dst = net_buf_simple_add((uint8_t *)command + 12, 18);
            *(uint16_t *)dst = handle;
            ((uint32_t *)(dst + 2))[0] = parameters[0];
            ((uint32_t *)(dst + 2))[1] = parameters[1];
            ((uint32_t *)(dst + 2))[2] = parameters[2];
            ((uint32_t *)(dst + 2))[3] = parameters[3];
        }
    } else {
        opcode = 0x201bu;
        command = bt_hci_cmd_create(opcode, 2);
        if (command) *(uint16_t *)net_buf_simple_add((uint8_t *)command + 12, 2) = handle;
    }
    if (!command) {
        const uint32_t r[2] = {2, 0x000f3125u};
        bt_log_forward_3arg(0x00088138u, 0x1040u, r);
    } else {
        bt_hci_cmd_send_or_create(opcode, command);
    }
    ble_conn_unref(connection);
}
