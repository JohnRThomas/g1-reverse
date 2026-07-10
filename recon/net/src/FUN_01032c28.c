/* net-core FUN_01032c28 @ 0x1032c28  (parity 300 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))

extern void FUN_0102eb2c(unsigned);
extern void FUN_01032860(unsigned);
extern void FUN_01032ad8(void);
extern void FUN_01033b18(unsigned,unsigned);
extern void FUN_01039bb0(unsigned,unsigned);
extern void FUN_01039bbe(unsigned,unsigned,unsigned);
extern void FUN_0103b53a(unsigned,unsigned,unsigned,unsigned);

void FUN_01032c28(void)
{
  W32(0x210049a8u) = 1;
  u32 pcVar4 = 0x21004a94u;
  u32 idx = W32(0x21004a60u + 0x24u);
  u8 cVar1 = W8(pcVar4);
  u32 pbVar9 = W32(0x21004a60u + idx*4u);
  u32 piVar5_addr = 0x21004a8cu;
  W32(piVar5_addr) = pbVar9;
  u32 pbVar3 = 0x2100635bu;
  u32 uVar13;

  if (cVar1 == 0) {
    W16(pbVar3) = 0; /* pbVar3[0]=0; pbVar3[1]=0 */
    {
      void (*fn)(unsigned char) = (void (*)(unsigned char))W32(0x2100499cu);
      fn(W8(pbVar9));
    }
    u32 puVar10 = W32(piVar5_addr);
    W8(pbVar3) = (u8)((W8(pbVar3) & 0xfcu) | (W8(puVar10+4) & 3u));
    FUN_0103b53a(pbVar3+2, puVar10+5, W8(puVar10), 0xfb);
    W32(0x41008000u + 0x200) = 0x11b;
    W32(0x41008000u + 0x304) = 0x10;
    W32(0x210049acu) = W16(pcVar4 + 0xe);
    W32(0x210049a0u) = 0x010338b1u;
    W8(0x21006458u) = 2;
    goto set13;
  } else if (cVar1 == 1) {
    u8 bVar2 = W8(pbVar9+3);
    W16(pbVar3) = 0;
    u8 bVar14 = 1;
    if (bVar2 != 0) {
      bVar14 = (u8)(W8(pcVar4+0x12) ^ 1);
    }
    W8(pbVar3) = W8(pbVar9);
    u8 bVar11 = (u8)((W8(pbVar9+4) & 3u) << 1);
    if (bVar2 == 0) bVar11 |= 1;
    W8(pbVar3+1) = (u8)(bVar11 | (W8(pbVar3+1) & 0xf8u));
    FUN_0103b53a(0x2100635du, pbVar9+5, W8(pbVar9), 0xfb);
    if (bVar14 == 0) {
      W32(0x41008000u+0x200) = 0x113;
      W32(0x210049a0u) = 0x010335e5u;
      W8(0x21006458u) = 1;
      W32(0x41008000u+0x304) = 0x10;
      uVar13 = 0;
      goto tail;
    }
    W32(0x41008000u+0x200) = 0x11b;
    W32(0x210049acu) = W16(pcVar4+0xe);
    W32(0x210049a0u) = 0x010338b1u;
    W8(0x21006458u) = 2;
    W32(0x41008000u+0x304) = 0x10;
    goto set13;
  }
set13:
  uVar13 = 1;
tail:
  {
    u32 iVar12 = W32(piVar5_addr);
    W32(0x41008000u+0x52c) = W8(iVar12+1);
    W32(0x41008000u+0x530) = (1u << W8(iVar12+1)) & 0xffu;
    u32 sz = (u32)W8(0x21000684u+0x13) + 0x960u;
    if (sz > 0x9c4u) {
      FUN_01039bbe(0x0103d2a7u, 0x0103e3e0u, 0x6b7u);
      FUN_01039bb0(0x0103e3e0u, 0x6b7u);
      __builtin_unreachable();
    }
    W32(0x41008000u+0x508) = (u32)W8(0x21000684u+0x13);
    FUN_01032ad8();
    W32(0x41008000u+0x504) = pbVar3;
    W32(0xe000e100u+0x180) = 0x100;
    FUN_0102eb2c(8);
    W32(0x41008000u+0x104) = 0;
    W32(0x41008000u+0x108) = 0;
    W32(0x41008000u+0x110) = 0;
    W32(0x41008000u+0x10c) = 0;
    FUN_01033b18(0, uVar13);
    FUN_01032860(uVar13);
    W32(0x41014000u+0x18) = 1;
    return;
  }
}


