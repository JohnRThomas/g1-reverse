#include "g1_app_symbols.h"
#include "../../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_0006666c @ 0x0006666c
 * public-name: gpio_configure_pin_output
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_configure_pin_output                <= FUN_0006666c @ 0x0006666c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f09d1                             @ 0x000f09d1
 *   rodata_f0a04                             @ 0x000f0a04   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0006666c @ 0x6666c  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned,unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
void gpio_configure_pin_output(unsigned param_1, int param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    unsigned r1v = (unsigned)param_2;
    unsigned uVar2; int iVar1;
    if ((param_1 >> 5) == 0) goto L_68e;
    if ((param_1 >> 5) == 1) goto L_6b4;
L_676:
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"nrf_gpio_pin_present_check(*p_pin)") /*=0xf0a04*/,((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f,param_4);
    { long long r = assert_post_action(((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f);
      r0v = (unsigned)r; r1v = (unsigned)((unsigned long long)r >> 32); }
L_68e:
    { unsigned s = r0v & 0xff; uVar2 = (s >= 32) ? 0u : (0xffffffffu >> s); }
    iVar1 = G1_NRF_P0_S_BASE;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
    goto L_join;
L_6b4:
    r0v = param_1 & 0x1f;
    uVar2 = 0xffffu >> r0v;
    iVar1 = G1_NRF_P1_S_BASE;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
L_join:
    {
        volatile unsigned* addr = (volatile unsigned*)(iVar1 + (r0v << 2) + 0x200);
        *addr = (*addr & 0xfffcf0f0) | (r1v << 8) | 2;
    }
}
