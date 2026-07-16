/* Full reconstruction FUN_00064b64 @ 0x64b64, exact extent 202 bytes. */
#include <stdint.h>
#include <stddef.h>
typedef struct { const uint8_t *start; uint32_t length, used, reserved; uint8_t work[12]; } parse_state_t;
extern void FUN_00086c78(void*,int,size_t);
extern uintptr_t FUN_00084fd4(void);
extern int FUN_00087036(const void*,uintptr_t,size_t);
extern uintptr_t FUN_00084ed8(void*);
extern int FUN_00012910(uintptr_t,uintptr_t);
extern void FUN_00064b1c(uintptr_t);
int FUN_00064b64(const uint8_t *input,uint32_t length,const uint8_t **end,int require_end){
 parse_state_t s;volatile uint32_t *error=(volatile uint32_t*)0x2000b314u;
 FUN_00086c78(&s,0,sizeof(s));error[0]=0;error[1]=0;
 if(!input)return 0;
 if(input&&length){
  const uint32_t *seed=(const uint32_t*)0x20002bacu;s.work[0]=((const uint8_t*)seed)[0];
  *(uint32_t*)&s.work[0]=seed[0];*(uint32_t*)&s.work[4]=seed[1];*(uint32_t*)&s.work[8]=seed[2];
  s.start=input;s.length=length;uintptr_t object=FUN_00084fd4();
  if(object){
   void *cursor=(void*)s.start;
   if(s.start){if(s.used==0){if(s.length>4&&FUN_00087036(s.start,0x000f6999u,3)==0)s.used=3;cursor=&s.start;}else cursor=0;}
   int valid=FUN_00012910(object,FUN_00084ed8(cursor));
   if(valid&&(require_end==0||(FUN_00084ed8(&s),s.used<s.length&&s.start[s.used]==0))){if(!end)return (int)object;*end=s.start+s.used;return (int)object;}
   FUN_00064b1c(object);
  }
 }
 if(s.used>=s.length)s.used=s.length? s.length-1:0;
 if(end)*end=input+s.used;error[0]=(uint32_t)(uintptr_t)input;error[1]=s.used;return 0;
}
