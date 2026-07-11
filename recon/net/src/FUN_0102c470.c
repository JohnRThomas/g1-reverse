/* net-core FUN_0102c470 @ 0x102c470 */
#include <stdint.h>

extern int FUN_010397ac(void *arena, int object, int mode);
extern int FUN_0103973c(void *arena, int offset, int mode);
extern int FUN_01039768(void *arena, int offset);
extern void *FUN_01039774(void *arena, int offset);
extern void FUN_010399f6(void *object, int offset);
extern void FUN_01039bbe(const void *module, const void *file, unsigned line);
extern void FUN_01039bb0(const void *file, unsigned line);

void FUN_0102c470(void **arena_slot, int object)
{
    void *arena;
    int offset;
    int span;
    int adjustment;

    if (object == 0)
        return;

    arena = *arena_slot;
    offset = FUN_010397ac(arena, object, 1);
    if ((FUN_0103973c(arena, offset, 1) & 1) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d373u, 0xaf);
        FUN_01039bb0((const void *)0x0103d373u, 0xaf);
        return;
    }

    span = offset + FUN_01039768(arena, offset);
    adjustment = FUN_0103973c(arena, span, 0);
    if (span - adjustment != offset) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d373u, 0xb7);
        FUN_01039bb0((const void *)0x0103d373u, 0xb7);
        return;
    }

    FUN_010399f6(FUN_01039774(arena, offset), offset);
}
