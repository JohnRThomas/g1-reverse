#include "g1_app_symbols.h"
/* named: cleanAppLanguageInfo */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003994  g_flash_store_cmd_msgq       
//   0x20007554  g_log_use_alt_sink           
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed cleanAppLanguageInfo @ 0x23b78  (parity: 300/300 trials, PROVEN) */

extern void debug_print(void);
extern int k_msgq_put(void*, void*, int, int);
extern void FUN_00072880(void*);
extern int DEBUG_PRINT(int, ...);

int cleanAppLanguageInfo(unsigned int param_1, unsigned int param_2)
{
  int iVar1;
  int uVar2;
  unsigned char buf[8];

  buf[0] = 2;
  *(unsigned int*)&buf[1] = 0;
  buf[5] = 0;
  iVar1 = k_msgq_put((void*)((uintptr_t)&g_flash_store_cmd_msgq) /*=0x20003994*/, buf, 0, 0);
  if (iVar1 == 0) {
    if (*(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT("%s(): SEND APP Language Command...\n" /*=0x9e968*/, "cleanAppLanguageInfo" /*=0x9ed8f*/);
      } else {
        debug_print();
      }
    }
    FUN_00072880((void*)((uintptr_t)&g_app_language_msgq) /*=0x200079e4*/);
    uVar2 = 0;
  } else {
    if (*(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT("%s(): setting flash store queue fill failed\r\n\n" /*=0x9e903*/, "cleanAppLanguageInfo" /*=0x9ed8f*/);
      } else {
        debug_print();
      }
    }
    uVar2 = -1;
  }
  return uVar2;
}

