/* Reconstructed FUN_00030c24 @ 0x30c24
 *
 * ITERATION 17 CORRECTION (collapsed stack objects).  The previous body
 * declared the six descriptor fields as SEPARATE stack scalars and passed only
 * `&local_20` to the callee.  GCC is entitled to drop stores to the other five
 * objects because taking the address of `local_20` does not make them escape,
 * and it did: the emitted frame was
 *     push {r0,r1,r4,lr} ; str r0,[sp,#4] ; ... ; add r1,sp,#4
 * i.e. FIVE of the six shipped stores were gone and the callee read garbage.
 * The original writes a two-element descriptor array:
 *     30c2a  strd r4,r1,[sp]      ; msgs[0] = { param_1, param_2 }
 *     30c38  strb r1,[sp,#8]      ; msgs[0].flags = 0
 *     30c2e  strd r2,r3,[sp,#12]  ; msgs[1] = { param_3, param_4 }
 *     30c3e  strb r3,[sp,#20]     ; msgs[1].flags = 7
 *     30c4c  blx api->transfer(dev, msgs, 2, 0x12)
 * Expressed as a real array the emitted frame is instruction-for-instruction
 * the original's (only the 0x20002418 address materialisation differs, because
 * our build reaches that global through a linker pin rather than a literal).
 *
 * flags 0 / 7 are I2C_MSG_WRITE and I2C_MSG_READ|STOP|RESTART, so this is the
 * write-then-read half of the ops table at 0x20002408; 0x30c60 is the
 * write-only half.
 */

struct g1_i2c_msg { unsigned char *buf; unsigned int len; unsigned char flags; };
typedef int (*fnptr)(unsigned int, struct g1_i2c_msg *, int, int);

int FUN_00030c24(unsigned char *param_1, unsigned int param_2,
                 unsigned char *param_3, unsigned int param_4)
{
  struct g1_i2c_msg msgs[2];
  int iVar1;
  unsigned int base;
  fnptr fp;
  msgs[0].buf = param_1;
  msgs[0].len = param_2;
  msgs[0].flags = 0;
  msgs[1].buf = param_3;
  msgs[1].len = param_4;
  msgs[1].flags = 7;
  base = *(volatile unsigned int *)0x20002418UL;
  fp = *(fnptr *)(*(unsigned int *)(base + 8) + 8);
  iVar1 = fp(base, msgs, 2, 0x12);
  if (iVar1 != 0) iVar1 = 1;
  return -iVar1;
}
