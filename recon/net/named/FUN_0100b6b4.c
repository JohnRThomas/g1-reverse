/* readable reconstruction; identity: FUN_0100b6b4 @ 0x0100b6b4
 * public-name: FUN_0100b6b4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 *   g_net_link_drv_ctx_0x24                  @ 0x21000c6c
 *   g_ll_conn_trace_ctx_addr                 @ 0x21000cd0
 */
/* net-core FUN_0100b6b4 @ 0x100b6b4  (parity 150 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))
#define S8(a)  (*(volatile s8*)(u32)(a))
#define S16(a) (*(volatile short*)(u32)(a))

extern void FUN_01008d00(unsigned,unsigned);
extern int FUN_0100a984(void);
extern void FUN_0100aba4(void*);
extern void FUN_0100ac34(void);
extern void FUN_0100ac98(void);
extern int FUN_0100aeac(unsigned);
extern void FUN_0100b630(unsigned,void*);
extern void FUN_0100ef88(unsigned,unsigned,unsigned);
extern int FUN_0100f5cc(void);
extern void FUN_01010578(unsigned);
extern void FUN_0101fdd0(unsigned,unsigned,unsigned,unsigned,unsigned);
extern int FUN_0101ff9c(void);
extern void FUN_0101ffd4(void);
extern void FUN_01020048(void);
extern void FUN_010209b8(void);
extern int FUN_01026bfe(unsigned,void*);
extern unsigned FUN_01026e48(unsigned);
extern unsigned FUN_010270d2(void);

#define IV4  0x21000c48u
#define DAT_0100b964 0x21000cd0u
#define DAT_0100b968 0x21000c6cu

void FUN_0100b6b4(unsigned param_1, unsigned param_2)
{
  s8 local_29 = 0;
  u32 local_28 = 0;
  u32 local_24 = 0;
  u32 iVar4 = IV4;
  u32 iVar13 = W32(iVar4+0x28);
  u32 iVar9 = 0;
  int have_iVar9 = 0;
  u32 uVar7;

  if (W8(iVar4+0x44) != 2) { for(;;) FUN_01008d00(0x27,0x4e2); }

  u16 uVar8 = W16(iVar4+0x30);
  if ((uVar8 & 0x40u) == 0) {
    void (*fn)(unsigned) = (void(*)(unsigned))W32(iVar4+0x34);
    fn(0x40);
    uVar8 = (u16)(W16(iVar4+0x30) | 0x40u);
    W16(iVar4+0x30) = uVar8;
  }

  if (param_1 == 0) {
    if (W8(iVar13+0xcb) != 0) {
      FUN_01020048();
      uVar8 = W16(iVar4+0x30);
    }
    iVar9 = 0; have_iVar9 = 1;
    W16(iVar4+0x30) = (u16)(uVar8 | 0x200u);
    W8(iVar4+0xc4) = (u8)(W8(iVar4+0xc4) + 1);
    goto LAB_b7d8;
  }

  u32 pbVar11;
  u8 bVar1;
  if (W8(iVar13+0xcb) == 0) {
    pbVar11 = W32(iVar4+0x2c);
    uVar8 = W8(pbVar11+1);
    goto LAB_b704;
  } else {
    FUN_0101ffd4();
    u32 r9 = FUN_0101ff9c();
    pbVar11 = W32(iVar4+0x2c);
    bVar1 = W8(pbVar11+1);
    uVar8 = bVar1;
    if (r9 != 0) goto LAB_b704;
    if (uVar8 == 0) {
      W16(iVar4+0xbc) = bVar1;
      goto LAB_b710;
    }
    if ((u32)W8(iVar13+0xc0) == (u32)((W8(pbVar11) >> 3) & 1u)) {
      W8(iVar4+0x3e) = 1;
      FUN_0100ac34();
      return;
    }
    W16(iVar4+0xbc) = bVar1;
    goto LAB_b948;
  }

LAB_b704:
  W16(iVar4+0xbc) = uVar8;
  if (uVar8 != 0) goto LAB_b948;
LAB_b710:
  W32(iVar4+0x38) = 0;
  goto AFTER_STORE;

LAB_b948:
  {
    u32 r = FUN_01026e48(W32(iVar4+200));
    pbVar11 = W32(iVar4+0x2c);
    W32(iVar4+0x38) = r;
  }

AFTER_STORE:
  {
    u32 uVar10 = (u32)W8(pbVar11);
    u8 bVar1b = W8(iVar13+0xbf);
    u16 uv8 = (u16)(W16(iVar4+0x30) | 0x100u);
    W16(iVar4+0x30) = uv8;
    iVar9 = param_1; have_iVar9 = 1;
    if ((u32)bVar1b != (u32)((uVar10 >> 2) & 1u)) {
      iVar9 = W32(iVar4+0x28);
      s8 cVar5 = S8(iVar4+0x24);
      if (W8(iVar9+0xbe) != 0) {
        if (W8(iVar9+0xbe) == 2) {
          int r6 = FUN_01026bfe(W32(iVar4+0x80), &local_28);
          if (r6 == 0) { for(;;) FUN_01008d00(0x27,0x3dd); }
          u32 u10b = W32(iVar9+0x120);
          cVar5 = S8(iVar4+0x24);
          W32(iVar9+0x120) = u10b + 1;
          W32(iVar9+0x124) = W32(iVar9+0x124) + (u10b > 0xfffffffeu ? 1u : 0u);
        }
        W8(iVar9+0xbe) = 0;
        if (cVar5 != 0 && S8(iVar9+0xba) != 0) {
          u16 uv8b = W16(iVar4+0x32);
          W8(iVar9+0xba) = 0;
          W16(iVar4+0x32) = (u16)(uv8b | 0x10u);
          void (*fn)(unsigned) = (void(*)(unsigned))W32(iVar4+0x34);
          fn(0x10);
        }
        if (S8(iVar9+0xb9) != 0) {
          W8(iVar9+0xb9) = 0;
          int r6 = FUN_0100a984();
          if (r6 == 0) { for(;;) FUN_01008d00(0x27,0x3f4); }
          W16(iVar4+0x32) = (u16)(W16(iVar4+0x32) | 8u);
          void (*fn2)(unsigned,unsigned) = (void(*)(unsigned,unsigned))W32(iVar4+0x34);
          fn2(8,0);
          u32 u10c = W32(iVar9+0x120);
          W32(iVar9+0x120) = u10c + 1;
          W32(iVar9+0x124) = W32(iVar9+0x124) + (u10c > 0xfffffffeu ? 1u : 0u);
        }
        W8(iVar9+0xbf) = (u8)(S8(iVar9+0xbf) != 1);
        uVar10 = (u32)W8(W32(iVar4+0x2c));
        uv8 = W16(iVar4+0x30);
      }
      W16(iVar4+0x30) = (u16)(uv8 | 0x400u);
      iVar9 = 0;
    }
    if ((u32)W8(iVar13+0xc0) == (u32)((uVar10 >> 3) & 1u)) {
      int r6 = FUN_0100f5cc();
      u32 pb = W32(iVar4+0x2c);
      if ((r6 == 0) ||
          ((u32)(((W8(pb) & 3u) - 1u)) > 1u) ||
          (W8(pb+1) <= W8(iVar4+0xcc))) {
        FUN_0100aba4(&local_29);
      } else {
        W8(iVar4+0x3d) = (u8)(W8(iVar4+0x3d) | 0x10u);
      }
    }
  }

LAB_b7d8:
  if (W8(iVar13+0xca) != 0) {
    W8(iVar4+0xa0) = (u8)(S8(iVar4+0x24) == 0);
    u32 base28 = W32(iVar4+0x28);
    u8 uVar2 = W8(base28+0x6e);
    if (W32(base28+0x14) < 0x1d4c) {
      uVar7 = 4;
    } else {
      uVar7 = 0;
    }
    u32 uVar12 = W32(iVar13+0x124);
    W32(iVar4+0x98) = W32(iVar13+0x120);
    W32(iVar4+0x9c) = uVar12;
    u8 uVar14 = 2;
    switch (uVar2) {
      case 1: uVar14 = 0; break;
      case 2: uVar14 = 1; break;
      case 4: uVar14 = 3; break;
      case 8: break;
      default:
        for(;;) FUN_01008d00(6,0x3c5);
    }
    FUN_0101fdd0(uVar7, DAT_0100b964, 0xfb, uVar14, 0);
  }

  int bVar3;
  if ((param_2 == 0) && (W8(iVar4+0xc4) < 2)) {
    int (*fn)(unsigned) = (int(*)(unsigned))W32(iVar4+0xc0);
    int r6 = fn(1);
    if (r6 != 0 && S8(iVar4+0x3d) == 0) {
      int r7 = FUN_0100aeac(1);
      if (r7 == 0) {
        FUN_0100ac98();
        bVar3 = 0;
        goto after_bVar3;
      }
    }
  }
  FUN_010209b8();
  bVar3 = 1;
after_bVar3:

  if (local_29 != 0) {
    FUN_0100b630(2,&local_24);
  }

  if (have_iVar9 && iVar9 != 0 &&
      (S8(iVar4+0x24) == 0 ||
       (S16(iVar4+5) != 0 || S16(iVar4+7) != 0 || S16(iVar13+0xbc) != 0))) {
    S16(iVar4+9) = (short)(S16(iVar4+9) + 1);
  }

  if (param_1 == 0) {
    S16(iVar4+7) = (short)(S16(iVar4+7) + 1);
  } else {
    W8(iVar4+0xc4) = 0;
    S16(iVar4+5) = (short)(S16(iVar4+5) + 1);
  }

  FUN_01010578(DAT_0100b968);

  if (local_28 != 0) {
    u32 r13 = FUN_010270d2();
    u32 u7 = W32(iVar4+0x28);
    W8(r13+9) = 0;
    FUN_0100ef88(r13+1, u7, 8);
  }
  if (local_24 != 0) {
    u32 u7 = W32(iVar4+0x28);
    W8(local_24+8) = 0;
    FUN_0100ef88(local_24, u7, 0x10);
  }

  if (!bVar3) {
    return;
  }
  FUN_0100ac34();
}
