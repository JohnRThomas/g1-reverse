/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_21001ce8[];
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004b30[];
extern unsigned char g1_net_ram_blk_21004c98[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_21001cf0 ((unsigned long)(g1_net_ram_blk_21001ce8 + 0x8))
#define G1N_210045e8 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x8))
#define G1N_210045ec ((unsigned long)(g1_net_ram_blk_210045e0 + 0xc))
#define G1N_210045f0 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x10))
#define G1N_210045f4 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x14))
#define G1N_21004b9c ((unsigned long)(g1_net_ram_blk_21004b30 + 0x6c))
#define G1N_21004b9d ((unsigned long)(g1_net_ram_blk_21004b30 + 0x6d))
#define G1N_21004c9b ((unsigned long)(g1_net_ram_blk_21004c98 + 0x3))
#define G1N_21004c9c ((unsigned long)(g1_net_ram_blk_21004c98 + 0x4))
#define G1N_21004c9d ((unsigned long)(g1_net_ram_blk_21004c98 + 0x5))
#define G1N_21004c9f ((unsigned long)(g1_net_ram_blk_21004c98 + 0x7))
#define G1N_21004ca0 ((unsigned long)(g1_net_ram_blk_21004c98 + 0x8))
#else
#define G1N_21000580 0x21000580ul
#define G1N_21001cf0 0x21001cf0ul
#define G1N_210045e8 0x210045e8ul
#define G1N_210045ec 0x210045ecul
#define G1N_210045f0 0x210045f0ul
#define G1N_210045f4 0x210045f4ul
#define G1N_21004b9c 0x21004b9cul
#define G1N_21004b9d 0x21004b9dul
#define G1N_21004c9b 0x21004c9bul
#define G1N_21004c9c 0x21004c9cul
#define G1N_21004c9d 0x21004c9dul
#define G1N_21004c9f 0x21004c9ful
#define G1N_21004ca0 0x21004ca0ul
#endif
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
    volatile int32_t *const log_level = (volatile int32_t *)G1N_21000580;
    volatile uint32_t *const rx_count = (volatile uint32_t *)G1N_210045e8;
    volatile uint32_t *const tx_failed_count = (volatile uint32_t *)G1N_210045ec;
    volatile uint32_t *const tx_success_count = (volatile uint32_t *)G1N_210045f0;
    volatile uint32_t *const service_slot = (volatile uint32_t *)G1N_210045f4;
    volatile uint8_t *const event_busy = (volatile uint8_t *)G1N_21004ca0;
    volatile uint8_t *const rx_state = (volatile uint8_t *)G1N_21004c9b;
    volatile uint8_t *const rx_ready = (volatile uint8_t *)G1N_21004c9c;
    volatile uint8_t *const rx_role = (volatile uint8_t *)G1N_21004c9d;
    volatile uint8_t *const rx_channel = (volatile uint8_t *)G1N_21004c9f;
    volatile uint8_t *const retry_count = (volatile uint8_t *)G1N_21004b9d;
    volatile uint8_t *const last_sequence = (volatile uint8_t *)G1N_21004b9c;
    volatile uint64_t *const last_rx_time = (volatile uint64_t *)G1N_21001cf0;

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
