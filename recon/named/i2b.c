/* readable reconstruction; identity: FUN_000787bc @ 0x000787bc
 * public-name: i2b
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_fatal_error_and_abort               <= FUN_00076a94 @ 0x00076a94
 *   Balloc                                   <= FUN_000785d4 @ 0x000785d4
 *   i2b                                      <= FUN_000787bc @ 0x000787bc
 * address symbols (name @ address):
 *   rodata_f8c42                             @ 0x000f8c42
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_000787bc @ 0x787bc  (parity: 300/300 trials, PROVEN) */

extern int Balloc(int a, int b);
extern int libc_fatal_error_and_abort(int a, int b, int c, int d);
void i2b(int param_1, int param_2)
{
  int iVar1;
  iVar1 = Balloc(param_1, 1);
  if (iVar1 == 0) {
    iVar1 = libc_fatal_error_and_abort(0x000f8cd5, 0x140, 0, 0x000f8c42);
  }
  *(volatile int *)(iVar1 + 0x14) = param_2;
  *(volatile int *)(iVar1 + 0x10) = 1;
}
