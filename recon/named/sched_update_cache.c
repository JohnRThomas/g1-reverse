/* readable reconstruction; identity: FUN_000737d8 @ 0x000737d8
 * public-name: sched_update_cache
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sched_switch_handle_timeout              <= FUN_00073788 @ 0x00073788
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84af                             @ 0x000f84af
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000737d8 @ 0x737d8  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);
extern void sched_switch_handle_timeout(int *a);

void sched_update_cache(int param_1, int param_2, int param_3, int param_4)
{
    int DAT = 0x2000b448;
    int *piVar4 = *(volatile int **)(DAT + 0x1c);
    int r3;
    int specialPath = 0;

    if (piVar4 == (int *)(DAT + 0x1c) || piVar4 == (int *)0) {
        piVar4 = *(volatile int **)(DAT + 0xc);
    }
    r3 = *(volatile int *)(DAT + 8);

    if (param_1 == 0) {
        if (r3 == 0) {
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0xf84af, 0xf82f4, 0x8f, param_4);
            r3 = 0x8f;
            printk(0xf53ff, 0, 0, 0, 0);
            assert_post_action(0xf82f4, 0x8f);
        }
        if (((*(volatile unsigned char *)(r3 + 0xd) & 0x1f) == 0)
            && (*(volatile int *)((int)piVar4 + 0x18) == 0)
            && (*(volatile unsigned short *)(r3 + 0xe) > 0x7f)) {
            specialPath = 1;
        }
    }
    if (!specialPath) {
        if (piVar4 != (int *)r3) {
            sched_switch_handle_timeout(piVar4);
        }
        r3 = (int)piVar4;
    }
    *(volatile int *)(DAT + 0x18) = r3;
}
