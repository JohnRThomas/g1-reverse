/* Reconstructed FUN_00075944 @ 0x75944  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00086406(void);
extern int* FUN_00075864(int,...);
int* FUN_00075944(unsigned p1, unsigned p2, unsigned p3, unsigned p4){
  int iVar2 = FUN_00086406();
  int iVar3;
  if(iVar2==0){
    iVar3 = *(volatile int*)(*(volatile int*)(0x2000b448+8)+0x88);
    if(iVar3==0) return 0;
  } else {
    iVar3 = 0x200037d8;
  }
  return FUN_00075864(iVar3, p1, p2);
}

