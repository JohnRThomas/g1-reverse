/* readable reconstruction; identity: FUN_00066214 @ 0x00066214
 * public-name: nrfx_pdm_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pdm_start                           <= FUN_00066214 @ 0x00066214
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6ceb                             @ 0x000f6ceb
 *   rodata_f6d26                             @ 0x000f6d26
 *   g_pdm_cb                                 @ 0x2000b330
 */
/* Reconstructed FUN_00066214 @ 0x66214  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void assert_post_action(unsigned int a0, unsigned int a1);

unsigned int nrfx_pdm_start(void)
{
    unsigned int iVar1 = 0x2000b330UL;
    unsigned int uVar2;

    if (*(volatile unsigned char*)(0x2000b330UL + 0x10) != 0) {
        if (*(volatile unsigned char*)(0x2000b330UL + 0x11) == 0) {
            *(volatile unsigned char*)(0x2000b330UL + 0x11) = 2;
            *(volatile unsigned char*)(iVar1 + 0x14) = 1;
            *(volatile unsigned int*)(0xe000e100UL + 0x104) = 0x40;
            uVar2 = 0x0bad0000UL;
        } else {
            if (*(volatile unsigned char*)(0x2000b330UL + 0x11) != 1) {
                uVar2 = 0x0bad000bUL;
            } else {
                uVar2 = 0x0bad0000UL;
            }
        }
        return uVar2;
    }
    printk(0x00099cbdUL, 0x000f6d26UL, 0x000f6cebUL, 0xdd);
    assert_post_action(0x000f6cebUL, 0xdd);
    return 0;
}
