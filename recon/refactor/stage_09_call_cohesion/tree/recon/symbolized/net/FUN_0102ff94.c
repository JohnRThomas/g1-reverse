#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ff94 @ 0x0102ff94
 * public-name: FUN_0102ff94
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103de3f                           @ 0x0103de3f
 */
/* net-core chained pool-buffer release @ 0x0102ff94.
 * Raw/address back-map: FUN_0102ff94 / 0x0102ff94.
 */
#include <stdint.h>
#include "../../headers/g1_dedupe.h"

extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t);
extern void FUN_0103b210(void *, void *);

/* P4 iteration 18: 0x21000994 is where the ORIGINAL image's net_buf pool array
 * (`_net_buf_pool_list`) starts.  In the cohesive link that section is
 * net_buf_pool_area = [_net_buf_pool_list_start 0x210008f8 ..
 * _net_buf_pool_list_end 0x21000994), so the raw literal indexes one element
 * PAST the last pool and every pool word read back is unrelated memory.  Bind
 * the linker's own section start instead. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char _net_buf_pool_list_start[];
#define G1_NET_BUF_POOL_LIST ((unsigned long)_net_buf_pool_list_start)
#else
#define G1_NET_BUF_POOL_LIST 0x21000994u
#endif

typedef void (*release_fn_t)(void *);
/* P4 iteration 20 -- the data-unref callback takes TWO arguments; see below. */
typedef void (*data_unref_fn_t)(void *, void *);

void FUN_0102ff94(uint8_t *buffer)
{
    if (buffer == 0) {
        G1_NET_ASSERT_FAIL(((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, (const void *)((unsigned long)&rodata_103de3f) /*=0x103de3f*/, 0x1d3), ((const void *)((unsigned long)&rodata_103de3f) /*=0x103de3f*/, 0x1d3));
    }
    do {
        uint8_t *next = *(uint8_t **)(buffer + 4);
        uint8_t refs = (uint8_t)(buffer[8] - 1u);
        buffer[8] = refs;
        if (refs != 0)
            return;

        /* P4 iteration 20 -- TWO defects, both proven against the shipped
         * disassembly (tools/net_recon_kit.py info 0x0102ff94):
         *
         *   102ffb2  ldr  r1, [r4, #0x14]   <- __buf kept in r1 and PASSED
         *   102ffb4  cbz  r1, #0x102ffce
         *   ...
         *   102ffc4  ldr  r3, [r3, #0x2c]   ; pool->alloc
         *   102ffc6  ldr  r3, [r3]          ; alloc->cb      <- THREE loads
         *   102ffc8  ldr  r3, [r3, #8]      ; cb->unref
         *   102ffca  blx  r3
         *
         * This body had only TWO loads (`*(pool+0x2c)` then `[2]`), so it
         * called `pool->alloc->max_alloc_size` instead of
         * `pool->alloc->cb->unref`.  MEASURED on /private/tmp/g1-i20a-net:
         * `blx r3` with r3 = 0x44 = CONFIG_BT_BUF_EVT_RX_SIZE, i.e. the net
         * core branched to address 0x44 at t = 5.0942 s -- the fault iteration
         * 19 §19.8 recorded as "PendSV restored PC = 0".  It also dropped the
         * second argument (`data`), which the shipped code leaves live in r1.
         * Wrong indirection + dropped register argument: the two classes the
         * differential harness is structurally blind to. */
        uint8_t *data = *(uint8_t **)(buffer + 0x14);
        if (data != 0) {
            if ((buffer[9] & 1u) == 0) {

                uint8_t *pool = (uint8_t *)G1_NET_BUF_POOL_LIST +
                                (uint32_t)buffer[10] * 0x34u;
                void **alloc = *(void ***)(pool + 0x2c);
                void **cb = (void **)alloc[0];
                ((data_unref_fn_t)cb[2])(buffer, data);
            }
            *(uint32_t *)(buffer + 0x14) = 0;
        }
        *(uint32_t *)(buffer + 0x0c) = 0;
        uint8_t *pool = (uint8_t *)G1_NET_BUF_POOL_LIST +
                        (uint32_t)buffer[10] * 0x34u;
        *(uint32_t *)(buffer + 4) = 0;
        release_fn_t release = *(release_fn_t *)(pool + 0x28);
        if (release != 0)
            release(buffer);
        else
            FUN_0103b210(pool, buffer);
        buffer = next;
    } while (buffer != 0);
}
