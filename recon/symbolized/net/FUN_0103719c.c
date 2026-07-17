#include "g1_net_symbols.h"
/* net-core FUN_0103719c @ 0x103719c */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern void FUN_01036fcc(void *item);
extern void FUN_01037130(void *lock, unsigned int key);
extern void FUN_01039bb0(uintptr_t message, unsigned line);
extern void FUN_01039bbe(uintptr_t file, uintptr_t message, unsigned line);

void FUN_0103719c(uint8_t *item)
{
    void *lock = (void *)0x21004b68;

    if (!FUN_0103610c(lock)) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    }
    FUN_01036144(lock);
    if ((item[0x0d] & 4) != 0) {
        item[0x0d] &= (uint8_t)~4u;
        FUN_01036fcc(item);
        FUN_01037130(lock, 0);
        return;
    }
    if (!FUN_01036128(lock)) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
}
