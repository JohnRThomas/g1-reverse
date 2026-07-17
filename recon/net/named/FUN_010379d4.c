/* readable reconstruction; identity: FUN_010379d4 @ 0x010379d4
 * public-name: FUN_010379d4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_010379d4 @ 0x10379d4 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01037814(void *item);
extern int FUN_010380d8(void *timer);
extern void FUN_01039bbe(const void *module, const void *file, unsigned line);
extern void FUN_01039bb0(const void *file, unsigned line);

void *FUN_010379d4(void **list_head)
{
    /* Original body is enclosed by a BASEPRI=0x40 critical section; final
     * Zephyr wiring wraps this operation with arch_irq_lock/unlock. */
    void *const lock = (void *)0x21004b68u;
    void *item;

    if (FUN_0103610c(lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0x72);
        FUN_01039bb0((const void *)0x0103d3b6u, 0x72);
        return 0;
    }

    FUN_01036144(lock);
    item = *list_head;
    if (item == list_head) {
        item = 0;
    } else if (item != 0) {
        FUN_01037814(item);
        FUN_010380d8((uint8_t *)item + 0x18);
    }

    if (FUN_01036128(lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0xf0);
        FUN_01039bb0((const void *)0x0103d3b6u, 0xf0);
    }
    return item;
}
