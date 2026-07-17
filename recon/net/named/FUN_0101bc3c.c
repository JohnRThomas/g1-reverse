/* readable reconstruction; identity: FUN_0101bc3c @ 0x0101bc3c
 * public-name: FUN_0101bc3c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c290                           @ 0x0103c290
 */
/* net-core FUN_0101bc3c @ 0x101bc3c  (parity 2 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))
#define S16(a) (*(volatile short*)(u32)(a))

extern void FUN_01008d00(unsigned,unsigned);
extern unsigned FUN_0101a0e8(void);
extern unsigned FUN_010209f0(unsigned);
extern void FUN_0100f48c(unsigned, unsigned);
extern unsigned FUN_0101dec4(void);
extern unsigned FUN_0100f69c(int, unsigned);
extern unsigned FUN_0101dc50(unsigned, unsigned, unsigned, unsigned);
extern unsigned FUN_0100f0fc(unsigned);
extern unsigned FUN_010231c8(unsigned, void*);

void FUN_0101bc3c(unsigned param_1)
{
  if (param_1 == 0) { for(;;) FUN_01008d00(0x35,0x1b1); }
  if (W8(param_1+0x300) != 0) { for(;;) FUN_01008d00(0x35,0x1b2); }
  if (W8(param_1+0x301) == 0x20) { for(;;) FUN_01008d00(0x35,0x1b3); }

  u16 uVar3 = (u16)FUN_0101a0e8();

  u32 uVar9 = 0;
  u32 uVar6;
  int local_1c;
  int skip_dec = 0;

  u8 sw = W8(param_1+0x300);
  if (sw > 3) { for(;;) FUN_01008d00(0x35,0x264); }

  if (sw == 0) {
    u8 bVar1 = W8(param_1+0x6f);
    u16 uVar2 = W16(0x0103c290u + (u32)W8(param_1+0x6e)*2u);
    W8(param_1+0x300) = 1;
    u32 iVar4 = FUN_010209f0(bVar1);
    int iVar5 = ((bVar1 & 0xc) == 0) ? 0 : 0x28;
    uVar9 = 0;
    unsigned long long prod = (unsigned long long)0x10624dd3u *
                               (unsigned long long)(u32)(uVar2 + 0x79d + iVar4);
    FUN_0100f48c(param_1, (u32)iVar5 + (u32)(prod >> 0x26) + 199u);
    u32 iVar4b = FUN_0101dec4();
    if (iVar4b != 0) {
      uVar6 = 0; local_1c = 0; skip_dec = 1;
    }
    /* else: fall directly into the "recompute uVar6" path below (LAB_0101bd1e) */
  } else {
    if (sw == 1 || sw == 3) {
      uVar9 = W32(param_1+0x14);
    } else { /* sw == 2 */
      uVar9 = W32(param_1+0x308);
      W8(param_1+0x300) = 3;
    }
  }

  if (!skip_dec) {
    u32 needRecalc;
    if (sw == 0) {
      needRecalc = 1; /* case0's else path always lands on LAB_0101bd1e */
    } else {
      u32 iVar4 = FUN_0101dec4();
      needRecalc = (iVar4 == 0);
    }
    if (needRecalc) {
      uVar6 = FUN_0100f69c((int)S16(param_1+0x2fc), 2);
      local_1c = (int)uVar6 >> 31;
      S16(param_1+0x2fc) = (short)(S16(param_1+0x2fc) - (short)uVar6);
    } else {
      uVar6 = 0; local_1c = 0;
    }
  }

  {
    u32 uVar7 = W32(param_1+0x2d8);
    u32 uVar8 = uVar9 + uVar7;
    u32 local_20 = uVar8 + uVar6;
    W32(param_1+0x2d8) = local_20;
    unsigned carry1 = (uVar8 < uVar9) ? 1u : 0u;
    unsigned carry2 = (local_20 < uVar8) ? 1u : 0u;
    local_1c = local_1c + (int)W32(param_1+0x2dc) + (int)carry1 + (int)carry2;
    W32(param_1+0x2dc) = (u32)local_1c;

    (void)uVar3;
    u8 fieldc5 = W8(param_1+0xc5);
    u8 local_26;
    if (((fieldc5 & 0xfd) == 0xc) || (fieldc5 == 0x26)) {
      FUN_0101dc50(param_1, 0, 0, fieldc5 & 0xfd);
      local_26 = 0;
    } else {
      u32 iVar4c = FUN_0101dc50(param_1, 0, 0, fieldc5 & 0xfd);
      if (iVar4c != 0) {
        local_26 = (W8(param_1+0x300) == 1) ? 1 : 2;
      } else {
        local_26 = 0;
      }
    }
    (void)local_26;

    u32 local_2c = FUN_0100f0fc(param_1+0x30);
    (void)local_2c;

    struct {
      u8 b0,b1,b2,b3;
      u32 w;
      u16 h;
      u8 c1,c2;
      /* The event transport reserves three trailing words for the producer. */
      u32 reserved[3];
    } buf;
    buf.b0 = 0;
    buf.h = uVar3;
    buf.c1 = local_26;
    buf.c2 = 1;
    buf.w = local_2c;

    u32 iVar4 = FUN_010231c8(W8(param_1+0x301), &buf);
    if (iVar4 != 0) {
      return;
    }
    for(;;) FUN_01008d00(0x35,0x1b7);
  }
}
