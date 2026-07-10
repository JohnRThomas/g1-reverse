/* net-core FUN_010315f0 @ 0x10315f0  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;

extern void thunk_FUN_0102cfec(void);
extern void FUN_103a6ae(u32);
extern u64  FUN_10313a8(void);

#define DAT_010316d0 0x41016000u
#define DAT_010316d4 0x21004970u
#define DAT_010316d8 0x21002b60u
#define DAT_010316dc 0x21004964u
#define DAT_010316e0 0x41016140u

void FUN_010315f0(void)
{
  i32 r4;
  u32 r5;

  thunk_FUN_0102cfec();
  if (((i32)(*(volatile i32*)(DAT_010316d0 + 0x304) << 0x1e)) < 0 &&
      (*(volatile i32*)(DAT_010316d0 + 0x104) != 0)) {
    *(volatile u32*)(DAT_010316d0 + 0x104) = 0;
    *(volatile u32*)DAT_010316d4 = *(volatile u32*)DAT_010316d4 + 1;
  }

  r5 = DAT_010316d8;
  r4 = 0;
  for (;;) {
    u32 mask = 0x10000u << r4;
    if ((mask & *(volatile u32*)(DAT_010316d0 + 0x304)) != 0) {
      u32 clearmask = ~(1u << r4);
      u32 old = 0, res;
      do {
        __asm__ volatile ("ldaex %0, [%1]" : "=&r"(old) : "r"((volatile u32*)DAT_010316dc) : "memory");
        u32 newv = old & clearmask;
        __asm__ volatile ("stlex %0, %2, [%1]" : "=&r"(res) : "r"((volatile u32*)DAT_010316dc), "r"(newv) : "memory");
      } while (res != 0);
      u32 bit = (old >> r4) & 1u;
      u32 proceed = 1;
      if (bit == 0) {
        if (*(volatile u32*)(DAT_010316e0 + (u32)r4 * 4) == 0) proceed = 0;
      }
      if (proceed) {
        u32 ip = DAT_010316d8 + (u32)r4 * 0x10;
        u64 now;
        u32 primask_save;
        FUN_103a6ae((u32)r4);
        now = FUN_10313a8();
        __asm__ volatile ("mrs %0, primask" : "=r"(primask_save));
        __asm__ volatile ("cpsid i" ::: "memory");
        {
          u32 slo = *(volatile u32*)(ip + 8);
          u32 shi = *(volatile u32*)(ip + 0xc);
          u64 sval = ((u64)shi << 32) | slo;
          if (now >= sval) {
            u32 cb_ptr = *(volatile u32*)(r5);
            u32 cb_ctx = *(volatile u32*)(r5 + 4);
            *(volatile u32*)r5 = 0;
            *(volatile u32*)(ip + 8) = 0xffffffffu;
            *(volatile u32*)(ip + 0xc) = 0xffffffffu;
            *(volatile u32*)(DAT_010316d0 + 0x348) = mask;
            FUN_103a6ae((u32)r4);
            __asm__ volatile ("msr primask, %0" :: "r"(primask_save) : "memory");
            if (cb_ptr != 0) {
              void (*fp)(u32,u32,u32,u32) = (void(*)(u32,u32,u32,u32))(unsigned long)cb_ptr;
              fp(0, cb_ctx, slo, shi);
            }
          } else {
            __asm__ volatile ("msr primask, %0" :: "r"(primask_save) : "memory");
          }
        }
      }
    }
    r5 += 0x10;
    if (r4 != 0) break;
    r4 = 1;
  }
}

