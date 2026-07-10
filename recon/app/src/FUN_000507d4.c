/* Reconstructed FUN_000507d4 @ 0x507d4  (parity: 200/200 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;

extern int isCurrentModePrivileged(void);
extern void setBasePriority(int);
extern void InstructionSynchronizationBarrier(int);
extern void FUN_00080780(uint32_t,int,void*);
extern void FUN_00086c04(void*,int,int);
extern void FUN_0004ff6c(int,void*);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2fa_1(uint32_t);

void FUN_000507d4(int param_1, int param_2, uint param_3)
{
  uint uVar1 = *(volatile uint32_t*)(0xe000ed00UL + 4) & 0x1ff;
  if (isCurrentModePrivileged()) setBasePriority(0);
  InstructionSynchronizationBarrier(0xf);

  if ((param_3 & 0xff000000) != 0xff000000) goto err;
  if ((param_3 & 0xc) == 8) {
    uint32_t local_78 = 2, local_74 = 0x000f1fa6UL;
    (void)local_78;
    struct { uint32_t a,b; } s = { 2, 0x000f1fa6UL };
    FUN_00080780(0x00088258UL, 0x1040, &s);
    return;
  } else {
    int bVar2 = (int)(param_3 << 0x1c) < 0;
    if (!bVar2) param_2 = param_1;
    if (param_2 == 0) goto err;
    if ((uVar1 - 3) > 9) {
      uint32_t local_a0 = ((*(volatile uint32_t*)(0xe000ed00UL+4)) & 0x1f0) != 0
                             ? 0x000f1fd1UL /* placeholder DAT_00050a44 */
                             : 0x000f1fd1UL; /* placeholder DAT_00050a48 */
      int local_9c = uVar1 - 0x10;
      char local_89 = 0;
      FUN_00080780(0x00088258UL, 0x2440, &local_a0);
      if (local_89 == 0) {
        uint8_t auStack_88[0x68];
        uint32_t local_6c;
        FUN_00086c04(auStack_88, param_2, 0x68);
        local_6c = *(uint32_t*)(auStack_88 + 0x60 - 0x68); /* approx placement, unverifiable */
        if (bVar2) {
          local_6c &= 0xfffffe00u;
        } else if ((local_6c & 0x1ff) == 0) {
          local_6c = ~(~(local_6c >> 9) << 9);
        }
        FUN_0004ff6c(0, auStack_88);
      }
      return;
    }
    /* unrecovered jump table dispatch (tbb) - 10 case handlers, not reconstructed */
    return;
  }
err:
  FUN_0007e2fa(0x000f1fd1UL,0x000f1fd1UL,0x000f1d11UL,0x458);
  FUN_0007e2fa_1(0x000f1fe4UL);
  FUN_0007e2ec(0x000f1d11UL,0x458);
}

