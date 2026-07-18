/* Full reconstruction FUN_00054444 @ 0x00054444 (214-byte exact extent). */
#include <stdint.h>

extern void *FUN_00056908(uint32_t, uint32_t);
extern int FUN_00083370(void *, uint32_t, uint32_t, uint32_t, uint32_t, void *);
extern void *FUN_00053cd4(uint32_t, uint32_t);
extern void *FUN_0005f5d0(void *, uint32_t);
extern void FUN_000543d8(uint32_t, void *);
extern void FUN_000566a4(void *);
extern void FUN_00080ea2(uintptr_t, uint32_t, const void *);

struct log3 { uint32_t count, format, value; };

void FUN_00054444(const void *event)
{
    const uint8_t *p = *(const uint8_t * const *)((const uint8_t *)event + 12);
    uint16_t handle = *(const uint16_t *)p;
    uint32_t parameters[4];
    void *connection = FUN_00056908(handle, 1);
    if (!connection) {
        struct log3 r = {3, 0x000f2db7u, handle};
        FUN_00080ea2(0x00088138u, 0x1840u, &r);
        return;
    }
    uint32_t diversifier = *(const uint16_t *)(p + 10);
    int enhanced = FUN_00083370(connection, diversifier,
                                *(const uint32_t *)(p + 2), *(const uint32_t *)(p + 6),
                                diversifier, parameters);
    void *command;
    uint32_t opcode;
    if (enhanced) {
        opcode = 0x201au;
        command = FUN_00053cd4(opcode, 18);
        if (command) {
            uint8_t *dst = FUN_0005f5d0((uint8_t *)command + 12, 18);
            *(uint16_t *)dst = handle;
            ((uint32_t *)(dst + 2))[0] = parameters[0];
            ((uint32_t *)(dst + 2))[1] = parameters[1];
            ((uint32_t *)(dst + 2))[2] = parameters[2];
            ((uint32_t *)(dst + 2))[3] = parameters[3];
        }
    } else {
        opcode = 0x201bu;
        command = FUN_00053cd4(opcode, 2);
        if (command) *(uint16_t *)FUN_0005f5d0((uint8_t *)command + 12, 2) = handle;
    }
    if (!command) {
        const uint32_t r[2] = {2, 0x000f3125u};
        FUN_00080ea2(0x00088138u, 0x1040u, r);
    } else {
        FUN_000543d8(opcode, command);
    }
    FUN_000566a4(connection);
}
