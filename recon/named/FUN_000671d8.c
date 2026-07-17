/* readable reconstruction; identity: FUN_000671d8 @ 0x000671d8
 * public-name: FUN_000671d8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6c00                             @ 0x000f6c00
 *   rodata_f6df0                             @ 0x000f6df0
 *   g_nrfx_spim_cb                           @ 0x2000b384
 */
/* Reconstructed FUN_000671d8 @ 0x671d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00066d78(void);
extern int FUN_00066ec0(int);
extern int assert_post_action(int,int);
extern int printk(int,...);
int FUN_000671d8(int param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int r0src = param_1;
  if(param_2 == 0){
    printk(0x00099cbd, 0x000f6c00, 0x000f6df0, 0x1ff, param_4);
    assert_post_action(0x000f6df0, 0x1ff);
    r0src = 0x000f6df0;
  }
  uint32_t off = (uint32_t)*(volatile uint8_t*)(r0src+4) * 0x24;
  uint32_t ip = 0x2000b384;
  int iVar3 = ip + off;
  uint8_t r7 = *(volatile uint8_t*)(iVar3+0x1c);
  if(r7 != 0){
    return 0x0bad0005;
  }
  *(volatile uint32_t*)(ip + off) = param_3;
  *(volatile uint32_t*)(iVar3+4) = param_4;
  int iVar1 = FUN_00066d78();
  if(iVar1 == 0x0bad0000){
    FUN_00066ec0(param_1);
    *(volatile uint8_t*)(iVar3+0x1d) = r7;
    *(volatile uint8_t*)(iVar3+0x1c) = 1;
  }
  return iVar1;
}
