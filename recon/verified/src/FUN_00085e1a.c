/* Reconstructed FUN_00085e1a @ 0x85e1a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00085d70(int*, uint32_t);
extern int FUN_00085d82(unsigned long);
extern void FUN_00086c78(uint8_t*, int, uint32_t);

int FUN_00085e1a(int *param_1, uint8_t *param_2, uint32_t param_3){
  int iVar1;
  uint32_t uVar2;
  if (param_3 == 0 || param_2 == 0){
    uVar2 = 0xe;
  } else {
    iVar1 = FUN_00085d82(param_1);
    if (iVar1 == 0) return 0;
    if (param_1[2] == 0){
      uVar2 = 3;
    } else {
      uint8_t *pbVar4 = (uint8_t*)*param_1;
      uint8_t bVar7 = *pbVar4;
      param_1[1] = (int)pbVar4;
      bVar7 = bVar7 & 0x1f;
      *param_1 = (int)(pbVar4 + 1);
      FUN_00086c78(param_2, 0, param_3);
      if (bVar7 < 0x18){
        *param_2 = bVar7;
        param_1[2] = param_1[2] - 1;
        return iVar1;
      }
      int iVar5 = *param_1;
      if ((uint8_t)(bVar7 - 0x18) < 4){
        uint32_t uVar3 = 1u << (uint8_t)(bVar7 - 0x18);
        if (param_3 < uVar3){
          uVar2 = 5;
          *param_1 = iVar5 - 1;
        } else {
          if ((uint32_t)(iVar5 + uVar3) <= (uint32_t)param_1[3]){
            uint32_t uVar6 = uVar3;
            param_2 = param_2 - 1;
            do {
              uVar6 = uVar6 - 1;
              param_2 = param_2 + 1;
              *param_2 = *(uint8_t*)(*param_1 + uVar6);
            } while (uVar6 != 0);
            *param_1 = *param_1 + uVar3;
            param_1[2] = param_1[2] - 1;
            return iVar1;
          }
          uVar2 = 8;
          *param_1 = iVar5 - 1;
        }
      } else {
        uVar2 = 7;
        *param_1 = iVar5 - 1;
      }
    }
  }
  FUN_00085d70(param_1, uVar2);
  return 0;
}

