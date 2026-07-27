/* readable reconstruction; identity: FUN_0007d7b6 @ 0x0007d7b6
 * public-name: projector_spi_write_chunked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_bus_lock                       <= FUN_00047698 @ 0x00047698
 *   projector_bus_unlock                     <= FUN_000476a8 @ 0x000476a8
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   projector_spi_write_chunked              <= FUN_0007d7b6 @ 0x0007d7b6
 * address symbols (name @ address):
 *   rodata_f000                              @ 0x0000f000
 */
/* Reconstructed FUN_0007d7b6 @ 0x7d7b6  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern int get_projector_controller(void);
extern void projector_bus_lock(unsigned int, unsigned int);
extern void projector_bus_unlock(void);
void projector_spi_write_chunked(int param_1,unsigned int param_2){
  int iVar1=get_projector_controller();
  unsigned char local_24[8]; int iVar2;
  local_24[0]=0;
  iVar2=param_1+(int)((param_2/0xf000)*0xf000);
  for(; param_1!=iVar2; param_1=param_1+0xf000){
    projector_bus_lock(0xffffffff,0xffffffff);
    (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,0xf000,local_24,1);
    projector_bus_unlock();
  }
  projector_bus_lock(0xffffffff,0xffffffff);
  (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,param_2%0xf000,local_24,1);
  projector_bus_unlock();
}
