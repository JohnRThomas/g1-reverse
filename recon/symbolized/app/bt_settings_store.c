#include "g1_app_symbols.h"
/* named: bt_settings_store */
/* Reconstructed bt_settings_store @ 0x52f18  (parity: 300/300 trials, PROVEN) */

extern unsigned int settings_save_one(void* a, unsigned int b, unsigned int c);
extern void bt_settings_encode_key(void* a, unsigned int b, unsigned int c, int d, void* e);
extern void u8_to_dec(void* a, unsigned int b, void* c);
extern int snprintk(void* a, unsigned int b, unsigned int c, unsigned int d);

unsigned int bt_settings_store(unsigned int param_1, unsigned char *param_2, int param_3, unsigned int param_4, unsigned int param_5)
{
  unsigned int uVar1;
  int iVar2;
  unsigned char auStack_38[4];
  unsigned char auStack_34[36];

  if (param_3 == 0) {
    iVar2 = snprintk(auStack_34, 0x24, "bt/%s" /*=0xf2c6b*/, param_1);
    if (iVar2 < 0) {
      return 0xffffffea;
    }
  } else {
    if (param_2 != 0) {
      u8_to_dec(auStack_38, 4, param_2);
      param_2 = auStack_38;
    }
    bt_settings_encode_key(auStack_34, 0x24, param_1, param_3, param_2);
  }
  uVar1 = settings_save_one(auStack_34, param_4, param_5);
  return uVar1;
}

