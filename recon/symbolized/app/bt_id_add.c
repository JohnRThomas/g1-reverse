#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054ea8 @ 0x00054ea8
 * public-name: bt_id_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_id_add                                <= FUN_00054ea8 @ 0x00054ea8
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_state_le                  <= FUN_00056f08 @ 0x00056f08
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
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
extern void *FUN_00080fc4(void *, const void *); /* bt_addr_le_copy */
extern uint8_t *bt_hci_cmd_create(uint32_t, uint32_t); /* bt_hci_cmd_create */
#ifdef G1_APP_SDK_INLINE_COHESION
extern uintptr_t net_buf_simple_add(void *, uint32_t); /* net_buf_simple_add */
/* Exact configured NCS 2.5.1 id.c local owner (receipt 781199a9..., line 797).
 * CONFIG_BT_ID_MAX=1 and CONFIG_BT_PRIVACY=n in the shipped CPUAPP build. */
static __attribute__((always_inline)) inline int
g1_hci_id_add_inline(uint8_t id, const void *address, const void *peer_irk)
{
    uint8_t *packet;
    uint8_t *command;

    if (id != 0U)
        return -22;
    packet = bt_hci_cmd_create(0x2027U, 0x27U);
    if (packet == 0)
        return -105;
    command = (uint8_t *)net_buf_simple_add(packet + 12, 0x27U);
    FUN_00080fc4(command, address);
    __builtin_memcpy(command + 7, peer_irk, 16U);
    __builtin_memset(command + 0x17, 0, 16U);
    return FUN_00053d70(0x2027U, packet, 0);
}
#define FUN_00080fd2 g1_hci_id_add_inline
#else
extern int FUN_00080fd2(uint8_t, const void *, const void *); /* hci_id_add */
#endif
extern void *FUN_00083740(void *, const void *, uint32_t); /* memcpy */

#define ID_LOG(mode_, text_) do {                                      \
    uint32_t package_[2] = { 2U, (text_) };                            \
    FUN_0008104a(((unsigned long)&rodata_88150) /*=0x88150*/, (mode_), package_);                     \
} while (0)

void bt_id_add(uint8_t *keys)
{
    volatile uint8_t *const bt_dev = (volatile uint8_t *)((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    void *connection = bt_conn_lookup_state_le(0U, 0, 6U);

    if (connection != 0) {
        (void)__atomic_fetch_or((uint32_t *)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/, 0x8000U,
                                __ATOMIC_SEQ_CST);
        keys[8] |= 1U;
        ble_conn_unref(connection);
        return;
    }

    FUN_00055710((void *)((unsigned long)&rodata_810ab) /*=0x810ab*/, 0);
    if (bt_dev[0x121] != 0U && addr_res_enable(0U) != 0) {
        ID_LOG(0x1080U, ((unsigned long)&rodata_f35bf) /*=0xf35bf*/);
        goto resume;
    }

    if (bt_dev[0x121] == bt_dev[0x120]) {
        int error;
        ID_LOG(0x1080U, ((unsigned long)&rodata_f35e4) /*=0xf35e4*/);
        error = FUN_00053d70(0x2029U, 0, 0);
        if (error != 0) {
            ID_LOG(0x1040U, ((unsigned long)&rodata_f3615) /*=0xf3615*/);
            goto resume;
        }
        bt_dev[0x121]++;
        keys[8] |= 4U;
        goto resume;
    }

    {
        int error = FUN_00080fd2(keys[0], keys + 1, keys + 0x2a);
        if (error != 0) {
            ID_LOG(0x1040U, ((unsigned long)&rodata_f3635) /*=0xf3635*/);
            goto resume;
        }
        bt_dev[0x121]++;
        keys[8] |= 4U;
        if ((bt_dev[0xa7] & 4U) == 0U) {
            ID_LOG(0x1080U, ((unsigned long)&rodata_f3655) /*=0xf3655*/);
            goto resume;
        }
        {
            uint8_t command[8];
            uint8_t *packet;
            FUN_00080fc4(command, keys + 1);
            command[7] = 1U;
            packet = bt_hci_cmd_create(0x204eU, 8U);
            if (packet == 0) {
                ID_LOG(0x1040U, ((unsigned long)&rodata_f367f) /*=0xf367f*/);
                goto resume;
            }
            FUN_00083740(packet + 12, command, 8U);
            if (FUN_00053d70(0x204eU, packet, 0) != 0) {
                ID_LOG(0x1040U, ((unsigned long)&rodata_f367f) /*=0xf367f*/);
                goto resume;
            }
        }
    }

resume:
    (void)addr_res_enable(1U);
    FUN_00055710((void *)ADDR_bt_le_adv_clear_pending_flag_THUMB /*=0x81081*/, 0);
}
