/* named: write_font_to_flash_with_verify */
/* Reconstructed write_font_to_flash_with_verify @ 0x22834  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int FUN_00074844(int,int);
extern int z_device_is_ready(int);
extern int memcmp(int,int,int);
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
  uVar2 = 0x9e430;
  puVar1 = (unsigned int*)0x87bf0;
  do {
    iVar3 = z_device_is_ready(0x87bf0);
    if (iVar3 == 0) {
      DEBUG_PRINT(0xa40ec, *(volatile unsigned int*)puVar1);
      iVar3 = -1;
    } else {
      iVar3 = get_device_info();
      pcVar5 = *(codeptr*)(iVar3 + 0x1030);
      uVar4 = get_device_info();
      iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
      if (iVar3 == 0) {
        iVar3 = memcmp(param_2, (int)&local_1028, param_3);
        if (iVar3 == 0) {
          DEBUG_PRINT(0x9e403);
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
          uVar4 = 0x9e44d;
          if (iVar3 == 0) {
            iVar3 = get_device_info();
            pcVar5 = *(codeptr*)(iVar3 + 0x1030);
            uVar4 = get_device_info();
            iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
            uVar4 = 0x9e3e7;
            if (iVar3 == 0) {
              iVar3 = memcmp(param_2, (int)&local_1028, param_3);
              if (iVar3 == 0) {
                return 0;
              }
              DEBUG_PRINT(0x9e46a);
              iVar3 = 1;
              goto LAB_874;
            }
          }
        }
        DEBUG_PRINT(uVar4, iVar3);
      } else {
        DEBUG_PRINT(0x9e3e7, iVar3);
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

