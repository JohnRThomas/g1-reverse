struct _reent;
#include <stdio.h>
/* Reconstructed FUN_00086c88 @ 0x86c88  (parity: 300/300 trials, PROVEN) */
extern int __swbuf_r(struct _reent *, int,  FILE *);
unsigned FUN_00086c88(int param_1, unsigned param_2, int *param_3){
  int iVar4 = param_3[2] - 1;
  *(volatile int*)(param_3 + 2) = iVar4;
  if (iVar4 >= 0 || (param_3[6] <= iVar4 && param_2 != 10)){
    unsigned char *p = *(unsigned char**)param_3;
    *(volatile int*)param_3 = (int)(p + 1);
    *(volatile unsigned char*)p = (unsigned char)param_2;
    return param_2;
  }
  return __swbuf_r(param_1, param_2, param_3);
}
