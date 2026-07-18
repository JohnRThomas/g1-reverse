/* CPUNET packed controller packet iterator @ 0x01009224.
 * Raw back-map: FUN_01009224@0x01009224; true executable extent 0xbc. */
#include <stdint.h>

extern unsigned controller_packet_build_next(void *cursor);
extern unsigned FUN_01025fd4(unsigned type, unsigned subtype);
extern void FUN_0102602e(void *packet, void *cursor);
extern void FUN_0102609e(void *packet, void *cursor);
extern unsigned FUN_01026122(void *packet, void *cursor);
extern unsigned FUN_010267fe(void *local_packet, void *local_metadata);
extern unsigned thunk_FUN_010294a2(void *local_metadata, void *local_packet);
extern void sdc_assertion_fail(unsigned module, unsigned line)
    __attribute__((noreturn));

unsigned FUN_01009224(uint8_t *packet, uint32_t metadata)
{
    volatile uint8_t *const cursor = (volatile uint8_t *)0x21000a6cu;
    uint32_t local_packet = (uint32_t)(uintptr_t)packet;
    uint32_t local_metadata = metadata;

    *(volatile uint32_t *)cursor = (uint32_t)(uintptr_t)(packet + 4);

    for (;;) {
        unsigned result = controller_packet_build_next((void *)cursor);

        if (result == 2) {
            FUN_0102602e(packet, (void *)cursor);
            return 2;
        }
        if (result != 4) {
            if (result == 8)
                FUN_0102609e(packet, (void *)cursor);
            return result;
        }

        if (cursor[0] == 9) {
            if (FUN_01025fd4(0x3e, 5) == 0) {
                *(uint16_t *)&local_packet =
                    (uint16_t)cursor[3] | ((uint16_t)cursor[4] << 8);
                if (FUN_010267fe(&local_packet, &local_metadata) != 0)
                    sdc_assertion_fail(8, 0x53);
                continue;
            }
        } else if (cursor[0] == 0x25) {
            if (FUN_01025fd4(0x3e, 0x1a) == 0) {
                *(uint16_t *)&local_metadata =
                    (uint16_t)((*(volatile uint32_t *)(cursor + 4) >> 8) &
                               0xffffu);
                *((uint8_t *)&local_metadata + 2) = 0x11;
                if (thunk_FUN_010294a2(&local_metadata, &local_packet) != 0)
                    sdc_assertion_fail(8, 0x65);
                continue;
            }
        }

        unsigned encoded_size = FUN_01026122(packet, (void *)cursor);
        if (encoded_size > 0x101)
            sdc_assertion_fail(8, 0x72);
        if (encoded_size != 0 && FUN_01025fd4(packet[0], packet[2]) != 0)
            return 4;
    }
}
