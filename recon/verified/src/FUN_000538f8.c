/* Reconstructed FUN_000538f8 @ 0x538f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005ee08(unsigned);
extern int FUN_0005ee18(int);
extern void FUN_0005f24c(void);
extern void FUN_00072880(unsigned);
extern void FUN_00080e6a(int);
extern void FUN_00080ea2(unsigned,unsigned,void*);
extern void FUN_00080ea8(int,int);

void FUN_000538f8(unsigned param_1, int param_2, int param_3, unsigned param_4){
  int iVar3 = FUN_0005ee08(*(unsigned char*)(param_3 + 10));
  if(*(volatile int*)0x20003b4cUL == iVar3){
    int iVar4 = FUN_0005ee18(param_3);
    if(*(volatile unsigned short*)(iVar4*0xc + 0x2000abf4 + 2) == (unsigned short)param_1){
      if(*(volatile int*)(0x20002000UL + 0x140) != 0){
        FUN_0005f24c();
        *(volatile int*)(0x20002000UL + 0x140) = 0;
      }
      {
        int i = FUN_0005ee18(param_3);
        if(*(volatile int*)(i*0xc + 0x2000abf4 + 4) != 0 && param_2 == 0){
          int j = FUN_0005ee18(param_3);
          int *piVar5 = *(int* volatile*)(j*0xc + 0x2000abf4 + 4);
          unsigned uVar6 = (unsigned)piVar5[1] >> 5;
          if((char)piVar5[2] == 0)
            FUN_00080ea8(piVar5[0] + uVar6*4, ~(1 << (piVar5[1] & 0x1f)));
          else
            FUN_00080e6a(piVar5[0] + uVar6*4);
        }
      }
      {
        int k = FUN_0005ee18(param_3);
        if(*(volatile int*)(k*0xc + 0x2000abf4 + 8) != 0){
          int m = FUN_0005ee18(param_3);
          *(volatile char*)(0x2000abf4UL + m*0xc) = (char)param_2;
          int n = FUN_0005ee18(param_3);
          FUN_00072880(*(volatile unsigned*)(n*0xc + 0x2000abf4 + 8));
        }
      }
    } else {
      int i = FUN_0005ee18(param_3);
      unsigned st[8];
      st[0]=4; st[3]=0x000f2f8e; st[4]=param_1; st[7]=*(volatile unsigned short*)(i*0xc + 0x2000abf4 + 2);
      FUN_00080ea2(0x00088138, 0x2080, st);
    }
  } else {
    unsigned char bVar1 = *(unsigned char*)(param_3 + 10);
    unsigned st[8];
    st[2] = FUN_0005ee08((unsigned)bVar1);
    st[0]=6; st[1]=0x000f2f59; st[7]=0x20003b4c; st[5]=param_1; st[6]=bVar1;
    FUN_00080ea2(0x00088138, 0x3080, st);
  }
}

