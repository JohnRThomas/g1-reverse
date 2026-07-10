#include "g1_app_symbols.h"
/* named: find_chinese_bitmap_by_unicode */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed find_chinese_bitmap_by_unicode @ 0x4792c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(int,...);
extern int debug_print(int,...);
extern int expand_bytes_via_lut32(int,...);
extern int FUN_0007d84c(int,...);
extern int memset_bytes(int,...);
typedef int (*codeptr)(int,...);
unsigned int find_chinese_bitmap_by_unicode(unsigned int param_1, short param_2, short param_3)
{
  unsigned int uVar1 = 0;
  int iVar2;
  volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  volatile int *E = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  unsigned char dummy[16];
  unsigned short lh[4];
  unsigned int uVar3 = ((int)param_2 * (int)param_3) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  if (param_1 - 0x20 < 0x60) {
    uVar1 = (unsigned int)FUN_0007d84c(param_1 & 0xff, uVar3);
  } else {
    iVar2 = get_device_info(0);
    if (*(int*)(iVar2 + 0x1030) != 0) {
      iVar2 = get_device_info(0);
      codeptr pcVar6 = *(codeptr*)(iVar2 + 0x1030);
      int u = get_device_info(0);
      iVar2 = pcVar6(u, (param_1 - 0xa4)*4 + FLASH_OFF_140000 /*=0x140000*/, (int)lh);
      if (iVar2 != 0) {
        if (0 < *piVar1) {
          if (*E == 0) DEBUG_PRINT("%s(): read flash fail\n\n" /*=0xbbfee*/, "find_chinese_bitmap_by_unicode" /*=0xd750b*/);
          else debug_print(0);
        }
        return 0;
      }
      DEBUG_PRINT("unicode=%x, offset=%d\n" /*=0xd74f4*/, (unsigned int)lh[0], (unsigned int)lh[1]);
      unsigned int puVar4 = (uVar3 >> 2) * (unsigned int)lh[1];
      if (uVar3 == 0x1b0) puVar4 = ((uintptr_t)&rodata_cf120) /*=0xcf120*/ + puVar4;
      memset_bytes((int)dummy, 0, uVar3);
      iVar2 = get_device_info(0);
      pcVar6 = *(codeptr*)(iVar2 + 0x1030);
      u = get_device_info(0);
      iVar2 = pcVar6(u, puVar4 + 0x200000, (int)dummy, uVar3 >> 2);
      if ((iVar2 != 0) && (0 < *piVar1)) {
        if (*E == 0) DEBUG_PRINT("%s(): read flash fail: %d\n\n" /*=0xa1ce0*/, "find_chinese_bitmap_by_unicode" /*=0xd750b*/, iVar2);
        else debug_print(0);
      }
    }
    uVar1 = ((uintptr_t)&g_chinese_glyph_bitmap_buf) /*=0x2001cf92*/;
    expand_bytes_via_lut32((int)dummy, uVar3, ((uintptr_t)&g_chinese_glyph_bitmap_buf) /*=0x2001cf92*/);
  }
  return uVar1;
}

