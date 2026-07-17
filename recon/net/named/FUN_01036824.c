/* readable reconstruction; identity: FUN_01036824 @ 0x01036824
 * public-name: FUN_01036824
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01036824 @ 0x1036824 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern void FUN_0103705c(void *item);
extern void FUN_01037130(void *lock, unsigned int key);
extern void *FUN_010379d4(void *queue);
extern void FUN_01039bb0(uintptr_t message, unsigned line);
extern void assert_print(uintptr_t file, uintptr_t message, unsigned line);
extern void FUN_0103b4f6(void *object, int event);

void FUN_01036824(uint8_t *queue)
{
    void *lock = (void *)0x21004b4c;
    uint8_t *item;
    uint32_t next;

    if (!FUN_0103610c(lock)) {
        assert_print(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
    }
    FUN_01036144(lock);
    item = FUN_010379d4(queue);
    if (item != 0) {
        *(uint32_t *)(item + 0x90) = 0;
        FUN_0103705c(item);
    } else {
        next = *(uint32_t *)(queue + 8);
        if (*(uint32_t *)(queue + 0x0c) != next)
            ++next;
        *(uint32_t *)(queue + 8) = next;
        FUN_0103b4f6(queue + 0x10, 2);
    }
    FUN_01037130(lock, 0);
}
