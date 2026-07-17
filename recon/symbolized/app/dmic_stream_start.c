#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002f080 @ 0x0002f080
 * public-name: dmic_stream_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   init_dmic_msgq                           <= FUN_0002ebd8 @ 0x0002ebd8
 *   dmic_stream_start                        <= FUN_0002f080 @ 0x0002f080
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87d40                             @ 0x00087d40
 *   rodata_a4038                             @ 0x000a4038
 *   rodata_a404b                             @ 0x000a404b
 *   rodata_a41b0                             @ 0x000a41b0
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002f080 @ 0x2f080  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern int DEBUG_PRINT(int,...); extern int get_device_info(int,...); extern int debug_print(int,...);
extern int ancs_get_conn_ctx(int,...); extern int init_dmic_msgq(int,...); extern int z_device_is_ready(int,...);
typedef int (*cp)(int,...);

uint dmic_stream_start(void)
{
  int iVar7, iVar8; uint uVar12;
  int *puVar2 = (int*)((unsigned long)&rodata_87d40) /*=0x87d40*/;
  iVar7 = ancs_get_conn_ctx(0);
  iVar8 = get_device_info(0);
  uVar12 = *(volatile ushort*)(iVar8 + 0x105c) & 2;
  if ((*(volatile ushort*)(iVar8 + 0x105c) & 2) != 0) {
    if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT(((unsigned long)&rodata_a4038) /*=0xa4038*/,((unsigned long)&rodata_a41b0) /*=0xa41b0*/);
      else debug_print(0);
    }
    iVar8 = z_device_is_ready(((unsigned long)&rodata_87d40) /*=0x87d40*/);
    if (iVar8 == 0) {
      if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT(((unsigned long)&rodata_a404b) /*=0xa404b*/,((unsigned long)&rodata_a41b0) /*=0xa41b0*/,*(volatile int*)puVar2);
        else debug_print(0);
      }
    } else {
      if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT(0,((unsigned long)&rodata_a41b0) /*=0xa41b0*/,*(volatile int*)puVar2);
        else debug_print(0);
      }
      iVar8 = init_dmic_msgq(0);
      if (iVar8 == 0) { for(;;) init_dmic_msgq(0); }
    }
    uVar12 = 1;
  }
  {
    int p2 = *(volatile int*)(((unsigned long)&rodata_87d40) /*=0x87d40*/ + 8);
    cp fp = *(cp volatile*)(p2 + 4);
    iVar7 = fp(((unsigned long)&rodata_87d40) /*=0x87d40*/, 0);
  }
  (void)iVar7;
  return uVar12;
}
