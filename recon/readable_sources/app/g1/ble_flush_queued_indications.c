#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_app_ble_ctx_block__param_0038          [param_0038; G1-original]
 * Raw function identity: 0x0007c20a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007c20a @ 0x0007c20a
 * public-name: ble_flush_queued_indications
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   dequeue_debug                            <= FUN_00019c44 @ 0x00019c44
 *   ble_flush_queued_indications             <= FUN_0007c20a @ 0x0007c20a
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007c20a @ 0x7c20a  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, unsigned int b, unsigned int c);
extern int dequeue_debug(void *a);
extern short strlen(void *a);

unsigned int ble_flush_queued_indications(int param_1)
{
    short sVar1;
    int iVar2;
    struct queue_frame {
        unsigned char reserved[4];
        unsigned char control;
        unsigned char payload[203];
    } frame;

    while (1) {
        memset_bytes(frame.payload, 0, 0xca);
        frame.control = 0xf4;
        iVar2 = dequeue_debug(frame.payload);
        if (iVar2 != 0) break;
        sVar1 = strlen(&frame.control);
        (*(void (**)(void *, unsigned short))(param_1 + 0xc))
            (&frame.control, (unsigned short)(sVar1 + 1));
    }
    return 0;
}
