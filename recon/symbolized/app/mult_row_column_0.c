#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ffd6 @ 0x0007ffd6
 * public-name: mult_row_column_0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _double_byte                             <= FUN_0007fec8 @ 0x0007fec8
 */
/* Reconstructed mult_row_column_0 @ 0x7ffd6  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
extern byte _double_byte(byte);

void mult_row_column_0(byte *param_1, byte *param_2)
{
  byte bVar1, bVar2, bVar3, bVar4, bVar5, tmp;

  bVar1 = _double_byte(*param_2);
  bVar2 = _double_byte(param_2[1]);
  *param_1 = bVar2 ^ bVar1 ^ param_2[1] ^ param_2[2] ^ param_2[3];
  bVar1 = *param_2;
  bVar2 = _double_byte(param_2[1]);
  bVar3 = _double_byte(param_2[2]);
  param_1[1] = bVar3 ^ bVar2 ^ bVar1 ^ param_2[2] ^ param_2[3];
  bVar1 = param_2[1];
  bVar2 = *param_2;
  bVar3 = _double_byte(param_2[2]);
  bVar4 = _double_byte(param_2[3]);
  param_1[2] = bVar4 ^ bVar3 ^ bVar2 ^ bVar1 ^ param_2[3];
  bVar4 = _double_byte(*param_2);
  bVar1 = param_2[1];
  bVar2 = *param_2;
  bVar3 = param_2[2];
  tmp = bVar4 ^ ((bVar2 ^ bVar1) ^ bVar3);
  bVar5 = _double_byte(param_2[3]);
  param_1[3] = tmp ^ bVar5;
  return;
}
