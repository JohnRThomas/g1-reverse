/* readable reconstruction; identity: FUN_00062644 @ 0x00062644
 * public-name: panel_temp_calibration_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __floatunsidf                            <= FUN_0000d804 @ 0x0000d804
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __fixunsdfsi                             <= FUN_0000dea8 @ 0x0000dea8
 *   exp                                      <= FUN_00012c80 @ 0x00012c80
 *   panel_temp_calibration_init              <= FUN_00062644 @ 0x00062644
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_write_reg4                           <= FUN_00083de6 @ 0x00083de6
 *   flash_page_index_lookup                  <= FUN_00084602 @ 0x00084602
 *   layout_select_region                     <= FUN_00084774 @ 0x00084774
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_8ba64                             @ 0x0008ba64
 *   rodata_8ba7c                             @ 0x0008ba7c
 *   rodata_8ba88                             @ 0x0008ba88
 *   rodata_8ba94                             @ 0x0008ba94
 */
/* Reconstructed FUN_00062644 @ 0x62644  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
typedef unsigned long long undefined8;
extern int __floatunsidf(int,...); extern unsigned long long __extendsfdf2(float);
extern int __muldf3(int,...); extern int __fixunsdfsi(int,...);
extern unsigned long long exp(unsigned long long); extern int dev_write_reg3(int,...);
extern int dev_write_reg4(int,...); extern int flash_page_index_lookup(int,...);
extern int layout_select_region(int,...); extern int z_device_is_ready(int,...);

int panel_temp_calibration_init(int param_1)
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
          uVar11 = exp(uVar5);
          uVar12 = __floatunsidf(iVar7);
          __muldf3((int)uVar12,(int)(uVar12 >> 0x20),(int)uVar11,(int)(uVar11 >> 0x20));
          iVar4 = __fixunsdfsi(0);
          uVar6 = (uint)(iVar4 << 10) / (uint)(iVar7 + iVar4);
          iVar4 = dev_write_reg4(*puVar8,3,cVar9,(uVar6 << 0x16) >> 0x18,uVar6 & 3);
          if (iVar4 != 0) return iVar4;
        }
        cVar9 = cVar9 + 2;
      } while (cVar9 != 0x18);
      iVar4 = layout_select_region(0x8ba94,puVar8[1],puVar8[1],(int)local_32);
      if (iVar4 != -0x16) {
        iVar4 = dev_write_reg3(*puVar8,3,0xc,(byte)local_32[0]);
        if (iVar4 != 0) return iVar4;
        iVar4 = layout_select_region(0x8ba94,puVar8[2],puVar8[2],(int)local_32);
        if (iVar4 != -0x16) {
          iVar4 = dev_write_reg3(*puVar8,3,0xd,(byte)local_32[0]);
          if (iVar4 != 0) return iVar4;
          iVar4 = flash_page_index_lookup(0x8ba88,puVar8[3] + -2000,puVar8[3],(int)local_32);
          if (iVar4 != -0x16) {
            iVar4 = dev_write_reg4(*puVar8,3,8,((uint)local_32[0] << 0x17) >> 0x18,local_32[0] & 1);
            if (iVar4 != 0) return iVar4;
            iVar4 = flash_page_index_lookup(0x8ba7c,puVar8[4] + -0xc9e,puVar8[4],(int)local_32);
            if (iVar4 != -0x16) {
              iVar4 = dev_write_reg4(*puVar8,3,10,((uint)local_32[0] << 0x17) >> 0x18,local_32[0] & 1);
              if (iVar4 != 0) return iVar4;
              iVar4 = layout_select_region(0x8ba64,puVar8[5],puVar8[5],(int)local_32);
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
