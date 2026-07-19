#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000678d0 @ 0x000678d0
 * public-name: nrfx_twim_disable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_twim_disable                        <= FUN_000678d0 @ 0x000678d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6e3a                             @ 0x000f6e3a
 *   rodata_f6fef                             @ 0x000f6fef
 *   g_nrfx_twim_cb                           @ 0x2000b3cc
 */
/* Reconstructed FUN_000678d0 @ 0x678d0  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern int assert_post_action(int a, int b);

void nrfx_twim_disable(int *param_1, int param_2, int param_3, int param_4)
{
    unsigned char byte = *(unsigned char *)((int)param_1 + 4);
    int iVar2 = (int)((unsigned int)byte * 0x28 + ((unsigned long)&g_nrfx_twim_cb) /*=0x2000b3cc*/);
    int r3 = iVar2;
    int r0 = (int)param_1;

    if (*(volatile char *)(iVar2 + 0x22) == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f6e3a) /*=0xf6e3a*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x176, param_4);
        r3 = 0x176;
        r0 = assert_post_action(((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x176);
    }
    *(volatile int *)(r3 + 8) = 0;
    int r2 = *(volatile int *)r0;
    *(volatile int *)(r2 + 0x308) = 0x019c0202;
    *(volatile unsigned int *)(r2 + 0x200) = *(volatile unsigned int *)(r2 + 0x200) & 0xffffe87f;
    *(volatile int *)(r2 + 0x500) = 0;
    *(volatile char *)(r3 + 0x24) = 0;
    *(volatile char *)(r3 + 0x22) = 1;
}
