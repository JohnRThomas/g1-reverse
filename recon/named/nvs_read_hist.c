/* named: nvs_read_hist */
/* Reconstructed nvs_read_hist @ 0x4cab4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern uint nvs_flash_rd(int,uint,unsigned,uint);
extern int nvs_log_err(int,int,void*);
extern int nvs_al_size(unsigned,int);
extern int nvs_ate_valid(int,void*);
extern uint nvs_prev_ate(int,void*,void*);

uint nvs_read_hist(int param_1, uint param_2, unsigned param_3, uint param_4, unsigned short param_5)
{
  uint uVar1; int iVar2; uint uVar3; unsigned short uVar4;
  uint local_3c;
  unsigned short s[3];
  unsigned local_28, local_24;
  if (*(volatile char*)(param_1 + 0x10) == 0) {
    local_24 = 0x000f0ae4; local_28 = 2;
    nvs_log_err(0x000881b8, 0x1040, &local_28);
    uVar1 = 0xfffffff3;
  } else {
    iVar2 = nvs_al_size(*(volatile unsigned*)(param_1 + 0x2c), 8);
    if ((uint)*(volatile unsigned short*)(param_1 + 0xc) + iVar2 * -2 < param_4) {
      uVar1 = 0xffffffea;
    } else {
      uVar4 = 0;
      local_3c = *(volatile uint*)(param_1 + 4);
      uVar1 = local_3c;
      do {
        uVar3 = local_3c;
        if (param_5 < uVar4) {
          uVar3 = uVar1;
          if (*(volatile uint*)(param_1 + 4) != local_3c) goto LAB;
          break;
        }
        uVar1 = nvs_prev_ate(param_1, &local_3c, &s[0]);
        if (uVar1 != 0) return uVar1;
        if ((s[0] == param_2) && (iVar2 = nvs_ate_valid(param_1, &s[0]), iVar2 != 0)) {
          uVar4 = uVar4 + 1;
        }
        uVar1 = uVar3;
      } while (*(volatile uint*)(param_1 + 4) != local_3c);
      if (s[0] == param_2) {
LAB:
        uVar1 = (uint)s[2];
        if ((uVar1 != 0) && (param_5 <= uVar4)) {
          if (param_4 <= uVar1) uVar1 = param_4;
          uVar1 = nvs_flash_rd(param_1, (uVar3 & 0xffff0000) + (uint)s[1], param_3, uVar1);
          if (uVar1 != 0) return uVar1;
          return (uint)s[2];
        }
      }
      uVar1 = 0xfffffffe;
    }
  }
  return uVar1;
}

