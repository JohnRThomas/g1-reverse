#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d8f8 @ 0x0004d8f8
 * public-name: log_msg_commit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_notify_backend_enabled             <= FUN_0004d44c @ 0x0004d44c
 *   log_msg_commit                           <= FUN_0004d8f8 @ 0x0004d8f8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0da7                             @ 0x000f0da7
 *   rodata_f0ddf                             @ 0x000f0ddf
 */
/* Reconstructed FUN_0004d8f8 @ 0x4d8f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void printk(int a, int b, int c, int d);
extern uint64_t assert_post_action(int a, int b);
extern void z_log_notify_backend_enabled(void);

void log_msg_commit(int param_1, unsigned int param_2, unsigned char param_3)
{
    volatile unsigned char index =
        (unsigned char)(((param_1 - ((unsigned long)&rodata_882a0) /*=0x882a0*/) >> 4) + 1);
    if (param_1 == 0) {
        uint64_t assertion_result;
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0ddf) /*=0xf0ddf*/, ((unsigned long)&rodata_f0da7) /*=0xf0da7*/, 0xdf);
        assertion_result = assert_post_action(((unsigned long)&rodata_f0da7) /*=0xf0da7*/, 0xdf);
        param_1 = (int)assertion_result;
        /* The assertion backend is expected not to return.  The original has
         * no recovery path: if it does return, the live caller-saved argument
         * registers flow into the subsequent record stores. */
        index = 0xdf;
        param_2 = (unsigned int)(assertion_result >> 32);
        param_3 = 0xa7;
    }
    *(unsigned char *)(*(int *)(param_1 + 4) + 4) = index;
    *(unsigned char *)(*(int *)(param_1 + 4) + 6) = param_3;
    **(unsigned int **)(param_1 + 4) = param_2;
    *(unsigned char *)(*(int *)(param_1 + 4) + 5) = 1;
    z_log_notify_backend_enabled();
}
