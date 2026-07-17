/* readable reconstruction; identity: FUN_00066300 @ 0x00066300
 * public-name: nrfx_pdm_stop
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pdm_stop                            <= FUN_00066300 @ 0x00066300
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6ceb                             @ 0x000f6ceb
 *   rodata_f6d26                             @ 0x000f6d26
 *   nrfx_pdm_drv_state                       @ 0x2000b340
 *   nrfx_pdm_state                           @ 0x2000b341
 *   REG_50026004                             @ 0x50026004
 *   REG_50026500                             @ 0x50026500
 */
/* Reconstructed FUN_00066300 @ 0x66300  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);

unsigned int nrfx_pdm_stop(void)
{
    unsigned char bVar1;
    unsigned int uVar3;

    if (*(volatile unsigned char *)0x2000b340UL == 0) {
        printk(0x99cbd, 0xf6d26, 0xf6ceb, 0x132, 0);
        assert_post_action(0xf6ceb, 0x132);
    }
    bVar1 = *(volatile unsigned char *)0x2000b341UL;
    if (bVar1 == 1) {
        *(volatile unsigned char *)0x2000b340UL = 1;
        *(volatile unsigned char *)0x2000b341UL = 3;
        *(volatile unsigned int *)0x50026004UL = (unsigned int)bVar1;
        uVar3 = 0x0bad0000;
    } else if (bVar1 == 0 || bVar1 == 2) {
        *(volatile unsigned int *)0x50026500UL = 0;
        *(volatile unsigned char *)0x2000b341UL = 0;
        uVar3 = 0x0bad0000;
    } else {
        uVar3 = 0x0bad000b;
    }
    return uVar3;
}
