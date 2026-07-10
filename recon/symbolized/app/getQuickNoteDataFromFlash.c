#include "g1_app_symbols.h"
/* named: getQuickNoteDataFromFlash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed getQuickNoteDataFromFlash @ 0x24534  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(void);
extern int z_device_is_ready(unsigned);
extern void memcpy(unsigned,int,int);
extern void memset_bytes(unsigned,int,int);

unsigned getQuickNoteDataFromFlash(unsigned param_1, unsigned param_2, int param_3, unsigned param_4, int param_5){
  volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  int iVar7; unsigned uVar4; unsigned uVar5 = 0;
  if(param_1 >= 4){
    if(*piVar1 < 1) return 0xffffffff;
    iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar4 = "%s(): quicknote upgrade index out of range\n" /*=0x9ee54*/;
    goto LAB_2arg;
  }
  if(*piVar1 > 2){
    if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
      DEBUG_PRINT("%s(): read quicknote flash data to ram...\r\n\n" /*=0x9ee80*/,"getQuickNoteDataFromFlash" /*=0x9f066*/);
    else
      debug_print();
  }
  {
    int iVar3 = z_device_is_ready(((uintptr_t)&tbl_87b30) /*=0x87bf0*/);
    iVar7 = (g_quicknote_flash_page_buf) /*=0x20018465*/;
    if(iVar3 == 0){
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
      uVar4 = "%s():  [%s] device not ready.\n\n" /*=0x9e9ea*/;
      uVar5 = *(volatile uint32_t*)((uintptr_t)&tbl_87b30) /*=0x87bf0*/;
    } else {
      memset_bytes((g_quicknote_flash_page_buf) /*=0x20018465*/,0,0x800);
      int t = get_device_info();
      int (*pcVar8)(unsigned,unsigned,int,int) = *(int(**)(unsigned,unsigned,int,int))(t+0x1030);
      unsigned a = get_device_info();
      iVar3 = pcVar8(a, 0x00403000, iVar7, 0x800);
      if(iVar3 == 0){
        int off = (int)(param_1 * 0x200);
        if(*(char*)(iVar7 + off) == -0x56){
          if(param_3 > 0x28) param_3 = 0x29;
          memcpy(param_2, off + 1 + iVar7, param_3);
          int iVar6 = 0x119;
          if(param_5 < 0x11a) iVar6 = param_5;
          memcpy(param_4, off + 0x2a + iVar7, iVar6);
          if(*piVar1 > 2){
            if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
              DEBUG_PRINT("%s(): export flash data to global ram...\n" /*=0x9eeeb*/,"getQuickNoteDataFromFlash" /*=0x9f066*/);
              return 0;
            }
            debug_print();
            return 0;
          }
          return 0;
        }
        if(*piVar1 < 3) return 0xffffffff;
        iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar4 = "%s(): quicknote data is invaild,don't export to global ram..\n" /*=0x9eead*/;
        goto LAB_2arg;
      }
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
      uVar4 = "%s():  form address [%d] read data failed.\n\n" /*=0x9ea0a*/;
      uVar5 = 0x00403000;
    }
    if(iVar7 == 0)
      DEBUG_PRINT(uVar4, "getQuickNoteDataFromFlash" /*=0x9f066*/, uVar5);
    else
      debug_print();
    return 0xffffffff;
  }
LAB_2arg:
  if(iVar7 == 0)
    DEBUG_PRINT(uVar4, "getQuickNoteDataFromFlash" /*=0x9f066*/);
  else
    debug_print();
  return 0xffffffff;
}

