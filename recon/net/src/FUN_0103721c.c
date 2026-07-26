/* net-core FUN_0103721c @ 0x103721c  (parity 300 trials PROVEN) */
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the shipped CPUNET `_kernel` is at 0x21004b28.
 * In the relocated cohesive link that address is inside `sdc_mempool`
 * (0x21002bb8..0x21007e79), so every recovered kernel body that reaches the
 * scheduler through this base read/wrote a SHADOW copy of `_kernel` carved out
 * of the SoftDevice Controller's heap while the linked Zephyr scheduler
 * (z_arm_pendsv, arch_swap, z_ready_thread) used the real one at
 * &_kernel.  Iteration 7 converted only the four spinlock validators and
 * recorded the rest as open; this pass closes the whole window structurally.
 * Field offsets are identical in both images: +0x08 = cpus[0].current and
 * +0x10 = cpus[0].id were verified against the shipped disassembly in
 * iteration 7, which fixes struct _cpu at 0x14 bytes and therefore
 * ready_q.cache at +0x14 and ready_q.runq at +0x18; `nm -S` reports
 * sizeof(_kernel) = 0x20 in this link.
 * Parity builds keep the original literal, so no proven body changes. */
/* Reached through an asm label so no reconstruction TU has to pull in the
 * Zephyr kernel headers (several of them declare assert_print /
 * assert_post_action with the recovered prototypes). */
extern char g1_net_kernel_object[] __asm__("_kernel");
#define G1_NET_KERNEL_BASE ((unsigned long)g1_net_kernel_object)
#else
#define G1_NET_KERNEL_BASE 0x21004b28ul
#endif
#define G1_NET_K(off) (G1_NET_KERNEL_BASE + (off))

#include <stdint.h>
#include <cmsis_gcc.h>
static inline unsigned int getBasePriority(void){return __get_BASEPRI();}
static inline void setBasePriority(unsigned p){__set_BASEPRI(p);}
static inline void isb(void){__ISB();}
static inline unsigned int readIPSR(void){return __get_IPSR();}

#define C_010372a0 0x21004b68
#define C_010372a4 0x0103d3b6
#define C_010372a8 0x0103d2a7
#define C_010372ac 0x0103eb30
#define C_010372b0 G1_NET_K(0x00)

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);

void FUN_0103721c(void)
{
  unsigned int r4save;
  int r0;
  int r1;
  unsigned int r2;
  int r3;

  r4save = getBasePriority();
  setBasePriority(0x40);
  isb();
  r0 = C_010372a0;
  r0 = FUN_0103610c(r0);
  if (r0 != 0) goto L246;

  r1 = C_010372a4;
  r2 = 0x72;
  FUN_01039bbe(C_010372a8, r1, r2);
  r1 = 0x72;
  goto L242;

L246:
  FUN_01036144(C_010372a0);
  r3 = (int)readIPSR();
  if (r3 == 0) goto L264;

  r1 = C_010372ac;
  r2 = 0xfd;
  FUN_01039bbe(C_010372a8, r1, r2);
  r1 = 0xfd;
  r0 = C_010372ac;
  goto L260;

L264:
  {
    int base = C_010372b0;
    int p = *(int *)(base + 8);
    signed char b = *(signed char *)(p + 0xf);
    if (b == 1) {
      r1 = C_010372ac;
      r2 = 0xfe;
      FUN_01039bbe(C_010372a8, r1, r2);
      r1 = 0xfe;
      goto L25e;
    } else {
      b = (signed char)(b - 1);
      *(signed char *)(p + 0xf) = b;
      r0 = FUN_01036128(C_010372a0);
      if (r0 != 0) {
        setBasePriority(r4save);
        isb();
        return;
      }
      r1 = C_010372a4;
      r2 = 0xf0;
      FUN_01039bbe(C_010372a8, r1, r2);
      r1 = 0xf0;
      goto L242;
    }
  }

L25e:
  r0 = C_010372ac;
  goto L260;

L242:
  r0 = C_010372a4;
L260:
  FUN_01039bb0(r0, (unsigned int)r1);
  goto L264;
}
