#include "g1_app_symbols.h"
/* named: display_reflash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_reflash @ 0x4967c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,unsigned);
extern void debug_print(unsigned,unsigned);
extern void submit_display_reflash_work(void);
extern int k_msgq_put(unsigned,void*,int,int);
extern void memcpy(void*,int,unsigned);
extern void memset_bytes(void*,int,unsigned);
extern long long thunk_FUN_00074f68(void);

unsigned display_reflash(int param_1, unsigned param_2){
  unsigned char local_30, uStack_2f;
  unsigned short local_2e;
  unsigned char auStack_2c[20];
  volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  memset_bytes(&local_30,0,0x18);
  if(param_2 < 0xb){
    long long lVar7 = thunk_FUN_00074f68();
    if(*piVar1 > 2){
      if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
        DEBUG_PRINT("%s(): send reflash command......\n" /*=0xeffd2*/,"display_reflash" /*=0xf019a*/,0,0);
      else
        debug_print(0,0);
    }
    memset_bytes(&uStack_2f,0,0x17);
    local_30 = 2;
    if(param_1 != 0){
      memcpy(auStack_2c,param_1,param_2);
      local_2e = (unsigned short)param_2;
    }
    int iVar2 = k_msgq_put(((uintptr_t)&g_display_msgq) /*=0x200038c4*/,&local_30,0,0);
    if(iVar2 == 0){
      if(*piVar1 > 2){
        if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
          DEBUG_PRINT("%s(): send reflash command end .......\n" /*=0xefff4*/,"display_reflash" /*=0xf019a*/,0,0);
        else
          debug_print(0,0);
      }
      long long lVar8 = thunk_FUN_00074f68();
      if(*piVar1 > 2){
        unsigned uVar5 = (unsigned)((unsigned long long)(lVar8*1000) >> 0x20);
        unsigned uVar3 = (unsigned)((unsigned long long)(lVar7*1000) >> 0x20);
        unsigned uVar4 = (unsigned)(lVar8*1000) >> 0xf | uVar5*((uintptr_t)&rodata_20000) /*=0x20000*/;
        unsigned uVar6 = (unsigned)(lVar7*1000) >> 0xf | uVar3*((uintptr_t)&rodata_20000) /*=0x20000*/;
        if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
          DEBUG_PRINT("%s(): send reflash command cost %lldMs\n" /*=0xf001c*/,"display_reflash" /*=0xf019a*/, uVar4-uVar6,
                      ((uVar5>>0xf)-(uVar3>>0xf)) - (unsigned)(uVar4<uVar6));
        else
          debug_print("%s(): send reflash command cost %lldMs\n" /*=0xf001c*/,"display_reflash" /*=0xf019a*/);
      }
      submit_display_reflash_work();
      return 0;
    }
    DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/,"display_reflash" /*=0xf019a*/,0,0);
  } else if(*piVar1 > 0){
    if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
      DEBUG_PRINT("%s(): send data length more than %d,can't load it,exit ...\n" /*=0xef01c*/,"display_reflash" /*=0xf019a*/,10,0);
    else
      debug_print(0,0);
  }
  return 0xffffffff;
}

