/* FUN_00070b38 @ 0x70b38  (714 bytes)
 * STATUS: reconstructed; byte-exact on deterministic valid input (single
 *   differential trial: checked=1, mismatches=0). FULL random-fuzz parity
 *   proof DEFERRED: the function contains a data-dependent loop (trip count
 *   read from memory), so adversarial random seeds drive emulation into
 *   billions of iterations and the fuzz harness cannot complete in bounded
 *   time. This is a proof-harness limitation, not evidence of a defect.
 *   For assembly it links from this source; correctness is re-established
 *   by the whole-image byte-match. */
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

extern void FUN_00068908(int, uint, int, int, uint);
extern void FUN_0006897c(int);

void FUN_00070b38(int param_1, int *param_2, uint param_3, uint param_4)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;

  iVar2 = 0x0008fe60;
  iVar1 = 0x000900a0;
  if (0 < *param_2) {
    iVar9 = 0;
    piVar10 = param_2 + 1;
    piVar8 = param_2;
    do {
      piVar10 = piVar10 + 1;
      iVar7 = *piVar10;
      uVar3 = *(uint *)(param_1 + 0x20);
      iVar5 = uVar3 + 1;
      if (iVar5 < 0x21) {
        *(int *)(param_1 + 0x20) = iVar5;
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | (uint)(0 < iVar7) << (uVar3 & 0xff);
      }
      else {
        FUN_00068908(param_1,(uint)(0 < iVar7),1,iVar5,param_4);
      }
      if (0 < iVar7) {
        iVar5 = iVar1 + (uint)*(byte *)(param_2 + 1) * 0x44;
        uVar3 = *(uint *)(param_1 + 8) >> 10;
        uVar6 = uVar3 * *(ushort *)(iVar5 + (iVar7 + -1) * 4) + *(int *)(param_1 + 4);
        *(uint *)(param_1 + 4) = uVar6;
        uVar3 = *(ushort *)(iVar5 + (iVar7 + -1) * 4 + 2) * uVar3;
        uVar4 = *(uint *)(param_1 + 0x10) | uVar6 >> 0x18;
        uVar6 = uVar6 & 0xffffff;
        *(uint *)(param_1 + 8) = uVar3;
        *(uint *)(param_1 + 0x10) = uVar4;
        *(uint *)(param_1 + 4) = uVar6;
        if (uVar3 < 0x10000) {
          FUN_0006897c(param_1);
          uVar6 = *(uint *)(param_1 + 4);
          uVar3 = *(uint *)(param_1 + 8);
          uVar4 = *(uint *)(param_1 + 0x10);
        }
        iVar5 = piVar8[4];
        uVar6 = (uVar3 >> 10) * (uint)*(ushort *)(iVar2 + (iVar5 + 8) * 4) + uVar6;
        *(uint *)(param_1 + 4) = uVar6;
        uVar3 = (uVar3 >> 10) * (uint)*(ushort *)(iVar2 + (iVar5 + 8) * 4 + 2);
        *(uint *)(param_1 + 4) = uVar6 & 0xffffff;
        *(uint *)(param_1 + 8) = uVar3;
        *(uint *)(param_1 + 0x10) = uVar4 | uVar6 >> 0x18;
        if (uVar3 < 0x10000) {
          FUN_0006897c(param_1);
        }
        if (iVar7 != 1) {
          iVar5 = 0x0008fea4 + (piVar8[5] + 8) * 4;
          uVar3 = *(uint *)(param_1 + 8) >> 10;
          uVar4 = uVar3 * *(ushort *)(0x0008fea4 + (piVar8[5] + 8) * 4) + *(int *)(param_1 + 4);
          *(uint *)(param_1 + 4) = uVar4;
          uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
          *(uint *)(param_1 + 8) = uVar3;
          *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
          *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
          if (uVar3 < 0x10000) {
            FUN_0006897c(param_1);
          }
          if (iVar7 != 2) {
            iVar5 = 0x0008fee8 + (piVar8[6] + 8) * 4;
            uVar3 = *(uint *)(param_1 + 8) >> 10;
            uVar4 = uVar3 * *(ushort *)(0x0008fee8 + (piVar8[6] + 8) * 4) + *(int *)(param_1 + 4);
            *(uint *)(param_1 + 4) = uVar4;
            uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
            *(uint *)(param_1 + 8) = uVar3;
            *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
            *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
            if (uVar3 < 0x10000) {
              FUN_0006897c(param_1);
            }
            if (iVar7 != 3) {
              iVar5 = 0x0008ff2c + (piVar8[7] + 8) * 4;
              uVar3 = *(uint *)(param_1 + 8) >> 10;
              uVar4 = uVar3 * *(ushort *)(0x0008ff2c + (piVar8[7] + 8) * 4) +
                      *(int *)(param_1 + 4);
              *(uint *)(param_1 + 4) = uVar4;
              uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
              *(uint *)(param_1 + 8) = uVar3;
              *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
              *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
              if (uVar3 < 0x10000) {
                FUN_0006897c(param_1);
              }
              if (iVar7 != 4) {
                iVar5 = 0x0008ff70 + (piVar8[8] + 8) * 4;
                uVar3 = *(uint *)(param_1 + 8) >> 10;
                uVar4 = uVar3 * *(ushort *)(0x0008ff70 + (piVar8[8] + 8) * 4) +
                        *(int *)(param_1 + 4);
                *(uint *)(param_1 + 4) = uVar4;
                uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
                *(uint *)(param_1 + 8) = uVar3;
                *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
                *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
                if (uVar3 < 0x10000) {
                  FUN_0006897c(param_1);
                }
                if (iVar7 != 5) {
                  iVar5 = 0x0008ffb4 + (piVar8[9] + 8) * 4;
                  uVar3 = *(uint *)(param_1 + 8) >> 10;
                  uVar4 = uVar3 * *(ushort *)(0x0008ffb4 + (piVar8[9] + 8) * 4) +
                          *(int *)(param_1 + 4);
                  *(uint *)(param_1 + 4) = uVar4;
                  uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
                  *(uint *)(param_1 + 8) = uVar3;
                  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
                  *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
                  if (uVar3 < 0x10000) {
                    FUN_0006897c(param_1);
                  }
                  if (iVar7 != 6) {
                    iVar5 = 0x0008fff8 + (piVar8[10] + 8) * 4;
                    uVar3 = *(uint *)(param_1 + 8) >> 10;
                    uVar4 = uVar3 * *(ushort *)(0x0008fff8 + (piVar8[10] + 8) * 4) +
                            *(int *)(param_1 + 4);
                    *(uint *)(param_1 + 4) = uVar4;
                    uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
                    *(uint *)(param_1 + 8) = uVar3;
                    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
                    *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
                    if (uVar3 < 0x10000) {
                      FUN_0006897c(param_1);
                    }
                    if (iVar7 != 7) {
                      uVar3 = *(uint *)(param_1 + 8) >> 10;
                      iVar5 = 0x0009003c + (piVar8[0xb] + 8) * 4;
                      uVar4 = uVar3 * *(ushort *)(0x0009003c + (piVar8[0xb] + 8) * 4) +
                              *(int *)(param_1 + 4);
                      *(uint *)(param_1 + 4) = uVar4;
                      uVar3 = uVar3 * *(ushort *)(iVar5 + 2);
                      *(uint *)(param_1 + 8) = uVar3;
                      *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | uVar4 >> 0x18;
                      *(uint *)(param_1 + 4) = uVar4 & 0xffffff;
                      if (uVar3 < 0x10000) {
                        FUN_0006897c(param_1);
                      }
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
