/* readable reconstruction; identity: FUN_0102e064 @ 0x0102e064
 * public-name: FUN_0102e064
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0ec                           @ 0x0103c0ec
 *   rodata_103c0fc                           @ 0x0103c0fc
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d5d7                           @ 0x0103d5d7
 *   g_net_current_thread_field_cache         @ 0x21004660
 *   g_net_tick_pending_cnt                   @ 0x21004668
 */
/* net-core FUN_0102e064 @ 0x0102e064
 *
 * Persistent controller participant/event supervisor.  This is the runtime
 * companion to FUN_0102e000's one-time initialization.  Raw function and
 * address identities remain explicit for reversible symbolization.
 */
#include <stdint.h>

extern uint32_t FUN_0102dcf4(uint32_t wait_until_ready,
                             uint32_t delay_between_retries);
extern uint32_t FUN_0102dc90(uint32_t retry_mask);
extern int32_t FUN_0102df2c(void);
extern uintptr_t FUN_0103b650(void);
extern void FUN_01036824(void *wait_object);
extern void FUN_0103689c(void *wait_object, uint32_t reserved,
                         uint32_t timeout_low, uint32_t timeout_high);
extern void FUN_01039bbe(uint32_t condition, uint32_t source, uint32_t line);
extern void FUN_01039bb0(uint32_t source, uint32_t line);

#define controller_participants_start FUN_0102dcf4
#define controller_participants_retry FUN_0102dc90
#define controller_process_one_event  FUN_0102df2c
#define controller_wait_source_get    FUN_0103b650
#define controller_wait_prepare       FUN_01036824
#define controller_wait               FUN_0103689c
#define assert_print                  FUN_01039bbe
#define arch_raise_kernel_oops        FUN_01039bb0

struct controller_participant;

struct controller_participant_ops {
    uintptr_t process_event;
    uintptr_t stop;
    uintptr_t initialize;
    uintptr_t start;
    uintptr_t retry;
    uintptr_t reserved;
    void (*on_events_drained)(const struct controller_participant *participant,
                              uint32_t reason);
};

struct controller_participant {
    const struct controller_participant_ops *ops;
    uintptr_t state;
    uint32_t reserved;
    uint8_t enabled;
    uint8_t padding[3];
};

_Static_assert(sizeof(struct controller_participant) == 16,
               "controller participant ABI");

__attribute__((noreturn)) void FUN_0102e064(void)
{
    const uintptr_t participants_begin = UINT32_C(0x0103c0ec);
    const uintptr_t participants_end = UINT32_C(0x0103c0fc);
    void *const wait_object = (void *)UINT32_C(0x21000944);

    if (((participants_end - participants_begin) >> 4) == 0U) {
        assert_print(UINT32_C(0x0103d2a7), UINT32_C(0x0103d5d7),
                     UINT32_C(0x35c));
        arch_raise_kernel_oops(UINT32_C(0x0103d5d7), UINT32_C(0x35c));
    }

    uint32_t retry_mask = controller_participants_start(0U, 0U);
    uint64_t timeout = retry_mask != 0U ? UINT64_C(0x667) : UINT64_MAX;

    const uintptr_t wait_source = controller_wait_source_get();
    const uint32_t wait_source_value =
        *(const volatile uint32_t *)(wait_source + 8U);
    *(volatile uint32_t *)UINT32_C(0x21004660) = wait_source_value;
    if (wait_source_value != 0U &&
        *(const volatile int32_t *)UINT32_C(0x21004668) > 9) {
        controller_wait_prepare(wait_object);
    }

    int32_t last_event = 0;
    for (;;) {
        const int32_t previous_event = last_event;

        if (retry_mask != 0U) {
            retry_mask = controller_participants_retry(retry_mask);
            if (retry_mask == 0U) {
                timeout = UINT64_MAX;
            }
        }

        last_event = controller_process_one_event();
        if (last_event != 0) {
            continue;
        }

        if (previous_event != 0) {
            for (uintptr_t participant_address = participants_begin;
                 participant_address != participants_end;
                 participant_address += sizeof(struct controller_participant)) {
                if (participant_address > participants_end) {
                    assert_print(UINT32_C(0x0103d2a7),
                                 UINT32_C(0x0103d5d7), UINT32_C(0x350));
                    arch_raise_kernel_oops(UINT32_C(0x0103d5d7),
                                           UINT32_C(0x350));
                }

                const struct controller_participant *const participant =
                    (const struct controller_participant *)participant_address;
                if (participant->ops->on_events_drained != 0) {
                    participant->ops->on_events_drained(participant, 0U);
                }
            }
        }

        /* FUN_0103689c never consumes its physical r1 slot.  Pass a stable
         * reserved value while preserving the live wait object and timeout. */
        controller_wait(wait_object, 0U, (uint32_t)timeout,
                        (uint32_t)(timeout >> 32));
    }
}
