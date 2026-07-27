#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064b64 @ 0x00064b64
 * public-name: cjson_parse_with_opts
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_parse_value                        <= FUN_00012910 @ 0x00012910
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_parse_with_opts                    <= FUN_00064b64 @ 0x00064b64
 *   cjson_skip_whitespace                    <= FUN_00084ed8 @ 0x00084ed8
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 * address symbols (name @ address):
 *   rodata_f6999                             @ 0x000f6999
 *   g_cjson_hooks                            @ 0x20002bac
 *   g_2000b314                               @ 0x2000b314
 */
/* Full reconstruction FUN_00064b64 @ 0x64b64, exact extent 202 bytes. */
#include <stdint.h>
#include <stddef.h>
typedef struct { const uint8_t *start; uint32_t length, used, reserved; uint8_t work[12]; } parse_state_t;
extern void memset_bytes(void*, int, int);
extern uintptr_t alloc_zeroed_node(void);
extern int strncmp(const void*, unsigned long, unsigned int);
extern uintptr_t cjson_skip_whitespace(void*);
extern unsigned int cjson_parse_value(int, int *);
extern void cjson_delete(volatile int*);
int cjson_parse_with_opts(const uint8_t *input,uint32_t length,const uint8_t **end,int require_end){
 parse_state_t s;volatile uint32_t *error=(volatile uint32_t*)((unsigned long)&g_2000b314) /*=0x2000b314*/;
 memset_bytes(&s,0,sizeof(s));error[0]=0;error[1]=0;
 if(!input)return 0;
 if(input&&length){
  const uint32_t *seed=(const uint32_t*)((unsigned long)&g_cjson_hooks) /*=0x20002bac*/;s.work[0]=((const uint8_t*)seed)[0];
  *(uint32_t*)&s.work[0]=seed[0];*(uint32_t*)&s.work[4]=seed[1];*(uint32_t*)&s.work[8]=seed[2];
  s.start=input;s.length=length;uintptr_t object=alloc_zeroed_node();
  if(object){
   void *cursor=(void*)s.start;
   if(s.start){if(s.used==0){if(s.length>4&&strncmp(s.start,((unsigned long)&rodata_f6999) /*=0xf6999*/,3)==0)s.used=3;cursor=&s.start;}else cursor=0;}
   int valid=cjson_parse_value(object,cjson_skip_whitespace(cursor));
   if(valid&&(require_end==0||(cjson_skip_whitespace(&s),s.used<s.length&&s.start[s.used]==0))){if(!end)return (int)object;*end=s.start+s.used;return (int)object;}
   cjson_delete(object);
  }
 }
 if(s.used>=s.length)s.used=s.length? s.length-1:0;
 if(end)*end=input+s.used;error[0]=(uint32_t)(uintptr_t)input;error[1]=s.used;return 0;
}
