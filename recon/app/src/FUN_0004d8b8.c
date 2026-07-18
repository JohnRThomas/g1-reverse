/* Reconstructed FUN_0004d8b8 @ 0x4d8b8
 * CFG_VERIFY_CALL_ARITIES=0,2,0
 * Readable identity: z_log_msg_commit.
 * Raw/address backmap: z_log_msg_commit <= FUN_0004d8b8 @ 0x0004d8b8.
 */

#include <stdint.h>

typedef uint32_t (*timestamp_fn_t)(void);

/* mpsc_pbuf_commit <= FUN_0004be0c @ 0x0004be0c */
extern void mpsc_pbuf_commit(void *buffer, void *message);
extern void FUN_0004d7d8(void); /* z_log_msg_post_finalize */

void FUN_0004d8b8(void *message)
{
    timestamp_fn_t timestamp =
        *(timestamp_fn_t volatile *)0x200027f8UL;

    *(volatile uint32_t *)((uintptr_t)message + 8U) = timestamp();
    mpsc_pbuf_commit((void *)0x20003648UL, message);
    FUN_0004d7d8();
}
