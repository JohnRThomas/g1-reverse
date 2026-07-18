/* Reconstructed FUN_00054a44 @ 0x54a44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00012080(void);
extern int FUN_00052edc(void);
extern void FUN_00071eac(unsigned,unsigned,int,unsigned,int,int,int,int);
extern void FUN_00072fdc(int);
extern void FUN_000730b4(unsigned);
extern void FUN_000730e8(unsigned,unsigned,int,int,int);
extern int FUN_00080e6a(unsigned,int);
extern void FUN_00080ea2(unsigned,unsigned,void*);
extern unsigned FUN_00080ea8(int,unsigned);
extern void FUN_00086412(unsigned,unsigned);
#define z_impl_k_queue_init FUN_000864e8
extern void z_impl_k_queue_init(void *queue);
extern void FUN_00086534(int,int);
typedef int (*cf)(void);
int FUN_00054a44(int param_1)
{
  int iVar1 = 0x20002000, iVar3; unsigned uVar2;
  int local_40, local_38; unsigned local_3c, uStack_34, local_20, local_1c;
  if (*(int*)(iVar1 + 0x168) == 0) {
    iVar3 = -0x13; local_1c = 0x000f3376; local_20 = 2;
    FUN_00080ea2(0x00088138, 0x1040, &local_20);
  } else {
    uVar2 = FUN_00080ea8(iVar1 + 0xd4, 0xfffffffd);
    iVar3 = FUN_00080e6a(uVar2, 1);
    if (iVar3 << 0x1f < 0) {
      iVar3 = -0x78;
    } else {
      iVar3 = FUN_00052edc();
      if (iVar3 == 0) {
        *(volatile int*)0x2000ac6c = param_1;
        FUN_00086534(iVar1 + 0x128, 1);
        z_impl_k_queue_init((void *)(iVar1 + 0x14c));
        local_38 = 0; uStack_34 = 0; local_40 = iVar3;
        FUN_00071eac(0x20005e30, 0x2002bb80, 0x400, 0x000545f1, 0, 0, 0, 0xfffffff7);
        FUN_00086412(0x20005e30, 0x000f338f);
        FUN_000730b4(0x20005f08);
        FUN_000730e8(0x20005f08, 0x2002bf80, 0x898, 0xfffffff8, 0);
        FUN_00086412(0x20005f08, 0x000f3395);
        iVar3 = (*(cf*)(*(int*)(iVar1 + 0x168) + 0xc))();
        if (iVar3 == 0) {
          if (param_1 == 0) iVar3 = FUN_00012080();
          else FUN_00072fdc(iVar1 + 0xc4);
        } else {
          local_3c = 0x000f339b; local_40 = 3; local_38 = iVar3;
          FUN_00080ea2(0x00088138, 0x1840, &local_40);
        }
      }
    }
  }
  return iVar3;
}
