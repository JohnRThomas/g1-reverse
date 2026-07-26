/* readable reconstruction; identity: FUN_00072e50 @ 0x00072e50
 * public-name: k_work_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_init                              <= FUN_00072e50 @ 0x00072e50
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f8230                             @ 0x000f8230
 *   rodata_f82e0                             @ 0x000f82e0
 */
/* Reconstructed FUN_00072e50 @ 0x72e50  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memset_bytes(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void k_work_init(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f82e0UL, 0x000f820fUL, 0x89);
        uVar1 = 0x89;
    } else {
        if (param_2 != 0) {
            memset_bytes(param_1, 0, 0x10, param_4, param_4);
            *(volatile int *)(param_1 + 4) = param_2;
            return;
        }
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f8230UL, 0x000f820fUL, 0x8a);
        uVar1 = 0x8a;
    }
    assert_post_action(0x000f820fUL, uVar1);
}
