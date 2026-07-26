/* readable reconstruction; identity: FUN_00049a28 @ 0x00049a28
 * public-name: display_powerEvent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_f00ea                             @ 0x000f00ea   [INLINED -- G6 literal batch]
 *   rodata_f0126                             @ 0x000f0126   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_powerEvent @ 0x49a28. */

#include <stdint.h>
#include "../headers/g1_log.h"

extern int k_msgq_put(void *owner, const void *packet,
                        int option_a, int option_b);
extern void memset_bytes(void *destination, int value,
                         unsigned int length);

int display_powerEvent(int powered_on)
{
    uint8_t packet[24];
    int result;

    memset_bytes(packet, 0, sizeof(packet));
    packet[0] = powered_on == 1 ? 7 : 8;

    result = k_msgq_put((void *)0x200038c4UL, packet, 0, 0);
    if (result != 0) {
        log_message(((unsigned long)"message queue send failed %s\r\n"), 0x000f0126UL);
        return -1;
    }

    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile int *)0x20007554UL == 0) {
            log_message(0x000f00eaUL, 0x000f0126UL, powered_on);
        } else {
            debug_print(0x000f00eaUL, 0x000f0126UL, powered_on);
        }
    }
    return 0;
}
