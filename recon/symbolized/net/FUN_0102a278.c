#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102a278 @ 0x0102a278
 * public-name: FUN_0102a278
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102a278 @ 0x102a278  (CFG-directed candidate) */
/* net-core FUN_0102a278 @ 0x102a278
 * The CPUNET "cpunet-hw-id" IPC service handler (service id 1).  FUN_0102a720
 * registers this body's runtime Thumb pointer 0x0102aa79 as the endpoint
 * callback, and FUN_0102ab14 dispatches it as handler(state, data + 1,
 * size - 1), so packet[0] is the sub-command.
 *
 * The only indirect call is state->send(message, 16); its reviewed ABI is two
 * arguments, so the ordinal-0 comparison is declared:
 * CFG_VERIFY_CALL_ARITIES=2
 */
#include <stdint.h>

typedef int (*net_send_fn)(const void *message, uint32_t size);

extern void FUN_01039722(const void *format, ...);
extern void FUN_0102b794(void);
extern void FUN_0102b7a0(void);
extern void FUN_0102b7ac(void);
extern void FUN_0102bbc4(void);

int FUN_0102a278(uint8_t *state, const uint8_t *packet, uint32_t size)
{
    volatile int32_t *const log_level = (volatile int32_t *)0x21000580u;
    volatile uint8_t *const reply_pending = (volatile uint8_t *)0x21000760u;
    uint8_t **const service_slot = (uint8_t **)0x210045f4u;
    union {
        uint32_t w[4];
        uint16_t h[8];
        uint8_t b[16];
    } message;

    message.w[0] = 0u;
    message.w[1] = 0u;
    message.w[2] = 0u;
    message.w[3] = 0u;

    switch (packet[0]) {
    case 0: {
        uint8_t primary;
        *(uint32_t *)(state + 0) = packet[1];
        *(uint32_t *)(state + 4) = packet[2];
        *(uint32_t *)(state + 8) = packet[3];
        primary = packet[4];
        if (primary != 0xffu) {
            uint8_t secondary = packet[5];
            if ((uint8_t)(secondary - 1u) <= 0xfdu && primary != 0u) {
                volatile uint8_t *const hi = (volatile uint8_t *)0x21000767u;
                volatile uint8_t *const lo = (volatile uint8_t *)0x21000761u;
                volatile uint8_t *const mid = (volatile uint8_t *)0x21000763u;
                hi[0] = primary;
                hi[1] = primary;
                hi[2] = primary;
                hi[3] = primary;
                lo[0] = primary;
                lo[1] = secondary;
                mid[0] = secondary;
                mid[1] = secondary;
                mid[2] = secondary;
                mid[3] = secondary;
            }
        }
        message.h[0] = 0x101u;
        (*(net_send_fn *)(state + 0xa8))(message.b, 16u);
        if (*reply_pending != 0u) {
            *reply_pending = 0u;
            if (*log_level > 1) {
                FUN_01039722((const void *)0x0103ccdau, size,
                             *(uint32_t *)(state + 0),
                             *(uint32_t *)(state + 4),
                             *(uint32_t *)(state + 8));
            }
        }
        break;
    }
    case 8:
        *(uint32_t *)(*service_slot + 4) = 1u;
        FUN_0102bbc4();
        if (*log_level > 1) {
            FUN_01039722((const void *)0x0103ccf1u,
                         *(uint32_t *)(*service_slot + 4));
        }
        break;
    case 10:
        FUN_0102b794();
        if (*log_level > 1) {
            FUN_01039722((const void *)0x0103ccf7u);
        }
        break;
    case 11:
        FUN_0102b7a0();
        if (*log_level > 1) {
            FUN_01039722((const void *)0x0103ccfau);
        }
        break;
    case 12:
        FUN_0102b7ac();
        if (*log_level > 1) {
            FUN_01039722((const void *)0x0103ccfdu);
        }
        break;
    default:
        break;
    }
    return 0;
}
