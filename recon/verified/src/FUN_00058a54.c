/* Full reconstruction FUN_00058a54 @ 0x58a54, exact extent 254 bytes.
 * The following 38 bytes are its literal pool, not executable ownership. */
#include <stdint.h>
#include <stdatomic.h>

extern int FUN_00083496(uint32_t);
extern void FUN_00081ddc(uintptr_t, uint32_t, const void *);
extern void FUN_0005833c(void *);
extern void FUN_0005f24c(void *);
extern uint32_t FUN_00083728(void *);
extern uint32_t FUN_000582b8(uint8_t);
extern int FUN_00081820(uint32_t, uint32_t, void *, uint32_t, void *);
extern void FUN_0007e2fa(uintptr_t, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

struct packet_58a54 {
    uint8_t pad00[12];
    uint8_t *cursor;
    uint16_t length;
    uint8_t pad12[2];
    uint32_t base;
    uint32_t *owner_slot;
};

static void log_58a54(uintptr_t message)
{
    struct { uint32_t count; uintptr_t message; } record = { 2, message };
    FUN_00081ddc(0x00088100u, 0x1040, &record);
}

int FUN_00058a54(uint32_t **context, struct packet_58a54 *packet)
{
    uint32_t *slot = packet->owner_slot;
    uint32_t saved_owner = *slot;
    int result;

    if ((atomic_load_explicit((_Atomic uint32_t *)((uint8_t *)context + 0x120),
                              memory_order_acquire) & 4) == 0) {
        log_58a54(0x000f445bu);
        return -22;
    }
    if (*packet->cursor == 0xd2 &&
        (result = FUN_00083496(**context)) != 0) {
        log_58a54(0x000f452bu);
        FUN_0005833c(packet->owner_slot);
        FUN_0005f24c(packet);
        return result;
    }

    uint32_t consumed = FUN_00083728(&packet->cursor);
    uint16_t saved_length = packet->length;
    *slot = (uint32_t)(uintptr_t)context;
    uint32_t connection = **context;
    uint32_t opcode = FUN_000582b8(*packet->cursor);
    if (opcode > 5) {
        FUN_0007e2fa(0x00099cbdu, 0x000f7a30u, 0x000f4388u, 0x28b);
        FUN_0007e2fa(0x000f453eu, opcode);
        FUN_0007e2ec(0x000f4388u, 0x28b);
    }
    result = FUN_00081820(connection, 4, packet,
                          ((const uint32_t *)0x0008b29cu)[opcode], slot);
    if (result != 0) {
        if (result == -105)
            log_58a54(0x000f4557u);
        packet->length = saved_length;
        packet->cursor = (uint8_t *)(uintptr_t)(packet->base + (uint16_t)consumed);
        *slot = saved_owner;
    }
    return result;
}
