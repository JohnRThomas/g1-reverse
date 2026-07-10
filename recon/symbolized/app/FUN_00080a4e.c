#include "g1_app_symbols.h"
/* named: FUN_00080a4e */
/* Reconstructed FUN_00080a4e @ 0x80a4e  (parity: 300/300 trials, PROVEN) */

extern int img_mgmt_read_hash_and_flags(int, unsigned int, void *, int);
extern int memcmp(void *, unsigned int, int);

int FUN_00080a4e(unsigned int param_1, unsigned int param_2)
{
  int iVar1;
  int iVar2;
  unsigned char auStack_30[32];
  iVar2 = 0;
  while (1) {
    iVar1 = img_mgmt_read_hash_and_flags(iVar2, param_2, auStack_30, 0);
    if (iVar1 == 0) {
      iVar1 = memcmp(auStack_30, param_1, 0x20);
    }
    if (iVar1 == 0) break;
    iVar2 = iVar2 + 1;
    if (iVar2 == 4) {
      return -1;
    }
  }
  return iVar2;
}

