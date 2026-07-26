#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025670 @ 0x00025670
 * public-name: dev_send_cmd16_payload
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_send_cmd16_payload                   <= FUN_00025670 @ 0x00025670
 *   ipc_transport_ops_dispatch               <= FUN_0007c85e @ 0x0007c85e
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9f1eb                             @ 0x0009f1eb   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00025670 @ 0x25670 CFG_VERIFY_CALL_ARITIES=3,4,0,2 */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void memcpy(uint8_t *, const uint8_t *, uint32_t);
extern int ipc_transport_ops_dispatch(uint32_t, void *, uint32_t, uint32_t);
extern void sleep_fixed_33_ticks(void);
struct part { uint8_t *data; uint32_t length; uint8_t type; };
int dev_send_cmd16_payload(uint32_t *dev, uint32_t op, uint32_t command,
                 uint32_t value, uint32_t n)
{
    uint8_t bytes[n + 2];
    bytes[0] = command >> 8; bytes[1] = command;
    memcpy(bytes + 2, (const uint8_t *)(uintptr_t)value, n);
    struct part p = {bytes, n + 2, 2};
    int r = ipc_transport_ops_dispatch(*dev, &p, 1, op);
    sleep_fixed_33_ticks();
    if (r < 0) log_message(((unsigned long)"_st25dv_write  ret %d \n") /*=0x9f1eb*/, r);
    return r;
}
