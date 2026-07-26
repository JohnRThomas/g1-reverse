#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00031cbc @ 0x00031cbc
 * public-name: set_brightness_lum_base
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 * address symbols (name @ address):
 *   rodata_a672f                             @ 0x000a672f   [INLINED -- G6 literal batch]
 *   rodata_a70a0                             @ 0x000a70a0   [INLINED -- G6 literal batch]
 *   rodata_a70c1                             @ 0x000a70c1   [INLINED -- G6 literal batch]
 *   rodata_a70e7                             @ 0x000a70e7   [INLINED -- G6 literal batch]
 *   rodata_a7655                             @ 0x000a7655   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed set_brightness_lum_base @ 0x31cbc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned,...);
extern void build_and_send_device_status_report(unsigned,int);
extern int read_sys_settting_from_flash(void*);
extern void k_msleep_ticks32768_b(int);
unsigned set_brightness_lum_base(int param_1, unsigned param_2, unsigned **param_3, unsigned char *param_4)
{
  char cVar2, cVar9; unsigned char bVar1; unsigned short uVar3; int *piVar4; unsigned uVar5;
  int iVar6; unsigned uVar7, uVar8; unsigned char *puVar10;
  unsigned char auStack_9c[116];
  unsigned short local_28, local_26, local_24;
  log_message(((unsigned long)"join in set_brightness_lum_base\n") /*=0xa70a0*/);
  if ((param_3 == 0) || (param_4 == 0)) {
    log_message(((unsigned long)"set_brightness_lum_base para is NULL\n") /*=0xa70c1*/);
    uVar5 = 0xffffffff;
  } else if (*(char*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ == 1) {
    puVar10 = (unsigned char*)*param_3;
    *(volatile unsigned char*)(puVar10) = 0x36;
    *(volatile unsigned char*)(puVar10+2) = 3;
    *(volatile unsigned char*)(puVar10+3) = 2;
    piVar4 = (int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    *(volatile unsigned char*)(puVar10+1) = 1;
    cVar2 = *(char*)(param_1 + 4);
    uVar8 = (unsigned)*(unsigned short*)(param_1 + 5);
    if (2 < *piVar4) {
      if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)"%s(): tmp_lum_value is:0x%x\n") /*=0xa70e7*/, ((unsigned long)"set_brightness_lum_base") /*=0xa7655*/, uVar8);
      else debug_print(((unsigned long)"%s(): tmp_lum_value is:0x%x\n") /*=0xa70e7*/, ((unsigned long)"set_brightness_lum_base") /*=0xa7655*/, uVar8);
    }
    bVar1 = 0x3f < uVar8;
    if (bVar1) uVar8 = 0x3f;
    *(volatile unsigned char*)(puVar10+4) = bVar1;
    uVar3 = (unsigned short)uVar8;
    if (cVar2 == 1) { iVar6 = get_device_info(); *(volatile unsigned short*)(iVar6 + 0xedc) = uVar3; }
    else if (cVar2 == 2) { iVar6 = get_device_info(); *(volatile unsigned short*)(iVar6 + 0xede) = uVar3; }
    else if (cVar2 == 0) { iVar6 = get_device_info(); *(volatile unsigned short*)(iVar6 + 0xeda) = uVar3; }
    iVar6 = get_device_info(); *(volatile unsigned short*)(iVar6 + 0xed8) = uVar3;
    uVar5 = get_device_info(); build_and_send_device_status_report(uVar5, 0);
    cVar9 = 0;
    do {
      iVar6 = read_sys_settting_from_flash(auStack_9c);
      if (iVar6 == 0) {
        if (cVar2 == 0) uVar7 = (unsigned)local_28;
        else if (cVar2 == 1) uVar7 = (unsigned)local_26;
        else { if (cVar2 != 2) goto LAB_6a; uVar7 = (unsigned)local_24; }
        if (uVar7 == uVar8) goto LAB_7c;
      }
LAB_6a:
      cVar9 = cVar9 + 1;
      k_msleep_ticks32768_b(100);
    } while (cVar9 != 5);
    *(volatile unsigned char*)(puVar10+4) = 2;
LAB_7c:
    *(volatile unsigned char*)(puVar10+5) = cVar2;
    uVar5 = 0;
    *(volatile unsigned char*)param_4 = 6;
  } else {
    log_message(((unsigned long)"warning: not test mode,disable setting\n") /*=0xa672f*/);
    uVar5 = 0xfffffffe;
  }
  return uVar5;
}
