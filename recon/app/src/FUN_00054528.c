/* Reconstructed FUN_00054528 @ 0x54528 */
#include <stdint.h>

extern int FUN_00053cd4(int pool, int size);
extern void FUN_000543d8(int queue, int packet);
extern void FUN_000566a4(int connection);
extern int FUN_00056908(unsigned int identifier, int selector);
extern int FUN_00056c78(int connection, const void *fields);
extern uint16_t *FUN_0005f5d0(int packet_data, int size);
extern void FUN_00080ea2(int source, int level, const void *record);
extern void FUN_00080f56(unsigned int identifier, int status);

struct diagnostic_record {
    unsigned int severity;
    unsigned int message;
    unsigned int identifier;
};

void FUN_00054528(int event)
{
    const uint8_t *source = *(const uint8_t **)(event + 0x0c);
    uint16_t identifier = *(const volatile uint16_t *)source;
    uint16_t fields[4];
    int connection;

    fields[0] = (uint16_t)(source[2] | (source[3] << 8));
    fields[1] = (uint16_t)(source[4] | (source[5] << 8));
    fields[2] = (uint16_t)(source[6] | (source[7] << 8));
    fields[3] = (uint16_t)(source[8] | (source[9] << 8));

    connection = FUN_00056908(identifier, 1);
    if (connection == 0) {
        struct diagnostic_record diagnostic = {
            3, 0x000f2db7, identifier
        };

        FUN_00080ea2(0x00088138, 0x1840, &diagnostic);
        FUN_00080f56(identifier, 2);
        return;
    }

    if (FUN_00056c78(connection, fields) == 0) {
        FUN_00080f56(identifier, 0x1e);
    } else {
        int packet = FUN_00053cd4(0x2020, 0x0e);

        if (packet != 0) {
            volatile uint16_t *output = FUN_0005f5d0(packet + 0x0c, 0x0e);

            output[0] = identifier;
            *(volatile uint32_t *)((volatile uint8_t *)output + 0x0a) = 0;
            output[1] = fields[0];
            output[2] = fields[1];
            output[3] = fields[2];
            output[4] = fields[3];
            FUN_000543d8(0x2020, packet);
        }
    }

    FUN_000566a4(connection);
}
