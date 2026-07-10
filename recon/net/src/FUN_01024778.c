/* net-core FUN_01024778 @ 0x1024778  (parity 300 trials PROVEN) */
/* net-core FUN_01024778 @ 0x1024778  (parity 300 trials PROVEN) */

extern void FUN_01024aa8(void);
extern void FUN_010256dc(int,int) __attribute__((noreturn));

volatile unsigned char *const G6 = (volatile unsigned char*)0x21001bd6;
volatile unsigned char *const Gf = (volatile unsigned char*)0x21001bdf;

void FUN_01024778(void)
{
  unsigned int primask;
  __asm__ volatile("mrs %0, primask" : "=r"(primask));
  __asm__ volatile("cpsid i");
  if (*G6 == 0) {
    FUN_010256dc(0x6d,300);
  }
  *G6 = *G6 - 1;
  if ((*G6 == 0) && (*Gf == 0)) {
    FUN_01024aa8();
  }
  if (primask == 0) {
    __asm__ volatile("cpsie i");
  }
}



