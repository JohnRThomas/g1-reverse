/* Reconstructed display_powerEvent @ 0x49a28. */

#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000720d0(void *owner, const void *packet,
                        int option_a, int option_b);
extern void FUN_00086c78(void *destination, int value,
                         unsigned int length);

int display_powerEvent(int powered_on)
{
    uint8_t packet[24];
    int result;

    FUN_00086c78(packet, 0, sizeof(packet));
    packet[0] = powered_on == 1 ? 7 : 8;

    result = FUN_000720d0((void *)0x200038c4UL, packet, 0, 0);
    if (result != 0) {
        DEBUG_PRINT(0x000ef058UL, 0x000f0126UL);
        return -1;
    }

    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000f00eaUL, 0x000f0126UL, powered_on);
        } else {
            FUN_00019c70(0x000f00eaUL, 0x000f0126UL, powered_on);
        }
    }
    return 0;
}
