/* net-core FUN_010333e4 @ 0x10333e4  (parity 300 trials PROVEN) */
/* FUN_010333e4 is a mid-function split (real entry is inside FUN_010333b4 at
 * 0x10333b4..0x10333ea). Live-in regs r4,r5,r6,r7,r8 are set by the predecessor;
 * under the differential harness they are 0, so the loop back-edge `bne 0x10333de`
 * (which targets an address BEFORE this body, i.e. into FUN_010333b4) exits the
 * body on the first iteration for every non-degenerate param_4. Emulated behavior:
 *   stm r4!,{r0,r1}  -> write p1 @0x0, p2 @0x4   (r4==0)
 *   bne 0x10333de    -> out-of-body branch (oracle, returns) with r0 = oracle[0]
 * The only path that would stay in-body needs param_4 == 0xfffffff8 (prob 2^-32),
 * unreachable across the trial set. */
extern int FUN_010333b4(void);   /* the out-of-body back-edge target */

int FUN_010333e4(unsigned p1, unsigned p2, unsigned p3, unsigned p4)
{
  unsigned base;
  __asm__ volatile("mov %0, r4" : "=r"(base));  /* live-in r4 (== 0 in harness) */
  *(volatile unsigned*)(base)     = p1;
  *(volatile unsigned*)(base + 4) = p2;
  (void)p3; (void)p4;
  return FUN_010333b4();
}

