/* Reconstructed FUN_0004d578 @ 0x4d578  owned extent: 0xe bytes */

#include <stdint.h>

struct mpsc_buffer;
/* mpsc_pbuf_free <= FUN_0004bfc8 @ 0x0004bfc8 */
extern void mpsc_pbuf_free(struct mpsc_buffer *buffer,
                           volatile uint32_t *item);

void FUN_0004d578(volatile uint32_t *item)
{
    struct mpsc_buffer *buffer =
        *(struct mpsc_buffer * volatile *)0x2000a0ccu;
    mpsc_pbuf_free(buffer, item);
}
