#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004967c @ 0x0004967c
 * public-name: display_reflash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   submit_display_reflash_work              <= FUN_0004904c @ 0x0004904c
 *   display_reflash                          <= FUN_0004967c @ 0x0004967c
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef01c                             @ 0x000ef01c   [INLINED -- G6 literal batch]
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_effd2                             @ 0x000effd2   [INLINED -- G6 literal batch]
 *   rodata_efff4                             @ 0x000efff4   [INLINED -- G6 literal batch]
 *   rodata_f001c                             @ 0x000f001c   [INLINED -- G6 literal batch]
 *   rodata_f019a                             @ 0x000f019a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004967c @ 0x4967c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void submit_display_reflash_work(void);
extern int k_msgq_put(unsigned,void*,int,int);
extern void memcpy(int, int, int);
extern void memset_bytes(void*, int, int);
extern long long thunk_FUN_00074f68(void);

unsigned display_reflash(int param_1, unsigned param_2){
  unsigned char packet[24];
  volatile int *piVar1 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
  memset_bytes(packet,0,24);
  if(param_2 < 0xb){
    long long lVar7 = thunk_FUN_00074f68();
    if(*piVar1 > 2){
      if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
        log_message(((unsigned long)"%s(): send reflash command......\n") /*=0xeffd2*/,((unsigned long)"display_reflash") /*=0xf019a*/);
      else
        debug_print(((unsigned long)"%s(): send reflash command......\n") /*=0xeffd2*/,((unsigned long)"display_reflash") /*=0xf019a*/);
    }
    memset_bytes(packet + 1,0,23);
    packet[0] = 2;
    if(param_1 != 0){
      memcpy(packet + 4,param_1,param_2);
      packet[2] = (uint8_t)param_2;
      packet[3] = (uint8_t)(param_2 >> 8);
    }
    int iVar2 = k_msgq_put(((unsigned long)&g_display_msgq) /*=0x200038c4*/,packet,0,0);
    if(iVar2 == 0){
      if(*piVar1 > 2){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
          log_message(((unsigned long)"%s(): send reflash command end .......\n") /*=0xefff4*/,((unsigned long)"display_reflash") /*=0xf019a*/);
        else
          debug_print(((unsigned long)"%s(): send reflash command end .......\n") /*=0xefff4*/,((unsigned long)"display_reflash") /*=0xf019a*/);
      }
      long long lVar8 = thunk_FUN_00074f68();
      if(*piVar1 > 2){
        unsigned uVar5 = (unsigned)(((uint64_t)lVar8 * UINT64_C(1000)) >> 0x20);
        unsigned uVar3 = (unsigned)(((uint64_t)lVar7 * UINT64_C(1000)) >> 0x20);
        unsigned uVar4 = (unsigned)((uint64_t)lVar8 * UINT64_C(1000)) >> 0xf | uVar5*0x20000;
        unsigned uVar6 = (unsigned)((uint64_t)lVar7 * UINT64_C(1000)) >> 0xf | uVar3*0x20000;
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
          log_message(((unsigned long)"%s(): send reflash command cost %lldMs\n") /*=0xf001c*/,((unsigned long)"display_reflash") /*=0xf019a*/, uVar4-uVar6,
                      ((uVar5>>0xf)-(uVar3>>0xf)) - (unsigned)(uVar4<uVar6));
        else
          debug_print(((unsigned long)"%s(): send reflash command cost %lldMs\n") /*=0xf001c*/,((unsigned long)"display_reflash") /*=0xf019a*/, uVar4-uVar6,
                       ((uVar5>>0xf)-(uVar3>>0xf)) -
                           (unsigned)(uVar4<uVar6));
      }
      submit_display_reflash_work();
      return 0;
    }
    log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/,((unsigned long)"display_reflash") /*=0xf019a*/,0,0);
  } else if(*piVar1 > 0){
    if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
      log_message(((unsigned long)"%s(): send data length more than %d,can't load it,exit ...\n") /*=0xef01c*/,((unsigned long)"display_reflash") /*=0xf019a*/,10);
    else
      debug_print(((unsigned long)"%s(): send data length more than %d,can't load it,exit ...\n") /*=0xef01c*/,((unsigned long)"display_reflash") /*=0xf019a*/,10);
  }
  return 0xffffffff;
}
