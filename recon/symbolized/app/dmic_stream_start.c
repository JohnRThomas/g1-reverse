#include "g1_app_symbols.h"
/* named: dmic_stream_start */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed dmic_stream_start @ 0x2f080  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern int DEBUG_PRINT(int,...); extern int get_device_info(int,...); extern int debug_print(int,...);
extern int ancs_get_conn_ctx(int,...); extern int init_dmic_msgq(int,...); extern int z_device_is_ready(int,...);
typedef int (*cp)(int,...);

uint dmic_stream_start(void)
{
  int iVar7, iVar8; uint uVar12;
  int *puVar2 = (int*)((uintptr_t)&tbl_87c80) /*=0x87d40*/;
  iVar7 = ancs_get_conn_ctx(0);
  iVar8 = get_device_info(0);
  uVar12 = *(volatile ushort*)(iVar8 + 0x105c) & 2;
  if ((*(volatile ushort*)(iVar8 + 0x105c) & 2) != 0) {
    if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): DMIC sample\n" /*=0xa4038*/,"dmic_stream_start" /*=0xa41b0*/);
      else debug_print(0);
    }
    iVar8 = z_device_is_ready(((uintptr_t)&tbl_87c80) /*=0x87d40*/);
    if (iVar8 == 0) {
      if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): %s is not ready\n" /*=0xa404b*/,"dmic_stream_start" /*=0xa41b0*/,*(volatile int*)puVar2);
        else debug_print(0);
      }
    } else {
      if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT(0,"dmic_stream_start" /*=0xa41b0*/,*(volatile int*)puVar2);
        else debug_print(0);
      }
      iVar8 = init_dmic_msgq(0);
      if (iVar8 == 0) { for(;;) init_dmic_msgq(0); }
    }
    uVar12 = 1;
  }
  {
    int p2 = *(volatile int*)(((uintptr_t)&tbl_87c80) /*=0x87d40*/ + 8);
    cp fp = *(cp volatile*)(p2 + 4);
    iVar7 = fp(((uintptr_t)&tbl_87c80) /*=0x87d40*/, 0);
  }
  (void)iVar7;
  return uVar12;
}

