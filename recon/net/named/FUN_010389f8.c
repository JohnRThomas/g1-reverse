/* readable reconstruction; identity: FUN_010389f8 @ 0x010389f8
 * public-name: FUN_010389f8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010389f8 @ 0x10389f8 */
#include <stdint.h>

extern int FUN_0103b14a(void);
extern void *FUN_01038958(void *heap, uint32_t alignment, uint32_t size);

void *FUN_010389f8(uint32_t alignment, uint32_t size)
{
    void *heap;

    if (FUN_0103b14a() != 0) {
        heap = (void *)0x210008b4u;
    } else {
        volatile uintptr_t *runtime = (volatile uintptr_t *)0x21004b28u;
        uintptr_t context = *(volatile uintptr_t *)(runtime[2] + 0x84u);
        if (context == 0)
            return 0;
        heap = (void *)context;
    }
    return FUN_01038958(heap, alignment, size);
}
