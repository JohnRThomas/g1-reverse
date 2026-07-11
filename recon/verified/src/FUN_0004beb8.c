/* Reconstructed FUN_0004beb8 @ 0x4beb8 (NCS mpsc_pbuf_claim) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
typedef struct { uint32_t tmp_wr_idx,wr_idx,tmp_rd_idx,rd_idx,flags,lock; void(*notify_drop)(void*,void*); uint32_t (*get_wlen)(void*); volatile uint32_t *buf; uint32_t size,max_usage; uint8_t sem[0x10]; } mpsc_buffer;
extern int FUN_00072040(void*); extern int FUN_0007205c(void*); extern void FUN_00072078(void*);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t) __attribute__((noreturn));
extern uint32_t FUN_0007e35c(mpsc_buffer*,uint32_t,uint32_t); extern void FUN_0007e378(mpsc_buffer*,uint32_t);
__attribute__((always_inline)) static inline uint32_t lock_checked(mpsc_buffer*b){uint32_t k=__get_BASEPRI();__set_BASEPRI_MAX(0x20);__ISB();if(!FUN_00072040(&b->lock)){FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72);FUN_0007e2fa(0xf0935,&b->lock);FUN_0007e2ec(0xf08c7,0x72);}FUN_00072078(&b->lock);return k;}
__attribute__((always_inline)) static inline void unlock_checked(mpsc_buffer*b,uint32_t k){if(!FUN_0007205c(&b->lock)){FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0);FUN_0007e2fa(0xf090b,&b->lock);FUN_0007e2ec(0xf08c7,0xf0);}__set_BASEPRI(k);__ISB();}
void *FUN_0004beb8(mpsc_buffer *b){
 void *item; uint32_t cont;
 do { cont=0; uint32_t key=lock_checked(b); uint32_t a;
  if((b->flags&8u)||b->tmp_rd_idx>b->wr_idx)a=b->size-b->tmp_rd_idx;else a=b->wr_idx-b->tmp_rd_idx;
  volatile uint32_t *raw=&b->buf[b->tmp_rd_idx]; item=(void*)raw; uint8_t hdr=*(volatile uint8_t*)raw;
  if(a==0||(hdr&3u)==0){item=0;}
  else {uint32_t skip=((hdr&3u)==2u)?(*raw>>2):0;
   if(skip||(hdr&1u)==0){uint32_t inc=skip?skip:b->get_wlen((void*)raw);b->tmp_rd_idx=FUN_0007e35c(b,b->tmp_rd_idx,inc);FUN_0007e378(b,inc);cont=1;}
   else {*(volatile uint8_t*)raw=hdr|2u;uint32_t inc=b->get_wlen((void*)raw);b->tmp_rd_idx=FUN_0007e35c(b,b->tmp_rd_idx,inc);}
  }
  unlock_checked(b,key);
 }while(cont);
 return item;
}
