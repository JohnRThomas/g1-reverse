#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076a94 @ 0x00076a94
 * public-name: libc_fatal_error_and_abort
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   abort                                    <= FUN_00051180 @ 0x00051180
 *   libc_fatal_error_and_abort               <= FUN_00076a94 @ 0x00076a94
 *   fprintf_stream                           <= FUN_00076cc8 @ 0x00076cc8
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00076a94 @ 0x76a94  (parity: 300/300 trials, PROVEN) */

extern void fprintf_stream(int,int);
extern int abort(void);
void libc_fatal_error_and_abort(void)
{
    int uVar1 = *(volatile int*)(*(volatile int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/ + 0xc);
    for (;;) {
        fprintf_stream(uVar1, 0);
        uVar1 = abort();
    }
}
