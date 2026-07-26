#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_28         => struct g1_layout_display_close_locals__stack_1050       [stack_1050; G1-original]
 * Raw function identity: 0x000497b0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000497b0 @ 0x000497b0
 * public-name: display_close
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef01c                             @ 0x000ef01c   [INLINED -- G6 literal batch]
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_f0044                             @ 0x000f0044   [INLINED -- G6 literal batch]
 *   rodata_f018c                             @ 0x000f018c   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_close @ 0x497b0. */

#include <stdint.h>
#include "../../../headers/g1_log.h"

struct display_close_packet {
    uint8_t type;
    uint8_t reserved;
    uint16_t payload_length;
    uint8_t payload[20];
};

extern int k_msgq_put(void *owner, const void *packet,
                        int option_a, int option_b);
extern void memcpy(void *destination, const void *source,
                         unsigned int length);
extern void memset_bytes(void *destination, int value,
                         unsigned int length);

int display_close(const void *payload, unsigned int payload_length)
{
    struct display_close_packet packet;
    int result;

    memset_bytes(&packet, 0, sizeof(packet));
    if (payload_length > 10) {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): send data length more than %d,can't load it,exit ...\n") /*=0xef01c*/, ((unsigned long)"display_close") /*=0xf018c*/, 10);
            } else {
                debug_print(((unsigned long)"%s(): send data length more than %d,can't load it,exit ...\n") /*=0xef01c*/, ((unsigned long)"display_close") /*=0xf018c*/, 10);
            }
        }
        return -1;
    }

    packet.type = 3;
    if (payload != 0) {
        memcpy(packet.payload, payload, payload_length);
        packet.payload_length = (uint16_t)payload_length;
    }

    result = k_msgq_put((void *)((unsigned long)&g_display_msgq) /*=0x200038c4*/, &packet, 0, 0);
    if (result != 0) {
        log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"display_close") /*=0xf018c*/);
        return -1;
    }

    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): send display close command.......\n") /*=0xf0044*/, ((unsigned long)"display_close") /*=0xf018c*/);
        } else {
            debug_print(((unsigned long)"%s(): send display close command.......\n") /*=0xf0044*/, ((unsigned long)"display_close") /*=0xf018c*/);
        }
    }
    return 0;
}
