#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102fdd0 @ 0x0102fdd0
 * public-name: FUN_0102fdd0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103de3f                           @ 0x0103de3f
 */
/* net-core FUN_0102fdd0 @ 0x0102fdd0
 * upstream identity: net_buf_alloc_len (Zephyr subsys/net/buf.c)
 * back-map: raw identity FUN_0102fdd0
 */
#include <stddef.h>
#include <stdint.h>
#include <cmsis_gcc.h>

struct net_buf_layout {
    uint32_t node;
    struct net_buf_layout *frags;
    uint8_t ref;
    uint8_t flags;
    uint8_t pool_id;
    uint8_t user_data_size;
    uint8_t *data;
    uint16_t len;
    uint16_t size;
    uint8_t *__buf;
};

struct net_buf_data_cb_layout {
    uint8_t *(*alloc)(struct net_buf_layout *, size_t *, uint64_t);
};

struct net_buf_data_alloc_layout {
    const struct net_buf_data_cb_layout *cb;
};

struct net_buf_pool_layout {
    uint8_t free_lifo[0x1c];
    uint32_t lock;
    uint16_t buf_count;
    uint16_t uninit_count;
    uint8_t user_data_size;
    uint8_t reserved_25[7];
    const struct net_buf_data_alloc_layout *alloc;
    uint8_t *buffers;
};

extern void sys_timepoint_calc(uint64_t *result, uint64_t timeout); /* =FUN_0103b304 */
extern void sys_timepoint_timeout(uint64_t *result, uint64_t end); /* =FUN_0103b34c */
extern int spinlock_validate(void *lock); /* =FUN_0103610c */
extern void spinlock_acquire(void *lock); /* =FUN_01036144 */
extern int spinlock_release(void *lock); /* =FUN_01036128 */
extern struct net_buf_layout *net_buf_free_get(void *, uint64_t); /* =FUN_01036774 */
extern void net_buf_destroy_from_pool(struct net_buf_pool_layout *, struct net_buf_layout *); /* =FUN_0103b210 */
extern void assert_report(uint32_t, uint32_t, uint32_t); /* =FUN_01039bbe */
extern void assert_post_action(uint32_t, uint32_t); /* =FUN_01039bb0 */

#define ASSERT_SOURCE       ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define ASSERT_POOL_MESSAGE ((unsigned long)&rodata_103de3f) /*=0x103de3f*/
#define ASSERT_SPIN_MESSAGE ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define NET_BUF_POOLS_BASE  0x21000994u
#define NET_BUF_POOL_STRIDE 0x34u

static __attribute__((always_inline)) inline void
net_buf_spin_unlock(struct net_buf_pool_layout *pool, uint32_t key)
{
    if (spinlock_release(&pool->lock) == 0) {
        assert_report(ASSERT_SOURCE, ASSERT_SPIN_MESSAGE, 0xf0u);
        assert_post_action(ASSERT_SPIN_MESSAGE, 0xf0u);
    }
    __set_BASEPRI(key);
    __ISB();
}

struct net_buf_layout *FUN_0102fdd0(struct net_buf_pool_layout *pool,
                                    size_t size, uint64_t timeout)
{
    uint64_t end;
    struct net_buf_layout *buf;
    uint32_t key;

    sys_timepoint_calc(&end, timeout);

    if (pool == NULL) {
        assert_report(ASSERT_SOURCE, ASSERT_POOL_MESSAGE, 0xf8u);
        assert_post_action(ASSERT_POOL_MESSAGE, 0xf8u);
    }

    key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (spinlock_validate(&pool->lock) == 0) {
        assert_report(ASSERT_SOURCE, ASSERT_SPIN_MESSAGE, 0x72u);
        assert_post_action(ASSERT_SPIN_MESSAGE, 0x72u);
    }
    spinlock_acquire(&pool->lock);

    if (pool->uninit_count != 0u) {
        uint16_t uninit_count;

        if (pool->uninit_count < pool->buf_count) {
            buf = net_buf_free_get(pool, 0u);
            if (buf != NULL) {
                net_buf_spin_unlock(pool, key);
                goto success;
            }
        }

        uninit_count = pool->uninit_count--;
        net_buf_spin_unlock(pool, key);

        {
            size_t stride = ((size_t)pool->user_data_size +
                             sizeof(struct net_buf_layout) + 3u) & ~3u;
            size_t index = (size_t)pool->buf_count - uninit_count;
            uintptr_t pool_offset = (uintptr_t)pool - NET_BUF_POOLS_BASE;

            buf = (struct net_buf_layout *)(pool->buffers + index * stride);
            *(volatile uint8_t *)&buf->pool_id =
                (uint8_t)(pool_offset / NET_BUF_POOL_STRIDE);
            *(volatile uint8_t *)&buf->user_data_size = pool->user_data_size;
        }
        goto success;
    }

    net_buf_spin_unlock(pool, key);
    buf = net_buf_free_get(pool, timeout);
    if (buf == NULL)
        return NULL;

success:
    if (size != 0u) {
        size_t requested_size = size;
        uint64_t remaining;
        const struct net_buf_data_alloc_layout *allocator;
        struct net_buf_pool_layout *owner;

        sys_timepoint_timeout(&remaining, end);
        owner = (struct net_buf_pool_layout *)(NET_BUF_POOLS_BASE +
                    (size_t)buf->pool_id * NET_BUF_POOL_STRIDE);
        allocator = owner->alloc;
        buf->__buf = allocator->cb->alloc(buf, &size, remaining);
        if (buf->__buf == NULL) {
            net_buf_destroy_from_pool(owner, buf);
            return NULL;
        }
        if (requested_size > size) {
            assert_report(ASSERT_SOURCE, ASSERT_POOL_MESSAGE, 0x14fu);
            assert_post_action(ASSERT_POOL_MESSAGE, 0x14fu);
        }
    } else {
        buf->__buf = NULL;
    }

    /* These are distinct observable stores in Zephyr's reset sequence. */
    {
        volatile struct net_buf_layout *published = buf;

        published->frags = NULL;
        *(volatile uint16_t *)&published->ref = 1u;
        published->len = 0u;
        published->size = (uint16_t)size;
        published->data = published->__buf;
    }
    return buf;
}
