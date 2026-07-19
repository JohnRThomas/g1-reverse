#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077914 @ 0x00077914
 * public-name: snprintf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   printf_parse_format                      <= FUN_00078d90 @ 0x00078d90
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00077914 @ 0x77914 */
#include <stdint.h>
extern int printf_parse_format(void *state,void *descriptor,uint32_t mode,void *arguments);
int snprintf(uint8_t *buffer,int length,uint32_t mode,uint32_t arguments){
  volatile uint32_t *state=*(volatile uint32_t**)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
  if(length<0){*state=0x8b;return -1;}
  struct descriptor {uint8_t *cursor; uint32_t pad; int remaining; uint16_t flags,limit; uint8_t *base; int count;} d;
  d.cursor=buffer; d.pad=0; d.remaining=length?length-1:0; d.flags=0x208; d.limit=0xffff;
  d.base=buffer; d.count=d.remaining;
  int result=printf_parse_format((void*)state,&d,mode,&arguments);
  if(result< -1)*state=0x8b;
  if(length)d.cursor[0]=0;
  return result;
}
