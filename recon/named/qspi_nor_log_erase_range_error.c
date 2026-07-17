/* readable reconstruction; identity: FUN_000609c4 @ 0x000609c4
 * public-name: qspi_nor_log_erase_range_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_nor_log_erase_range_error           <= FUN_000609c4 @ 0x000609c4
 * address symbols (name @ address):
 *   rodata_88270                             @ 0x00088270
 *   rodata_f5bd6                             @ 0x000f5bd6
 */
/* Reconstructed FUN_000609c4 @ 0x609c4  (parity: 300/300 trials, PROVEN) */

extern void FUN_000838d6(unsigned int a, unsigned int b, void *c);

unsigned int qspi_nor_log_erase_range_error(unsigned int param_1, unsigned int param_2)
{
  struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } local;
  local.a = 4;
  local.b = 0xf5bd6;
  local.c = param_1;
  local.d = param_2;
  FUN_000838d6(0x88270, 0x2040, &local);
  return 0xffffffea;
}
