/* readable reconstruction; identity: FUN_0008790e @ 0x0008790e
 * public-name: dynbuf_push_byte_grow
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   _realloc_r                               <= FUN_000876ec @ 0x000876ec
 *   dynbuf_push_byte_grow                    <= FUN_0008790e @ 0x0008790e
 */
/* Reconstructed FUN_0008790e @ 0x8790e  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int _malloc_r(uint32_t,int);
extern void memcpy(int, int, int);
extern int _realloc_r(uint32_t,int,int);
uint32_t dynbuf_push_byte_grow(uint32_t param_1,volatile int* param_2){
  int iVar1,iVar2;
  if((int*)param_2[0xd]==(int*)(param_2+0x11)){
    iVar1=_malloc_r(param_1,0x400);
    if(iVar1!=0){
      param_2[0xd]=iVar1;
      param_2[0xe]=0x400;
      *(volatile uint8_t*)(iVar1+0x3ff)=*(volatile uint8_t*)((int)param_2+0x46);
      *(volatile uint8_t*)(iVar1+0x3fe)=*(volatile uint8_t*)((int)param_2+0x45);
      *(volatile uint8_t*)(iVar1+0x3fd)=*(volatile uint8_t*)((int)param_2+0x44);
      *param_2=iVar1+0x3fd;
      return 0;
    }
  } else {
    iVar2=param_2[0xe];
    iVar1=_realloc_r(param_1,param_2[0xd],iVar2<<1);
    if(iVar1!=0){
      memcpy(iVar1+iVar2,iVar1,iVar2);
      *param_2=iVar1+iVar2;
      param_2[0xd]=iVar1;
      param_2[0xe]=iVar2<<1;
      return 0;
    }
  }
  return 0xffffffff;
}
