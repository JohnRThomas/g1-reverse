/* Reconstructed FUN_00052180 @ 0x52180. */
#include <stdint.h>

extern int FUN_00080872(int source, void *descriptor, unsigned int count,
                        uint32_t *auxiliary);
extern int FUN_00052038(uint32_t handle, void *scratch,
                        uint32_t option, uint32_t context);
extern int FUN_000809f6(uint32_t handle);
extern unsigned int FUN_000516ac(uint32_t handle);
extern void FUN_00051fe4(void);
extern void FUN_0005160c(int destination, unsigned int command,
                         unsigned int status);

struct parse_result {
    uint32_t handle;
    uint32_t auxiliary;
};

struct request_descriptor {
    uint32_t token;
    uint32_t token_length;
    uint32_t callback;
    struct parse_result *result;
    uint8_t flags;
};

uint32_t FUN_00052180(const uint8_t *request)
{
    int destination = *(const int *)(request + 8);
    struct parse_result result = {1, 0};
    uint8_t parse_scratch[8];
    struct request_descriptor descriptor = {
        0x000f272f, 4, 0x00085f8d, &result, 0
    };

    int status = FUN_00080872(*(const int *)(request + 4) + 4,
                              &descriptor, 1, &result.auxiliary);
    if (status != 0)
        return 3;

    status = FUN_00052038(result.handle, parse_scratch, 0, 0);
    unsigned int response;
    if (status == 0 && FUN_000809f6(result.handle) != 0) {
        response = 9;
    } else {
        response = FUN_000516ac(result.handle);
        FUN_00051fe4();
        if (response == 0)
            return 0;
        response &= 0xffffu;
    }

    FUN_0005160c(destination + 4, 1, response);
    return 0;
}
