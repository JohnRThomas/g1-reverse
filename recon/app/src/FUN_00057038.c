/* Reconstructed send_conn_le_param_update @ 0x00057038 from NCS 2.5.1 conn.c.
 * Raw backmap: FUN_00057038@0x00057038. */

#include <stdint.h>
#define send_conn_le_param_update FUN_00057038
struct bt_le_conn_param_view {
    uint16_t interval_min;
    uint16_t interval_max;
    uint16_t latency;
    uint16_t timeout;
};
extern int bt_le_conn_params_valid(const struct bt_le_conn_param_view *param);
extern int bt_conn_le_conn_update(void *conn, const struct bt_le_conn_param_view *param);
extern int FUN_00081adc(void *conn, const struct bt_le_conn_param_view *param); /* bt_l2cap_update_conn_param */
int send_conn_le_param_update(void *conn_arg, const struct bt_le_conn_param_view *param)
{
    volatile uint8_t *conn = (volatile uint8_t *)conn_arg;
    if (!bt_le_conn_params_valid(param)) {
        return -22;
    }
    uint32_t flags = __atomic_load_n(
        (volatile uint32_t *)(conn + 4), __ATOMIC_ACQUIRE);
    if ((((*(volatile uint8_t *)0x200020d8u & 2u) != 0u) &&
         ((conn[0xb5u] & 2u) != 0u) && ((flags & 0x400u) == 0u)) ||
        conn[3] == 0u) {
        int rc = bt_conn_le_conn_update(conn_arg, param);
        if (rc == 0) {
            *(volatile uint16_t *)(conn + 0xa8u) = param->interval_min;
            *(volatile uint16_t *)(conn + 0xaau) = param->interval_max;
            *(volatile uint16_t *)(conn + 0xb0u) = param->latency;
            *(volatile uint16_t *)(conn + 0xb2u) = param->timeout;
        }
        return rc;
    }
    return FUN_00081adc(conn_arg, param);
}
