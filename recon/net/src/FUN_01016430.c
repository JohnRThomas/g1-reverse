/* net-core radio-operation setup @ 0x01016430.
 *
 * Raw provenance: the TBB at 0x0101645a dispatches modes 1..8.  Modes 1, 4,
 * and 8 share the dynamic-channel path, mode 2 selects channel 13, and every
 * other value reaches the noreturn controller fault at 0x0101649c.  That
 * fault call ends at 0x010164a6; 0x010164a6 is alignment and the words at
 * 0x010164a8/0x010164ac are the state/table literals.
 */
#include <stdint.h>

extern uint32_t FUN_0100a5b4(void);
extern __attribute__((noreturn)) void FUN_01008d00(uint32_t module,
                                                   uint32_t line);
extern void FUN_010202fc(uint32_t channel, uint32_t operation_mode);
extern void FUN_010204f4(uint32_t mapped_value);
extern void FUN_01020764(uintptr_t packet);
extern void FUN_01021108(uint32_t direction, uint32_t operation_mode);
extern int32_t FUN_010212ec(uint32_t direction, uint32_t operation_mode);

#define read_requested_channel          FUN_0100a5b4
#define controller_fault                FUN_01008d00
#define configure_radio_channel         FUN_010202fc
#define latch_mapped_radio_value        FUN_010204f4
#define arm_radio_packet                FUN_01020764
#define finish_radio_setup              FUN_01021108
#define finish_radio_setup_with_status  FUN_010212ec

#define CONTROLLER_STATE ((volatile uint8_t *)UINT32_C(0x21000f90))
#define RADIO_VALUE_MAP  ((const uint8_t *)UINT32_C(0x0103c24c))

uint32_t FUN_01016430(uint32_t return_finish_status, uintptr_t packet)
{
    uint8_t mapped_value;
    uint8_t operation_mode;
    uint32_t channel;

    mapped_value = RADIO_VALUE_MAP[CONTROLLER_STATE[0x7a]];
    latch_mapped_radio_value(mapped_value);
    CONTROLLER_STATE[0x8f] = mapped_value;

    operation_mode = CONTROLLER_STATE[0xbd + CONTROLLER_STATE[0x98]];
    switch (operation_mode) {
    case 1:
    case 4:
    case 8:
        channel = read_requested_channel();
        if (channel >= 0x40)
            channel = 0x40;
        channel = (uint8_t)channel;
        break;
    case 2:
        channel = 0x0d;
        break;
    default:
        controller_fault(0x32, 0x90f);
    }

    configure_radio_channel(channel, operation_mode);
    arm_radio_packet(packet);
    if (return_finish_status != 0)
        return finish_radio_setup_with_status(1, operation_mode) != 0;

    finish_radio_setup(1, operation_mode);
    return 1;
}
