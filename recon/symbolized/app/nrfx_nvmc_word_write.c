#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00065f80 @ 0x00065f80
 * public-name: nrfx_nvmc_word_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvmc_readonly_mode_set                   <= FUN_00065ef0 @ 0x00065ef0
 *   nvmc_word_write                          <= FUN_00065f04 @ 0x00065f04
 *   nrfx_nvmc_word_write                     <= FUN_00065f80 @ 0x00065f80
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6c32                             @ 0x000f6c32
 *   rodata_f6ca8                             @ 0x000f6ca8   [INLINED -- G6 literal batch]
 *   rodata_f6cc2                             @ 0x000f6cc2   [INLINED -- G6 literal batch]
 *   NRF_NVMC_S                               @ 0x50039000
 */
/* Reconstructed FUN_00065f80 @ 0x65f80  (parity: 300/300 trials, PROVEN) */
extern int assert_post_action(int, int);
extern void nvmc_word_write(void);
extern void nvmc_readonly_mode_set(void);
void nrfx_nvmc_word_write(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    if (param_1 < 0x100000) goto L_fae;
    if ((param_1 - 0xff8000) < 0x1000) goto L_fae;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"is_valid_address(addr, 1)") /*=0xf6ca8*/,((unsigned long)&rodata_f6c32) /*=0xf6c32*/,0x195,param_4);
    { long long r = assert_post_action(((unsigned long)&rodata_f6c32) /*=0xf6c32*/,0x195); r0v=(unsigned)r; }
L_fae:
    if ((r0v & 3) == 0) goto L_fc6;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"nrfx_is_word_aligned((void const *)addr)") /*=0xf6cc2*/,((unsigned long)&rodata_f6c32) /*=0xf6c32*/,0x196,param_4);
    { long long r = assert_post_action(((unsigned long)&rodata_f6c32) /*=0xf6c32*/,0x196); r0v=(unsigned)r; }
    goto L_fae;
L_fc6:
    *(volatile unsigned*)(NRF_NVMC_S /*=0x50039000*/ + 0x584) = 1;
    *(volatile unsigned*)(NRF_NVMC_S /*=0x50039000*/ + 0x504) = 1;
    nvmc_word_write();
    nvmc_readonly_mode_set();
}
