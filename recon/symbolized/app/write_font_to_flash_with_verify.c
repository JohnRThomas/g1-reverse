#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00022834 @ 0x00022834
 * public-name: write_font_to_flash_with_verify
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   write_font_to_flash_with_verify          <= FUN_00022834 @ 0x00022834
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e3e7                             @ 0x0009e3e7
 *   rodata_9e403                             @ 0x0009e403
 *   rodata_9e430                             @ 0x0009e430
 *   rodata_9e44d                             @ 0x0009e44d
 *   rodata_9e46a                             @ 0x0009e46a
 *   rodata_a40ec                             @ 0x000a40ec
 */
/* Reconstructed FUN_00022834 @ 0x22834  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int log_message(int,...);
extern int get_device_info(void);
extern int FUN_00074844(int,int);
extern int z_device_is_ready(int);
extern int FUN_00086be4(int,int,int);
extern int memset_bytes(void*,int,int);

int write_font_to_flash_with_verify(int param_1, int param_2, int param_3)
{
  unsigned int *puVar1;
  int uVar2;
  int iVar3;
  int uVar4;
  codeptr pcVar5;
  int iVar6;
  int local_1028;
  unsigned char auStack_1024[4096];

  local_1028 = 0;
  iVar6 = 1;
  memset_bytes(auStack_1024, 0, 0xffc);
  uVar2 = ((unsigned long)&rodata_9e430) /*=0x9e430*/;
  puVar1 = (unsigned int*)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
  do {
    iVar3 = z_device_is_ready(((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
    if (iVar3 == 0) {
      log_message(((unsigned long)&rodata_a40ec) /*=0xa40ec*/, *(volatile unsigned int*)puVar1);
      iVar3 = -1;
    } else {
      iVar3 = get_device_info();
      pcVar5 = *(codeptr*)(iVar3 + 0x1030);
      uVar4 = get_device_info();
      iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
      if (iVar3 == 0) {
        iVar3 = FUN_00086be4(param_2, (int)&local_1028, param_3);
        if (iVar3 == 0) {
          log_message(((unsigned long)&rodata_9e403) /*=0x9e403*/);
          return 0;
        }
        iVar3 = get_device_info();
        pcVar5 = *(codeptr*)(iVar3 + 0x1038);
        uVar4 = get_device_info();
        iVar3 = (*pcVar5)(uVar4, param_1, 0x1000);
        uVar4 = uVar2;
        if (iVar3 == 0) {
          iVar3 = get_device_info();
          pcVar5 = *(codeptr*)(iVar3 + 0x1034);
          uVar4 = get_device_info();
          iVar3 = (*pcVar5)(uVar4, param_1, param_2, param_3);
          uVar4 = ((unsigned long)&rodata_9e44d) /*=0x9e44d*/;
          if (iVar3 == 0) {
            iVar3 = get_device_info();
            pcVar5 = *(codeptr*)(iVar3 + 0x1030);
            uVar4 = get_device_info();
            iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
            uVar4 = ((unsigned long)&rodata_9e3e7) /*=0x9e3e7*/;
            if (iVar3 == 0) {
              iVar3 = FUN_00086be4(param_2, (int)&local_1028, param_3);
              if (iVar3 == 0) {
                return 0;
              }
              log_message(((unsigned long)&rodata_9e46a) /*=0x9e46a*/);
              iVar3 = 1;
              goto LAB_874;
            }
          }
        }
        log_message(uVar4, iVar3);
      } else {
        log_message(((unsigned long)&rodata_9e3e7) /*=0x9e3e7*/, iVar3);
      }
    }
LAB_874:
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xb) {
      return iVar3;
    }
    FUN_00074844(0xccd, 0);
  } while (1);
}
