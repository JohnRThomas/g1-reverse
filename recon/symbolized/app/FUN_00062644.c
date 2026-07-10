#include "g1_app_symbols.h"
/* named: FUN_00062644 */
/* Reconstructed FUN_00062644 @ 0x62644  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
typedef unsigned long long undefined8;
extern int __floatunsidf(int,...); extern unsigned long long __extendsfdf2(float);
extern int __muldf3(int,...); extern int __fixunsdfsi(int,...);
extern unsigned long long FUN_00012c80(unsigned long long); extern int dev_write_reg3(int,...);
extern int dev_write_reg4(int,...); extern int FUN_00084602(int,...);
extern int FUN_00084774(int,...); extern int z_device_is_ready(int,...);

int FUN_00062644(int param_1)
{
  float fVar1,fVar2,fVar3; int iVar4; unsigned long long uVar5; uint uVar6; int iVar7;
  int *puVar8; char cVar9; int *piVar10; unsigned long long uVar11, uVar12; ushort local_32[3];
  const uint32_t c1=0x49742400u,c2=0x43889333u,c3=0x3b5bcf0fu;
  puVar8 = *(int **)(param_1 + 4);
  iVar4 = z_device_is_ready(*puVar8);
  if (iVar4 == 0) { iVar4 = -0x13; }
  else {
    iVar4 = dev_write_reg3(*puVar8,5,10,*(char *)((int)puVar8 + 0x2e) + 1);
    __builtin_memcpy(&fVar3,&c3,4); __builtin_memcpy(&fVar2,&c2,4); __builtin_memcpy(&fVar1,&c1,4);
    if (iVar4 == 0) {
      cVar9 = 0x10; piVar10 = puVar8 + 5;
      do {
        piVar10 = piVar10 + 1;
        if (*piVar10 != 0x7fffffff) {
          uVar5 = __extendsfdf2((1.0f / ((float)*piVar10 / fVar1 + fVar2) - fVar3) *
                               (float)(uint)*(ushort *)((int)puVar8 + 0x2c));
          iVar7 = puVar8[10];
          uVar11 = FUN_00012c80(uVar5);
          uVar12 = __floatunsidf(iVar7);
          __muldf3((int)uVar12,(int)(uVar12 >> 0x20),(int)uVar11,(int)(uVar11 >> 0x20));
          iVar4 = __fixunsdfsi(0);
          uVar6 = (uint)(iVar4 << 10) / (uint)(iVar7 + iVar4);
          iVar4 = dev_write_reg4(*puVar8,3,cVar9,(uVar6 << 0x16) >> 0x18,uVar6 & 3);
          if (iVar4 != 0) return iVar4;
        }
        cVar9 = cVar9 + 2;
      } while (cVar9 != 0x18);
      iVar4 = FUN_00084774(((uintptr_t)&tbl_8ba64) /*=0x8ba94*/,puVar8[1],puVar8[1],(int)local_32);
      if (iVar4 != -0x16) {
        iVar4 = dev_write_reg3(*puVar8,3,0xc,(byte)local_32[0]);
        if (iVar4 != 0) return iVar4;
        iVar4 = FUN_00084774(((uintptr_t)&tbl_8ba64) /*=0x8ba94*/,puVar8[2],puVar8[2],(int)local_32);
        if (iVar4 != -0x16) {
          iVar4 = dev_write_reg3(*puVar8,3,0xd,(byte)local_32[0]);
          if (iVar4 != 0) return iVar4;
          iVar4 = FUN_00084602(((uintptr_t)&tbl_8ba64) /*=0x8ba88*/,puVar8[3] + -2000,puVar8[3],(int)local_32);
          if (iVar4 != -0x16) {
            iVar4 = dev_write_reg4(*puVar8,3,8,((uint)local_32[0] << 0x17) >> 0x18,local_32[0] & 1);
            if (iVar4 != 0) return iVar4;
            iVar4 = FUN_00084602(((uintptr_t)&tbl_8ba64) /*=0x8ba7c*/,puVar8[4] + -0xc9e,puVar8[4],(int)local_32);
            if (iVar4 != -0x16) {
              iVar4 = dev_write_reg4(*puVar8,3,10,((uint)local_32[0] << 0x17) >> 0x18,local_32[0] & 1);
              if (iVar4 != 0) return iVar4;
              iVar4 = FUN_00084774(((uintptr_t)&tbl_8ba64) /*=0x8ba64*/,puVar8[5],puVar8[5],(int)local_32);
              if (iVar4 != -0x16) {
                iVar4 = dev_write_reg3(*puVar8,2,2,(byte)local_32[0]);
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,3,0xe,*(byte *)((int)puVar8 + 0x2f));
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,3,0xf,*(byte *)((int)puVar8 + 0x30));
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,5,0x24,1);
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,5,0,1);
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,5,1);
                if (iVar4 != 0) return iVar4;
                iVar4 = dev_write_reg3(*puVar8,5,0xc,1);
                if (iVar4 != 0) return iVar4;
                if ((*(char *)((int)puVar8 + 0x32) != 0) &&
                   (iVar4 = dev_write_reg3(*puVar8,3,0x50,1), iVar4 != 0)) return iVar4;
                if ((*(char *)((int)puVar8 + 0x33) != 0) &&
                   (iVar4 = dev_write_reg3(*puVar8,3,6,1), iVar4 != 0)) return iVar4;
                if (*(char *)((int)puVar8 + 0x31) == 0) return 0;
                iVar4 = dev_write_reg3(*puVar8,3,4,1);
                return iVar4;
              }
            }
          }
        }
      }
      iVar4 = -0x16;
    }
  }
  return iVar4;
}

