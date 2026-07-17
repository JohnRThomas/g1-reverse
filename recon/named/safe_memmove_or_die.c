/* readable reconstruction; identity: FUN_00055ba0 @ 0x00055ba0
 * public-name: safe_memmove_or_die
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   safe_memmove_or_die                      <= FUN_00055ba0 @ 0x00055ba0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 */
/* Reconstructed FUN_00055ba0 @ 0x55ba0  (parity: 300/300 trials, PROVEN) */
extern void assert_post_action(void);
extern void printk(void);

void safe_memmove_or_die(unsigned char *param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
    (void)param_3; (void)param_4;
    unsigned char *puVar1 = param_2 + 0x10;
    int bVar2;
    if (param_2 < param_1) {
        bVar2 = (puVar1 <= param_1);
    } else {
        if (param_1 == param_2) {
            printk();
            printk();
            assert_post_action();
            return;
        }
        bVar2 = ((param_1 + 0x10) <= param_2);
    }
    if (bVar2) {
        param_1 = param_1 - 1;
        do {
            puVar1 = puVar1 - 1;
            param_1 = param_1 + 1;
            *param_1 = *puVar1;
        } while (puVar1 != param_2);
        return;
    }
    printk();
    printk();
    assert_post_action();
}
