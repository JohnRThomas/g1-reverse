#include "g1_app_symbols.h"
/* named: stage_pending_message_for_resend */
/* Reconstructed stage_pending_message_for_resend @ 0x33b88  (parity: 300/300 trials, PROVEN) */

extern void memcpy(unsigned int, unsigned int, int, int, unsigned int);

unsigned int stage_pending_message_for_resend(void)
{
    unsigned int base = ((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/;
    unsigned char v118 = *(volatile unsigned char*)(base + 0x118);
    unsigned int uVar2 = v118;
    if (v118 != 0) {
        unsigned char v116 = *(volatile unsigned char*)(base + 0x116);
        if (v116 == 0) {
            uVar2 = 0;
            unsigned char v115 = *(volatile unsigned char*)(base + 0x115);
            if (v115 < 4) {
                *(volatile unsigned char*)(base + 0x114) = 10;
                memcpy((g_esb_notify_ring_staging_buf) /*=0x20007bf4*/, base + 0x108, 0x1b4, 10, 0);
                uVar2 = (g_esb_notify_ring_staging_buf) /*=0x20007bf4*/;
            }
        } else {
            uVar2 = 0;
        }
    }
    return uVar2;
}

