/* readable reconstruction; identity: FUN_0103721c @ 0x0103721c
 * public-name: FUN_0103721c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb30                           @ 0x0103eb30
 */
/* net-core FUN_0103721c @ 0x103721c  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline unsigned int getBasePriority(void){return __get_BASEPRI();}
static inline void setBasePriority(unsigned p){__set_BASEPRI(p);}
static inline void isb(void){__ISB();}
static inline unsigned int readIPSR(void){return __get_IPSR();}

#define C_010372a0 0x21004b68
#define C_010372a4 0x0103d3b6
#define C_010372a8 0x0103d2a7
#define C_010372ac 0x0103eb30
#define C_010372b0 0x21004b28

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void assert_print(int, int, unsigned int);
extern void assert_post_action(int, unsigned int);

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
  assert_print(C_010372a8, r1, r2);
  r1 = 0x72;
  goto L242;

L246:
  FUN_01036144(C_010372a0);
  r3 = (int)readIPSR();
  if (r3 == 0) goto L264;

  r1 = C_010372ac;
  r2 = 0xfd;
  assert_print(C_010372a8, r1, r2);
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
      assert_print(C_010372a8, r1, r2);
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
      assert_print(C_010372a8, r1, r2);
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
  assert_post_action(r0, (unsigned int)r1);
  goto L264;
}
