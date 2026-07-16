/* Full reconstruction FUN_00058808 @ 0x58808, exact extent 166 bytes. */
#include <stdint.h>
#include <stdbool.h>

extern int FUN_00080d3e(uint32_t, uint32_t, void *, uint32_t);
extern int FUN_00082cba(uint32_t, void *, uint32_t);
extern uint32_t FUN_0005f304(uint32_t);
extern void *FUN_0005f5d0(uint32_t, uint32_t);
extern int32_t FUN_00081e2a(void *, void *, uint32_t, uint32_t, uintptr_t, void *);
extern uint32_t FUN_00081bc0(uint32_t);

struct request_58808 {
    void *owner;
    uint32_t value;
    uint32_t buffer;
    uint8_t *limit;
    uint16_t *payload;
    uint8_t status;
};

bool FUN_00058808(uint32_t *context, uint32_t value,
                  struct request_58808 *request, uint32_t arg3)
{
    uint8_t *owner = request->owner;
    uint32_t connection = *(uint32_t *)(owner + 8);
    int status = FUN_00080d3e(*context, request->value, request, arg3);

    if (status != 0)
        return true;

    status = FUN_00082cba(connection, context, 0x95);
    request->status = (uint8_t)status;
    if (status != 0) {
        if (*request->limit != 0)
            request->status = 0;
        return false;
    }

    request->payload = FUN_0005f5d0(FUN_0005f304(request->buffer) + 12, 2);
    *request->payload = (uint16_t)value;
    status = FUN_00081e2a(owner, context, request->buffer, 0,
                          0x00081bd1u, request);
    if (status < 0) {
        request->status = status < -255 ? 14 : (uint8_t)-status;
        return false;
    }
    if (request->payload != 0) {
        uint32_t used = FUN_00081bc0(request->buffer);
        uint32_t available = *(uint16_t *)(owner + 0x2e);
        uint32_t alternate = *(uint16_t *)(owner + 0x1e);
        if (alternate <= available)
            available = alternate;
        return *request->limit < available - used;
    }
    return false;
}
