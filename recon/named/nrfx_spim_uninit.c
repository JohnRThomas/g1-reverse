/* readable reconstruction; identity: FUN_00067248 @ 0x00067248
 * public-name: nrfx_spim_uninit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_disable                         <= FUN_000500c8 @ 0x000500c8
 *   spim_pin_uninit                          <= FUN_00067138 @ 0x00067138
 *   nrfx_spim_uninit                         <= FUN_00067248 @ 0x00067248
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   spim_abort                               <= FUN_000852ba @ 0x000852ba
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6df0                             @ 0x000f6df0
 *   rodata_f6e3a                             @ 0x000f6e3a
 *   g_nrfx_spim_cb                           @ 0x2000b384
 */
/* Reconstructed FUN_00067248 @ 0x67248  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern void arch_irq_disable(int);
/* The cleanup helper's live context word occupies the aligned r2 slot; r1 is
 * an unused ABI hole in the shipped implementation. */
extern void spim_pin_uninit(uint32_t handle, uint64_t context_word);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,uint32_t,...);
extern void spim_abort(int, int);

void nrfx_spim_uninit(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint uVar3 = *(uint8_t*)((char*)param_1 + 4);
  if (*(volatile char*)(0x2000b384 + uVar3*0x24 + 0x1c) == 0){
    printk(0x99cbd, 0xf6e3a, 0xf6df0, 0x255, param_4);
    assert_post_action(0xf6df0, 0x255);
  }
  arch_irq_disable((*param_1 << 0xc) >> 0x18);
  uint32_t cleanup_arg3 = param_3;
  if (*(volatile int*)(0x2000b384 + uVar3*0x24) != 0){
    *(volatile uint32_t*)(*param_1 + 0x308) = 0x80152;
    cleanup_arg3 = 0x80152;
    spim_abort(*param_1, 0x2000b384 + uVar3*0x24);
  }
  int iVar4 = uVar3*0x24 + 0x2000b384;
  int iVar2 = *param_1;
  uint32_t uVar5 = *(uint32_t*)(iVar2 + 0x50c);
  uint32_t uVar6 = *(uint32_t*)(iVar2 + 0x510);
  if ((int)((uint32_t)*(uint8_t*)(iVar4 + 0x1e) << 0x1f) >= 0){
    spim_pin_uninit(*(uint32_t*)(iVar2 + 0x508), cleanup_arg3);
    spim_pin_uninit(uVar6, cleanup_arg3);
    spim_pin_uninit(uVar5, cleanup_arg3);
    spim_pin_uninit(*(uint32_t*)(iVar4 + 0x20), cleanup_arg3);
    if ((char)*(uint8_t*)((char*)param_1+4) != 0){
      uVar5 = *(uint32_t*)(*param_1 + 0x514);
      spim_pin_uninit(*(uint32_t*)(*param_1 + 0x56c), cleanup_arg3);
      spim_pin_uninit(uVar5, cleanup_arg3);
    }
  }
  *(volatile uint8_t*)(uVar3*0x24 + 0x2000b384 + 0x1c) = 0;
}
