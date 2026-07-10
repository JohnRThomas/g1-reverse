/* Reconstructed slave_display_thread @ 0x27cfe  (parity: 1/1 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT();
extern void FUN_00019c70();
extern int32_t FUN_000167a8();
extern int32_t FUN_00032ee4();
extern void change_work_mode_to();
extern void thunk_FUN_00072908();
extern void thunk_FUN_00074844();
extern void thunk_FUN_00072880();
extern void thunk_FUN_000745c8();
extern void thunk_FUN_00043308();
extern void FUN_00047058();
extern int32_t FUN_0002bed0();
extern void FUN_0007cbfe();
extern void FUN_0002bc2c();
extern void FUN_00042fb0();
extern void FUN_00023bfc();
extern void FUN_000498c0();
extern void FUN_0007cdb6();
extern void FUN_0002bef4();
extern void FUN_0003707c();
extern void FUN_00049938();
extern int32_t FUN_0007d224();
extern void FUN_00037108();
extern void FUN_000371e8();
extern void FUN_000499b8();
extern void FUN_00049a28();
extern void FUN_00023af0();
extern void FUN_000429f8();
extern void FUN_00040708();
extern uint64_t FUN_0007cb2c();
extern int32_t FUN_0007c132();
extern void FUN_0002bffc();
extern void FUN_00033d58();
extern void FUN_0002c1fc();
extern void FUN_0003439c();
extern void FUN_00034274();
extern void FUN_0003443c();
extern int32_t FUN_00033cf8();
extern void FUN_0007cce8();
extern void FUN_0003441c();
extern void FUN_00023eec();
extern void FUN_0002c0e8();
extern void FUN_0003cb4c();
extern void FUN_0007cb54();

#define B(o)   (*(volatile uint8_t *)(param_1+(o)))
#define SB(o)  (*(volatile int8_t  *)(param_1+(o)))
#define I32(o) (*(volatile int32_t *)(param_1+(o)))
#define DL     (*(volatile int32_t *)0x2000230cUL)
#define GV     (*(volatile int32_t *)0x20007554UL)
#define DBG1     do{ if (GV==0) DEBUG_PRINT(); else FUN_00019c70(); }while(0)
#define DBG_D224 do{ FUN_0007d224(); if (GV==0) DEBUG_PRINT(); else FUN_00019c70(); goto top; }while(0)

void slave_display_thread(int param_1, uint32_t param_2, uint32_t param_3, uint8_t param_4)
{
  int32_t p;
  int8_t cv;
  uint8_t b2, b15;

  B(0xfe7) = param_4;
  B(0xd5) = 0;
  if (1 < DL) DBG1;
  if (B(0xfea) == 0xb) change_work_mode_to();

top:
  if (B(0xfea) == 0xb) {
    B(0xd4) = B(0xd4) & 0xc0;
    B(0xd5) = (FUN_00032ee4() == 0) ? 6 : 3;
    thunk_FUN_00074844();
    goto while_cond;
  }
  thunk_FUN_00072908();
  goto while_cond;
while_body:
  thunk_FUN_00074844();
while_cond:
  if (SB(1) == 1 || *(volatile int8_t *)(FUN_000167a8() + 1) == 8) goto while_body;

  if (SB(0xed7) != SB(0xcb) || SB(0xed5) != SB(0xed7)) {
    if (FUN_00032ee4() == 1) {
      FUN_00047058();
      B(0xcb)  = B(0xed5);
      B(0xed7) = B(0xed5);
    } else {
      B(0xed7) = B(0xcb);
      B(0xed5) = B(0xcb);
      FUN_00047058();
    }
  }

  switch (B(0xd4) & 0x3f) {

  case 0:
    if (SB(0xfe6) != 1) goto Ldefault;
    if (SB(0xd5) != 6 && FUN_0002bed0() == 0) {
      if (0 < DL) DBG1;
      goto top;
    }
    if (2 < DL) DBG1;
    change_work_mode_to();
    if (SB(0xd5) == 6 && SB(0xee4) != 2) B(0xee4) = 2;
    goto Ldefault;

  case 1:
    if (2 < DL) DBG1;
    cv = SB(0xfe6);
    *(volatile uint8_t *)0x20018d97UL = 1;
    *(volatile uint8_t *)0x20018d96UL = 1;
    if (cv == 0) {
      FUN_0007cbfe();
      B(0xee4) = 1;
      {
        volatile uint8_t *p13 = *(volatile uint8_t **)(param_1 + 0x1054);
        p13[0] = 0; p13[1] = 0; p13[2] = 0; p13[3] = 0;
      }
      FUN_0002bc2c();
      thunk_FUN_00072880();
    } else {
      thunk_FUN_00074844();
    }
    if (2 < DL) DBG1;
    goto top;

  case 2:
    if (2 < DL) DBG1;
    if (SB(0xe5) == 0xb) {
      if (1 < DL) DBG1;
      if (B(0xe6) < 10 && B(0xe7) < 9) {
        *(volatile uint8_t *)(FUN_000167a8() + 0xec1) = B(0xe6);
        *(volatile uint8_t *)(FUN_000167a8() + 0xec0) = B(0xe7);
        (void)FUN_000167a8();
        (void)FUN_000167a8();
        FUN_00042fb0();
      }
    }
    *(volatile uint8_t *)0x20018d96UL = 1;
    {
      int8_t d5 = SB(0xd5);
      if (d5 == 9 || d5 == 0xc || d5 == 0xa || d5 == 0xb || d5 == 6 ||
          d5 == 7 || d5 == 0xe || d5 == 0xf || d5 == 0x10 || d5 == 0x11 || d5 == 0)
        B(0xee4) = 2;
      change_work_mode_to();
      if (d5 != 9 || d5 != 0xa || d5 != 0xb || d5 != 0x10) thunk_FUN_00072880();
    }
    if (2 < DL) DBG1;
    *(volatile uint8_t *)0x20018d96UL = 0;
    goto top;

  case 3:
    FUN_0007cbfe();
    change_work_mode_to();
    goto top;

  case 4:
    FUN_0007cbfe();
    B(0xfea) = 0xc;
    I32(0x104c) = 3;
    thunk_FUN_00072880();
    goto top;

  case 5:
    B(0xfea) = 0xa;
    I32(0x104c) = 3;
    thunk_FUN_00072880();
    goto top;

  case 6:
    if (2 < DL) DBG1;
    if (SB(0xe5) == 9) {
      if (2 < DL) DBG1;
      FUN_00023bfc();
      goto top;
    }
    switch (B(0xe5)) {

    case 1:
      if (SB(0xd5) == 0xc) {
        if (SB(0xe6) == 0) {
          if (2 < DL) DBG1;
          FUN_000498c0();
          goto L2812a;
        }
      } else if (SB(0xe6) == 1) {
        if (2 < DL) DBG1;
        FUN_0007cdb6();
        B(0xec) = 0xc;
        **(volatile uint8_t **)(param_1 + 0x1020) = 1;
        FUN_0002bef4();
        {
          volatile int8_t *q = (volatile int8_t *)(I32(0x1020) + 2);
          *q = (int8_t)(*q + 1);
        }
        goto Ldefault;
      }
      goto top;

    case 2: {
      b2 = B(0xe6);
      b15 = b2 & 0xf;
      if (b15 == 1) {
        if (SB(0xd5) != 6) goto L282f6;
        FUN_0003707c();
        FUN_00049938();
        thunk_FUN_000745c8();
        if (DL < 3) goto top;
        DBG_D224;
      } else if (b15 == 2) {
        FUN_0003707c();
        if (2 < DL) DBG_D224;
      } else if (b15 == 3) {
        if (SB(0xd5) != 6) goto L282f6;
        FUN_00037108();
      L28260:
        FUN_00049938();
        thunk_FUN_000745c8();
        if (2 < DL) DBG_D224;
      } else if (b15 == 4) {
        FUN_00037108();
      L28296:
        if (2 < DL) DBG_D224;
      } else {
        if (b15 == 5) {
          if (SB(0xd5) == 6) { FUN_000371e8(); goto L28260; }
        } else if (b15 == 6) {
          FUN_000371e8();
          goto L28296;
        }
      L282f6:
        if (1 < DL) DBG1;
      }
      goto top;
    }

    case 3:
      if (SB(0xd5) == 9) {
        if (SB(0xe6) == 1) {
          if (2 < DL) DBG1;
          goto L28342;
        }
        if (0 < DL) DBG1;
        goto top;
      }
      if (0 < DL) DBG1;
      goto top;

    case 4: {
      volatile uint8_t *sb5 = (volatile uint8_t *)0x2001cdceUL;
      if (2 < DL) DBG1;
      B(0xcd) = *(volatile uint8_t *)(I32(0x1014) + 3);
      *(volatile uint8_t *)(I32(0x1014) + 2) = B(0xe6);
      *(volatile uint8_t *)(I32(0x1014) + 3) = B(0xe7);
      FUN_000429f8();
      cv = SB(0xe8);
      *sb5 = B(0xe7);
      thunk_FUN_00043308();
      FUN_00040708();
      {
        uint64_t r = FUN_0007cb2c();
        *(volatile int32_t *)(I32(0x1014) + 4) = (int32_t)r;
        *(volatile int32_t *)(I32(0x1014) + 8) = (int32_t)(r >> 32);
      }
      if (**(volatile int32_t **)(param_1 + 0x1054) == 0xe ||
          (FUN_0007c132() != 0 && *(volatile int8_t *)(I32(0x1014) + 1) == 0)) {
        int8_t c1 = *(volatile int8_t *)(I32(0x1014) + 2);
        if (c1 == 3) {
          if (*sb5 == 0x12) {
            *(volatile int8_t  *)(I32(0x1014) + 0xc) = cv;
            *(volatile uint8_t *)(I32(0x1014) + 0xd) = 3;
            *(volatile uint8_t *)(I32(0x1014) + 0xe) = 3;
          }
        } else if (c1 == 0xb) {
          **(volatile uint8_t **)(FUN_000167a8() + 0x1014) = 0;
          *(volatile uint8_t *)(*(volatile int32_t *)(FUN_000167a8() + 0x1014) + 1) = 0;
        }
      } else {
        if (cv == 1) {
          **(volatile uint8_t **)(param_1 + 0x1014) = 1;
          FUN_0002bef4();
          *(volatile uint8_t *)(I32(0x1014) + 0x20) = B(0xed5);
          B(0xed5) = 0x2a;
        }
      }
      goto L2850c;
    }

    case 5:
      if (2 < DL) DBG1;
      {
        uint8_t v = B(0xe6);
        *(volatile uint8_t *)(I32(0x1010) + 2) = v;
        *(volatile uint8_t *)0x2001b9abUL = v;
      }
      *(volatile uint8_t *)(FUN_000167a8() + 0xcd) = *(volatile uint8_t *)0x2001b9abUL;
      FUN_0003cb4c();
      **(volatile uint8_t **)(param_1 + 0x1010) = 1;
      FUN_0002bef4();
      goto L2850c;

    case 6:
      if (SB(0xd5) == 0xa) {
        if (SB(0xe6) != 1) { if (0 < DL) DBG1; goto top; }
        if (2 < DL) DBG1;
      L28342:
        FUN_000499b8();
      L2812a:
        thunk_FUN_000745c8();
        goto top;
      }
      if (0 < DL) DBG1;
      goto top;

    case 7:
      if (SB(0xd5) == 6) {
        if (2 < DL) DBG1;
        FUN_00049a28();
        goto L2812a;
      }
      if (0 < DL) DBG1;
      goto top;

    case 8:
      if (2 < DL) DBG1;
      cv = SB(0xe6);
      if (*(volatile int8_t *)0x20018462UL != cv && 1 < DL) DBG1;
      FUN_00023af0();
      goto top;

    case 10:
      if (2 < DL) DBG1;
      FUN_0007cb54();
      goto top;

    default:
      goto top;
    }

  case 7:
    switch (B(0xe5)) {
    case 0:
      FUN_0002bffc();
      goto L2850c;
    case 1:
      *(volatile uint8_t *)0x20018d9fUL = 1;
      FUN_00033d58();
      FUN_0002c1fc();
      FUN_0003439c();
      FUN_0002bffc();
    L2850c:
      FUN_0002bc2c();
      goto Ldefault;
    case 2:
      FUN_00034274();
      cv = *(volatile int8_t *)(FUN_000167a8() + 0xdd);
      if (cv != 0) cv = 6;
      FUN_0003443c();
      goto Ldefault;
    case 3:
      *(volatile uint8_t *)0x20018d8dUL = 1;
      if (*(volatile int8_t *)(FUN_000167a8() + 0x108f) != 0 &&
          FUN_00033cf8() != 0 &&
          *(volatile int8_t *)(FUN_000167a8() + 0xd5) != 4) {
        (void)FUN_000167a8();
        FUN_0002bffc();
        (void)FUN_000167a8();
        FUN_0002bc2c();
        FUN_0002c1fc();
      }
      goto Ldefault;
    default:
      goto Ldefault;
    }

  case 8:
    FUN_0007cce8();
    if (SB(0xe5) != 0 && SB(0xd5) == 4) {
      FUN_0003441c();
      cv = *(volatile int8_t *)(FUN_000167a8() + 0xdd);
      if (cv != 0) cv = 6;
      FUN_0003443c();
    }
    if (SB(0xee4) == 2) FUN_00023eec();
    FUN_0002c0e8();
    goto Ldefault;

  default:
    goto top;
  }

Ldefault:
  thunk_FUN_00072880();
  goto top;
  (void)p; (void)param_2; (void)param_3;
}

