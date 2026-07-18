#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ee74 @ 0x0007ee74
 * public-name: FUN_0007ee74
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_z_log_msg_commit                <= FUN_0004d8b8 @ 0x0004d8b8
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Full reconstruction FUN_0007ee74 @ 0x7ee74 (exact code extent 50 bytes). */
#include <stdint.h>
extern uint32_t FUN_0004d468(void *, uint32_t, uint32_t);
extern void memcpy(uint8_t *, uint32_t, uint32_t);
extern uint32_t g1_recon_z_log_msg_commit(void *);
uint32_t FUN_0007ee74(uint32_t *object, uint32_t upper, uint32_t lower, uint32_t tag)
{
    if (object == 0) return FUN_0004d468(0, tag, lower >> 20);
    if (tag != 0) {
        unsigned offset = (lower >> 9) & 0x7ff;
        memcpy((uint8_t *)object + 16 + offset, tag, lower >> 20);
    }
    object[0] = lower;
    object[1] = upper;
    return g1_recon_z_log_msg_commit(object);
}
