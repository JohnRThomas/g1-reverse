/* Reconstructed FUN_00052e7c @ 0x52e7c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007ddbe(int,int,int,int,...);
void FUN_00052e7c(int param_1,int param_2,int param_3,uint8_t *param_4,int param_5){
  volatile uint8_t *p = param_4;
  uint8_t b6=p[6],b5=p[5],b4=p[4],b3=p[3],b2=p[2],b1=p[1],b0=p[0];
  if(param_5 == 0){
    FUN_0007ddbe(param_1,param_2,0x000f2c25,param_3,b6,b5,b4,b3,b2,b1,b0);
  } else {
    FUN_0007ddbe(param_1,param_2,0x000f2c01,param_3,b6,b5,b4,b3,b2,b1,b0,param_5);
  }
}

