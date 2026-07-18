/* readable reconstruction; identity: FUN_00054ea8 @ 0x00054ea8
 * public-name: bt_id_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_id_add                                <= FUN_00054ea8 @ 0x00054ea8
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_state_le                  <= FUN_00056f08 @ 0x00056f08
 *   addr_res_enable                          <= FUN_00081050 @ 0x00081050
 * address symbols (name @ address):
 *   ADDR_bt_le_adv_clear_pending_flag_THUMB  @ 0x00081081
 *   rodata_810ab                             @ 0x000810ab
 *   rodata_88150                             @ 0x00088150
 *   rodata_f35bf                             @ 0x000f35bf
 *   rodata_f35e4                             @ 0x000f35e4
 *   rodata_f3615                             @ 0x000f3615
 *   rodata_f3635                             @ 0x000f3635
 *   rodata_f3655                             @ 0x000f3655
 *   rodata_f367f                             @ 0x000f367f
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_00054ea8 @ 0x54ea8
 * Readable identity: bt_id_add.
 * Raw/address backmap: bt_id_add <= FUN_00054ea8 @ 0x00054ea8.
 */
#include <stdint.h>

extern void *bt_conn_lookup_state_le(uint32_t, const void *, uint32_t); /* bt_conn_lookup_state_le */
extern void ble_conn_unref(void *); /* bt_conn_unref */
extern void FUN_00055710(void *, void *); /* bt_le_ext_adv_foreach */
extern int addr_res_enable(uint32_t); /* addr_res_enable */
extern void FUN_0008104a(uint32_t, uint32_t, const void *); /* log frontend */
extern int FUN_00053d70(uint32_t, void *, void *); /* bt_hci_cmd_send_sync */
extern int FUN_00080fd2(uint8_t, const void *, const void *); /* hci_id_add */
extern void *FUN_00080fc4(void *, const void *); /* bt_addr_le_copy */
extern uint8_t *bt_hci_cmd_create(uint32_t, uint32_t); /* bt_hci_cmd_create */
extern void *FUN_00083740(void *, const void *, uint32_t); /* memcpy */

#define ID_LOG(mode_, text_) do {                                      \
    uint32_t package_[2] = { 2U, (text_) };                            \
    FUN_0008104a(0x00088150UL, (mode_), package_);                     \
} while (0)

void bt_id_add(uint8_t *keys)
{
    volatile uint8_t *const bt_dev = (volatile uint8_t *)0x20002000UL;
    void *connection = bt_conn_lookup_state_le(0U, 0, 6U);

    if (connection != 0) {
        (void)__atomic_fetch_or((uint32_t *)0x200020d4UL, 0x8000U,
                                __ATOMIC_SEQ_CST);
        keys[8] |= 1U;
        ble_conn_unref(connection);
        return;
    }

    FUN_00055710((void *)0x000810abUL, 0);
    if (bt_dev[0x121] != 0U && addr_res_enable(0U) != 0) {
        ID_LOG(0x1080U, 0x000f35bfUL);
        goto resume;
    }

    if (bt_dev[0x121] == bt_dev[0x120]) {
        int error;
        ID_LOG(0x1080U, 0x000f35e4UL);
        error = FUN_00053d70(0x2029U, 0, 0);
        if (error != 0) {
            ID_LOG(0x1040U, 0x000f3615UL);
            goto resume;
        }
        bt_dev[0x121]++;
        keys[8] |= 4U;
        goto resume;
    }

    {
        int error = FUN_00080fd2(keys[0], keys + 1, keys + 0x2a);
        if (error != 0) {
            ID_LOG(0x1040U, 0x000f3635UL);
            goto resume;
        }
        bt_dev[0x121]++;
        keys[8] |= 4U;
        if ((bt_dev[0xa7] & 4U) == 0U) {
            ID_LOG(0x1080U, 0x000f3655UL);
            goto resume;
        }
        {
            uint8_t command[8];
            uint8_t *packet;
            FUN_00080fc4(command, keys + 1);
            command[7] = 1U;
            packet = bt_hci_cmd_create(0x204eU, 8U);
            if (packet == 0) {
                ID_LOG(0x1040U, 0x000f367fUL);
                goto resume;
            }
            FUN_00083740(packet + 12, command, 8U);
            if (FUN_00053d70(0x204eU, packet, 0) != 0) {
                ID_LOG(0x1040U, 0x000f367fUL);
                goto resume;
            }
        }
    }

resume:
    (void)addr_res_enable(1U);
    FUN_00055710((void *)0x00081081UL, 0);
}
