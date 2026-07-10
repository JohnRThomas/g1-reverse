#include "g1_app_symbols.h"
/* named: read_sys_settting_from_flash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed read_sys_settting_from_flash @ 0x232f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern void debug_print(unsigned,...);
extern int flash_settings_read(int,void*,int);
extern void memset_bytes(void*,int,int);
unsigned read_sys_settting_from_flash(unsigned *param_1)
{
  int iVar1; unsigned *puVar2; char *pcVar3, *pcVar4; unsigned uVar5;
  unsigned local_94[2]; unsigned char local_8c; unsigned local_88, local_84; unsigned char local_80;
  char local_7f[16]; char acStack_6f[16]; char local_5f[16]; char acStack_4f[16];
  unsigned char local_3f, local_3e; unsigned local_34,local_30,local_2c,local_28,local_24,local_20;
  unsigned short local_1c; unsigned local_18, local_14;
  memset_bytes(local_94, 0, 0x84);
  iVar1 = flash_settings_read(FLASH_OFF_130000 /*=0x130000*/, local_94, 0x84);
  if (iVar1 == 0) {
    if (1 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): read sys settings success!\n" /*=0x9e5a6*/, "read_sys_settting_from_flash" /*=0x9e747*/);
      else debug_print("%s(): read sys settings success!\n" /*=0x9e5a6*/, "read_sys_settting_from_flash" /*=0x9e747*/);
    }
    *param_1 = local_94[0];
    *(volatile unsigned char*)(param_1+2) = local_8c;
    param_1[3] = local_88;
    param_1[4] = local_84;
    *(volatile unsigned char*)(param_1+5) = local_80;
    if (local_7f[0] != -1) {
      puVar2 = (unsigned*)((int)param_1 + 0x15);
      pcVar4 = local_7f;
      do { pcVar3 = pcVar4+4; *puVar2 = *(unsigned*)pcVar4; puVar2++; pcVar4=pcVar3; } while(pcVar3 != acStack_6f);
    }
    if (local_5f[0] != -1) {
      puVar2 = (unsigned*)((int)param_1 + 0x35);
      pcVar4 = local_5f;
      do { pcVar3 = pcVar4+4; *puVar2 = *(unsigned*)pcVar4; puVar2++; pcVar4=pcVar3; } while(pcVar3 != acStack_4f);
    }
    param_1[0x18]=local_34; *(volatile unsigned char*)((int)param_1+0x55)=local_3f;
    param_1[0x19]=local_30; *(volatile unsigned char*)((int)param_1+0x56)=local_3e;
    param_1[0x1a]=local_2c; param_1[0x1f]=local_18;
    param_1[0x1b]=local_28; param_1[0x20]=local_14;
    param_1[0x1c]=local_24; *(volatile unsigned short*)(param_1+0x1e)=local_1c;
    param_1[0x1d]=local_20;
    uVar5 = 0;
  } else {
    if (1 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): sys_flash_settings_read error!\n" /*=0x9e580*/, "read_sys_settting_from_flash" /*=0x9e747*/);
      else debug_print("%s(): sys_flash_settings_read error!\n" /*=0x9e580*/, "read_sys_settting_from_flash" /*=0x9e747*/);
    }
    uVar5 = 0xffffffff;
  }
  return uVar5;
}

