#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103576c @ 0x0103576c
 * public-name: FUN_0103576c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   metal_io_block_write                     <= FUN_0103ab0e @ 0x0103ab0e
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e889                           @ 0x0103e889
 */
/* net-core FUN_0103576c @ 0x103576c */
#include <stdint.h>
extern uint8_t *FUN_0103aff2(void *, uint32_t *, uint32_t);
extern uint32_t metal_io_block_write(void *, uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_010355bc(void *, uint32_t, uint32_t, void *, uint32_t);
extern void assert_print(uint32_t, uint32_t, uint32_t);
extern void assert_post_action(uint32_t, uint32_t);

uint32_t FUN_0103576c(uint8_t *object, uint32_t arg2, uint32_t arg3,
                      uint32_t arg4, int32_t requested, uint32_t arg6)
{
    uint32_t available;
    uint8_t *position = FUN_0103aff2(object, &available, arg6);
    if (position == 0) return 0xfffff82e;
    if ((int32_t)available < requested) requested = (int32_t)available;

    uint32_t *window = *(uint32_t **)(object + 0xac);
    uint32_t offset = (uint32_t)(position - (uint8_t *)(uintptr_t)window[0]);
    if (offset >= window[2]) offset = UINT32_MAX;
    if (metal_io_block_write(window, offset, arg4, (uint32_t)requested) != (uint32_t)requested) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e889) /*=0x103e889*/, 0x207);
        assert_post_action(((unsigned long)&rodata_103e889) /*=0x103e889*/, 0x207);
    }
    return FUN_010355bc(object, arg2, arg3, position, (uint32_t)requested);
}
