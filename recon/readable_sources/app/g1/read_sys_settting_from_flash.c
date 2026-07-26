#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_sys_settings_record__param_0045        [param_0045; G1-original]
 *   local_94         => struct g1_layout_flash_addr_len_tmp__stack_0870         [stack_0870; G1-original]
 *   local_7f         => struct g1_layout_sys_setting_scan_locals__stack_0871    [stack_0871; G1-original]
 *   local_5f         => struct g1_layout_flash_setting_record_local__stack_0873 [stack_0873; G1-original]
 * Raw function identity: 0x000232f8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000232f8 @ 0x000232f8
 * public-name: read_sys_settting_from_flash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e580                             @ 0x0009e580
 *   rodata_9e5a6                             @ 0x0009e5a6
 *   rodata_9e747                             @ 0x0009e747   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed read_sys_settting_from_flash @ 0x232f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned,...);
extern void debug_print(unsigned,...);
extern int flash_settings_read(int,void*,int);
extern void memset_bytes(void*,int,int);
unsigned read_sys_settting_from_flash(unsigned *param_1)
{
  unsigned char record[0x84];
  unsigned char *output = (unsigned char *)param_1;
  unsigned uVar5;
  int iVar1;
  unsigned i;

  memset_bytes(record, 0, sizeof(record));
  iVar1 = flash_settings_read(0x130000, record, sizeof(record));
  if (iVar1 == 0) {
    if (1 < *(int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)&rodata_9e5a6) /*=0x9e5a6*/, ((unsigned long)"read_sys_settting_from_flash") /*=0x9e747*/);
      else debug_print(((unsigned long)&rodata_9e5a6) /*=0x9e5a6*/, ((unsigned long)"read_sys_settting_from_flash") /*=0x9e747*/);
    }
    *(unsigned *)(output + 0x00) = *(unsigned *)(record + 0x00);
    output[0x08] = record[0x08];
    *(unsigned *)(output + 0x0c) = *(unsigned *)(record + 0x0c);
    *(unsigned *)(output + 0x10) = *(unsigned *)(record + 0x10);
    output[0x14] = record[0x14];
    if (record[0x15] != 0xff) {
      for (i = 0; i < 16; i += 4)
        *(unsigned *)(output + 0x15 + i) = *(unsigned *)(record + 0x15 + i);
    }
    if (record[0x35] != 0xff) {
      for (i = 0; i < 16; i += 4)
        *(unsigned *)(output + 0x35 + i) = *(unsigned *)(record + 0x35 + i);
    }
    *(unsigned *)(output + 0x60) = *(unsigned *)(record + 0x60);
    output[0x55] = record[0x55];
    *(unsigned *)(output + 0x64) = *(unsigned *)(record + 0x64);
    output[0x56] = record[0x56];
    *(unsigned *)(output + 0x68) = *(unsigned *)(record + 0x68);
    *(unsigned *)(output + 0x7c) = *(unsigned *)(record + 0x7c);
    *(unsigned *)(output + 0x6c) = *(unsigned *)(record + 0x6c);
    *(unsigned *)(output + 0x80) = *(unsigned *)(record + 0x80);
    *(unsigned *)(output + 0x70) = *(unsigned *)(record + 0x70);
    *(unsigned short *)(output + 0x78) = *(unsigned short *)(record + 0x78);
    *(unsigned *)(output + 0x74) = *(unsigned *)(record + 0x74);
    uVar5 = 0;
  } else {
    if (1 < *(int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)&rodata_9e580) /*=0x9e580*/, ((unsigned long)"read_sys_settting_from_flash") /*=0x9e747*/);
      else debug_print(((unsigned long)&rodata_9e580) /*=0x9e580*/, ((unsigned long)"read_sys_settting_from_flash") /*=0x9e747*/);
    }
    uVar5 = 0xffffffff;
  }
  return uVar5;
}
