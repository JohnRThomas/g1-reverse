#include "g1_net_symbols.h"
/* net-core FUN_01039190 @ 0x1039190  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned int undefined4;
typedef int (*code)(int, int);

extern uint FUN_0103b5c4(undefined1 *s, uint n);
extern undefined1 *FUN_0103b5dc(uint v, undefined1 *buf, uint base);

undefined1 * FUN_01039190(int param_1,byte *param_2,uint *param_3)
{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  undefined4 uVar5;
  code pcVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  uint uVar12;
  undefined1 *puVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  byte *local_48;
  uint local_44;
  undefined1 auStack_35 [17];

  pcVar6 = *(code *)(param_1 + 4);
  if ((int)((uint)*(byte *)(param_1 + 2) << 0x1e) < 0) {
    puVar10 = (undefined1 *)0x0;
    do {
      while( 1 ) {
        uVar15 = (uint)*param_2;
        if (uVar15 == 0) {
          return puVar10;
        }
        if (uVar15 != 0x25) break;
        uVar15 = (uint)param_2[1];
        local_48 = param_2 + 2;
        if (uVar15 == 0x25) goto LAB_010391be;
        uVar16 = 0;
        uVar12 = 0;
        uVar4 = 0;
        puVar8 = param_3;
        do {
          uVar7 = uVar4;
          param_3 = puVar8;
          if (uVar12 < 0x20) {
            switch(uVar15) {
            default:
              if (9 < uVar15 - 0x30) goto LAB_01039210;
LAB_01039276:
              uVar12 = uVar12 | 0x20;
              uVar16 = uVar16 * 10 + (uVar15 - 0x30);
              break;
            case 0x23:
              uVar12 = uVar12 | 0x10;
              break;
            case 0x27:
              break;
            case 0x2b:
              uVar12 = uVar12 | 2;
            case 0x20:
              uVar12 = uVar12 | 4;
              break;
            case 0x2d:
              uVar12 = uVar12 | 8;
              break;
            case 0x30:
              uVar12 = uVar12 | 1;
            }
          }
          else if (uVar12 < 0x80) {
            if (uVar15 - 0x30 < 10) {
              if (-1 < (int)(uVar12 << 0x19)) goto LAB_01039276;
              uVar7 = uVar4 * 10 + (uVar15 - 0x30);
            }
            else {
LAB_01039210:
              if (uVar15 == 0x2a) {
                param_3 = puVar8 + 1;
                uVar15 = *puVar8;
                uVar7 = uVar15;
                if (-1 < (int)(uVar12 << 0x19)) {
                  if ((int)uVar15 < 0) {
                    uVar16 = -uVar15;
                    uVar12 = uVar12 | 0x28;
                    uVar7 = uVar4;
                  }
                  else {
                    uVar12 = uVar12 | 0x20;
                    uVar7 = uVar4;
                    uVar16 = uVar15;
                  }
                }
              }
              else {
                if (uVar15 != 0x2e) goto LAB_01039294;
                if ((int)(uVar12 << 0x19) < 0) {
                  return puVar10;
                }
                uVar12 = uVar12 | 0x40;
              }
            }
          }
          else {
LAB_01039294:
            if (uVar15 == 0x6c) {
              if ((int)(uVar12 << 0x18) < 0) {
                uVar12 = uVar12 | 0x200;
              }
              uVar12 = uVar12 | 0x80;
            }
            else if (uVar15 < 0x6d) {
              if (uVar15 != 0x68) {
                if ((uVar15 == 0x6a) || (uVar15 == 0x4c)) {
                  uVar12 = uVar12 | 0x280;
                  goto switchD_010391f2_caseD_27;
                }
                break;
              }
              if ((int)(uVar12 << 0x17) < 0) {
                uVar12 = uVar12 | 0x200;
              }
              uVar12 = uVar12 | 0x100;
            }
            else if ((uVar15 != 0x74) && (uVar15 != 0x7a)) break;
          }
switchD_010391f2_caseD_27:
          pbVar3 = local_48 + 1;
          uVar15 = (uint)*local_48;
          uVar4 = uVar7;
          puVar8 = param_3;
          local_48 = pbVar3;
        } while (uVar15 != 0);
        uVar4 = uVar15 | 0x20;
        if ((int)uVar7 < 0) {
          uVar12 = uVar12 & 0xffffffbf;
        }
        if ((int)uVar7 < 0) {
          uVar7 = 0;
        }
        if ((uVar4 - 0x65 < 3) || (uVar4 == 0x61)) {
          uVar15 = 7;
          puVar8 = (uint *)(((int)param_3 + 7U & 0xfffffff8) + 8);
          puVar11 = (undefined1 *)((unsigned long)&rodata_103ed18) /*=0x103ed18*/;
          goto LAB_010392da;
        }
        uVar17 = uVar7;
        uVar14 = uVar7;
        switch(uVar15) {
        case 99:
          puVar8 = param_3 + 1;
          uVar15 = 1;
          puVar11 = auStack_35 + 1;
          auStack_35[1] = (char)*param_3;
          goto LAB_010392da;
        case 100:
        case 0x69:
          if ((int)(uVar12 << 0x18) < 0) {
            if ((int)(uVar12 << 0x16) < 0) {
              puVar9 = (uint *)((int)param_3 + 7U & 0xfffffff8);
              puVar8 = puVar9 + 2;
              uVar4 = *puVar9;
            }
            else {
              puVar8 = param_3 + 1;
              uVar4 = *param_3;
            }
          }
          else {
            puVar8 = param_3 + 1;
            uVar4 = *param_3;
            if ((int)(uVar12 << 0x17) < 0) {
              if ((int)(uVar12 << 0x16) < 0) {
                uVar4 = (uint)(char)uVar4;
              }
              else {
                uVar4 = (uint)(short)uVar4;
              }
            }
          }
          local_44 = uVar12 & 0xffffffef;
          if ((int)uVar4 < 0) {
            uVar4 = -uVar4;
            local_44 = local_44 | 0x400;
LAB_010393ea:
            uVar5 = 10;
            goto LAB_010393f0;
          }
          if (((uVar4 != 0) || (-1 < (int)(uVar12 << 0x19))) || (uVar7 != 0)) goto LAB_010393ea;
          goto LAB_0103945c;
        default:
          if (uVar4 == 0x78) {
            if (uVar15 == 0x58) {
              uVar5 = 0x210;
            }
            else {
              uVar5 = 0x10;
            }
            break;
          }
          iVar1 = (*pcVar6)(0x25,param_1);
          if (iVar1 < 0) {
            return (undefined1 *)0xffffffff;
          }
          puVar10 = puVar10 + 2;
          goto LAB_010391c0;
        case 0x6f:
          uVar5 = 8;
          uVar15 = 0;
          break;
        case 0x70:
          uVar12 = uVar12 | 0x10;
          uVar5 = 0x10;
          uVar15 = 0x78;
          break;
        case 0x73:
          puVar8 = param_3 + 1;
          puVar11 = (undefined1 *)*param_3;
          if ((undefined1 *)*param_3 == (undefined1 *)0x0) {
            puVar11 = (undefined1 *)((unsigned long)&rodata_103ed11) /*=0x103ed11*/;
          }
          if ((uVar12 & 0x40) == 0) {
            uVar7 = 0xffffffff;
          }
          uVar15 = FUN_0103b5c4(puVar11,uVar7);
LAB_010392da:
          uVar4 = uVar16;
          if (-1 < (int)(uVar12 << 0x1c)) {
            for (; uVar15 < uVar4; uVar4 = uVar4 - 1) {
              iVar1 = (*pcVar6)(0x20,param_1);
              if (iVar1 < 0) {
                return (undefined1 *)0xffffffff;
              }
            }
            puVar10 = puVar10 + (uVar16 - uVar4);
          }
          puVar13 = puVar11;
          while (puVar13 != puVar11 + uVar15) {
            iVar1 = (*pcVar6)(*puVar13,param_1);
            puVar13 = puVar13 + 1;
            if (iVar1 < 0) {
              return (undefined1 *)0xffffffff;
            }
          }
          iVar1 = uVar4 - uVar15;
          puVar10 = puVar13 + ((int)puVar10 - (int)puVar11);
          puVar11 = puVar10;
          param_3 = puVar8;
          goto LAB_01039610;
        case 0x75:
          uVar12 = uVar12 & 0xffffffef;
          uVar5 = 10;
        }
        if ((int)(uVar12 << 0x18) < 0) {
          if ((int)(uVar12 << 0x16) < 0) {
            puVar9 = (uint *)((int)param_3 + 7U & 0xfffffff8);
            puVar8 = puVar9 + 2;
            uVar4 = *puVar9;
          }
          else {
            puVar8 = param_3 + 1;
            uVar4 = *param_3;
          }
        }
        else {
          puVar8 = param_3 + 1;
          uVar4 = *param_3;
          if ((int)(uVar12 << 0x17) < 0) {
            if ((int)(uVar12 << 0x16) < 0) {
              uVar4 = uVar4 & 0xff;
            }
            else {
              uVar4 = uVar4 & 0xffff;
            }
          }
        }
        if (uVar4 == 0) {
          local_44 = uVar12 & 0xffffffe9;
          if ((-1 < (int)(uVar12 << 0x19)) || (uVar7 != 0)) goto LAB_010393f0;
          uVar4 = uVar12 & 0xffffffe8;
LAB_01039498:
          local_44 = uVar4 & 0x10;
          uVar17 = uVar14;
          if (local_44 == 0) {
LAB_01039422:
            local_44 = uVar4 & 0x406;
            if (local_44 != 0) {
              uVar17 = uVar17 + 1;
              local_44 = 0;
            }
          }
          else {
            if (uVar15 != 0) goto LAB_0103952a;
            uVar17 = uVar14 + 1;
          }
        }
        else {
          local_44 = uVar12 & 0xfffffff9;
LAB_010393f0:
          iVar1 = (int)FUN_0103b5dc(uVar4,auStack_35 + 1,uVar5);
          uVar14 = iVar1 - (int)(auStack_35 + 1);
          uVar4 = local_44;
          if ((-1 < (int)(local_44 << 0x19)) ||
             (uVar4 = local_44 & 0xfffffffe, (int)uVar7 <= (int)uVar14)) goto LAB_01039498;
          uVar12 = local_44;
          if (uVar15 == 0) {
LAB_0103945c:
            uVar4 = uVar12 & 0xffffffee;
            goto LAB_01039422;
          }
          local_44 = local_44 & 0x10;
          if (local_44 == 0) goto LAB_01039422;
LAB_0103952a:
          uVar17 = uVar17 + 2;
        }
        if (-1 < (int)(uVar4 << 0x1c)) {
          uVar12 = uVar17;
          if (((int)(uVar4 << 0x1f) < 0) && (uVar7 = uVar14, (int)uVar17 < (int)uVar16)) {
            iVar1 = uVar16 - uVar17;
            uVar17 = uVar16;
            uVar12 = uVar16;
            uVar7 = iVar1 + uVar14;
          }
          for (; (int)uVar17 < (int)uVar16; uVar17 = uVar17 + 1) {
            iVar1 = (*pcVar6)(0x20,param_1);
            if (iVar1 < 0) {
              return (undefined1 *)0xffffffff;
            }
          }
          puVar10 = puVar10 + (uVar17 - uVar12);
        }
        if (local_44 == 0) {
          puVar11 = puVar10;
          if ((uVar4 & 0x406) != 0) {
            puVar10 = puVar10 + 1;
            if ((uVar4 & 2) == 0) {
              uVar15 = 0x20;
            }
            else {
              uVar15 = 0x2b;
            }
            if ((uVar4 & 0x400) != 0) {
              uVar15 = 0x2d;
            }
            goto LAB_010395ae;
          }
        }
        else {
          iVar1 = (*pcVar6)(0x30,param_1);
          if (iVar1 < 0) {
            return (undefined1 *)0xffffffff;
          }
          if (uVar15 != 0) {
            puVar10 = puVar10 + 2;
LAB_010395ae:
            iVar1 = (*pcVar6)(uVar15,param_1);
            puVar11 = puVar10;
            goto joined_r0x010395b6;
          }
          puVar10 = puVar10 + 1;
          puVar11 = puVar10;
        }
        while (uVar15 = uVar14, (int)uVar14 < (int)(puVar11 + (uVar7 - (int)puVar10))) {
          puVar10 = puVar10 + 1;
          iVar1 = (*pcVar6)(0x30,param_1);
joined_r0x010395b6:
          if (iVar1 < 0) {
            return (undefined1 *)0xffffffff;
          }
        }
        while (uVar15 != 0) {
          iVar1 = (*pcVar6)(auStack_35[uVar15],param_1);
          uVar15 = uVar15 - 1;
          if (iVar1 < 0) {
            return (undefined1 *)0xffffffff;
          }
        }
        puVar10 = puVar10 + uVar14;
        iVar1 = uVar16 - uVar17;
        puVar11 = puVar10;
        param_3 = puVar8;
LAB_01039610:
        while (param_2 = local_48, 0 < (int)(puVar11 + (iVar1 - (int)puVar10))) {
          puVar10 = puVar10 + 1;
          iVar2 = (*pcVar6)(0x20,param_1);
          if (iVar2 < 0) {
            return (undefined1 *)0xffffffff;
          }
        }
      }
      local_48 = param_2 + 1;
LAB_010391be:
      puVar10 = puVar10 + 1;
LAB_010391c0:
      iVar1 = (*pcVar6)(uVar15,param_1);
      param_2 = local_48;
    } while (-1 < iVar1);
  }
  return (undefined1 *)0xffffffff;
}
