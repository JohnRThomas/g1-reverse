/* readable reconstruction; identity: FUN_00086cb6 @ 0x00086cb6
 * public-name: libc_write_buffer_via_putc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_putc_buffered                       <= FUN_00086c88 @ 0x00086c88
 *   libc_write_buffer_via_putc               <= FUN_00086cb6 @ 0x00086cb6
 */
/* Reconstructed FUN_00086cb6 @ 0x86cb6  (parity: 300/300 trials, PROVEN) */

extern int libc_putc_buffered(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

int libc_write_buffer_via_putc(unsigned int param_1, unsigned int param_2, unsigned char *param_3, int param_4)
{
  int iVar1;
  unsigned char *puVar2 = param_3 + param_4;
  int iVar3 = param_4;
  while (1) {
    if (param_3 == puVar2) {
      return 0;
    }
    iVar1 = libc_putc_buffered(param_1, *param_3, param_2, param_4, iVar3);
    param_4 = iVar1 + 1;
    param_3 = param_3 + 1;
    if (param_4 == 0) break;
  }
  return iVar1;
}
