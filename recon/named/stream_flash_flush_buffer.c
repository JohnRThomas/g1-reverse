/* readable reconstruction; identity: FUN_0004e1ac @ 0x0004e1ac
 * public-name: stream_flash_flush_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   stream_flash_flush_buffer                <= FUN_0004e1ac @ 0x0004e1ac
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_880d8                             @ 0x000880d8
 *   rodata_f1052                             @ 0x000f1052
 *   rodata_f1080                             @ 0x000f1080
 *   rodata_f10a4                             @ 0x000f10a4
 *   rodata_f10ba                             @ 0x000f10ba
 */
/* Reconstructed FUN_0004e1ac @ 0x4e1ac  owned extent: 0xf4 bytes */

#include <stdint.h>

struct buffered_writer {
    uint8_t *buffer;
    uint32_t capacity;
    uint32_t count;
    void *device;
    uint32_t committed;
    uint32_t base;
    uint32_t limit;
    int (*transform)(uint8_t *buffer, uint32_t count, uint32_t offset);
};

struct writer_ops {
    int (*reset)(void *device, uint32_t offset);
    int (*write)(void *device, uint32_t offset, const uint8_t *buffer,
                 uint32_t length);
    uint32_t reserved;
    const uint8_t *(*fill_value)(void *device);
};

struct writer_device {
    uint32_t reserved[2];
    const struct writer_ops *ops;
};

struct diagnostic_record {
    uint32_t severity;
    uintptr_t message;
    int status;
    uint32_t context;
};

extern int FUN_0004e124(struct buffered_writer *writer, uint32_t last_offset);
extern uint32_t FUN_0007f064(void *device);
extern void memset_bytes(void *destination, uint8_t value, uint32_t length);
extern void FUN_0004d944(uintptr_t source, uint32_t event,
                         const struct diagnostic_record *record,
                         uint32_t reserved);

int stream_flash_flush_buffer(struct buffered_writer *writer, uint32_t unused_2,
                 uint32_t unused_3, uint32_t unused_4)
{
    uint32_t offset;
    uint32_t padding = 0;
    uintptr_t message = 0x000f1052u;
    int status;

    (void)unused_2;
    (void)unused_3;
    (void)unused_4;

    if (writer->count == 0)
        return 0;

    offset = writer->base + writer->committed;
    status = FUN_0004e124(writer, offset + writer->count - 1u);
    if (status >= 0) {
        uint32_t unit = FUN_0007f064(writer->device);
        uint32_t remainder = writer->count % unit;

        if (remainder != 0) {
            const struct writer_device *device = writer->device;
            const uint8_t *fill = device->ops->fill_value(writer->device);

            padding = unit - remainder;
            memset_bytes(writer->buffer + writer->count, fill[4], padding);
        }

        {
            const struct writer_device *device = writer->device;
            status = device->ops->write(writer->device, offset,
                                        writer->buffer,
                                        writer->count + padding);
        }
        message = 0x000f1080u;
        if (status == 0) {
            if (writer->transform == 0)
                goto complete;

            for (uint32_t i = 0; i < writer->count; ++i)
                writer->buffer[i] = (uint8_t)~writer->buffer[i];

            {
                const struct writer_device *device = writer->device;
                status = device->ops->reset(writer->device, offset);
            }
            message = 0x000f10a4u;
            if (status == 0) {
                status = writer->transform(writer->buffer, writer->count,
                                           offset);
                message = 0x000f10bau;
                if (status == 0)
                    goto complete;
            }

            {
                struct diagnostic_record diagnostic = {
                    .severity = 3,
                    .message = message,
                    .status = status,
                    .context = 0,
                };
                FUN_0004d944(0x000880d8u, 0x1840u, &diagnostic, 0);
            }
            return status;
        }
    }

    {
        struct diagnostic_record diagnostic = {
            .severity = 4,
            .message = message,
            .status = status,
            .context = offset,
        };
        FUN_0004d944(0x000880d8u, 0x2040u, &diagnostic, 0);
    }
    return status;

complete:
    writer->committed += writer->count;
    writer->count = 0;
    return 0;
}
