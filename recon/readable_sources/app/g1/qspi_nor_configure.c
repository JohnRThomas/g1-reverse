#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_param_0299_driver_data_collision__param_0299 [param_0299; G1-original]
 * Raw function identity: 0x00060c00.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00060c00 @ 0x00060c00
 * public-name: qspi_nor_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_priority_set                    <= FUN_0005010c @ 0x0005010c
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   qspi_nor_suspend_bus                     <= FUN_00060a5c @ 0x00060a5c
 *   qspi_nor_send_cinstr                     <= FUN_00060ab0 @ 0x00060ab0
 *   qspi_nor_configure                       <= FUN_00060c00 @ 0x00060c00
 *   nrfx_qspi_init                           <= FUN_00066994 @ 0x00066994
 *   qspi_log_forward                         <= FUN_000838d6 @ 0x000838d6
 *   qspi_pinctrl_apply_state                 <= FUN_000838dc @ 0x000838dc
 *   audio_apply_config_cmd_0xab              <= FUN_0008397e @ 0x0008397e
 *   qspi_rdsr                                <= FUN_000839a6 @ 0x000839a6
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_838cb                             @ 0x000838cb
 *   rodata_88270                             @ 0x00088270
 *   rodata_f5c49                             @ 0x000f5c49   [INLINED -- G6 literal batch]
 *   rodata_f5c59                             @ 0x000f5c59   [INLINED -- G6 literal batch]
 *   rodata_f5c6a                             @ 0x000f5c6a   [INLINED -- G6 literal batch]
 *   NRF_I2S0_CONFIG_CHANNELS                 @ 0x500055b8
 */
/* Reconstructed FUN_00060c00 @ 0x00060c00 (432-byte executable extent). */
#include <stdint.h>

extern void arch_irq_priority_set(uint32_t irq, int priority, int flags);
extern int qspi_get_zephyr_ret_code(int registration_result);
extern int qspi_nor_acquire(void *context);
extern void qspi_nor_suspend_bus(void *context);
extern int qspi_nor_send_cinstr(void *context, uint8_t *command, uint8_t mode);
#define g1_recon_nrfx_qspi_init nrfx_qspi_init
extern int g1_recon_nrfx_qspi_init(void *device, uintptr_t callback,
                                   void *callback_context);
extern void qspi_log_forward(uintptr_t source, uint32_t level, const void *record);
extern int qspi_pinctrl_apply_state(uintptr_t transport, void *result,
                        uintptr_t unused, void *owner);
extern int audio_apply_config_cmd_0xab(unsigned int);
extern int qspi_rdsr(void *context);
extern int memcmp(const void *expected, const void *actual, uint32_t length);

struct driver_context {
    uint32_t reserved0;
    uint8_t *configuration;
    uint32_t reserved8[2];
    void *callback_context;
};

/* The command helper receives &opcode.  Its two following words point to
 * optional {data,length} pairs; the pairs immediately preceding the command
 * are kept together here to preserve their real ownership and layout. */
struct command_frame {
    uint8_t response[4];
    uint8_t *payload;
    uint32_t payload_length;
    uint32_t opcode;
    uint8_t **cursor;
    uint8_t **cursor_owner;
};

struct log3 {
    uint32_t count;
    uintptr_t format;
    int32_t error;
};

struct transition_log {
    uint32_t descriptor;
    uintptr_t format;
    uintptr_t expected;
    int32_t error;
    uint16_t operation;
};

struct mismatch_log {
    uint32_t count;
    uintptr_t format;
    uint32_t actual[3];
    uint32_t expected[3];
};

static __attribute__((always_inline)) inline void
log_transition_error(int error, uint32_t expected_state)
{
    const struct transition_log record = {
        0x01000004u,
        ((unsigned long)"QE %s failed: %d") /*=0xf5c59*/,
        expected_state ? 0x000f3c77u : 0x000f5c43u,
        error,
        0x0200u,
    };
    qspi_log_forward(((unsigned long)&rodata_88270) /*=0x88270*/, 0x2440u, &record);
}

int qspi_nor_configure(struct driver_context *context)
{
    uint8_t *const configuration = context->configuration;

    /* The transport wrapper's third register is unused; the fourth carries
     * the owning configuration object in the shipped call sequence. */
    int result = qspi_pinctrl_apply_state(*(uintptr_t *)(configuration + 0x34),
                              0, 0, configuration);
    if (result < 0)
        return result;

    arch_irq_priority_set(0x2bu, 1, 0);
    *(volatile uint32_t *)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 0;
    int registration = g1_recon_nrfx_qspi_init(configuration, ((unsigned long)&rodata_838cb) /*=0x838cb*/,
                                               context->callback_context);
    *(volatile uint32_t *)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 2;

    result = qspi_get_zephyr_ret_code(registration);
    if (result < 0)
        return result;

    result = audio_apply_config_cmd_0xab(context);
    if (result < 0)
        return result;

    const uint32_t expected_state =
        (((uint32_t)configuration[0x1d] - 2u) < 2u ||
         ((uint32_t)configuration[0x1c] - 3u) < 2u);

    result = qspi_rdsr(context);
    if (result < 0) {
        const struct log3 record = {3, ((unsigned long)"RDSR failed: %d") /*=0xf5c49*/, result};
        qspi_log_forward(((unsigned long)&rodata_88270) /*=0x88270*/, 0x1840u, &record);
        return result;
    }

    struct command_frame frame;
    if (expected_state != (((uint32_t)result >> 6) & 1u)) {
        frame.response[0] = (uint8_t)result ^ 0x40u;
        frame.response[1] = 0;
        frame.payload = frame.response;
        frame.payload_length = 1;
        frame.opcode = 1;
        frame.cursor = &frame.payload;
        frame.cursor_owner = 0;

        result = qspi_nor_send_cinstr(context, (uint8_t *)&frame.opcode, 1);
        if (result != 0) {
            if (result >= 0)
                return result;
            log_transition_error(result, expected_state);
            return result;
        }

        do {
            result = qspi_rdsr(context);
            if (result < 0) {
                log_transition_error(result, expected_state);
                return result;
            }
        } while ((result & 1) != 0);
    }

    qspi_nor_suspend_bus(context);
    frame.payload = frame.response;
    frame.payload_length = 3;
    frame.opcode = 0x9f;
    frame.cursor = 0;
    frame.cursor_owner = &frame.payload;

    result = qspi_nor_acquire(context);
    if (result == 0) {
        result = qspi_nor_send_cinstr(context, (uint8_t *)&frame.opcode, 0);
        qspi_nor_suspend_bus(context);
        if (result == 0) {
            result = memcmp(configuration + 0x30, frame.response, 3);
            if (result == 0)
                return 0;

            const struct mismatch_log record = {
                8,
                ((unsigned long)"JEDEC id [%02x %02x %02x] expect [%02x %02x %02x]") /*=0xf5c6a*/,
                {frame.response[0], frame.response[1], frame.response[2]},
                {configuration[0x30], configuration[0x31], configuration[0x32]},
            };
            qspi_log_forward(((unsigned long)&rodata_88270) /*=0x88270*/, 0x4040u, &record);
        }
    } else {
        qspi_nor_suspend_bus(context);
    }
    return -0x13;
}
