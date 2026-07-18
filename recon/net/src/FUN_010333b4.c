/* net-core radio-owner initialization @ 0x010333b4, true extent 0x22c.
 * Raw-address callees remain declared below; semantic aliases keep every
 * recovered role mechanically reversible to the shipped symbol/address.
 */
#include <stdint.h>

extern void FUN_01033354(void);
extern uint32_t FUN_0103b62e(uint32_t, uint32_t, uint32_t);
/* This leaf returns status in r0 and deliberately preserves its incoming r1;
 * model that live-through pair as one AAPCS 64-bit result. */
extern uint64_t FUN_01032764(uint32_t, uint32_t);
extern uint32_t *FUN_010327a0(uint32_t);
extern uint32_t FUN_01034fa8(uint32_t, void *, uint32_t);
extern int FUN_01033df0(void);
extern uint8_t FUN_01033de4(void);
extern void FUN_0103a83e(void);
extern void FUN_0102eb8c(uint32_t, uint32_t, uint32_t);
extern void FUN_0103a38a(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void FUN_0102eb2c(uint32_t);
extern void FUN_0102e284(uint32_t, uint32_t, void *, uint32_t);

#define reset_radio_owner             FUN_01033354
#define clear_radio_storage           FUN_0103b62e
#define initialize_radio_mode_state   FUN_01032764
#define acquire_radio_buffer_table    FUN_010327a0
#define start_radio_owner_timer       FUN_01034fa8
#define initialize_radio_backend      FUN_01033df0
#define read_radio_device_state       FUN_01033de4
#define activate_radio_backend        FUN_0103a83e
#define configure_radio_irq           FUN_0102eb8c
#define connect_radio_irq_handler     FUN_0103a38a
#define enable_radio_irq              FUN_0102eb2c
#define publish_radio_diagnostic      FUN_0102e284

struct timer_init {
    uint32_t period;
    uint32_t flags;
    uint32_t context;
};

int FUN_010333b4(const uint32_t *configuration)
{
    volatile uint8_t *const initialized = (volatile uint8_t *)0x21006459U;
    volatile uint8_t *const active = (volatile uint8_t *)0x21006458U;
    volatile uint32_t *const saved_word = (volatile uint32_t *)0x21004a90U;
    volatile uint8_t *const saved = (volatile uint8_t *)0x21004a94U;
    volatile uint32_t *const control = (volatile uint32_t *)0x210049b0U;
    volatile uint32_t *callback_slot;
    volatile uint32_t *const radio = (volatile uint32_t *)0x41008000U;
    volatile uint8_t *const device_state = (volatile uint8_t *)0x2100065cU;
    volatile uint32_t *table;
    uint32_t value;
    int status;

    if (configuration == 0)
        return -22;
    if (*initialized != 0)
        reset_radio_owner();

    *saved_word = configuration[1];
    {
        const uint32_t *source = configuration;
        volatile uint32_t *destination = (volatile uint32_t *)saved;
        const uint32_t *const paired_end = configuration + 4;
        __asm__ volatile ("" : "+r" (destination));
        do {
            uint32_t first = source[0];
            uint32_t second = source[1];
            source += 2;
            *destination++ = first;
            *destination++ = second;
        } while (source != paired_end);
        *destination = *source;
    }

    *control = 0;
    value = clear_radio_storage(0x21004b7cU, 0, 0x20);
    *(volatile uint32_t *)0x21006256U = 0;
    *(volatile uint32_t *)0x2100625aU = 0;
    uint64_t init_result = initialize_radio_mode_state(value, 0x2100499cU);
    callback_slot = (volatile uint32_t *)(uintptr_t)(uint32_t)(init_result >> 32);

    if (saved[0] == 0)
        *callback_slot = 0x010333a5U;
    else if (saved[0] == 1)
        *callback_slot = 0x010333e5U;

    if (saved[9] == 0) {
        radio[0x53c / 4] = 0;
        radio[0x534 / 4] = 0;
        radio[0x538 / 4] = 0;
    } else if (saved[9] == 1) {
        radio[0x53c / 4] = 0xff;
        radio[0x534 / 4] = 1;
        radio[0x538 / 4] = 0x107;
    } else if (saved[9] == 2) {
        radio[0x53c / 4] = 0xffff;
        radio[0x534 / 4] = 2;
        radio[0x538 / 4] = 0x11021;
    }
    ((void (*)(uint32_t))(uintptr_t)*callback_slot)(saved[0x11]);

    radio[0x51c / 4] = 0xe7e7e7e7U;
    radio[0x520 / 4] = 0x43434343U;
    radio[0x524 / 4] = 0x23c343e7U;
    radio[0x528 / 4] = 0x13e363a3U;

    table = acquire_radio_buffer_table(0x21004a60U);
    value = 0x21005a56U;
    for (unsigned i = 0; i < 8; ++i, value += 0x100U)
        table[i] = value;

    table = (volatile uint32_t *)0x21004a34U;
    value = 0x21005256U;
    __asm__ volatile ("" : "+r" (table));
    for (unsigned i = 0; i < 8; ++i, value += 0x100U)
        *table++ = value;

    value = 0x21005a56U;
    for (unsigned i = 0; i < 8; ++i, value += 0x100U) {
        volatile uint8_t *entry = (volatile uint8_t *)(0x210049d4U + 12U * i);
        *(volatile uint32_t *)(entry + 0) = value;
        entry[4] = 0;
        *(volatile uint32_t *)(entry + 8) = 0;
    }

    clear_radio_storage(0x210049b4U, 0, 0x20);
    struct timer_init timer = { 1000000U, 0, 0 };
    status = (int)start_radio_owner_timer(0x21000698U, &timer,
                                          0x01032fbdU);
    if ((uint32_t)status != 0x0bad0000U) {
        struct { uint32_t count, text, code; } first = {
            3, 0x0103e414U, (uint32_t)status
        };
        publish_radio_diagnostic(0x0103c05cU, 0x1840U, &first, 0);
        struct { uint32_t count, text; } second = { 2, 0x0103e43dU };
        publish_radio_diagnostic(0x0103c05cU, 0x1040U, &second, 0);
        return -14;
    }

    status = initialize_radio_backend();
    if (status != 0) {
        struct { uint32_t count, text; } message = { 2, 0x0103e463U };
        publish_radio_diagnostic(0x0103c05cU, 0x1040U, &message, 0);
        return status;
    }

    device_state[4] = read_radio_device_state();
    radio[0x650 / 4] = (radio[0x650 / 4] & 0x300U) | saved[0x13];
    activate_radio_backend();
    configure_radio_irq(8, 1, 0);
    configure_radio_irq(0x1d, 2, 0);
    configure_radio_irq(0x19, 2, 0);
    connect_radio_irq_handler(8, 1, 0x01032fd9U, 0, 0);
    connect_radio_irq_handler(0x1d, 2, 0x0103309dU, 0, 0);
    connect_radio_irq_handler(0x19, 2, 0x0103b03bU, 0, 0);
    enable_radio_irq(8);
    enable_radio_irq(0x1d);
    enable_radio_irq(0x19);
    *active = 0;
    *initialized = 1;
    return 0;
}
