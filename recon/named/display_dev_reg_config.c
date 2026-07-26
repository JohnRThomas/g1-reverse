/* readable reconstruction; identity: FUN_0002eaa8 @ 0x0002eaa8
 * public-name: display_dev_reg_config
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_dev_reg_config                   <= FUN_0002eaa8 @ 0x0002eaa8
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_a3e48                             @ 0x000a3e48   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0002eaa8 @ 0x2eaa8  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void log_message(unsigned int a0);

unsigned int display_dev_reg_config(void)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int base = *(volatile unsigned int*)(0x00087ce0UL + 4);
  iVar1 = dev_write_reg3(*(volatile unsigned int*)(base + 0x1c), 3, 4, 1);
  if (iVar1 < 0) {
    log_message(((unsigned long)"Could not enable charger\n"));
    uVar2 = 0xffffffff;
  } else {
    uVar2 = 0;
  }
  return uVar2;
}
