/* net-core FUN_01036c2c @ 0x1036c2c */
#include <stdint.h>

extern void FUN_01039bbe(uintptr_t file, uintptr_t message, unsigned line);
extern void FUN_01039bb0(uintptr_t message, unsigned line);
extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern int FUN_01036b18(void *object, unsigned int *value);

int FUN_01036c2c(unsigned int value, void *object)
{
    void *lock = (void *)0x21004b58;
    int result;

    if (object == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103eaed, 0x174);
        FUN_01039bb0(0x0103eaed, 0x174);
    }
    if (!FUN_0103610c(lock)) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
    }
    FUN_01036144(lock);
    result = FUN_01036b18(object, &value);
    if (!FUN_01036128(lock)) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
    }
    return result;
}
