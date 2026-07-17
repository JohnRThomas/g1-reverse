/* readable reconstruction; identity: FUN_010127f8 @ 0x010127f8
 * public-name: sdc_ext_adv_event_complete
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_1011add                           @ 0x01011add
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core sdc_ext_adv_event_complete @ 0x010127f8
 *
 * Back mapping: FUN_010127f8.  This is the forced-completion entry used when
 * the extended-advertising event cannot reserve its next radio window.  It
 * increments num_completed_ext_adv_events, either reschedules another event
 * or emits the LE Advertising Set Terminated record.  Status 0x43 is the
 * Bluetooth HCI "Limit Reached" status; 0xffff is the no-connection handle.
 *
 * True executable extent is 0xba bytes: the tail branch at 0x10128ae ends at
 * 0x10128b2.  The alignment halfword and two literal words occupy
 * 0x10128b2..0x10128bb; FUN_010128bc is the next independent entry.
 * NCS 2.5.1 SDC reference matches two controller-role variants at 0.964 over
 * 67 normalized operations (raw obfuscated symbols retained in the catalog).
 * CFG verification uses six production fixtures covering cleanup, existing
 * termination, unlimited/below-limit rescheduling, event suppression, and
 * both connectable/no-connection termination records.  A status mutation is
 * rejected on both publication paths.
 */
#include <stdint.h>

extern void sdc_work_submit(void *, uintptr_t, uint32_t);       /* FUN_0100ef88 */
extern void sdc_ext_adv_reschedule(void *, uint32_t);           /* FUN_010140ec */
extern int sdc_hci_event_suppressed(void);                      /* FUN_0101f888 */
extern void sdc_llcp_release_rx_context(void);                  /* FUN_0101fca8 */
extern void sdc_llcp_stop_rx_timeout(void);                     /* FUN_010208b0 */

/* Shared radio state at literal 0x21000f20. */
#define RADIO_STATE                 ((volatile uint8_t *)0x21000f20u)
#define RADIO_EVENT_ACTIVE          RADIO_STATE[0x04]
#define RADIO_RX_CLEANUP_PENDING     RADIO_STATE[0x12]

/* Extended-advertising set fields used by this completion path. */
#define ADV_U8(ctx, off)  (*(volatile uint8_t *)((ctx) + (off)))
#define ADV_U16(ctx, off) (*(volatile uint16_t *)((ctx) + (off)))
#define ADV_PTR(ctx, off) (*(volatile uintptr_t *)((ctx) + (off)))

#define ADV_HANDLE(ctx)               ADV_U8((ctx), 0x00)
#define ADV_PROPERTIES(ctx)           ADV_U16((ctx), 0x02)
#define ADV_MAX_EVENTS(ctx)           ADV_U8((ctx), 0x0d)
#define ADV_TX_PDU_PTR(ctx)           ADV_PTR((ctx), 0x1c)
#define ADV_COMPLETED_EVENTS(ctx)      ADV_U16((ctx), 0x40)
#define ADV_TERMINATED(ctx)            ADV_U8((ctx), 0x79)
#define ADV_TERMINATION_WORK(ctx)      ((ctx) + 0xa6)
#define ADV_TERMINATION_STATUS(ctx)    ADV_U8((ctx), 0xaf)
#define ADV_TERMINATION_HANDLE(ctx)    ADV_U8((ctx), 0xb0)
#define ADV_CONNECTION_HANDLE(ctx)     ADV_U16((ctx), 0xb1)
#define ADV_TERMINATION_COUNT(ctx)     ADV_U8((ctx), 0xb3)

#define ADV_PROP_CONNECTABLE 0x0001u
#define HCI_STATUS_LIMIT_REACHED 0x43u
#define HCI_CONN_HANDLE_NONE 0xffffu

/* Thumb callback pointer loaded from the original literal at 0x010128b8.
 * It is an internal entry at 0x01011adc inside the controller's advertising
 * dispatcher, hence the explicit address provenance rather than a guessed C
 * symbol boundary. */
#define ADV_TERMINATION_CALLBACK ((uintptr_t)0x01011addu)

void sdc_ext_adv_event_complete(uint8_t *adv)
{
    uint8_t completed;

    ADV_COMPLETED_EVENTS(adv)++;

    if (RADIO_RX_CLEANUP_PENDING != 0) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        RADIO_RX_CLEANUP_PENDING = 0;
    }
    RADIO_EVENT_ACTIVE = 0;

    if (ADV_TERMINATED(adv) != 0) {
        sdc_ext_adv_reschedule(adv, 1);
        return;
    }

    completed = ADV_MAX_EVENTS(adv);
    if (completed == 0 || ADV_COMPLETED_EVENTS(adv) < completed) {
        sdc_ext_adv_reschedule(adv, 0);
        return;
    }

    sdc_ext_adv_reschedule(adv, 1);
    if ((ADV_PROPERTIES(adv) & ADV_PROP_CONNECTABLE) != 0) {
        uint16_t connection_handle =
            *(volatile uint16_t *)ADV_TX_PDU_PTR(adv);
        if (sdc_hci_event_suppressed() != 0)
            return;
        completed = ADV_MAX_EVENTS(adv);
        ADV_CONNECTION_HANDLE(adv) = connection_handle;
        ADV_TERMINATION_HANDLE(adv) = ADV_HANDLE(adv);
        ADV_TERMINATION_STATUS(adv) = HCI_STATUS_LIMIT_REACHED;
    } else {
        if (sdc_hci_event_suppressed() != 0)
            return;
        completed = ADV_MAX_EVENTS(adv);
        /* The shipped controller publishes the sentinel as two byte writes;
         * retain that externally observable ordering. */
        ADV_TERMINATION_HANDLE(adv) = ADV_HANDLE(adv);
        ADV_U8(adv, 0xb1) = (uint8_t)HCI_CONN_HANDLE_NONE;
        ADV_U8(adv, 0xb2) = (uint8_t)(HCI_CONN_HANDLE_NONE >> 8);
        ADV_TERMINATION_STATUS(adv) = HCI_STATUS_LIMIT_REACHED;
    }

    if (completed != 0)
        completed = (uint8_t)ADV_COMPLETED_EVENTS(adv);
    ADV_TERMINATION_COUNT(adv) = completed;
    sdc_work_submit(ADV_TERMINATION_WORK(adv), ADV_TERMINATION_CALLBACK, 2);
}
