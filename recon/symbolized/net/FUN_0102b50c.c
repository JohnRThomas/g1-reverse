#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102b50c @ 0x0102b50c
 * public-name: FUN_0102b50c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102b50c @ 0x102b50c  (P4 iteration 24; parity 400/400 trials, 0 mismatches, event id 0/1/2/default all directed) */
/* CPUNET ESB EVENT HANDLER @ 0x0102b50c.
 * Raw back-map: FUN_0102b50c@0x0102b50c; true extent 0x90 (literal pool
 * 0x0102b59c..0x0102b5bc).
 *
 * This is the `event_handler` member of the ESB configuration template at
 * runtime 0x0103c100: FUN_0102b31c stores the runtime Thumb pointer
 * 0x0102bd0d (= analysis 0x0102b50c | 1) into config[1], and FUN_010333b4
 * publishes it at 0x21004a90 for the ESB driver to call.
 *
 * event ids: 0 = TX failed, 1 = TX success, 2 = RX received.
 */
#include <stdint.h>

extern void FUN_0102b3f0(unsigned int announce_start);
extern unsigned int FUN_0102bbe0(void);
extern int FUN_010337ac(void *payload);
extern void FUN_0102b49c(void);

void FUN_0102b50c(const void *event)
{
    volatile uint8_t *const sync_pending  = (volatile uint8_t *)((unsigned long)&g_esb_sync_pending_flag) /*=0x21004fa3*/;
    volatile uint8_t *const message       = (volatile uint8_t *)((unsigned long)&g_esb_sync_message) /*=0x21004618*/;
    void (*volatile *const dispatch)(volatile uint8_t *) =
        (void (*volatile *)(volatile uint8_t *))((unsigned long)&g_net_ipc_msg_data) /*=0x21004628*/;
    volatile uint8_t *const clock_ready   = (volatile uint8_t *)0x21004fa1u;
    volatile uint8_t *const receive_mode  = (volatile uint8_t *)0x21004fa2u;
    volatile uint8_t *const rx            = (volatile uint8_t *)((unsigned long)&g_esb_rx_payload) /*=0x21004da1*/;
    volatile uint8_t *const service_state = (volatile uint8_t *)((unsigned long)&g_net_ctrl_rx_ready_flag) /*=0x21004c9c*/;
    uint8_t id = *(const volatile uint8_t *)event;

    if (id == 1) {
        FUN_0102b3f0(0);
        if (*clock_ready == 0)
            return;
        if (FUN_0102bbe0() == 0)
            return;
    } else if (id == 2) {
        *sync_pending = 0;
        if (*receive_mode == 1)
            FUN_0102b3f0(1);
        for (;;) {
            if (FUN_010337ac((void *)rx) != 0)
                return;
            if (*receive_mode == 0 && rx[5] == 0x11u) {
                *sync_pending = 1;
                FUN_0102b49c();
                continue;
            }
            *service_state = 2;
            message[0] = 2;
            *(volatile uint32_t *)(message + 4) =
                (uint32_t)(((unsigned long)&g_esb_rx_payload) + 5u) /*=0x21004da6*/;
            *(volatile uint32_t *)(message + 8) = rx[0];
            message[12] = rx[2];
            (*dispatch)(message);
        }
    } else if (id != 0) {
        return;
    } else {
        *sync_pending = 0;
    }

    message[0] = id;
    (*dispatch)(message);
}
