/* Full reconstruction FUN_00053658 @ 0x00053658 (88-byte exact extent). */
#include <stdint.h>

extern void FUN_00053580(uint32_t event);
extern void FUN_00080ea2(uintptr_t module, uint32_t level, const void *record);

struct log_record4 { uint32_t count, format, available, event; };

void FUN_00053658(uint32_t event, void *buffer,
                  const uint8_t *handlers, uint32_t handler_count)
{
    const uint8_t *end = handlers + handler_count * 8u;

    while (handlers != end) {
        if (handlers[0] == event) {
            uint32_t available = *(const uint16_t *)((const uint8_t *)buffer + 0x10);
            if (available < handlers[1]) {
                struct log_record4 record = {4, 0x000f2e62u, available, event};
                FUN_00080ea2(0x00088138u, 0x2040u, &record);
            } else {
                ((void (*)(void *))*(const uintptr_t *)(handlers + 4))(buffer);
            }
            return;
        }
        handlers += 8;
    }
    FUN_00053580(event);
}
