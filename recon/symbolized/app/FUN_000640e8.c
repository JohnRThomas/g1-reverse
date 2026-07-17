#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000640e8 @ 0x000640e8
 * public-name: FUN_000640e8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_fatal_error_and_abort               <= FUN_00076a94 @ 0x00076a94
 *   flash_calc_prev_ate_offset               <= FUN_00084d64 @ 0x00084d64
 *   flash_write_padded_entry                 <= FUN_00084dea @ 0x00084dea
 * address symbols (name @ address):
 *   rodata_f68c5                             @ 0x000f68c5
 *   rodata_f68d7                             @ 0x000f68d7
 *   rodata_f691a                             @ 0x000f691a
 *   rodata_f693a                             @ 0x000f693a
 */
/* Full reconstruction FUN_000640e8 @ 0x640e8, exact extent 60 bytes. */
#include <stdint.h>
extern uint64_t libc_fatal_error_and_abort(uintptr_t,uint32_t,uintptr_t,uintptr_t,uint32_t,uint32_t);
extern uintptr_t flash_calc_prev_ate_offset(void);
extern void flash_write_padded_entry(uintptr_t,uintptr_t,const uint8_t*,uint32_t);
void FUN_000640e8(uintptr_t object,uint32_t low,uint32_t high){
 if(high>14){
  uint64_t result=libc_fatal_error_and_abort(((unsigned long)&rodata_f68d7) /*=0xf68d7*/,0x182,((unsigned long)&rodata_f693a) /*=0xf693a*/,((unsigned long)&rodata_f68c5) /*=0xf68c5*/,object,low);
  low=(uint32_t)(result>>32);high=((unsigned long)&rodata_f693a) /*=0xf693a*/;
  while(low>14){result=libc_fatal_error_and_abort(((unsigned long)&rodata_f68d7) /*=0xf68d7*/,0x182,((unsigned long)&rodata_f693a) /*=0xf693a*/,((unsigned long)&rodata_f691a) /*=0xf691a*/,object,low);low=(uint32_t)(result>>32);}
 }
 uint8_t packed=(uint8_t)(low|(high<<4));
 flash_write_padded_entry(object,flash_calc_prev_ate_offset(),&packed,1);
}
