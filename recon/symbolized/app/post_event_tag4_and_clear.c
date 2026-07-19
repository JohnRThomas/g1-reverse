#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084880 @ 0x00084880
 * public-name: post_event_tag4_and_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_notify_callback                <= FUN_00084840 @ 0x00084840
 *   post_event_tag4_and_clear                <= FUN_00084880 @ 0x00084880
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00084880 @ 0x84880  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, unsigned int c);
extern void transport_notify_callback(unsigned int a, void *b);

void post_event_tag4_and_clear(unsigned int param_1, int *param_2)
{
    unsigned char local_24[20];
    int iVar1 = *param_2;
    if (iVar1 != 0) {
        memset_bytes(local_24, 0, 0x14);
        local_24[0] = 4;
        *(int*)(local_24+4) = iVar1;
        transport_notify_callback(param_1, local_24);
        *param_2 = 0;
    }
}
