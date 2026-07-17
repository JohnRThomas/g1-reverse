#include "g1_net_symbols.h"
/* net-core FUN_0102e000 @ 0x0102e000
 *
 * One-time initialization of the closed controller's linker-collected
 * participant table.  The raw FUN identity and every fixed address remain in
 * place as the reversible mapping; descriptive aliases make the recovered
 * control flow readable without inventing new link symbols.
 */
#include <stdint.h>

extern uint32_t FUN_0102dcf4(uint32_t wait_until_ready,
                             uint32_t delay_between_retries);
extern int32_t FUN_0102df2c(void);
extern void FUN_01039bbe(uint32_t condition, uint32_t source, uint32_t line);
extern void FUN_01039bb0(uint32_t source, uint32_t line);

#define controller_participants_start FUN_0102dcf4
#define controller_process_one_event  FUN_0102df2c
#define assert_print                  FUN_01039bbe
#define arch_raise_kernel_oops        FUN_01039bb0

struct controller_participant;

struct controller_participant_ops {
    uintptr_t process_event;
    uintptr_t stop;
    void (*initialize)(const struct controller_participant *participant);
};

struct controller_participant_state {
    uint32_t value;
    uint8_t slot;
    uint8_t active;
};

struct controller_participant {
    const struct controller_participant_ops *ops;
    volatile struct controller_participant_state *state;
    uint32_t reserved;
    uint8_t enabled;
    uint8_t padding[3];
};

void FUN_0102e000(void)
{
    volatile uint8_t *const initialized =
        (volatile uint8_t *)UINT32_C(0x21004fad);
    const uintptr_t participants_begin = UINT32_C(0x0103c0ec);
    const uintptr_t participants_end = UINT32_C(0x0103c0fc);

    if (*initialized != 0U) {
        return;
    }

    /* r1 is deliberately zero at the original call boundary.  This asks the
     * shared start routine to retry immediately without an inter-retry delay. */
    (void)controller_participants_start(1U, 0U);

    for (uintptr_t participant_address = participants_begin;
         participant_address != participants_end;
         participant_address += sizeof(struct controller_participant)) {
        if (participant_address > participants_end) {
            assert_print(UINT32_C(0x0103d2a7), UINT32_C(0x0103d5d7),
                         UINT32_C(0x188));
            arch_raise_kernel_oops(UINT32_C(0x0103d5d7), UINT32_C(0x188));
        }

        const struct controller_participant *const participant =
            (const struct controller_participant *)participant_address;
        if (participant->state->active != 0U) {
            participant->ops->initialize(participant);
        }
    }

    while (controller_process_one_event() != 0) {
        /* Drain all controller work made pending during participant init. */
    }

    *initialized = 1U;
}
