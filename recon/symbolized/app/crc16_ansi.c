#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007da4a @ 0x0007da4a
 * public-name: crc16_ansi
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   crc16_reflect                            <= FUN_0007d9c0 @ 0x0007d9c0
 *   crc16_ansi                               <= FUN_0007da4a @ 0x0007da4a
 */
/* Reconstructed FUN_0007da4a @ 0x7da4a  (parity: 300/300 trials, PROVEN) */

extern unsigned int crc16_reflect(unsigned int a,unsigned int b,unsigned int c,unsigned int d,unsigned int e,unsigned int f,unsigned int g,unsigned int h);

unsigned int crc16_ansi(unsigned int param_1, int param_2, int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_2 == 0 || param_3 < 1) {
    uVar1 = 0;
  } else {
    uVar1 = crc16_reflect(param_1, 0x8005, 0xffff, 1, 1, (unsigned int)param_2, (unsigned int)param_3, param_4);
  }
  return uVar1;
}
