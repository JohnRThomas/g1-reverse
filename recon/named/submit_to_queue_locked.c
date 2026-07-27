/* readable reconstruction; identity: FUN_00072cd4 @ 0x00072cd4
 * public-name: submit_to_queue_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   submit_to_queue_locked                   <= FUN_00072cd4 @ 0x00072cd4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 *   notify_queue_locked                      <= FUN_00086588 @ 0x00086588
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f8247                             @ 0x000f8247
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00072cd4 @ 0x72cd4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../headers/g1_log.h"
extern int assert_post_action(int, int);
extern int k_is_in_isr(void);
extern void notify_queue_locked(int);

unsigned submit_to_queue_locked(volatile uint32_t *param_1, volatile int *param_2, uint32_t param_3, uint32_t param_4){
    uint32_t r3 = param_1[3];
    uint32_t uVar4 = (r3 >> 1) & 1;
    uint32_t v, iVar3; int r5;
    if (r3 & 2) goto L_d58;
    if (r3 & 4) goto L_d34;
    if (*param_2 == 0) *param_2 = (int)param_1[2];
    r3 = param_1[3];
    if (!(r3 & 1)) goto L_d3a;
    v = param_1[2];
    if (v == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f8247,0x000f820f,0x14e,param_4);
        assert_post_action(0x000f820f,0x14e);
    }
    uVar4 = 2;
    *param_2 = (int)v;
  L_d16:
    r5 = *param_2;
    if (r5 == 0) goto L_d96;
    if (*(volatile int*)(0x2000b448UL+8) == r5){
        int rc = k_is_in_isr();
        iVar3 = *(volatile uint32_t*)(r5+0xf0);
        if (rc != 0) goto L_d28;
        if (!(iVar3 & 1)) goto L_d30;
        if (!(iVar3 & 8)) goto L_d6a;
        if (iVar3 & 4) goto L_d6a;
        goto L_d58;
    } else {
        iVar3 = *(volatile uint32_t*)(r5+0xf0);
    }
  L_d28:
    if (iVar3 & 1){
        if (iVar3 & 4) goto L_d58;
        if (iVar3 & 8) goto L_d58;
        goto L_d6a;
    }
  L_d30:
    uVar4 = 0xffffffed;
  L_d34:
    *param_2 = 0;
    goto L_d8a;
  L_d3a:
    uVar4 = 1;
    goto L_d16;
  L_d58:
    uVar4 = 0xfffffff0;
    goto L_d34;
  L_d96:
    uVar4 = 0xffffffea;
    goto L_d34;
  L_d6a:
    *param_1 = 0;
    if (*(volatile uint32_t*)(r5+0xdc) == 0){
        *(volatile uint32_t*)(r5+0xd8) = (uint32_t)param_1;
        *(volatile uint32_t*)(r5+0xdc) = (uint32_t)param_1;
    } else {
        *(volatile uint32_t*)(*(volatile uint32_t*)(r5+0xdc)) = (uint32_t)param_1;
        *(volatile uint32_t*)(r5+0xdc) = (uint32_t)param_1;
    }
    notify_queue_locked(r5);
    param_1[3] = param_1[3] | 4;
    param_1[2] = (uint32_t)*param_2;
  L_d8a:
    return uVar4;
}
