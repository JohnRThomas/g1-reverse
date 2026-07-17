/* readable reconstruction; identity: FUN_00065190 @ 0x00065190
 * public-name: nrfx_clock_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_clock_init                          <= FUN_00065190 @ 0x00065190
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6abf                             @ 0x000f6abf
 *   g_clock_cb                               @ 0x2000b31c
 */
/* Reconstructed FUN_00065190 @ 0x65190  (parity: 300/300 trials, PROVEN) */

extern unsigned int printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned int assert_post_action(unsigned int a,unsigned int b);

unsigned int nrfx_clock_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000b31cUL;
    unsigned int uVar2;
    int inVal;
    if (param_1 == 0) {
        printk(0x00099cbdUL, 0x000f6abfUL, 0x000f6a4eUL, 0x115);
        inVal = (int)assert_post_action(0x000f6a4eUL, 0x115);
    } else {
        inVal = param_1;
    }
    if (*(volatile unsigned char*)((char*)piVar1+4) == 0) {
        *piVar1 = inVal;
        uVar2 = 0x0bad0000UL;
        *(volatile unsigned char*)((char*)piVar1+4) = 1;
    } else {
        uVar2 = 0x0bad000cUL;
    }
    return uVar2;
}
