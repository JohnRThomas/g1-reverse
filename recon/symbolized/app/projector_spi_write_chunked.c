#include "g1_app_symbols.h"
/* named: projector_spi_write_chunked */
/* Reconstructed projector_spi_write_chunked @ 0x7d7b6  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern int get_projector_controller(void);
extern void projector_bus_lock(unsigned int,unsigned int);
extern void projector_bus_unlock(void);
void projector_spi_write_chunked(int param_1,unsigned int param_2){
  int iVar1=get_projector_controller();
  unsigned char local_24[8]; int iVar2;
  local_24[0]=0;
  iVar2=param_1+(int)((param_2/((uintptr_t)&rodata_f000) /*=0xf000*/)*((uintptr_t)&rodata_f000) /*=0xf000*/);
  for(; param_1!=iVar2; param_1=param_1+((uintptr_t)&rodata_f000) /*=0xf000*/){
    projector_bus_lock(0xffffffff,0xffffffff);
    (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,((uintptr_t)&rodata_f000) /*=0xf000*/,local_24,1);
    projector_bus_unlock();
  }
  projector_bus_lock(0xffffffff,0xffffffff);
  (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,param_2%((uintptr_t)&rodata_f000) /*=0xf000*/,local_24,1);
  projector_bus_unlock();
}

