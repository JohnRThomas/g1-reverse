#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076ad0 @ 0x00076ad0
 * public-name: _fflush_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   lock_release_or_fatal                    <= FUN_00051134 @ 0x00051134
 *   _fflush_r                                <= FUN_00076ad0 @ 0x00076ad0
 *   stdio_streams_init                       <= FUN_00076bcc @ 0x00076bcc
 *   stdio_flush_write_buffer                 <= FUN_00086a0e @ 0x00086a0e
 */
/* Reconstructed FUN_00076ad0 @ 0x76ad0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void stdio_streams_init(void);
extern void lock_acquire_or_fatal(uint32_t);
extern uint32_t stdio_flush_write_buffer(int,int);
extern void lock_release_or_fatal(uint32_t);
uint32_t _fflush_r(int param_1,int param_2){
  uint32_t uVar1;
  if(*(volatile int*)(param_2+0x10)!=0){
    if(param_1!=0 && *(volatile int*)(param_1+0x18)==0) stdio_streams_init();
    if(param_2==0x9871c) param_2=*(volatile int*)(param_1+4);
    else if(param_2==0x986fc) param_2=*(volatile int*)(param_1+8);
    else if(param_2==0x986dc) param_2=*(volatile int*)(param_1+0xc);
    if(*(volatile int16_t*)(param_2+0xc)!=0){
      if((*(volatile int*)(param_2+100)<<0x1f)>=0 && ((int)*(volatile int16_t*)(param_2+0xc)<<0x16)>=0)
        lock_acquire_or_fatal(*(volatile uint32_t*)(param_2+0x58));
      uVar1=stdio_flush_write_buffer(param_1,param_2);
      if((*(volatile int*)(param_2+100)<<0x1f)<0) return uVar1;
      if((int)((uint32_t)*(volatile uint16_t*)(param_2+0xc)<<0x16)<0) return uVar1;
      lock_release_or_fatal(*(volatile uint32_t*)(param_2+0x58));
      return uVar1;
    }
  }
  return 0;
}
