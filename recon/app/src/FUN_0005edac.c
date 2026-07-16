/* Reconstructed FUN_0005edac @ 0x5edac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005ec84(void*,int,int);
extern int FUN_000835ae(void*,void*,int);
void FUN_0005edac(int param_1,int param_2,int param_3,int param_4,int *param_5){
  uint8_t buf[0x60];
  FUN_0005ec84(buf+0x10, param_1, 0x20);
  FUN_0005ec84(buf+0x30, param_2, 0x20);
  FUN_0005ec84(buf+0x50, param_4, 0x10);
  FUN_0005ec84(buf, param_3, 0x10);
  int iVar1 = FUN_000835ae(buf, buf+0x10, 0x50);
  if(iVar1 == 0){
    uint32_t local_64 = *(volatile uint32_t*)(buf+0xc);
    uint32_t uVar2 = __builtin_bswap32(local_64);
    uint32_t d = 0x000f4240;
    uint32_t rem = uVar2 - d*(uVar2/d);
    *param_5 = rem;
  }
}
