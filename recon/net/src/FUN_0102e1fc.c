/* Reconstructed z_log_msg_commit @ 0x0102e1fc.
 * Raw/address back-map: FUN_0102e1fc / 0x0102e1fc.
 */
#include <stdint.h>

extern void FUN_0102cd8c(void *buffer, void *message); /* msg_commit */
extern void FUN_0102e140(void);                       /* z_log_msg_post_finalize */

void FUN_0102e1fc(uint8_t *message)
{
    uint32_t (*timestamp_get)(void) =
        *(uint32_t (**)(void))0x2100461cu;
    *(uint32_t *)(message + 8) = timestamp_get();
    FUN_0102cd8c((void *)0x2100086cu, message);
    FUN_0102e140();
}
