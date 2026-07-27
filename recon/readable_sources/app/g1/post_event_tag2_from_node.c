#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_driver_ctx__param_0314           [param_0314; G1-original]
 *   local_24         => struct g1_layout_post_event_tag2_locals__stack_1556     [stack_1556; G1-original]
 * Raw function identity: 0x0008484e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008484e @ 0x0008484e
 * public-name: post_event_tag2_from_node
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_notify_callback                <= FUN_00084840 @ 0x00084840
 *   post_event_tag2_from_node                <= FUN_0008484e @ 0x0008484e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0008484e @ 0x8484e  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int transport_notify_callback(unsigned char*, unsigned long);

void post_event_tag2_from_node(int param_1, unsigned int param_2)
{
    unsigned int iVar1 = *(volatile unsigned int*)(param_1 + 0x10);
    unsigned char buf[20];
    memset_bytes(buf, 0, 0x14);
    buf[0] = 2;
    unsigned int iVar1_2 = *(volatile unsigned int*)(iVar1 + 0xc);
    *(unsigned int*)(buf+4) = *(volatile unsigned int*)(iVar1_2 + 0x58);
    *(unsigned int*)(buf+8) = *(volatile unsigned int*)(iVar1_2 + 0x60);
    *(unsigned int*)(buf+12) = param_2;
    transport_notify_callback(param_1, buf);
}
