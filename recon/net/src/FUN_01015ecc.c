/* net-core FUN_01015ecc @ 0x1015ecc  (parity 300 trials PROVEN) */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
#define RB(a) (*(volatile unsigned char*)(a))
#define RH(a) (*(volatile unsigned short*)(a))
#define RW(a) (*(volatile unsigned int*)(a))
extern int FUN_0100a17c(u32);
extern void FUN_0100a8f8(u32);
extern void FUN_0100a954(u32);
extern int FUN_0100dc1c(u32,u32,u32);
extern int FUN_01026d16(u32);
extern void FUN_0100b180(u32,u32,u32,u32);
extern void FUN_01020864(u32);
extern int FUN_0100d3c0(u32,u32,u32,u32);
extern void FUN_0100cff4(u32,u32);
extern int FUN_01014748(void);
extern int FUN_010144e4(void);
extern void FUN_01014b18(u32);
extern void FUN_0100b170(void);
extern void FUN_01008d00(u32,u32);
extern void FUN_01014884(void);

void FUN_01015ecc(u32 param_1)
{
  u32 G = 0x21000f68u;
  u32 r0,r1,r2,r3,r5,r6;
  r3 = param_1;
  RB(G) = 1;
  r0 = RH(param_1);
  RB(r3 + 0x2eb) = 1;
  RH(G + 0xc) = 0;
  RW(G + 4) = r3;
  RB(G + 0x18) = 0;
  RB(G + 0x1c) = 0;
  r0 = (u32)FUN_0100a17c(r0);
  if (r0 == 0) goto L1016124;
  r3 = RW(G+4);
  r6 = r0;
  r0 = RH(r3);
  FUN_0100a8f8(r0);
  r3 = RW(G+4);
  r0 = RH(r3);
  FUN_0100a954(r0);
  r1 = RW(G+4);
  r3 = RH(r1 + 0x2e2);
  if (r3 == 0) goto L1016002;
  r0 = RB(r1 + 0x14e);
  if (r0 == 0xfe) goto L1015fe4;
 L1015f16:
  FUN_010144e4();
  r1 = RW(G+4);
 L1015f1c:
  r3 = RB(r1 + 0x2ed);
  if (r3 == 0) goto L1016012;
 L1015f24:
  RH(G + 0x1a) = 0;
 L1015f28:
  r2 = RH(r1 + 0x2e6);
  r3 = RH(r1 + 0x2e8);
  r5 = (r2 - 1) & 0xffff;
  RH(r1 + 0x2e8) = (u16)(r3 + r5);
  r3 = RH(r1 + 0xf6);
  RH(r1 + 0xf6) = (u16)(r3 + r5);
  r3 = RB(r1 + 0xcb);
  if (r3 == 0) goto L1016070;
 L1015f4e:
  r3 = RW(r1 + 0xe8);
  RW(r1 + 0xe8) = r3 + r5;
 L1015f58:
  r3 = RH(r1 + 0x2e2);
  if (r3 <= 1) goto L1016024;
 L1015f60:
  if (r5 == 0) goto L1015f68;
  RB(r1 + 0x2f4) = 0;
 L1015f68:
  RB(r1 + 0x2ea) = 0;
  r0 = (u32)FUN_0100dc1c(r1 + 0xa8, r1, r2);
  r5 = r0;
  if (r0 != 0) goto L101611a;
  r0 = RW(G+4);
  r2 = RB(r0 + 0xc6);
  r1 = (r2 - 0xb) & 0xffffffffu;
  if (r1 <= 1) goto L101603e;
  if (r2 != 0x26) goto L101608e;
  r2 = RH(r0 + 0xbc);
  r1 = RH(r0 + 0x3bc);
  r2 = r2 - r1;
  if ((int)(r2 << 16) >= 0) goto L10160c6;
  goto L1015fa0;
 L1015fa0:
  r0 = (u32)FUN_01026d16(r6);
  r3 = RW(G+4);
  if (r0 != 0) goto L1016032;
  RB(r3 + 0x2ee) = 0;
 L1015fb0:
  r0 = RW(G+0);
  r1 = RW(G+4);
  FUN_0100b180(r0, r1, 0x01014c0du, 0x010151b9u);
  r1 = RW(G + 0x20);
  if (r1 == 0) goto L1015fcc;
  r0 = RB(G + 0x24);
  FUN_01020864(r0);
 L1015fcc:
  r0 = RW(G+4);
  r2 = RB(r0 + 0xc6);
  r0 = (u32)FUN_0100d3c0(r0 + 0xa8, 5, r2, 1);
  if (r0 != 0) goto L10160da;
  return;
 L1015fe4:
  r3 = RB(r1 + 0x160);
  if (r3 == 0) goto L1015f1c;
  r2 = RB(r1 + 0xc7);
  r0 = (u32)FUN_0100d3c0(r1 + 0xa8, 1, r2, 1);
  if (r0 == 0) goto L10160e4;
  r1 = RW(G+4);
 L1016002:
  r0 = RB(r1 + 0x14e);
  if (r0 != 0xfe) goto L1015f16;
  r3 = RB(r1 + 0x2ed);
  if (r3 != 0) goto L1015f24;
 L1016012:
  r3 = RB(r1 + 0x22c);
  if (r3 != 0) goto L101602c;
  r2 = RH(r1 + 0x2a);
  r3 = RH(r1 + 0x1c);
  if (r2 <= r3) goto L101602e;
  RH(G + 0x1a) = (u16)r2;
  goto L1015f28;
 L1016024:
  RH(r1 + 0x2e2) = (u16)(r3 + 1);
  goto L1015f60;
 L101602c:
  r3 = RH(r1 + 0x1c);
 L101602e:
  RH(G + 0x1a) = (u16)r3;
  goto L1015f28;
 L1016032:
  r3 = RB(r3 + 0x2ee);
  if (r3 == 0) goto L1015fb0;
  return;
 L101603e:
  r1 = RH(r0 + 0x3bc);
  r2 = RH(r0 + 0xbc);
  r2 = r2 - r1;
  if ((int)(r2 << 16) < 0) goto L1015fa0;
  r2 = RW(r0 + 0x3be);
  RW(r0 + 0xce) = r2;
  r2 = RB(r0 + 0x3c2);
  RB(r0 + 0xd2) = (u8)r2;
  FUN_0100cff4(r0, 3);
  r3 = RW(G+4);
  RB(r3 + 0xc6) = (u8)r5;
  RB(r3 + 0x11e) = 0xff;
  goto L1015fa0;
 L1016070:
  r2 = RB(r1 + 0xc6);
  r0 = (u32)FUN_0100d3c0(r1 + 0xa8, 6, r2, 1);
  r1 = RW(G+4);
  r2 = RH(r1 + 0x2e6);
  if (r0 == 0) goto L1015f58;
  goto L1015f4e;
 L101608e:
  r2 = RB(r0 + 0xc5);
  if (r2 == 0x26) goto S101609a;
  if (r2 != 0x28) goto L1015fa0;
 S101609a:
  r2 = RH(r0 + 0xbc);
  r1 = RH(r0 + 0x3bc);
  r2 = r2 - r1;
  if ((int)(r2 << 16) < 0) goto L1015fa0;
  RB(r0 + 0xc5) = 0;
  r0 = (u32)FUN_01014748();
  r1 = r0;
  if (r0 != 0) goto L1015fa0;
 L10160bc:
  FUN_01014b18(r1);
  return;
 L10160c6:
  RB(r0 + 0xc6) = (u8)r5;
  r0 = (u32)FUN_01014748();
  r3 = RW(G+4);
  r1 = r0;
  if (r0 == 0) goto L1016114;
  RB(r3 + 0x16c) = (u8)r5;
  goto L1015fa0;
 L10160da:
  FUN_0100b170();
  return;
 L10160e4:
  r3 = RW(G+4);
  r2 = RB(r3 + 0x161);
  RH(r3 + 0xfa) = (u16)r0;
  RB(r3 + 0x150) = (u8)r2;
  r2 = RB(r3 + 0x14e);
  if (r2 != 0xfe) goto L101612e;
  RH(r3 + 0xfc) = (u16)r0;
  RB(r3 + 0x2ea) = (u8)r0;
  RB(r3 + 0x100) = (u8)r5;
  RB(r3 + 0x14e) = 2;
  FUN_010144e4();
  r1 = RW(G+4);
  goto L1015f1c;
 L1016114:
  RB(r3 + 0x16c) = (u8)r0;
  goto L10160bc;
 L101611a:
  FUN_01008d00(0x31, 0xa20);
 L1016124:
  FUN_01008d00(0x31, 0x9d9);
 L101612e:
  for(;;) FUN_01014884();
}

