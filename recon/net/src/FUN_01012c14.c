/* net-core FUN_01012c14 @ 0x01012c14 */
#include <stdint.h>

/* Raw/address backmaps retain the private-controller identities. */
extern int FUN_010126e8(const void *controller);
extern int FUN_010126b0(const void *controller);
extern int FUN_010126b8(const void *controller);
extern void FUN_01021908(int8_t *state);
extern void FUN_01021914(uint8_t *state);
extern int FUN_01025d28(void);
extern int FUN_01025be0(void);

uint16_t FUN_01012c14(const void *controller)
{
    int8_t signed_state;
    uint8_t unsigned_state;
    uint16_t selected;
    uint16_t alternate;

    if (FUN_010126e8(controller) == 0) {
        return 0x8bu;
    }
    if (FUN_010126b0(controller) != 0 || FUN_010126b8(controller) != 0) {
        selected = 0x7fu;
        alternate = 0x89u;
    } else {
        selected = 0x75u;
        alternate = 0x7fu;
    }

    FUN_01021908(&signed_state);
    FUN_01021914(&unsigned_state);
    if ((int8_t)((uint8_t)signed_state | unsigned_state) != 0) {
        selected = alternate;
    }
    if (FUN_01025d28() != 0) {
        return (uint16_t)(selected + 0x18u);
    }
    if (FUN_01025be0() != 0) {
        selected = (uint16_t)(selected + 0x0fu);
    }
    return selected;
}
