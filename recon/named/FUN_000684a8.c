/* readable reconstruction; identity: FUN_000684a8 @ 0x000684a8
 * public-name: FUN_000684a8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_000684a8 @ 0x684a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void memset_bytes(unsigned char*, int, int);
#define WU(off) (*(volatile unsigned*)(param_1+(off)))
void FUN_000684a8(unsigned char *param_1,int param_2,unsigned char *param_3,int param_4)
{
  unsigned uVar1, uVar4;
  unsigned char *pbVar2;
  int iVar3, iVar5;
  iVar5 = (unsigned)(param_2 == 0) * 0x20;
  memset_bytes(param_1,0,0x38);
  pbVar2 = param_3 + param_4;
  WU(8) = 0xffffff;
  WU(0xc) = 0xffffffff;
  *(volatile unsigned char*)param_1 = (char)param_2;
  WU(0x20) = iVar5;
  WU(0x28) = (unsigned)param_3;
  WU(0x30) = (unsigned)param_3;
  WU(0x2c) = (unsigned)pbVar2;
  WU(0x34) = (unsigned)pbVar2;
  if (param_2 == 0) {
    uVar4 = 0;
    if (param_3 < pbVar2) {
      WU(0x30) = (unsigned)(param_3 + 1);
      uVar4 = (unsigned)*param_3 << 0x10;
      WU(4) = uVar4;
      if (param_3+1 < pbVar2) {
        WU(0x30) = (unsigned)(param_3+2);
        uVar4 = uVar4 | (unsigned)param_3[1] << 8;
        WU(4) = uVar4;
        if (param_3+2 < pbVar2) {
          WU(0x30) = (unsigned)(param_3+3);
          uVar4 = uVar4 | param_3[2];
        }
      }
    }
    iVar3 = iVar5 >> 3;
    if (param_4 <= iVar5 >> 3) iVar3 = param_4;
    uVar1 = iVar5 + iVar3 * -8;
    WU(4) = uVar4;
    WU(0x20) = uVar1;
    if (iVar3 != 0) {
      WU(0x34) = (unsigned)(pbVar2 + -1);
      uVar4 = (unsigned)pbVar2[-1] << 0x18;
      if (iVar3 != 1) {
        WU(0x1c) = uVar4 >> 8;
        WU(0x34) = (unsigned)(pbVar2 + -2);
        uVar4 = uVar4 >> 8 | (unsigned)pbVar2[-2] << 0x18;
        if (iVar3 != 2) {
          WU(0x1c) = uVar4 >> 8;
          WU(0x34) = (unsigned)(pbVar2 + -3);
          uVar4 = uVar4 >> 8 | (unsigned)pbVar2[-3] << 0x18;
          if (iVar3 != 3) {
            WU(0x1c) = uVar4 >> 8;
            WU(0x34) = (unsigned)(pbVar2 + -4);
            uVar4 = uVar4 >> 8 | (unsigned)pbVar2[-4] << 0x18;
          }
        }
      }
      WU(0x1c) = uVar4;
    }
    if (7 < (int)uVar1) {
      uVar4 = uVar1;
      if (0x1f < (int)uVar1) uVar4 = 0x20;
      WU(0x20) = 0;
      WU(0x24) = uVar4;
      WU(0x1c) = WU(0x1c) >> (uVar1 & 0xff);
    }
  }
  return;
}
