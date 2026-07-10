#include "g1_app_symbols.h"
/* named: projector_send_command */
/* Reconstructed projector_send_command @ 0x7d82e  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c1e(void *, unsigned int, int, int);
extern void projector_spi_write_chunked(void *, int);

void projector_send_command(unsigned int param_1, unsigned int param_2, int param_3)
{
  unsigned int local_10;
  unsigned int uStack_c;

  local_10 = param_1;
  uStack_c = param_2;
  FUN_00086c1e((unsigned char*)&local_10 + 1, param_2, param_3, 5);
  projector_spi_write_chunked(&local_10, param_3 + 1);
  return;
}

