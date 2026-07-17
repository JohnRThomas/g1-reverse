#include "g1_net_symbols.h"
/* net-core FUN_0101c420 @ 0x101c420  (parity 300 trials PROVEN) */
#define P_0101c4a4 ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/

extern int FUN_010091f8(int, unsigned int);
extern void FUN_01008d00(int, int);

void FUN_0101c420(void)
{
  int r2;
  unsigned char r3;
  int r0;
  unsigned char r1;

  r2 = *(int *)(P_0101c4a4 + 4);
  r3 = *(unsigned char *)(r2 + 0x154);
  if (r3 < 8) goto L478;

L42e:
  r1 = (unsigned char)(r3 - 8);
  if (r1 <= 3) goto L458;

L438:
  if (r3 <= 0xb) return;
  if (r3 != 0xc) {
    for (;;) {
      FUN_01008d00(0x36, 0x963);
    }
  }
  *(unsigned char *)(r2 + 0x154) = 0;
  *(unsigned char *)(r2 + 0x14e) = 3;
  *(unsigned short *)(r2 + 0xfc) = 0;
  *(unsigned char *)(r2 + 0x100) = 1;
  return;

L458:
  r0 = FUN_010091f8(r2 + r3 + 0x138, (unsigned char)(4 - r1));
  r2 = *(int *)(P_0101c4a4 + 4);
  r3 = (unsigned char)(*(unsigned char *)(r2 + 0x154) + r0);
  *(unsigned char *)(r2 + 0x154) = r3;
  goto L438;

L478:
  r1 = (unsigned char)(8 - r3);
  r0 = FUN_010091f8(r2 + r3 + 0x34b, r1);
  r2 = *(int *)(P_0101c4a4 + 4);
  r3 = (unsigned char)(*(unsigned char *)(r2 + 0x154) + r0);
  *(unsigned char *)(r2 + 0x154) = r3;
  goto L42e;
}
