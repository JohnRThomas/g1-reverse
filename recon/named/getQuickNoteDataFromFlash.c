/* readable reconstruction; identity: FUN_00024534 @ 0x00024534
 * public-name: getQuickNoteDataFromFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   getQuickNoteDataFromFlash                <= FUN_00024534 @ 0x00024534
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9ee54                             @ 0x0009ee54
 *   rodata_9ee80                             @ 0x0009ee80
 *   rodata_9eeeb                             @ 0x0009eeeb
 *   rodata_9f066                             @ 0x0009f066
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_quicknote_flash_page_buf               @ 0x20018465
 */
/* Reconstructed FUN_00024534 @ 0x24534  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned,...);
extern int z_device_is_ready(unsigned);
extern void memcpy(unsigned,int,int);
extern void memset_bytes(unsigned,int,int);

unsigned getQuickNoteDataFromFlash(unsigned param_1, unsigned param_2, int param_3, unsigned param_4, int param_5){
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  int iVar7; unsigned uVar4; unsigned uVar5 = 0;
  if(param_1 >= 4){
    if(*piVar1 < 1) return 0xffffffff;
    iVar7 = *(volatile int*)0x20007554UL;
    uVar4 = 0x0009ee54;
    goto LAB_2arg;
  }
  if(*piVar1 > 2){
    if(*(volatile int*)0x20007554UL == 0)
      DEBUG_PRINT(0x0009ee80,0x0009f066);
    else
      debug_print(0x0009ee80,0x0009f066);
  }
  {
    int iVar3 = z_device_is_ready(0x00087bf0);
    iVar7 = 0x20018465;
    if(iVar3 == 0){
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)0x20007554UL;
      uVar4 = 0x0009e9ea;
      uVar5 = *(volatile uint32_t*)0x00087bf0UL;
    } else {
      memset_bytes(0x20018465,0,0x800);
      int t = get_device_info();
      int (*pcVar8)(unsigned,unsigned,int,int) = *(int(**)(unsigned,unsigned,int,int))(t+0x1030);
      unsigned a = get_device_info();
      iVar3 = pcVar8(a, 0x00403000, iVar7, 0x800);
      if(iVar3 == 0){
        int off = (int)(param_1 * 0x200);
        if(*(volatile uint8_t*)(iVar7 + off) == 0xaa){
          if(param_3 > 0x28) param_3 = 0x29;
          memcpy(param_2, off + 1 + iVar7, param_3);
          int iVar6 = 0x119;
          if(param_5 < 0x11a) iVar6 = param_5;
          memcpy(param_4, off + 0x2a + iVar7, iVar6);
          if(*piVar1 > 2){
            if(*(volatile int*)0x20007554UL == 0){
              DEBUG_PRINT(0x0009eeeb,0x0009f066);
              return 0;
            }
            debug_print(0x0009eeeb,0x0009f066);
            return 0;
          }
          return 0;
        }
        if(*piVar1 < 3) return 0xffffffff;
        iVar7 = *(volatile int*)0x20007554UL;
        uVar4 = 0x0009eead;
        goto LAB_2arg;
      }
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)0x20007554UL;
      uVar4 = 0x0009ea0a;
      uVar5 = 0x00403000;
    }
    if(iVar7 == 0)
      DEBUG_PRINT(uVar4, 0x0009f066, uVar5);
    else
      debug_print(uVar4,0x0009f066,uVar5);
    return 0xffffffff;
  }
LAB_2arg:
  if(iVar7 == 0)
    DEBUG_PRINT(uVar4, 0x0009f066);
  else
    debug_print(uVar4,0x0009f066);
  return 0xffffffff;
}
