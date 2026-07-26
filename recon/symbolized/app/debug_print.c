#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019c70 @ 0x00019c70
 * public-name: debug_print
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   enqueue_debug                            <= FUN_00019bfc @ 0x00019bfc
 *   vsnprintf_impl                           <= FUN_00077c30 @ 0x00077c30
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_ring_log_pending                       @ 0x20007550
 */
/* Reconstructed debug_print @ 0x19c70  (parity: 300/300 trials, PROVEN) */

#include <stdarg.h>
#include <stdint.h>
#include "../../headers/g1_log.h"

extern uintptr_t ancs_get_conn_ctx(void);
extern void memset_bytes(void *dst, int val, unsigned int len);
extern void vsnprintf_impl(void *dst, unsigned int size, unsigned int fmt, va_list args);
extern void enqueue_debug(void *buf);
extern void process_sync_buffer(uintptr_t arg);

void debug_print(uintptr_t format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    uintptr_t context = ancs_get_conn_ctx();
    unsigned char message[200];

    memset_bytes(message, 0, sizeof(message));
    vsnprintf_impl(message, sizeof(message), format, arguments);
    enqueue_debug(message);
    message[0] = 0;

    if ((*(volatile unsigned char *)(context + 0x248) == 0) &&
        (*(volatile unsigned int *)(context + 0x220) == 0)) {
        *(volatile unsigned int *)((unsigned long)&g_ring_log_pending) /*=0x20007550*/ = 1;
        process_sync_buffer(context + 0x218);
    }
    va_end(arguments);
}
