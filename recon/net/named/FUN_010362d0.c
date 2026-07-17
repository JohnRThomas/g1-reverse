/* readable reconstruction; identity: FUN_010362d0 @ 0x010362d0
 * public-name: FUN_010362d0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103ea89                           @ 0x0103ea89
 */
/* net-core FUN_010362d0 @ 0x10362d0 */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern void FUN_0103705c(void *item);
extern void FUN_01037130(void *lock, uint32_t key);
extern int FUN_010375b8(void *lock, uint32_t key, void *queue, void *item,
                        uint32_t low, uint32_t high);
extern void *FUN_010379d4(void *queue);
extern __attribute__((noreturn)) void FUN_01039bb0(uint32_t source,
                                                   uint32_t line);
extern void FUN_01039bbe(uint32_t module, uint32_t source, uint32_t line, ...);
extern void FUN_0103b614(void *destination, const void *source, uint32_t size);

typedef struct {
    uint8_t reserved_00[0x0c];
    uint32_t element_size;
    uint32_t reserved_10;
    uint8_t *buffer_begin;
    uint8_t *buffer_end;
    uint8_t *write_cursor;
    uint8_t *read_cursor;
    uint32_t queued;
} queue_t;

typedef struct {
    uint8_t reserved_00[0x14];
    const void *payload;
    uint8_t reserved_18[0x78];
    uint32_t ownership;
} queue_item_t;

static __attribute__((noreturn)) void queue_fatal(uint32_t source,
                                                  uint32_t line)
{
    FUN_01039bb0(source, line);
}

int FUN_010362d0(queue_t *queue, void *destination,
                 uint32_t timeout_low, uint32_t timeout_high)
{
    /* Zephyr callers enter this API from thread context.  Timed queue writes
     * from an ISR are forbidden by the kernel contract. */
    if ((__get_IPSR() & 0x1fu) != 0 && (timeout_low | timeout_high) != 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103ea89, 0xd2,
                     timeout_low | timeout_high, queue, destination, timeout_low);
        queue_fatal(0x0103ea89, 0xd2);
    }

    void *lock = (uint8_t *)queue + 8;
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    if (FUN_0103610c(lock) == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        queue_fatal(0x0103d3b6, 0x72);
    }

    FUN_01036144(lock);
    int result;
    if (queue->queued == 0) {
        if ((timeout_low | timeout_high) != 0) {
            queue_item_t *item = *(queue_item_t **)(UINT32_C(0x21004b28) + 8);
            item->payload = destination;
            return FUN_010375b8(lock, key, queue, item,
                                timeout_low, timeout_high);
        }
        result = -0x23;
    } else {
        FUN_0103b614(destination, queue->write_cursor, queue->element_size);
        queue->write_cursor += queue->element_size;
        if (queue->write_cursor == queue->buffer_end)
            queue->write_cursor = queue->buffer_begin;
        queue->queued--;

        queue_item_t *item = FUN_010379d4(queue);
        result = (int)(intptr_t)item;
        if (item != 0) {
            if (queue->read_cursor < queue->buffer_begin ||
                queue->read_cursor >= queue->buffer_end) {
                FUN_01039bbe(0x0103d2a7, 0x0103ea89, 0xeb,
                             queue->buffer_begin, queue->read_cursor, destination,
                             timeout_low);
                queue_fatal(0x0103ea89, 0xeb);
            }

            FUN_0103b614(queue->read_cursor, item->payload,
                         queue->element_size);
            queue->read_cursor += queue->element_size;
            if (queue->read_cursor == queue->buffer_end)
                queue->read_cursor = queue->buffer_begin;
            queue->queued++;
            item->ownership = 0;
            FUN_0103705c(item);
            FUN_01037130(lock, key);
            return 0;
        }
    }

    result = FUN_01036128(lock) ? result : 0;
    if (result == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        queue_fatal(0x0103d3b6, 0xf0);
    }
    __set_BASEPRI(key);
    __ISB();
    return result;
}
