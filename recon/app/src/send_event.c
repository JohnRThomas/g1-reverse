/* Reconstructed send_event @ 0x276ec. */

#include <stdint.h>

extern int FUN_00017eec(const void *event, unsigned int length);
extern void *FUN_000181fc(void);
extern void FUN_0007cb4c(void *work);
extern void FUN_0007cb8e(int enabled);

void send_event(int event_id, unsigned int unused_2, unsigned int unused_3)
{
    uint8_t *pending_event = (uint8_t *)0x2000302eUL;
    uint8_t event[3];
    uint8_t *state = FUN_000181fc();

    (void)unused_2;
    (void)unused_3;

    if ((unsigned int)(event_id - 0xf0) <= 2 && *pending_event != 0xff) {
        return;
    }

    *pending_event = (uint8_t)event_id;
    if (state[0x248] != 0 || *(uint32_t *)(state + 0x220) != 0) {
        event[0] = 0xf5;
        event[1] = (uint8_t)event_id;
        event[2] = 0xcb;
        FUN_00017eec(event, sizeof(event));
        *pending_event = 0xff;
        return;
    }

    if (state[0x248] == 0) {
        FUN_0007cb4c(state + 0x218);
        FUN_0007cb8e(1);
    }
}
