/* Reconstructed FUN_0004967c @ 0x4967c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,unsigned);
extern void FUN_00019c70(unsigned,unsigned,...);
extern void FUN_0004904c(void);
extern int FUN_000720d0(unsigned,void*,int,int);
extern void FUN_00086c04(void*,int,unsigned);
extern void FUN_00086c78(void*,int,unsigned);
extern long long thunk_FUN_00074f68(void);

unsigned FUN_0004967c(int param_1, unsigned param_2){
  unsigned char packet[24];
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  FUN_00086c78(packet,0,24);
  if(param_2 < 0xb){
    long long lVar7 = thunk_FUN_00074f68();
    if(*piVar1 > 2){
      if(*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0x000effd2,0x000f019a,0,0);
      else
        FUN_00019c70(0x000effd2,0x000f019a);
    }
    FUN_00086c78(packet + 1,0,23);
    packet[0] = 2;
    if(param_1 != 0){
      FUN_00086c04(packet + 4,param_1,param_2);
      packet[2] = (uint8_t)param_2;
      packet[3] = (uint8_t)(param_2 >> 8);
    }
    int iVar2 = FUN_000720d0(0x200038c4,packet,0,0);
    if(iVar2 == 0){
      if(*piVar1 > 2){
        if(*(volatile int*)0x20007554UL == 0)
          DEBUG_PRINT(0x000efff4,0x000f019a,0,0);
        else
          FUN_00019c70(0x000efff4,0x000f019a);
      }
      long long lVar8 = thunk_FUN_00074f68();
      if(*piVar1 > 2){
        unsigned uVar5 = (unsigned)(((uint64_t)lVar8 * UINT64_C(1000)) >> 0x20);
        unsigned uVar3 = (unsigned)(((uint64_t)lVar7 * UINT64_C(1000)) >> 0x20);
        unsigned uVar4 = (unsigned)((uint64_t)lVar8 * UINT64_C(1000)) >> 0xf | uVar5*0x20000;
        unsigned uVar6 = (unsigned)((uint64_t)lVar7 * UINT64_C(1000)) >> 0xf | uVar3*0x20000;
        if(*(volatile int*)0x20007554UL == 0)
          DEBUG_PRINT(0x000f001c,0x000f019a, uVar4-uVar6,
                      ((uVar5>>0xf)-(uVar3>>0xf)) - (unsigned)(uVar4<uVar6));
        else
          FUN_00019c70(0x000f001c,0x000f019a, uVar4-uVar6,
                       ((uVar5>>0xf)-(uVar3>>0xf)) -
                           (unsigned)(uVar4<uVar6));
      }
      FUN_0004904c();
      return 0;
    }
    DEBUG_PRINT(0x000ef058,0x000f019a,0,0);
  } else if(*piVar1 > 0){
    if(*(volatile int*)0x20007554UL == 0)
      DEBUG_PRINT(0x000ef01c,0x000f019a,10,0);
    else
      FUN_00019c70(0x000ef01c,0x000f019a,10);
  }
  return 0xffffffff;
}
