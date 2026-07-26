/* Reconstructed FUN_0004bc8c @ 0x4bc8c (NCS mpsc_pbuf_alloc) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef struct { volatile uint32_t tmp_wr_idx; uint32_t wr_idx,tmp_rd_idx; volatile uint32_t rd_idx,flags; uint32_t lock; void (*notify_drop)(void *,void *); uint32_t get_wlen; volatile uint32_t *buf; uint32_t size,max_usage; uint8_t sem[0x10]; } mpsc_buffer;
extern int FUN_00072040(void *); extern int FUN_0007205c(void *); extern void FUN_00072078(void *);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t) __attribute__((noreturn));
extern void FUN_0007e4bc(mpsc_buffer*,uint32_t,uint32_t); extern int FUN_0007e314(mpsc_buffer*,uint32_t*);
extern uint32_t FUN_0007e35c(mpsc_buffer*,uint32_t,uint32_t); extern void FUN_0007e390(mpsc_buffer*,uint32_t);
extern int FUN_00086406(void); extern int FUN_00072908(void*,uint64_t);
extern int FUN_0007e3ce(mpsc_buffer*,uint32_t,void**,uint32_t*);
__attribute__((always_inline)) static inline uint32_t checked_lock(mpsc_buffer *b){ uint32_t k=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB(); if(!FUN_00072040(&b->lock)){ FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72); FUN_0007e2fa(0xf0935,&b->lock); FUN_0007e2ec(0xf08c7,0x72); } FUN_00072078(&b->lock); return k; }
__attribute__((always_inline)) static inline void checked_unlock(mpsc_buffer *b,uint32_t k){ if(!FUN_0007205c(&b->lock)){ FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0); FUN_0007e2fa(0xf090b,&b->lock); FUN_0007e2ec(0xf08c7,0xf0); } __set_BASEPRI(k); __ISB(); }
void *FUN_0004bc8c(mpsc_buffer *b,uint32_t wlen,uint32_t to_lo,uint32_t to_hi){
 struct { uint32_t pad0,to_lo,to_hi,saved,pad10; void *dropped; uint32_t free_wlen,shift; } l;
 l.to_lo=to_lo; l.to_hi=to_hi; l.dropped=0; l.shift=0;
 void *item=0; uint32_t cont=1,prev=0;
 if(wlen>b->size) return 0;
 do { uint32_t key=checked_lock(b);
  if(l.shift){ FUN_0007e4bc(b,prev,l.shift); l.shift=0; }
  uint32_t wrap=(uint32_t)FUN_0007e314(b,&l.free_wlen);
  if(l.free_wlen>=wlen){ uint32_t idx=b->tmp_wr_idx; volatile uint8_t *h=(volatile uint8_t*)&b->buf[idx]; item=(void*)h; *h&=(uint8_t)~3u; uint32_t n=FUN_0007e35c(b,idx,wlen); b->tmp_wr_idx=n; if(n==b->rd_idx)b->flags|=8u; cont=0; }
  else if(wrap){ FUN_0007e390(b,l.free_wlen); cont=1; }
  else if((l.to_lo|l.to_hi)&&!FUN_00086406()){ checked_unlock(b,key); uint64_t timeout=((uint64_t)l.to_hi<<32)|l.to_lo; int e=FUN_00072908(b->sem,timeout); key=checked_lock(b); cont=(e==0); }
  else if(cont){ prev=b->tmp_wr_idx; cont=(uint32_t)FUN_0007e3ce(b,l.free_wlen,&l.dropped,&l.shift); }
  checked_unlock(b,key);
  if(l.dropped){ if(b->notify_drop)b->notify_drop(b,l.dropped); l.dropped=0; }
 }while(cont);
 return item;
}
