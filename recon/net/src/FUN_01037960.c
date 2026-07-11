/* net-core FUN_01037960 @ 0x1037960 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01037814(void *item);
extern void FUN_01039bb0(uintptr_t message, unsigned line);
extern void FUN_01039bbe(uintptr_t file, uintptr_t message, unsigned line);

void *FUN_01037960(void **list)
{
    void *lock = (void *)0x21004b68;
    void *item;

    if (!FUN_0103610c(lock)) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
    }
    FUN_01036144(lock);
    item = *list;
    if (item == list)
        item = 0;
    else if (item != 0)
        FUN_01037814(item);

    if (!FUN_01036128(lock)) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
    }
    return item;
}
