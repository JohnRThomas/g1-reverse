#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073d1c @ 0x00073d1c
 * public-name: sched_requeue_by_prio
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   sched_requeue_by_prio                    <= FUN_00073d1c @ 0x00073d1c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 *   _kernel                                  @ 0x2000b448
 *   g_sched_ready_runq                       @ 0x2000b464
 */
/* Reconstructed FUN_00073d1c @ 0x73d1c  (parity: 300/300 trials, PROVEN) */

extern void sched_update_cache(int a);
extern void dlist_unlink_node(unsigned a, int* b);
extern void printk(unsigned a,unsigned b,unsigned c,unsigned d);
extern void assert_post_action(unsigned a,unsigned b);
void sched_requeue_by_prio(int *param_1){
    volatile unsigned char *p = (volatile unsigned char*)param_1;
    if ((signed char)p[0xd] < 0){
        p[0xd] = p[0xd] & 0x7f;
        dlist_unlink_node(((unsigned long)&g_sched_ready_runq) /*=0x2000b464*/, param_1);
    }
    p[0xd] = p[0xd] | 0x80;
    int iVar1 = ((unsigned long)&_kernel) /*=0x2000b448*/;
    if ((unsigned)param_1 == 0x20006720u){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f84d6) /*=0xf84d6*/,((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0xc1);
        assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0xc1);
    }
    volatile int *puVar3 = (volatile int*)(iVar1 + 0x1c);
    volatile int *puVar4 = (volatile int*)*puVar3;
    volatile int *puVar2 = (volatile int*)*(volatile int*)(iVar1 + 0x20);
    if (puVar4 == puVar3) puVar4 = 0;
    for (; puVar4 != 0; puVar4 = (volatile int*)*puVar4){
        signed char a = (signed char)p[0xe];
        signed char b2 = (signed char)((volatile unsigned char*)puVar4)[0xe];
        if (a != b2 && a < b2){
            volatile int *t = (volatile int*)puVar4[1];
            ((volatile int*)param_1)[0] = (int)puVar4;
            ((volatile int*)param_1)[1] = (int)t;
            *t = (int)param_1;
            puVar4[1] = (int)param_1;
            goto done;
        }
        if (puVar2 == puVar4) break;
    }
    ((volatile int*)param_1)[0] = (int)puVar3;
    ((volatile int*)param_1)[1] = (int)puVar2;
    *puVar2 = (int)param_1;
    *(volatile int*)(iVar1 + 0x20) = (int)param_1;
done:
    sched_update_cache(*(volatile int*)(iVar1 + 8) == (int)param_1);
}
