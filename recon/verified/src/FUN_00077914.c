/* Reconstructed FUN_00077914 @ 0x77914 */
#include <stdint.h>
extern int FUN_00078d90(void *state,void *descriptor,uint32_t mode,void *arguments);
int FUN_00077914(uint8_t *buffer,int length,uint32_t mode,uint32_t arguments){
  volatile uint32_t *state=*(volatile uint32_t**)0x20002d20u;
  if(length<0){*state=0x8b;return -1;}
  struct descriptor {uint8_t *cursor; uint32_t pad; int remaining; uint16_t flags,limit; uint8_t *base; int count;} d;
  d.cursor=buffer; d.pad=0; d.remaining=length?length-1:0; d.flags=0x208; d.limit=0xffff;
  d.base=buffer; d.count=d.remaining;
  int result=FUN_00078d90((void*)state,&d,mode,&arguments);
  if(result< -1)*state=0x8b;
  if(length)d.cursor[0]=0;
  return result;
}
