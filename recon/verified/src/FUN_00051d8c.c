/* Reconstructed FUN_00051d8c @ 0x51d8c. */
#include <stdint.h>

extern void FUN_0004d944(uint32_t channel, uint32_t flags,
                         const void *record, int context);
extern int FUN_0004e048(unsigned int selector, uint32_t *handle);
extern unsigned int FUN_0005169c(unsigned int request);
extern unsigned int FUN_00051c68(void);
extern int FUN_000641e4(uint32_t handle, unsigned int is_selected, int mode);
extern void FUN_0007ef7e(uint32_t handle);
extern unsigned int FUN_000809b0(int group, uint8_t *state);
extern unsigned int FUN_00080a46(int group);
extern int FUN_00080a4a(void);

struct failure_record {
    uint32_t count;
    uint32_t format;
    int error;
    uint32_t requested;
    uint32_t selected;
    int mode;
};

int FUN_00051d8c(unsigned int request, int mode)
{
    unsigned int selected = request;
    if (request > 3u)
        selected = FUN_00051c68();

    int group = (int)selected >> 1;
    unsigned int primary = FUN_00080a46(group);
    uint8_t state = 0;
    unsigned int secondary = FUN_000809b0(group, &state);

    if (mode == 0) {
        if (primary == request)
            return 0x21;
        if (state == 1)
            return secondary == request ? 0 : 0x1c;
        if ((state == 0 && secondary == request) || state == 2)
            return 0x1c;
    } else {
        if (FUN_00080a4a() == group) {
            if (state == 1)
                return 0x1c;
            if (state == 0) {
                if (secondary == request)
                    return 0;
                if (primary == request)
                    return 0x1c;
            } else if (state == 2 && secondary == request) {
                return 0;
            }
        } else {
            if (primary == request)
                return 0x20;
            if (state == 1)
                return 0x1c;
            if ((state == 0 || state == 2) && secondary == request)
                return 0;
        }
    }

    uint32_t handle;
    unsigned int selector = FUN_0005169c(request) & 0xffu;
    if (FUN_0004e048(selector, &handle) != 0)
        return 10;

    int status = FUN_000641e4(handle, primary == request, mode);
    if (status != 0) {
        struct failure_record failure = {
            6, 0x000f2772, status, request, primary, mode
        };
        FUN_0004d944(0x00088208, 0x3040, &failure, 0);
        if (status == 1)
            status = 0x0c;
        else if (status == 4)
            status = 0x1d;
        else if (status == 3)
            status = 0x17;
        else
            status = 1;
    }
    FUN_0007ef7e(handle);
    return status;
}
