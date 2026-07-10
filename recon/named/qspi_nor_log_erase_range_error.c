/* named: qspi_nor_log_erase_range_error */
/* Reconstructed qspi_nor_log_erase_range_error @ 0x609c4  (parity: 300/300 trials, PROVEN) */

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

