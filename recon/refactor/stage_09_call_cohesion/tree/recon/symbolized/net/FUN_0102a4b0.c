#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102a4b0 @ 0x0102a4b0
 * public-name: FUN_0102a4b0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_hci_transport_obj                  @ 0x210045f4
 */
/* net-core FUN_0102a4b0 @ 0x102a4b0  (parity 300 trials PROVEN) */

/* P4 iteration 30 - MEASURED DEFECT, fixed: ONE dereference too many.
 *
 * Shipped body at analysis 0x0102a4b0 (runtime 0x0102acb0):
 *     ldr r3,[pc,#16]     ; r3 = &0x210045f4        (the service slot)
 *     ldr r2,[r3,#0]      ; r2 = *slot = state
 *     ldr r2,[r2,#0x2c]   ; r2 = state->sem_b.count
 *     cbnz r2, return
 *     ldr r0,[r3,#0]      ; r0 = *slot = state
 *     adds r0,#0x24       ; r0 = &state->sem_b
 *     b.w  k_sem_give
 * i.e. `base` is the ONE-level dereference of the slot.  The previous
 * rendering computed `*(int *)*p`, i.e. state->role (= 1 on a master), so the
 * guard read address 0x2d and the give landed on address 0x25 -- unmapped, so
 * silently a no-op rather than a fault.
 *
 * MEASURED consequence (iteration 30, Renode block hooks, g1-i30d link): this
 * function ran 151 times in 9 s while the ESB uplink worker thread
 * FUN_0102b204 -- which blocks on exactly that k_sem -- completed its loop
 * body ONCE and then never woke again, so the {0x0d, 0x02} sync-ack relay
 * FUN_0102a408 never ran and device_info[0x105a] never left 1. */
extern void FUN_01036824(int);
void FUN_0102a4b0(void)
{
    volatile int * const * const p = (volatile int * const * const)((unsigned long)&g_sdc_hci_transport_obj) /*=0x210045f4*/;
    int base = (int)(unsigned long)*p;
    if (*(int*)(base + 0x2c) == 0) {
        FUN_01036824(base + 0x24);
    }
}
