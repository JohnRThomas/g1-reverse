/* Reconstructed FUN_00052d58 @ 0x52d58  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d944(int,...);
extern int FUN_0007f1e8(int,...);
extern int FUN_00087036(int,...);
typedef int (*codeptr)(int, uintptr_t, unsigned int);
struct unaligned_u32 { unsigned int value; } __attribute__((packed));
_Static_assert(sizeof(struct unaligned_u32) == 4, "packed word layout");
unsigned int FUN_00052d58(int param_1, int param_2, codeptr param_3, int param_4)
{
  const uintptr_t g_addr = UINT32_C(0x200020d4);
  volatile int *const g = (volatile int *)g_addr;
  int iVar3, uVar2; unsigned int uVar4;
  unsigned char scratch[20];
  if ((int)((unsigned)*g << 0x1f) < 0) {
    if (param_1 == 0) {
      struct { unsigned kind, descriptor; } short_log = {2, 0xf2b65};
      FUN_0004d944(0x88178,0x1040,&short_log,0);
      return 0xfffffffe;
    }
    uVar2 = FUN_0007f1e8(param_1, scratch);
    iVar3 = FUN_00087036(param_1, 0x9a1dd, uVar2);
    if (iVar3 == 0) {
      int t = *g;
      unsigned uVar5 = (unsigned)t << 0x1c;
      unsigned uVar6 = uVar5 >> 0x1f;
      if ((int)uVar5 < 0) {
        struct { unsigned kind, descriptor; } short_log = {2, 0xf2b86};
        FUN_0004d944(0x88178,0x1080,&short_log,0);
      } else {
        uVar4 = param_3(param_4, g_addr - UINT32_C(0xd4), 7);
        if (uVar4 < 7) {
          struct { unsigned kind, descriptor; } short_log = {2, 0xf2baa};
          FUN_0004d944(0x88178,0x1040,&short_log,uVar6);
          *(volatile int *)(g_addr - UINT32_C(0xd4)) = (int)uVar6;
          *(volatile unsigned char *)(g_addr - UINT32_C(0xcd)) =
              (unsigned char)(uVar5 >> 0x1f);
          ((volatile struct unaligned_u32 *)(g_addr - UINT32_C(0xd1)))->value = uVar6;
        } else {
          *(volatile unsigned char *)(g_addr - UINT32_C(0xcd)) =
              (unsigned char)(uVar4 / 7);
        }
      }
    } else {
      iVar3 = FUN_00087036(param_1, 0xf33e4, uVar2, iVar3);
      if (iVar3 != 0) return 0xfffffffe;
      int iStack_48 = param_3(param_4, g_addr + UINT32_C(0x98), 0x1c);
      if (iStack_48 < 0) {
        struct { unsigned kind, descriptor, value; } full_log = {
          3, 0xf2bcf, (unsigned)iStack_48
        };
        FUN_0004d944(0x88178,0x1840,&full_log,0);
      } else {
        *(volatile unsigned char *)(g_addr + UINT32_C(0x98) +
                                    (uintptr_t)iStack_48) = 0;
      }
    }
  }
  return 0;
}
