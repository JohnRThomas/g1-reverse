/* readable reconstruction; identity: FUN_00076ad0 @ 0x00076ad0
 * public-name: _fflush_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_acquire_recursive <= FUN_000510fc @ 0x000510fc
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 *   _fflush_r                                <= FUN_00076ad0 @ 0x00076ad0
 *   __sinit                                  <= FUN_00076bcc @ 0x00076bcc
 *   stdio_flush_write_buffer                 <= FUN_00086a0e @ 0x00086a0e
 */
/* Reconstructed FUN_00076ad0 @ 0x76ad0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void __sinit(unsigned long);
#define g1_recon_retarget_lock_acquire_recursive g1_recon_retarget_lock_acquire_recursive
extern void g1_recon_retarget_lock_acquire_recursive(uint32_t); /* FUN_000510fc@0x000510fc */
extern unsigned int stdio_flush_write_buffer(int *, int *);
#define g1_recon_retarget_lock_release_recursive g1_recon_retarget_lock_release_recursive
extern void g1_recon_retarget_lock_release_recursive(uint32_t); /* FUN_00051134@0x00051134 */
uint32_t _fflush_r(int param_1,int param_2){
  uint32_t uVar1;
  if(*(volatile int*)(param_2+0x10)!=0){
    if(param_1!=0 && *(volatile int*)(param_1+0x18)==0) __sinit(param_1);
    if(param_2==0x9871c) param_2=*(volatile int*)(param_1+4);
    else if(param_2==0x986fc) param_2=*(volatile int*)(param_1+8);
    else if(param_2==0x986dc) param_2=*(volatile int*)(param_1+0xc);
    if(*(volatile int16_t*)(param_2+0xc)!=0){
      if((*(volatile int*)(param_2+100)<<0x1f)>=0 && ((int)*(volatile int16_t*)(param_2+0xc)<<0x16)>=0)
        g1_recon_retarget_lock_acquire_recursive(*(volatile uint32_t*)(param_2+0x58));
      uVar1=stdio_flush_write_buffer(param_1,param_2);
      if((*(volatile int*)(param_2+100)<<0x1f)<0) return uVar1;
      if((int)((uint32_t)*(volatile uint16_t*)(param_2+0xc)<<0x16)<0) return uVar1;
      g1_recon_retarget_lock_release_recursive(*(volatile uint32_t*)(param_2+0x58));
      return uVar1;
    }
  }
  return 0;
}
