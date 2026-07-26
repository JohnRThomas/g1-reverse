/* readable reconstruction; identity: FUN_000640e8 @ 0x000640e8
 * public-name: boot_write_swap_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   boot_write_swap_info                     <= FUN_000640e8 @ 0x000640e8
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   flash_calc_prev_ate_offset               <= FUN_00084d64 @ 0x00084d64
 *   flash_write_padded_entry                 <= FUN_00084dea @ 0x00084dea
 * address symbols (name @ address):
 *   rodata_f68c5                             @ 0x000f68c5   [INLINED -- G6 literal batch]
 *   rodata_f68d7                             @ 0x000f68d7
 *   rodata_f691a                             @ 0x000f691a   [INLINED -- G6 literal batch]
 *   rodata_f693a                             @ 0x000f693a
 */
/* Full reconstruction FUN_000640e8 @ 0x640e8, exact extent 60 bytes. */
#include <stdint.h>
extern uint64_t __assert_func(uintptr_t,uint32_t,uintptr_t,uintptr_t,uint32_t,uint32_t);
extern uintptr_t flash_calc_prev_ate_offset(void);
extern void flash_write_padded_entry(uintptr_t,uintptr_t,const uint8_t*,uint32_t);
void boot_write_swap_info(uintptr_t object,uint32_t low,uint32_t high){
 if(high>14){
  uint64_t result=__assert_func(0x000f68d7u,0x182,0x000f693au,0x000f68c5u,object,low);
  low=(uint32_t)(result>>32);high=0x000f693au;
  while(low>14){result=__assert_func(0x000f68d7u,0x182,0x000f693au,0x000f691au,object,low);low=(uint32_t)(result>>32);}
 }
 uint8_t packed=(uint8_t)(low|(high<<4));
 flash_write_padded_entry(object,flash_calc_prev_ate_offset(),&packed,1);
}
