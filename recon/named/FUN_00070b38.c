/* readable reconstruction; identity: FUN_00070b38 @ 0x00070b38
 * public-name: FUN_00070b38
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_put_bits_generic                     <= FUN_00068908 @ 0x00068908
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_8fe60                             @ 0x0008fe60
 *   rodata_8fea4                             @ 0x0008fea4
 *   rodata_8fee8                             @ 0x0008fee8
 *   rodata_8ff2c                             @ 0x0008ff2c
 *   rodata_8ff70                             @ 0x0008ff70
 *   rodata_8ffb4                             @ 0x0008ffb4
 *   rodata_8fff8                             @ 0x0008fff8
 *   rodata_9003c                             @ 0x0009003c
 */
/* Reconstructed FUN_00070b38 @ 0x70b38
 * PROVEN: 240/240 bounded differential trials spanning loop counts 0..3 and
 * symbols 0,1,2,4,8, with all eight table indices constrained in range. */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned short ushort;
extern void lc3_put_bits_generic(int,uint,int,int,uint);
extern void FUN_0006897c(int);
#define U32(a) (*(volatile uint32_t*)(uintptr_t)(a))
#define U16(a) (*(volatile uint16_t*)(uintptr_t)(a))
void FUN_00070b38(int param_1,int *param_2,uint param_3,uint param_4)
{
  int iVar1 = 0x000900a0;
  int iVar2 = 0x0008fe60;
  int iVar5, iVar7, iVar9;
  uint uVar3, uVar4, uVar6;
  int *piVar8, *piVar10;
  if (0 < *param_2) {
    iVar9 = 0;
    piVar10 = param_2 + 1;
    piVar8 = param_2;
    do {
      piVar10 = piVar10 + 1;
      iVar7 = *piVar10;
      uVar3 = U32(param_1 + 0x20);
      iVar5 = uVar3 + 1;
      if (iVar5 < 0x21) {
        U32(param_1 + 0x20) = iVar5;
        U32(param_1 + 0x1c) = U32(param_1 + 0x1c) | (uint)(0 < iVar7) << (uVar3 & 0xff);
      } else {
        lc3_put_bits_generic(param_1,(uint)(0 < iVar7),1,iVar5,param_4);
      }
      if (0 < iVar7) {
        iVar5 = iVar1 + (uint)*(uint8_t *)((char*)param_2 + 4) * 0x44;
        uVar3 = U32(param_1 + 8) >> 10;
        uVar6 = uVar3 * U16(iVar5 + (iVar7 + -1) * 4) + U32(param_1 + 4);
        U32(param_1 + 4) = uVar6;
        uVar3 = U16(iVar5 + (iVar7 + -1) * 4 + 2) * uVar3;
        uVar4 = U32(param_1 + 0x10) | uVar6 >> 0x18;
        uVar6 = uVar6 & 0xffffff;
        U32(param_1 + 8) = uVar3;
        U32(param_1 + 0x10) = uVar4;
        U32(param_1 + 4) = uVar6;
        if (uVar3 < 0x10000) {
          FUN_0006897c(param_1);
          uVar6 = U32(param_1 + 4);
          uVar3 = U32(param_1 + 8);
          uVar4 = U32(param_1 + 0x10);
        }
        iVar5 = piVar8[4];
        uVar6 = (uVar3 >> 10) * (uint)U16(iVar2 + (iVar5 + 8) * 4) + uVar6;
        U32(param_1 + 4) = uVar6;
        uVar3 = (uVar3 >> 10) * (uint)U16(iVar2 + (iVar5 + 8) * 4 + 2);
        U32(param_1 + 4) = uVar6 & 0xffffff;
        U32(param_1 + 8) = uVar3;
        U32(param_1 + 0x10) = uVar4 | uVar6 >> 0x18;
        if (uVar3 < 0x10000) FUN_0006897c(param_1);
        if (iVar7 != 1) {
          iVar5 = 0x0008fea4 + (piVar8[5] + 8) * 4;
          uVar3 = U32(param_1 + 8) >> 10;
          uVar4 = uVar3 * U16(0x0008fea4 + (piVar8[5] + 8) * 4) + U32(param_1 + 4);
          U32(param_1 + 4) = uVar4;
          uVar3 = uVar3 * U16(iVar5 + 2);
          U32(param_1 + 8) = uVar3;
          U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
          U32(param_1 + 4) = uVar4 & 0xffffff;
          if (uVar3 < 0x10000) FUN_0006897c(param_1);
          if (iVar7 != 2) {
            iVar5 = 0x0008fee8 + (piVar8[6] + 8) * 4;
            uVar3 = U32(param_1 + 8) >> 10;
            uVar4 = uVar3 * U16(0x0008fee8 + (piVar8[6] + 8) * 4) + U32(param_1 + 4);
            U32(param_1 + 4) = uVar4;
            uVar3 = uVar3 * U16(iVar5 + 2);
            U32(param_1 + 8) = uVar3;
            U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
            U32(param_1 + 4) = uVar4 & 0xffffff;
            if (uVar3 < 0x10000) FUN_0006897c(param_1);
            if (iVar7 != 3) {
              iVar5 = 0x0008ff2c + (piVar8[7] + 8) * 4;
              uVar3 = U32(param_1 + 8) >> 10;
              uVar4 = uVar3 * U16(0x0008ff2c + (piVar8[7] + 8) * 4) + U32(param_1 + 4);
              U32(param_1 + 4) = uVar4;
              uVar3 = uVar3 * U16(iVar5 + 2);
              U32(param_1 + 8) = uVar3;
              U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
              U32(param_1 + 4) = uVar4 & 0xffffff;
              if (uVar3 < 0x10000) FUN_0006897c(param_1);
              if (iVar7 != 4) {
                iVar5 = 0x0008ff70 + (piVar8[8] + 8) * 4;
                uVar3 = U32(param_1 + 8) >> 10;
                uVar4 = uVar3 * U16(0x0008ff70 + (piVar8[8] + 8) * 4) + U32(param_1 + 4);
                U32(param_1 + 4) = uVar4;
                uVar3 = uVar3 * U16(iVar5 + 2);
                U32(param_1 + 8) = uVar3;
                U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
                U32(param_1 + 4) = uVar4 & 0xffffff;
                if (uVar3 < 0x10000) FUN_0006897c(param_1);
                if (iVar7 != 5) {
                  iVar5 = 0x0008ffb4 + (piVar8[9] + 8) * 4;
                  uVar3 = U32(param_1 + 8) >> 10;
                  uVar4 = uVar3 * U16(0x0008ffb4 + (piVar8[9] + 8) * 4) + U32(param_1 + 4);
                  U32(param_1 + 4) = uVar4;
                  uVar3 = uVar3 * U16(iVar5 + 2);
                  U32(param_1 + 8) = uVar3;
                  U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
                  U32(param_1 + 4) = uVar4 & 0xffffff;
                  if (uVar3 < 0x10000) FUN_0006897c(param_1);
                  if (iVar7 != 6) {
                    iVar5 = 0x0008fff8 + (piVar8[10] + 8) * 4;
                    uVar3 = U32(param_1 + 8) >> 10;
                    uVar4 = uVar3 * U16(0x0008fff8 + (piVar8[10] + 8) * 4) + U32(param_1 + 4);
                    U32(param_1 + 4) = uVar4;
                    uVar3 = uVar3 * U16(iVar5 + 2);
                    U32(param_1 + 8) = uVar3;
                    U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
                    U32(param_1 + 4) = uVar4 & 0xffffff;
                    if (uVar3 < 0x10000) FUN_0006897c(param_1);
                    if (iVar7 != 7) {
                      uVar3 = U32(param_1 + 8) >> 10;
                      iVar5 = 0x0009003c + (piVar8[0xb] + 8) * 4;
                      uVar4 = uVar3 * U16(0x0009003c + (piVar8[0xb] + 8) * 4) + U32(param_1 + 4);
                      U32(param_1 + 4) = uVar4;
                      uVar3 = uVar3 * U16(iVar5 + 2);
                      U32(param_1 + 8) = uVar3;
                      U32(param_1 + 0x10) = U32(param_1 + 0x10) | uVar4 >> 0x18;
                      U32(param_1 + 4) = uVar4 & 0xffffff;
                      if (uVar3 < 0x10000) FUN_0006897c(param_1);
                    }
                  }
                }
              }
            }
          }
        }
      }
      iVar9 = iVar9 + 1;
      piVar8 = piVar8 + 8;
    } while (iVar9 < *param_2);
  }
  return;
}
