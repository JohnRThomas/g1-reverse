/* readable reconstruction; identity: FUN_01013da8 @ 0x01013da8
 * public-name: FUN_01013da8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* FUN_01013da8 @ 0x01013da8: advance a connection event cursor to controller time. */
#include <stdint.h>

extern uint64_t controller_time_now(void);
extern uint32_t FUN_010237b0(uint32_t selector);
extern uint32_t sdc_conn_event_timing_prepare(void *connection, uint32_t event,
                                              uint32_t prepare, uint32_t flags,
                                              uint16_t *step);
extern void sdc_assertion_fail(uint32_t file_id, uint32_t line);

static uint16_t load_u16(const uint8_t *p) { return *(const uint16_t *)p; }
static void store_u16(uint8_t *p, uint16_t value) { *(uint16_t *)p = value; }
static uint32_t load_u32(const uint8_t *p) { return *(const uint32_t *)p; }
static uint64_t load_u64(const uint8_t *p) { return *(const uint64_t *)p; }

void FUN_01013da8(uint8_t *connection)
{
    if (connection[0x2eb] != 0u || connection[0x31c] != 3u) {
        return;
    }

    int64_t elapsed = (int64_t)(controller_time_now() - load_u64(connection + 0x350));
    if (elapsed < 1) {
        return;
    }
    if ((uint64_t)elapsed > 0xfffffffeu) {
        sdc_assertion_fail(0x30u, 0x603u);
    }

    uint32_t interval = load_u32(connection + 0x14);
    uint16_t elapsed_slots = interval == 0u ? 0u : (uint16_t)((uint64_t)elapsed / interval);
    uint16_t current = (uint16_t)(elapsed_slots + load_u16(connection + 0xbc) + 1u);
    store_u16(connection + 0x32c, current);

    if ((int16_t)(load_u16(connection + 0x2e4) - current) <= 0 ||
        FUN_010237b0(connection[0x364]) == 0u) {
        return;
    }

    connection[0x331] = 0xffu;
    uint16_t bound = (uint16_t)(load_u16(connection + 0xbc) +
                                load_u16(connection + 0xf8) - 1u -
                                load_u16(connection + 0xf6));
    while ((int16_t)(bound - current) >= 0) {
        uint16_t step = 0u;
        uint32_t result = sdc_conn_event_timing_prepare(connection, current, 1u, 0u, &step);
        if (result == 0u) {
            return;
        }
        if (result != 1u) {
            sdc_assertion_fail(0x30u, 0x63cu);
        }
        current = (uint16_t)(current + step);
        store_u16(connection + 0x32c, current);
    }
}

/* Raw identity/back-map: FUN_01013da8 @ 0x01013da8, true extent 0xee. */
