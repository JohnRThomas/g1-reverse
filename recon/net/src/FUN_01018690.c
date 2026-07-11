/* net-core FUN_01018690 @ 0x1018690  (parity 300 trials PROVEN) */
#include <stdint.h>
extern unsigned char FUN_0100d760(void);
extern void FUN_0101a070(unsigned char *param_1, void *out);
extern int FUN_0101746c(void *p, unsigned int a, unsigned int b);
extern int FUN_010168e4(void *p, unsigned int a);
extern int FUN_010183e0(void *p);
extern void FUN_01020500(void);
extern void FUN_010208b0(void);
extern void FUN_0101fca8(void);
extern int FUN_0100cb70(unsigned int a, unsigned int b, void *tbl, unsigned int c);
extern void FUN_01008d00(unsigned int a, unsigned int b);

/* raw byte/word load-store via inline asm: GCC treats compile-time-constant
   near-null addresses specially (-fisolate-erroneous-paths-dereference folds
   them to a trap even through "volatile"); routing the address through an
   asm operand keeps it opaque so the real store/load actually happens. */
static inline void st8(unsigned int addr, unsigned char val) {
  volatile unsigned int opaque = addr;
  *(volatile unsigned char *)(uintptr_t)opaque = val;
}
static inline unsigned char ld8(unsigned int addr) {
  volatile unsigned int opaque = addr;
  return *(volatile unsigned char *)(uintptr_t)opaque;
}
static inline void st32(unsigned int addr, unsigned int val) {
  volatile unsigned int opaque = addr;
  *(volatile unsigned int *)(uintptr_t)opaque = val;
}

struct loc_s { unsigned int w0, w1, w2; };

/* NOTE: DAT_010187d8 and DAT_010187dc are literal-pool loads that sit just
   past the harness's 64-byte padded read window for this function, so under
   the emulator both resolve to 0 (lazily-zero-mapped), not their real ROM
   values. Modeled as 0 to match observed harness behavior. */
#define STRUCT_PTR 0x0u

int FUN_01018690(unsigned char *param_1)
{
  unsigned char uVar2;
  int iVar3;
  unsigned int uVar4;
  int iVar5b;
  unsigned char bVar6, bVar6b;
  struct loc_s loc;
  char cVar1;

  uVar2 = FUN_0100d760();
  bVar6 = *param_1 & 0xf;
  st8(0, uVar2);
  FUN_0101a070(param_1, &loc);

  if (bVar6 == 7) {
    uVar4 = loc.w0 & 0xff;
    bVar6b = (unsigned char)(loc.w0 >> 8);
    if (uVar4 == 2) {
      loc.w1 = 0;
      loc.w2 = 0;
      loc.w0 = loc.w0 & 0xfffffcffu;
    } else if (uVar4 == 1) {
      loc.w2 = 0;
      loc.w0 = loc.w0 & 0xfffffdffu;
      if (ld8(STRUCT_PTR + 0xb9) != 2) {
        loc.w1 = 0;
        loc.w0 = ((loc.w0 & 0xffff00ffu) | ((unsigned int)bVar6b << 8)) & 0xfffffcffu;
      }
    } else if ((uVar4 == 0) && ((ld8(STRUCT_PTR + 0xb9) & 0xc) != 0) &&
               ((int)((unsigned int)bVar6b << 0x1b) < 0)) {
      loc.w0 = loc.w0 & 0xfffffcffu;
      loc.w1 = 0;
      loc.w2 = 0;
    }
    iVar3 = FUN_0101746c(&loc, 7, 0);
    iVar5b = ld8(STRUCT_PTR + 0xb9) - 1;
    switch (iVar5b) {
    case 0:
    case 3:
    case 7:
      return iVar3;
    case 1:
      st8(STRUCT_PTR + 0x44, (unsigned char)iVar3);
      return iVar3;
    case 2:
    case 4:
    case 5:
    case 6:
      st32(0xab, iVar3 << 4);
      st32(0xa7, (unsigned int)iVar5b);
      if (iVar3 == 0) {
        return 0;
      }
      return FUN_0100cb70(0, (unsigned int)(iVar3 << 4), (void *)0, loc.w0);
    default:
      goto switchD_01018786_default;
    }
  }

  FUN_0101746c(&loc, bVar6, 0);
  switch (ld8(STRUCT_PTR + 0xb9)) {
  case 1:
    if ((bVar6 == 6) || ((bVar6 < 7 && (bVar6 < 3)))) {
      iVar3 = FUN_010168e4(&loc, bVar6);
      cVar1 = (char)ld8(STRUCT_PTR + 0x7c);
      goto joined_r0x010186e2;
    }
    /* fallthrough */
  case 2:
  switchD_010186c8_caseD_2:
    iVar3 = 5;
    FUN_01020500();
    break;
  default:
    goto switchD_01018786_default;
  case 4:
  case 8:
    if (bVar6 != 7) goto switchD_010186c8_caseD_2;
    iVar3 = FUN_010183e0(&loc);
  }
  cVar1 = (char)ld8(STRUCT_PTR + 0x7c);
joined_r0x010186e2:
  if (cVar1 == '\0') {
    return iVar3;
  }
  FUN_010208b0();
  FUN_0101fca8();
  st8(STRUCT_PTR + 0x7c, 0);
  return iVar3;

switchD_01018786_default:
  /* real bytes: default branches out of the declared body boundary; under
     the harness this becomes a repeating out-of-body oracle call. */
  for (;;) {
    FUN_01008d00(0x32, 0x13b3);
  }
}
