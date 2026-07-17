#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037960 @ 0x01037960
 * public-name: FUN_01037960
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
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
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    }
    FUN_01036144(lock);
    item = *list;
    if (item == list)
        item = 0;
    else if (item != 0)
        FUN_01037814(item);

    if (!FUN_01036128(lock)) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
    return item;
}
