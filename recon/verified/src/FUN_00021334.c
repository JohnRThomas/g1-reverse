/* Reconstructed FUN_00021334 @ 0x21334  (parity: 11/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00086c78(void*,int,int);
extern unsigned char FUN_00032784(void);
extern unsigned char FUN_000327c4(void);

unsigned FUN_00021334(int param_1, unsigned short *param_2){
  unsigned char loc[0x18];
  *(unsigned*)loc = 0;
  FUN_00086c78(loc+4, 0, 0x11);
  unsigned char bVar2 = *((unsigned char*)param_2 + 1);
  if(bVar2 > 0x12){
    if(bVar2 == 0xf1){
      *(unsigned short*)loc = 0xc90f;
      loc[2] = *(unsigned char*)(param_1 - 0x6b0);
    } else if(bVar2 == 0xf2){
      *(unsigned short*)loc = 0xc94e;
      loc[2] = *(unsigned char*)(param_1 - 0x6b0);
    } else if(bVar2 == 0xf0){
      *(unsigned short*)loc = 0xc90d;
      loc[2] = *(unsigned char*)(param_1 - 0x6af);
    } else {
      goto def;
    }
    loc[3] = *(volatile unsigned char*)0x20018d9aUL;
    *(volatile unsigned char*)0x20018d9aUL = 0;
    loc[4] = *(volatile unsigned char*)0x20018d99UL;
    *(volatile unsigned char*)0x20018d99UL = 0;
    goto call;
  }
  if(bVar2 <= 8) goto def;
  switch(bVar2){
  case 9:
    bVar2 = *((unsigned char*)param_2 + 2);
    *(unsigned short*)loc = *param_2;
    break;
  case 10:
    *(unsigned short*)loc = 0xaf5;
    bVar2 = *(unsigned char*)(param_1 + 0x844);
    if(bVar2 == 0x5d){
      bVar2 = (*(char*)(param_1+0x846)==0) ? 0x5e : 0x5f;
    } else if(bVar2 == 0x5e){
      bVar2 = (*(char*)(param_1+0x846)==0) ? 0x60 : 0x61;
    } else if(bVar2 == 0x5f){
      bVar2 = 0x62;
    } else if(bVar2 == 0x60){
      bVar2 = 0x63;
    } else if(bVar2 > 0x60){
      bVar2 = 0x64;
    }
    break;
  case 0xe:
    *(unsigned short*)loc = 0xef5;
    loc[2] = FUN_00032784();
    goto call;
  case 0xf:
    *(unsigned short*)loc = 0xff5;
    loc[2] = FUN_000327c4();
    goto call;
  case 0x12:
    *(unsigned short*)loc = 0x12f5;
    bVar2 = *(unsigned char*)(param_1 + 0x759);
    break;
  default:
    goto def;
  }
  loc[2] = bVar2;
  goto call;
def:
  *(unsigned short*)loc = (unsigned short)(((unsigned)bVar2 << 8) | 0xf5u);
  goto call;
call:
  (*(int(**)(void*,int))(param_1 + 0xc))(loc, 0x15);
  return 0;
}
