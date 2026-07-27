/* Reconstructed FUN_00060c00 @ 0x00060c00 (432-byte executable extent). */
#include <stdint.h>

extern void FUN_0005010c(uint32_t irq, int priority, int flags);
extern int FUN_00060990(int registration_result);
extern int FUN_00060a10(void *context);
extern void FUN_00060a5c(void *context);
extern int FUN_00060ab0(void *context, uint8_t *command, uint8_t mode);
#define g1_recon_nrfx_qspi_init FUN_00066994
extern int g1_recon_nrfx_qspi_init(void *device, uintptr_t callback,
                                   void *callback_context);
extern void FUN_000838d6(uintptr_t source, uint32_t level, const void *record);
extern int FUN_000838dc(uintptr_t transport, void *result,
                        uintptr_t unused, void *owner);
extern int FUN_0008397e(unsigned int);
extern int FUN_000839a6(void *context);
extern int FUN_00086be4(const void *expected, const void *actual, uint32_t length);

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
        0x000f5c59u,
        expected_state ? 0x000f3c77u : 0x000f5c43u,
        error,
        0x0200u,
    };
    FUN_000838d6(0x00088270u, 0x2440u, &record);
}

int FUN_00060c00(struct driver_context *context)
{
    uint8_t *const configuration = context->configuration;

    /* The transport wrapper's third register is unused; the fourth carries
     * the owning configuration object in the shipped call sequence. */
    int result = FUN_000838dc(*(uintptr_t *)(configuration + 0x34),
                              0, 0, configuration);
    if (result < 0)
        return result;

    FUN_0005010c(0x2bu, 1, 0);
    *(volatile uint32_t *)0x500055b8u = 0;
    int registration = g1_recon_nrfx_qspi_init(configuration, 0x000838cbu,
                                               context->callback_context);
    *(volatile uint32_t *)0x500055b8u = 2;

    result = FUN_00060990(registration);
    if (result < 0)
        return result;

    result = FUN_0008397e(context);
    if (result < 0)
        return result;

    const uint32_t expected_state =
        (((uint32_t)configuration[0x1d] - 2u) < 2u ||
         ((uint32_t)configuration[0x1c] - 3u) < 2u);

    result = FUN_000839a6(context);
    if (result < 0) {
        const struct log3 record = {3, 0x000f5c49u, result};
        FUN_000838d6(0x00088270u, 0x1840u, &record);
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

        result = FUN_00060ab0(context, (uint8_t *)&frame.opcode, 1);
        if (result != 0) {
            if (result >= 0)
                return result;
            log_transition_error(result, expected_state);
            return result;
        }

        do {
            result = FUN_000839a6(context);
            if (result < 0) {
                log_transition_error(result, expected_state);
                return result;
            }
        } while ((result & 1) != 0);
    }

    FUN_00060a5c(context);
    frame.payload = frame.response;
    frame.payload_length = 3;
    frame.opcode = 0x9f;
    frame.cursor = 0;
    frame.cursor_owner = &frame.payload;

    result = FUN_00060a10(context);
    if (result == 0) {
        result = FUN_00060ab0(context, (uint8_t *)&frame.opcode, 0);
        FUN_00060a5c(context);
        if (result == 0) {
            result = FUN_00086be4(configuration + 0x30, frame.response, 3);
            if (result == 0)
                return 0;

            const struct mismatch_log record = {
                8,
                0x000f5c6au,
                {frame.response[0], frame.response[1], frame.response[2]},
                {configuration[0x30], configuration[0x31], configuration[0x32]},
            };
            FUN_000838d6(0x00088270u, 0x4040u, &record);
        }
    } else {
        FUN_00060a5c(context);
    }
    return -0x13;
}
