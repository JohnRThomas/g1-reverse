/* readable reconstruction; identity: FUN_00076bcc @ 0x00076bcc
 * public-name: __sinit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 *   newlib_stdio_init_stream                 <= FUN_00076b48 @ 0x00076b48
 *   __sinit_lock_acquire                     <= FUN_00076bb4 @ 0x00076bb4
 *   __sinit_lock_release                     <= FUN_00076bc0 @ 0x00076bc0
 *   __sinit                                  <= FUN_00076bcc @ 0x00076bcc
 *   __sfp                                    <= FUN_00076c3c @ 0x00076c3c
 * address symbols (name @ address):
 *   rodata_76b91                             @ 0x00076b91
 *   rodata_9873c                             @ 0x0009873c
 */
/* Reconstructed FUN_00076bcc @ 0x76bcc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void g1_recon_retarget_lock_release_recursive(uint32_t);
extern void newlib_stdio_init_stream(uint32_t,int,int);
extern void __sinit_lock_acquire(void);
extern uint32_t __sfp(int);
extern void __sinit_lock_release(void);
void __sinit(int param_1){
  __sinit_lock_acquire();
  if(*(volatile int*)(param_1+0x18)!=0){ __sinit_lock_release(); return; }
  *(volatile uint32_t*)(param_1+0x48)=0;
  *(volatile uint32_t*)(param_1+0x4c)=0;
  *(volatile uint32_t*)(param_1+0x50)=0;
  int iVar2=*(volatile int*)0x9873cUL;
  *(volatile uint32_t*)(param_1+0x28)=0x76b91;
  if(iVar2==param_1) *(volatile uint32_t*)(param_1+0x18)=1;
  uint32_t u;
  u=__sfp(param_1); *(volatile uint32_t*)(param_1+4)=u;
  u=__sfp(param_1); *(volatile uint32_t*)(param_1+8)=u;
  u=__sfp(param_1); *(volatile uint32_t*)(param_1+0xc)=u;
  newlib_stdio_init_stream(*(volatile uint32_t*)(param_1+4),4,0);
  newlib_stdio_init_stream(*(volatile uint32_t*)(param_1+8),9,1);
  newlib_stdio_init_stream(*(volatile uint32_t*)(param_1+0xc),0x12,2);
  *(volatile uint32_t*)(param_1+0x18)=1;
  __sinit_lock_release();
}
