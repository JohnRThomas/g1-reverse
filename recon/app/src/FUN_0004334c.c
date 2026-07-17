/* Reconstructed FUN_0004334c @ 0x4334c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned,...);
extern unsigned FUN_000431a8(void);
extern int FUN_0004588c(int,unsigned,int*,int*,int*,unsigned char*);
extern void FUN_000471cc(unsigned,int,int,int,int,int);
extern void FUN_00047260(unsigned,unsigned,int,int,int,int);
extern void FUN_0007d53a(unsigned,int,int,int,int,int);

unsigned FUN_0004334c(unsigned param_1,int param_2,int param_3,int p4,int p5,int p6,unsigned char in_stack8){
  struct __attribute__((packed, aligned(4))) {
    unsigned char reserved[3];
    unsigned char depth;
    int width;
    int height;
    int bitmap[2];
    unsigned char tail_padding[4];
  } local;
  local.width = 0;
  local.height = 0;
  local.bitmap[0] = 0;
  int iVar5 = FUN_0004588c(5, param_1, &local.width, &local.height,
                           local.bitmap, &local.depth);
  if(iVar5 < 0){
    if(*(volatile int*)0x2000230cUL > 1){
      if(*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0x000aa8eb, 0x000aade4);
      else
        FUN_00019c70(0x000aa8eb, 0x000aade4);
    }
    return 0xffffffff;
  }
  *(volatile unsigned short*)0x2000f702UL = (unsigned short)local.depth;
  unsigned uVar7 = FUN_000431a8();
  unsigned pv4 = *(volatile unsigned*)0x2000a034UL;
  if((uVar7 & 2) != 0){
    FUN_000471cc(pv4, 0, param_2, param_3,
                 local.width + param_2, local.height + param_3);
  }
  unsigned short us = *(volatile unsigned short*)0x2000f700UL;
  FUN_0007d53a(pv4,
               local.height * ((int)(local.width * (unsigned)us) / 2) + local.bitmap[0],
               local.width / 2, local.height, param_2, param_3);
  int iVar = FUN_000431a8();
  if((int)(iVar << 0x1e) < 0){
    int t = FUN_000167a8();
    unsigned uv6 = *(volatile unsigned*)(t + 0xeb4);
    t = FUN_000167a8();
    FUN_00047260(uv6, *(volatile unsigned*)(t + 0xeb8), param_2, param_3,
                 local.width + param_2, local.height + param_3);
  }
  unsigned short uVar1 = *(volatile unsigned short*)0x2000f702UL;
  if(((int)(unsigned)*(volatile unsigned short*)0x2000f700UL < (int)(unsigned short)(uVar1 - 1))
     || (in_stack8 == 0)
     || ((int)(unsigned)*(volatile unsigned short*)0x2000f6feUL < (int)(in_stack8 - 1))){
    *(volatile unsigned short*)0x2000f700UL = *(volatile unsigned short*)0x2000f700UL + 1;
  }
  if((unsigned)uVar1 <= (unsigned)*(volatile unsigned short*)0x2000f700UL){
    *(volatile unsigned short*)0x2000f700UL = 0;
    *(volatile unsigned short*)0x2000f6feUL = *(volatile unsigned short*)0x2000f6feUL + 1;
  }
  return 0;
}
