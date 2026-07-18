/* readable reconstruction; identity: FUN_01034d8c @ 0x01034d8c
 * public-name: FUN_01034d8c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_0102eb2c @ 0x0102eb2c
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e700                           @ 0x0103e700
 *   g_sdc_radio_context_area                 @ 0x21004aec
 */
/* net-core FUN_01034d8c @ 0x1034d8c  (parity 300 trials PROVEN) */

extern void arch_irq_enable(int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
unsigned int FUN_01034d8c(unsigned int param_1, int param_2, int param_3)
{
  if (param_2 == 0) {
    assert_print(0x0103d2a7, 0x0103e700, 0x34);
    assert_post_action(0x0103e700, 0x34);
  }
  int *piVar1 = (int*)0x21004aec;
  unsigned int uVar2;
  if (*(char*)((char*)piVar1+4) == 0) {
    arch_irq_enable(0x12);
    uVar2 = 0x0bad0000;
    *(unsigned char*)((char*)piVar1+4) = 1;
    *piVar1 = param_2;
    piVar1[2] = param_3;
  } else {
    uVar2 = 0x0bad000c;
  }
  return uVar2;
}
