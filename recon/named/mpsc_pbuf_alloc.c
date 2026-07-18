/* readable reconstruction; identity: FUN_0004bc8c @ 0x0004bc8c
 * public-name: mpsc_pbuf_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_alloc                          <= FUN_0004bc8c @ 0x0004bc8c
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   free_space                               <= FUN_0007e314 @ 0x0007e314
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   add_skip_item                            <= FUN_0007e390 @ 0x0007e390
 *   drop_item_locked                         <= FUN_0007e3ce @ 0x0007e3ce
 *   post_drop_action                         <= FUN_0007e4bc @ 0x0007e4bc
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 */
/* Reconstructed FUN_0004bc8c @ 0x4bc8c (NCS mpsc_pbuf_alloc) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
typedef struct { volatile uint32_t tmp_wr_idx; uint32_t wr_idx,tmp_rd_idx; volatile uint32_t rd_idx,flags; uint32_t lock; void (*notify_drop)(void *,void *); uint32_t get_wlen; volatile uint32_t *buf; uint32_t size,max_usage; uint8_t sem[0x10]; } mpsc_buffer;
extern int z_spin_lock_valid(void *); extern int z_spin_unlock_valid(void *); extern void z_spin_lock_set_owner(void *);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t) __attribute__((noreturn));
extern void post_drop_action(mpsc_buffer*,uint32_t,uint32_t); extern int free_space(mpsc_buffer*,uint32_t*);
extern uint32_t idx_inc(mpsc_buffer*,uint32_t,uint32_t); extern void add_skip_item(mpsc_buffer*,uint32_t);
extern int k_is_in_isr(void); extern int z_impl_k_sem_take(void*,uint64_t);
extern int drop_item_locked(mpsc_buffer*,uint32_t,void**,uint32_t*);
__attribute__((always_inline)) static inline uint32_t checked_lock(mpsc_buffer *b){ uint32_t k=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB(); if(!z_spin_lock_valid(&b->lock)){ printk(0x99cbd,0xf0920,0xf08c7,0x72); printk(0xf0935,&b->lock); assert_post_action(0xf08c7,0x72); } z_spin_lock_set_owner(&b->lock); return k; }
__attribute__((always_inline)) static inline void checked_unlock(mpsc_buffer *b,uint32_t k){ if(!z_spin_unlock_valid(&b->lock)){ printk(0x99cbd,0xf08f4,0xf08c7,0xf0); printk(0xf090b,&b->lock); assert_post_action(0xf08c7,0xf0); } __set_BASEPRI(k); __ISB(); }
void *mpsc_pbuf_alloc(mpsc_buffer *b,uint32_t wlen,uint32_t to_lo,uint32_t to_hi){
 struct { uint32_t pad0,to_lo,to_hi,saved,pad10; void *dropped; uint32_t free_wlen,shift; } l;
 l.to_lo=to_lo; l.to_hi=to_hi; l.dropped=0; l.shift=0;
 void *item=0; uint32_t cont=1,prev=0;
 if(wlen>b->size) return 0;
 do { uint32_t key=checked_lock(b);
  if(l.shift){ post_drop_action(b,prev,l.shift); l.shift=0; }
  uint32_t wrap=(uint32_t)free_space(b,&l.free_wlen);
  if(l.free_wlen>=wlen){ uint32_t idx=b->tmp_wr_idx; volatile uint8_t *h=(volatile uint8_t*)&b->buf[idx]; item=(void*)h; *h&=(uint8_t)~3u; uint32_t n=idx_inc(b,idx,wlen); b->tmp_wr_idx=n; if(n==b->rd_idx)b->flags|=8u; cont=0; }
  else if(wrap){ add_skip_item(b,l.free_wlen); cont=1; }
  else if((l.to_lo|l.to_hi)&&!k_is_in_isr()){ checked_unlock(b,key); uint64_t timeout=((uint64_t)l.to_hi<<32)|l.to_lo; int e=z_impl_k_sem_take(b->sem,timeout); key=checked_lock(b); cont=(e==0); }
  else if(cont){ prev=b->tmp_wr_idx; cont=(uint32_t)drop_item_locked(b,l.free_wlen,&l.dropped,&l.shift); }
  checked_unlock(b,key);
  if(l.dropped){ if(b->notify_drop)b->notify_drop(b,l.dropped); l.dropped=0; }
 }while(cont);
 return item;
}
