/* Reconstructed FUN_00055734 @ 0x55734. */
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

extern void FUN_0004d944(u32 sink, u32 code, const void *record, u32 context);
extern int FUN_00053cd4(u32 key, u32 size);
extern int FUN_00053d70(u32 key, int object, u32 flags);
extern int FUN_00055454(u8 *output, u32 flags, int mode, u8 *details);
extern int FUN_00055614(u8 *resource, u8 *preserved_resource,
                        u32 preserved_argument, u32 zero);
extern unsigned int FUN_000556b0(unsigned char*, int*);
extern void FUN_000566a4(int allocation);
extern void FUN_00056704(int allocation, int reason);
extern int FUN_00081130(int);
extern u32 FUN_0008115c(u32 value, u32 mask);
extern uint64_t FUN_0008117a(const void *object);
extern void FUN_00081180(const void *object);
extern void FUN_00081196(unsigned int *, unsigned int *);
extern void FUN_000811a4(u8 *object, u32 field, u32 value);
extern int FUN_000811ce(u8 *output, u32 argument3, u32 argument4,
                        int argument5, u32 argument6, int state, int kind);
extern int FUN_000812b2(u8 *resource);
extern int FUN_000812d2(void *, unsigned int);
extern void FUN_00083740(void *destination, const void *source, u32 size);

struct __attribute__((packed)) operation_record {
    u16 resource_field8;
    u16 resource_field12;
    u8 mode;
    u8 details[8];
    u8 filtered_flags;
    u8 reserved;
};

struct error_record {
    u32 severity;
    u32 message;
};

int FUN_00055734(u8 *output, int object, u32 argument3, u32 argument4,
                  int argument5, u32 argument6)
{
    int allocation = 0;
    int configured = *(volatile int *)(object + 0x10);
    int initial_mode = configured != 0;

    uint64_t lookup = FUN_0008117a((const void *)0x200020d4);
    u32 lookup_status = (u32)lookup;
    u8 *resource = (u8 *)(uintptr_t)(lookup >> 32);
    if ((lookup_status & 4u) == 0)
        return -11;

    if (FUN_00055614(resource, resource, argument3, 0) == 0)
        return -22;
    int state = FUN_00081130(resource);
    if (state == 0)
        return -22;

    u8 *fields = output + 0x10;
    u32 field_status = (u32)FUN_0008117a(fields);
    if ((field_status & 0x80u) != 0)
        return -120;

    struct operation_record record;
    record.resource_field8 = *(volatile u16 *)(resource + 8);
    record.resource_field12 = *(volatile u16 *)(resource + 0x0c);
    record.mode = 0;
    record.details[0] = 0;
    record.details[1] = 0;
    record.details[2] = 0;
    record.details[3] = 0;
    record.details[4] = 0;
    record.details[5] = 0;
    record.details[6] = 0;
    record.details[7] = 0;
    record.filtered_flags = 0;
    record.reserved = 0;
    u32 resource_flags = *(volatile u32 *)(resource + 4);
    record.filtered_flags = (u8)FUN_0008115c(resource_flags, 0xffffdfffu);
    FUN_00081180((const void *)0x200020d4);

    u8 resource_id = *(volatile u8 *)resource;
    *output = resource_id;
    *(volatile u8 *)0x2000206f = resource_id;

    int result = FUN_00055454(output, resource_flags, initial_mode,
                              record.details);
    if (result != 0)
        return result;

    int kind;
    if (configured == 0) {
        FUN_00081196(output + 9, 0x000f2b3a);
        kind = FUN_000812b2(resource);
        resource_flags = *(volatile u32 *)(resource + 4);
        if ((resource_flags & 1u) != 0) {
            record.mode = 0;
        } else if ((resource_flags & 0x200u) != 0 || argument5 != 0 ||
                   kind == 2) {
            record.mode = 2;
        } else {
            record.mode = 3;
            state = argument5;
        }
    } else {
        FUN_00081196(output + 9, *(volatile u32 *)(resource + 0x10));
        kind = FUN_000812b2(resource);
        resource_flags = *(volatile u32 *)(resource + 4);
        if ((resource_flags & 1u) != 0) {
            record.mode = (resource_flags & 0x10u) == 0 ? 1 : 4;
            FUN_00081196(&record.details[1],
                         *(volatile u32 *)(resource + 0x10));
            state = 0;
        } else if ((resource_flags & 0x200u) != 0 || argument5 != 0 ||
                   kind == 2) {
            record.mode = 2;
        } else {
            record.mode = 3;
            state = argument5;
        }
    }

    int object15 = FUN_00053cd4(0x2006, 15);
    if (object15 == 0)
        return -105;
    FUN_00083740((void *)(uintptr_t)(object15 + 0x0c), &record, 15);
    result = FUN_00053d70(0x2006, object15, 0);
    if (result != 0)
        return result;

    if (configured == 0) {
        result = FUN_000811ce(output, argument3, argument4, argument5,
                              argument6, state, kind);
        if (result != 0)
            return result;
    }

    resource_flags = *(volatile u32 *)(resource + 4);
    if ((resource_flags & 1u) != 0) {
        result = FUN_000556b0(output, &allocation);
        if (result != 0) {
            if (result != -12 || configured != 0 ||
                (resource_flags & 2u) != 0)
                return result;
            goto publish_fields;
        }
    }

    result = FUN_000812d2(output, 1);
    if (result != 0) {
        const struct error_record error = {2, 0x000f381d};
        FUN_0004d944(0x000880f8, 0x1040, &error, 0);
        if (allocation != 0) {
            FUN_00056704(allocation, 0);
            FUN_000566a4(allocation);
        }
        return result;
    }
    if (allocation != 0)
        FUN_000566a4(allocation);

publish_fields:
    resource_flags = *(volatile u32 *)(resource + 4);
    u32 alternate = configured != 0 ? 0 : ((resource_flags ^ 2u) >> 1) & 1u;
    FUN_000811a4(fields, 14, alternate);
    FUN_000811a4(fields, 8, kind == 1);
    FUN_000811a4(fields, 9, kind == 2);
    FUN_000811a4(fields, 10, resource_flags & 1u);
    FUN_000811a4(fields, 11, (u32)state);
    FUN_000811a4(fields, 13, (resource_flags >> 2) & 1u);
    return 0;
}
