/* net-core FUN_0102a4c8 @ 0x0102a4c8
 * Readable identity: g1_esb_event_handler.
 * Raw back-map: main stores runtime Thumb pointer 0x0102acc9.
 */
#include <stdint.h>

#ifdef G1_COHESIVE_BUILD
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app_esb, LOG_LEVEL_INF);
#endif

#define g1_esb_event_handler FUN_0102a4c8

extern void FUN_01039722(const char *format, ...);
extern void FUN_0102a4b0(void);
extern uint64_t FUN_0103963c(void);
extern uint64_t FUN_0103b300(uint64_t value);

struct g1_esb_event {
    uint8_t type;
    uint8_t reserved[3];
    const uint8_t *payload;
    uint32_t length;
    uint8_t channel;
};

void g1_esb_event_handler(const struct g1_esb_event *event)
{
    volatile int32_t *const log_level = (volatile int32_t *)0x21000580u;
    volatile uint32_t *const rx_count = (volatile uint32_t *)0x210045e8u;
    volatile uint32_t *const tx_failed_count = (volatile uint32_t *)0x210045ecu;
    volatile uint32_t *const tx_success_count = (volatile uint32_t *)0x210045f0u;
    volatile uint32_t *const service_slot = (volatile uint32_t *)0x210045f4u;
    volatile uint8_t *const event_busy = (volatile uint8_t *)0x21004ca0u;
    volatile uint8_t *const rx_state = (volatile uint8_t *)0x21004c9bu;
    volatile uint8_t *const rx_ready = (volatile uint8_t *)0x21004c9cu;
    volatile uint8_t *const rx_role = (volatile uint8_t *)0x21004c9du;
    volatile uint8_t *const rx_channel = (volatile uint8_t *)0x21004c9fu;
    volatile uint8_t *const retry_count = (volatile uint8_t *)0x21004b9du;
    volatile uint8_t *const last_sequence = (volatile uint8_t *)0x21004b9cu;
    volatile uint64_t *const last_rx_time = (volatile uint64_t *)0x21001cf0u;

    *event_busy = 1;

    if (event->type == 0) {
        ++*tx_success_count;
        if (*log_level > 2)
            FUN_01039722((const char *)0x0103cd00u);
    } else if (event->type == 1) {
        ++*tx_failed_count;
        if (*log_level > 2)
            FUN_01039722((const char *)0x0103cd0cu);
    } else if (event->type == 2) {
        ++*rx_count;

        volatile uint32_t *service =
            (volatile uint32_t *)(uintptr_t)*service_slot;
        if (service[1] != 1) {
            uint8_t state = *rx_state;
            if (service[0] == 2) {
                if (state == 1 && *rx_ready == 2) {
                    uint8_t next = (uint8_t)(*retry_count + 1u);
                    if (next > 1) {
                        *retry_count = 0;
                        *rx_ready = 0;
                        *rx_state = 0;
                        *rx_role = 2;
                        FUN_0102a4b0();
                    } else {
                        *retry_count = next;
                    }
                }
            } else if (state != 0) {
                if (state == 2) {
                    *rx_state = 0;
                } else if (state == 1 && *rx_ready == 2) {
                    *rx_state = 0;
                    *rx_role = 2;
                    FUN_0102a4b0();
                }
            }

            *rx_channel = event->channel;
            if ((uint8_t)(event->payload[0] - 0x10u) > 1u) {
                if (service[0] == 2 && event->length > 15u) {
                    uint8_t sequence = event->payload[0x11];
                    if (*last_sequence == sequence)
                        goto done;
                    *last_sequence = sequence;
                }

                uint64_t ticks = FUN_0103963c();
                uint64_t converted = FUN_0103b300(ticks);
                *last_rx_time = (converted * 1000u + 0x7fffu) >> 15;
            }
        }
    } else if (*log_level > 0) {
        FUN_01039722((const char *)0x0103cd17u);
    }

done:
    *event_busy = 0;
}
