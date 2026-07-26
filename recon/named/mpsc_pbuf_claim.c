/* readable reconstruction; identity: FUN_0004beb8 @ 0x0004beb8
 * public-name: mpsc_pbuf_claim
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_claim                          <= FUN_0004beb8 @ 0x0004beb8
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   rd_idx_inc                               <= FUN_0007e378 @ 0x0007e378
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 */
/* Reconstructed FUN_0004beb8 @ 0x4beb8 (NCS mpsc_pbuf_claim) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef struct { uint32_t tmp_wr_idx,wr_idx,tmp_rd_idx,rd_idx,flags,lock; void(*notify_drop)(void*,void*); uint32_t (*get_wlen)(void*); volatile uint32_t *buf; uint32_t size,max_usage; uint8_t sem[0x10]; } mpsc_buffer;
extern int z_spin_lock_valid(void*); extern int z_spin_unlock_valid(void*); extern void z_spin_lock_set_owner(void*);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t) __attribute__((noreturn));
extern uint32_t idx_inc(mpsc_buffer*,uint32_t,uint32_t); extern void rd_idx_inc(mpsc_buffer*,uint32_t);
__attribute__((always_inline)) static inline uint32_t lock_checked(mpsc_buffer*b){uint32_t k=__get_BASEPRI();__set_BASEPRI_MAX(0x20);__ISB();if(!z_spin_lock_valid(&b->lock)){printk(0x99cbd,0xf0920,0xf08c7,0x72);printk(0xf0935,&b->lock);assert_post_action(0xf08c7,0x72);}z_spin_lock_set_owner(&b->lock);return k;}
__attribute__((always_inline)) static inline void unlock_checked(mpsc_buffer*b,uint32_t k){if(!z_spin_unlock_valid(&b->lock)){printk(0x99cbd,0xf08f4,0xf08c7,0xf0);printk(0xf090b,&b->lock);assert_post_action(0xf08c7,0xf0);}__set_BASEPRI(k);__ISB();}
void *mpsc_pbuf_claim(mpsc_buffer *b){
 void *item; uint32_t cont;
 do { cont=0; uint32_t key=lock_checked(b); uint32_t a;
  if((b->flags&8u)||b->tmp_rd_idx>b->wr_idx)a=b->size-b->tmp_rd_idx;else a=b->wr_idx-b->tmp_rd_idx;
  volatile uint32_t *raw=&b->buf[b->tmp_rd_idx]; item=(void*)raw; uint8_t hdr=*(volatile uint8_t*)raw;
  if(a==0||(hdr&3u)==0){item=0;}
  else {uint32_t skip=((hdr&3u)==2u)?(*raw>>2):0;
   if(skip||(hdr&1u)==0){uint32_t inc=skip?skip:b->get_wlen((void*)raw);b->tmp_rd_idx=idx_inc(b,b->tmp_rd_idx,inc);rd_idx_inc(b,inc);cont=1;}
   else {*(volatile uint8_t*)raw=hdr|2u;uint32_t inc=b->get_wlen((void*)raw);b->tmp_rd_idx=idx_inc(b,b->tmp_rd_idx,inc);}
  }
  unlock_checked(b,key);
 }while(cont);
 return item;
}
