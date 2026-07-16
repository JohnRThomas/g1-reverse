/* Full reconstruction of FUN_000571e8 @ 0x571e8 (owned code: 258 bytes). */
#include <stdint.h>

typedef struct {
    uint8_t reserved_00[0x0d];
    uint8_t state;
    uint8_t reserved_0e[0x2a];
    uint8_t queue[1];
} stream_owner_t;

typedef struct {
    uint8_t reserved_00[0x10];
    uint16_t length;
    uint8_t reserved_12[6];
    void *pending;
    uint8_t split;
    uint8_t tag;
} stream_fragment_t;

extern int FUN_000813b4(const void *object, int selector);
extern void FUN_00056300(stream_owner_t *owner);
extern void *FUN_0008652c(void *queue);
extern void FUN_0007e2fa(uintptr_t subsystem, uintptr_t file,
                         uintptr_t message, unsigned line);
extern stream_fragment_t *FUN_0005f2d4(void *object);
extern stream_fragment_t *FUN_000571dc(unsigned kind, int a, int b, int c);
extern int FUN_000560cc(stream_owner_t *owner, stream_fragment_t *source,
                        stream_fragment_t *destination, unsigned mode);
extern void FUN_0005f24c(void *object);
extern void FUN_00056080(stream_owner_t *owner, void *pending);

void FUN_000571e8(stream_owner_t *owner)
{
    stream_fragment_t *fragment;
    int result;
    uint8_t split;

    if (owner->state == 0 &&
        ((uint32_t)FUN_000813b4((uint8_t *)owner + 4, -65) & 0x40u) != 0) {
        FUN_00056300(owner);
        return;
    }

    void *queued = FUN_0008652c(owner->queue);
    if (queued == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f45beu, 0x000f3a5du, 0x397u);
        /* The following BASEPRI/SVC fatal path does not return in firmware. */
        return;
    }

    fragment = FUN_0005f2d4(queued);
    split = fragment->split;

    if (fragment->length <= *(volatile uint16_t *)0x20002104u && split == 0) {
        result = FUN_000560cc(owner, fragment, 0, 2);
    } else {
        for (;;) {
            if (fragment->length <= *(volatile uint16_t *)0x20002104u) {
                fragment->split = 1;
                result = FUN_000560cc(owner, fragment, 0, 3);
                break;
            }

            stream_fragment_t *part = FUN_000571dc(0, -1, -1, -1);
            if (owner->state != 7) {
                FUN_0005f24c(part);
                FUN_0005f24c(fragment);
                return;
            }

            part->pending = 0;
            part->split = 0;
            part->tag = fragment->tag;
            result = FUN_000560cc(owner, fragment, part, split);
            if (result != 0) {
                fragment->split = split & 1u;
                FUN_0005f24c(part);
                break;
            }
            split = 1;
        }
    }

    FUN_0005f24c(fragment);
    if (result == -5) {
        void *pending = fragment->pending;
        fragment->pending = 0;
        FUN_0005f24c(fragment);
        if (pending != 0)
            FUN_00056080(owner, pending);
    }
}
