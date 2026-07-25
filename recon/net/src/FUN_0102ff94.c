/* net-core chained pool-buffer release @ 0x0102ff94.
 * Raw/address back-map: FUN_0102ff94 / 0x0102ff94.
 */
#include <stdint.h>

extern void assert_print(const void *, const void *, uint32_t);
extern void FUN_01039bb0(const void *, uint32_t);
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

void FUN_0102ff94(uint8_t *buffer)
{
    if (buffer == 0) {
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103de3fu, 0x1d3);
        FUN_01039bb0((const void *)0x0103de3fu, 0x1d3);
    }
    do {
        uint8_t *next = *(uint8_t **)(buffer + 4);
        uint8_t refs = (uint8_t)(buffer[8] - 1u);
        buffer[8] = refs;
        if (refs != 0)
            return;

        if (*(uint32_t *)(buffer + 0x14) != 0) {
            if ((buffer[9] & 1u) == 0) {

                uint8_t *pool = (uint8_t *)G1_NET_BUF_POOL_LIST +
                                (uint32_t)buffer[10] * 0x34u;
                void **owner = *(void ***)(pool + 0x2c);
                ((release_fn_t)owner[2])(buffer);
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
