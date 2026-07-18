/* net-core FUN_0102ab14 @ 0x0102ab14 (CFG-directed PASS) */
#include <stddef.h>
#include <stdint.h>

typedef void (*ipc0_handler_fn)(void *owner, const uint8_t *payload,
                                size_t payload_size);

struct ipc0_handler {
    uint8_t message_id;
    uint8_t reserved[7];
    ipc0_handler_fn receive;
};

void FUN_0102ab14(const uint8_t *data, size_t size, void *priv)
{
    (void)priv;

    uint8_t *registry = *(uint8_t *volatile *)UINT32_C(0x21004604);
    const uint8_t message_id = data[0];
    const uint32_t *cursor = (const uint32_t *)(registry + 4);

    for (int32_t index = 0; (int32_t)cursor[0] > index; ++index) {
        const struct ipc0_handler *handler =
            (const struct ipc0_handler *)(uintptr_t)cursor[1];
        cursor += 2;
        if (handler != NULL && handler->message_id == message_id) {
            handler->receive(registry - 0x48, data + 1, size - 1);
            return;
        }
    }
}
