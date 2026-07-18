/* readable reconstruction; identity: FUN_00065f1c @ 0x00065f1c
 * public-name: nrfx_nvmc_page_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvmc_readonly_mode_set                   <= FUN_00065ef0 @ 0x00065ef0
 *   nrfx_nvmc_page_erase                     <= FUN_00065f1c @ 0x00065f1c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6c32                             @ 0x000f6c32
 *   rodata_f6c8e                             @ 0x000f6c8e
 *   NRF_NVMC_S                               @ 0x50039000
 */
/* Reconstructed FUN_00065f1c @ 0x65f1c  (parity: 300/300 trials, PROVEN) */

extern void nvmc_readonly_mode_set(void);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void assert_post_action(unsigned int a, unsigned int b);

unsigned int nrfx_nvmc_page_erase(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if ((unsigned int)param_1 >= 0x100000u) {
    printk(0x99cbd, 0xf6c8e, 0xf6c32, 0x107, param_4);
    assert_post_action(0xf6c32, 0x107);
    return 0x0bad000a;
  }
  if (((unsigned int)param_1 & 0xfff) != 0) {
    return 0x0bad000a;
  }
  *(volatile unsigned int *)(0x50039000UL + 0x584) = 2;
  *(volatile unsigned int *)(0x50039000UL + 0x504) = 2;
  *param_1 = 0xffffffff;
  while (((int)(*(volatile unsigned int *)(0x50039000UL + 0x400) << 0x1f)) >= 0) {}
  nvmc_readonly_mode_set();
  return 0x0bad0000;
}
