#include "g1_app_symbols.h"
/* named: get_message_type_param */
/* Reconstructed get_message_type_param @ 0x2c30c  (parity: 300/300 trials, PROVEN) */

unsigned int get_message_type_param(int param_1,unsigned int param_2)
{
  if (param_1 != 0xb) {
    if (param_1 == 0xc) {
      param_2 = 1;
    }
    return param_2;
  }
  return 0x01e13380UL;
}

