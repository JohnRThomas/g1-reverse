#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100b630 @ 0x0100b630
 * public-name: FUN_0100b630
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100b630 @ 0x100b630  (CFG-directed candidate) */
extern __attribute__((noreturn)) void sdc_assertion_fail(unsigned int, unsigned int); /* FUN_01008d00 @ 0x01008d00 */
extern unsigned int FUN_01025998(unsigned int, unsigned int, unsigned int);
extern void sdc_buffer_descriptor_resolve(unsigned int, unsigned int *, unsigned short *); /* FUN_0102714a @ 0x0102714a */
extern unsigned int sdc_buffer_payload_get(unsigned int); /* FUN_010270d2 @ 0x010270d2 */
extern void sdc_buffer_accumulate(unsigned int, unsigned int, unsigned int); /* FUN_01026f32 @ 0x01026f32 */

void FUN_0100b630(unsigned int flags, unsigned int *payload_out)
{
    volatile unsigned char *state = (volatile unsigned char *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/;
    volatile unsigned char *connection = *(volatile unsigned char * volatile *)(state + 0x28);

    if ((flags & 2u) != 0) {
        unsigned int descriptor = *(volatile unsigned int *)(state + 0x38);
        unsigned int cursor;
        unsigned int payload;
        unsigned short fragment;
        unsigned int consumed;
        if (descriptor == 0)
            sdc_assertion_fail(0x27, 0x45f);
        cursor = *(volatile unsigned int *)(state + 0x2c);
        consumed = *(volatile unsigned char *)(cursor + 1);
        cursor = FUN_01025998(descriptor, cursor,
                             *(volatile unsigned short *)(state + 0xbc) + 3u);
        *(volatile unsigned int *)(state + 0x2c) = cursor;
        sdc_buffer_descriptor_resolve(*(volatile unsigned int *)(state + 0xc8),
                                      &payload, &fragment);
        payload = sdc_buffer_payload_get(payload);
        *payload_out = payload;
        sdc_buffer_accumulate(*(volatile unsigned int *)(state + 0xc8), consumed, 1);
    }

    if ((flags & 1u) != 0) {
        volatile unsigned char *toggle = connection + 0xc0;
        volatile unsigned long long *counter =
            (volatile unsigned long long *)(connection + 0x128);
        unsigned char old_toggle = *toggle;
        *counter = *counter + 1u;
        *toggle = old_toggle == 1u ? 0u : 1u;
    }
}
