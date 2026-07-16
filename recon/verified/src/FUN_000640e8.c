/* Full reconstruction FUN_000640e8 @ 0x640e8, exact extent 60 bytes. */
#include <stdint.h>
extern uint64_t FUN_00076a94(uintptr_t,uint32_t,uintptr_t,uintptr_t,uint32_t,uint32_t);
extern uintptr_t FUN_00084d64(void);
extern void FUN_00084dea(uintptr_t,uintptr_t,const uint8_t*,uint32_t);
void FUN_000640e8(uintptr_t object,uint32_t low,uint32_t high){
 if(high>14){
  uint64_t result=FUN_00076a94(0x000f68d7u,0x182,0x000f693au,0x000f68c5u,object,low);
  low=(uint32_t)(result>>32);high=0x000f693au;
  while(low>14){result=FUN_00076a94(0x000f68d7u,0x182,0x000f693au,0x000f691au,object,low);low=(uint32_t)(result>>32);}
 }
 uint8_t packed=(uint8_t)(low|(high<<4));
 FUN_00084dea(object,FUN_00084d64(),&packed,1);
}
