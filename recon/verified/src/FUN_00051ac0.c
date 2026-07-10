/* Reconstructed FUN_00051ac0 @ 0x51ac0  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0000ef12(void*);
extern int FUN_00051f88(void*,void*);
extern int FUN_00052038(unsigned,void*,void*,void*);
extern int FUN_0008099e(unsigned,void*,int);
extern int FUN_00086320(unsigned,unsigned);
extern int FUN_00086338(unsigned,void*);
extern int FUN_0008634c(unsigned,int);
extern int FUN_00086378(unsigned,unsigned);
extern int thunk_FUN_00086354(unsigned,int);
unsigned FUN_00051ac0(unsigned param_1,unsigned param_2,unsigned param_3){
  unsigned char buf5c[8], buf54[24], l3c, buf38[36];
  unsigned local_68; unsigned char* local_64=buf38; int local_60=0x20; (void)local_60;
  int iVar1; unsigned uVar2; unsigned char* puVar3; int uVar4;
  iVar1 = FUN_00052038(param_2,buf5c,local_64,&local_68);
  if (iVar1==0){
    iVar1 = FUN_0008634c(param_1,0xf);
    uVar2 = 0;
    if (iVar1!=0 && (iVar1=FUN_0008099e(param_1,(void*)0xf349f,5))!=0 &&
        (iVar1=FUN_00086320(param_1,param_2>>1))!=0 &&
        (iVar1=FUN_0008099e(param_1,(void*)0xf272f,4))!=0 &&
        (iVar1=FUN_00086320(param_1,param_2&1))!=0 &&
        (iVar1=FUN_0008099e(param_1,(void*)0xf6589,7))!=0){
      iVar1 = FUN_00051f88(buf5c,buf54);
      if (iVar1<0){ uVar4=5; puVar3=(void*)0xf2734; }
      else { l3c=0; buf54[0]=l3c; uVar4=FUN_0000ef12(buf54); puVar3=buf54; }
      iVar1 = FUN_0008099e(param_1,puVar3,uVar4);
      if (iVar1!=0 && (iVar1=FUN_0008099e(param_1,(void*)0xf4a01,4))!=0 &&
          (iVar1=FUN_00086338(param_1,&local_64))!=0 &&
          (iVar1=FUN_0008099e(param_1,(void*)0xf273a,8))!=0 &&
          (iVar1=FUN_00086378(param_1,((local_68^0x10)>>4)&1))!=0 &&
          (iVar1=FUN_0008099e(param_1,(void*)0xf2743,7))!=0 &&
          (iVar1=FUN_00086378(param_1,(param_3>>1)&1))!=0 &&
          (iVar1=FUN_0008099e(param_1,(void*)0xf274b,9))!=0 &&
          (iVar1=FUN_00086378(param_1,(param_3>>2)&1))!=0 &&
          (iVar1=FUN_0008099e(param_1,(void*)0xf5702,6))!=0 &&
          (iVar1=FUN_00086378(param_1,param_3&1))!=0 &&
          (iVar1=FUN_0008099e(param_1,(void*)0xf2755,9))!=0 &&
          (iVar1=FUN_00086378(param_1,(param_3>>3)&1))!=0){
        uVar2 = thunk_FUN_00086354(param_1,0xf);
      }
    }
    uVar2 = uVar2 & 1;
  } else uVar2 = 1;
  return uVar2;
}

