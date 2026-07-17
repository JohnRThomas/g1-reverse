/* readable reconstruction; identity: FUN_01008fd4 @ 0x01008fd4
 * public-name: FUN_01008fd4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01008fd4 @ 0x1008fd4 */
#include <stdint.h>

extern int32_t FUN_01009210(void);
extern uint8_t FUN_010257e4(int32_t handle);
extern void FUN_01008a58(uint32_t size, int32_t flags);
extern void FUN_0101fc14(void);
extern void FUN_0101f818(uint8_t value, int32_t setting);
extern void FUN_01008d7c(void);

struct controller_state {
    uint8_t reserved_00[0x24];
    int32_t setting;
    uint8_t reserved_28[4];
    uint8_t ready;
    uint8_t reserved_2d;
    uint8_t value;
};

int32_t FUN_01008fd4(int32_t handle, uint32_t size)
{
    volatile struct controller_state *const state =
        (volatile struct controller_state *)0x21000a30u;

    if (handle == 0 || size == 0 || (size & 7u) != 0) {
        return -22;
    }
    if (FUN_01009210() == 0) {
        return -1;
    }

    state->value = FUN_010257e4(handle);
    FUN_01008a58(size, 0);
    FUN_0101fc14();
    FUN_0101f818(state->value, state->setting);
    FUN_01008d7c();
    state->ready = 1;
    return 0;
}
