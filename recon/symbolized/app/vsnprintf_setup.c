#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000779bc @ 0x000779bc
 * public-name: vsnprintf_setup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   vsnprintf_setup                          <= FUN_000779bc @ 0x000779bc
 *   vfprintf_core                            <= FUN_00078f88 @ 0x00078f88
 * address symbols (name @ address):
 *   rodata_86f57                             @ 0x00086f57
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_000779bc @ 0x779bc  (parity: 300/300 trials, PROVEN) */

extern int strlen(const char *text);
extern void vfprintf_core(unsigned int a, void* b, unsigned int c, void* d);

struct format_record {
  unsigned int value;
  unsigned int text_length;
  unsigned int reserved_08;
  unsigned short type;
  unsigned short limit;
  unsigned int repeated_value;
  unsigned int repeated_length;
  unsigned int reserved_18[3];
  unsigned int formatter;
  unsigned int reserved_28[3];
  unsigned int state_34;
  unsigned int reserved_38[4];
  unsigned int state_48;
};

void vsnprintf_setup(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  struct format_record record;
  unsigned int arguments[2] = {param_3, param_4};

  record.type = 0x204;
  record.value = param_1;
  record.repeated_value = param_1;
  record.text_length = strlen((const char *)param_1);
  record.formatter = ((unsigned long)&rodata_86f57) /*=0x86f57*/;
  record.limit = 0xffff;
  record.repeated_length = record.text_length;
  record.state_34 = 0;
  record.state_48 = 0;
  vfprintf_core(*(volatile unsigned int *)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/, &record, param_2, arguments);
}
