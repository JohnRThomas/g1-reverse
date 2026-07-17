#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033b88 @ 0x00033b88
 * public-name: stage_pending_message_for_resend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   stage_pending_message_for_resend         <= FUN_00033b88 @ 0x00033b88
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   g_esb_notify_ring_staging_buf            @ 0x20007bf4
 */
/* Reconstructed FUN_00033b88 @ 0x33b88  (parity: 300/300 trials, PROVEN) */

extern void memcpy(unsigned int, unsigned int, int, int, unsigned int);

unsigned int stage_pending_message_for_resend(void)
{
    unsigned int base = 0x20008dacUL;
    unsigned char v118 = *(volatile unsigned char*)(base + 0x118);
    unsigned int uVar2 = v118;
    if (v118 != 0) {
        unsigned char v116 = *(volatile unsigned char*)(base + 0x116);
        if (v116 == 0) {
            uVar2 = 0;
            unsigned char v115 = *(volatile unsigned char*)(base + 0x115);
            if (v115 < 4) {
                *(volatile unsigned char*)(base + 0x114) = 10;
                memcpy(((unsigned long)g_esb_notify_ring_staging_buf) /*=0x20007bf4*/, base + 0x108, 0x1b4, 10, 0);
                uVar2 = ((unsigned long)g_esb_notify_ring_staging_buf) /*=0x20007bf4*/;
            }
        } else {
            uVar2 = 0;
        }
    }
    return uVar2;
}
