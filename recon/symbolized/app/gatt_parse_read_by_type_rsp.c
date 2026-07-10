#include "g1_app_symbols.h"
/* named: gatt_parse_read_by_type_rsp */
/* Reconstructed gatt_parse_read_by_type_rsp @ 0x5bd18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned char byte;
typedef int (*codeptr)(int,...);

void gatt_parse_read_by_type_rsp(undefined4 param_1,int param_2,byte *param_3,int param_4,int *param_5)
{
  codeptr pcVar6;
  if (param_2 != 0) { pcVar6 = (codeptr)param_5[1]; goto call; }
  pcVar6 = (codeptr)param_5[1];
call:
  (*pcVar6)(param_1,0,param_5);
  return;
}

