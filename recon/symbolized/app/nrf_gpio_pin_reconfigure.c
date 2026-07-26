#include "g1_app_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_00067548 @ 0x00067548
 * public-name: nrf_gpio_pin_reconfigure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_reconfigure                 <= FUN_00067548 @ 0x00067548
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f09d1                             @ 0x000f09d1
 *   rodata_f0a04                             @ 0x000f0a04
 */
/* Reconstructed FUN_00067548 @ 0x67548  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
void nrf_gpio_pin_reconfigure(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned r0v=param_1, r1v=param_2, r2v=param_3, r3v=param_4;
    unsigned uVar2; int iVar1;
    if ((param_1 >> 5) == 0) goto L_6a;
    if ((param_1 >> 5) == 1) goto L_94;
L_52:
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0a04) /*=0xf0a04*/,((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f);
    r2v = ((unsigned long)&rodata_f09d1) /*=0xf09d1*/; r3v = 0x32f;
    { long long r=assert_post_action(((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32); }
L_6a:
    { unsigned s=r0v & 0xff; uVar2=(s>=32)?0u:(0xffffffffu>>s); }
    iVar1 = G1_NRF_P0_S_BASE;
    if ((int)(uVar2<<0x1f) >= 0) goto L_52;
    goto L_join;
L_94:
    r0v = param_1 & 0x1f;
    uVar2 = 0xffffu >> r0v;
    iVar1 = G1_NRF_P1_S_BASE;
    if ((int)(uVar2<<0x1f) >= 0) goto L_52;
L_join:
    {
        volatile unsigned* addr = (volatile unsigned*)(iVar1 + (r0v<<2) + 0x200);
        *addr = (r3v<<8) | (r2v<<2) | (r1v<<1) | (0xfffcf0f0 & *addr);
    }
}
