/* readable reconstruction; identity: FUN_01022a84 @ 0x01022a84
 * public-name: FUN_01022a84
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01022a84 @ 0x1022a84  (parity 300 trials PROVEN) */
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char byte;
typedef unsigned int uint;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef void (*fnptr_t)(void);

extern int FUN_01021ee0(int, int, int, unsigned int);
extern unsigned int FUN_01022774(unsigned int);
extern void FUN_01024440(unsigned int);
extern void FUN_010244cc(short, void *, void *);
extern void FUN_0102460c(void);
extern unsigned char FUN_01024644(void);
extern undefined1 FUN_01024650(void);
extern unsigned int FUN_01024678(unsigned int, unsigned int);
extern int FUN_010245d8(void);
extern int FUN_010246d8(void);
extern void FUN_01024778(void);
extern int FUN_01024ad0(void);
extern void FUN_01024c6c(int, int);
extern void FUN_01024ef0(void);
extern unsigned long long FUN_01025084(void);
extern void FUN_0102524c(int);
extern void FUN_01025344(void);
extern __attribute__((noreturn)) void FUN_010256dc(unsigned int, unsigned int);
extern void FUN_0102583c(unsigned char);

#define DAT_01022dbc ((volatile undefined4 *)0x210016f0)

#define CARRY4(a, b) ((unsigned int)((a) + (b)) < (unsigned int)(a))

void FUN_01022a84(void)
{
  volatile byte *bp;
  volatile undefined1 *bp1;
  int bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  short sVar7;
  volatile undefined4 *puVar8;
  undefined1 uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  longlong lVar19;
  longlong lVar20;
  undefined1 uStack_2d;
  undefined1 auStack_2c[8];

  puVar8 = DAT_01022dbc;
  lVar19 = (longlong)FUN_01025084();
  uVar13 = (uint)((ulonglong)lVar19 >> 0x20);
  FUN_01025344();
  if (puVar8[3] != (undefined4)-1 || puVar8[2] != (undefined4)-1) {
    puVar8[2] = 0xffffffff;
    puVar8[3] = 0xffffffff;
  }
  if ((*(volatile char *)((int)puVar8 + 0x2a) == '\0') &&
      (uVar17 = FUN_01024678(puVar8[6], 0x230), uVar10 = puVar8[6] + puVar8[4],
       uVar18 = puVar8[5] + (uint)CARRY4(puVar8[6], puVar8[4]) + (uint)CARRY4(uVar10, uVar17),
       uVar18 < uVar13 || uVar13 - uVar18 < (uint)(uVar10 + uVar17 <= (uint)lVar19))) {
    uint cbidx = (uint)*(volatile byte *)((int)puVar8 + 0x4a);
    void (*f)(unsigned int, unsigned int) =
        (void (*)(unsigned int, unsigned int))puVar8[cbidx * 8 + 0x34];
    f(puVar8[cbidx * 8 + 0x35], 8);
    FUN_010256dc(0x70, 0x3cb);
    return;
  }
  if ((*(volatile char *)((int)puVar8 + 0x21) == '\0') || (*(volatile char *)((int)puVar8 + 0x37) == '\0')) {
    FUN_01024c6c((int)(lVar19 + 3), (int)((ulonglong)(lVar19 + 3) >> 0x20));
  } else {
    FUN_01024ef0();
  }
  if (*(volatile char *)((int)puVar8 + 0x38) != '\0') {
    FUN_010256dc(0x70, 0x3e4);
    return;
  }
  *(volatile undefined1 *)((int)puVar8 + 0x38) = 1;
  if (*(volatile char *)((int)puVar8 + 0x4a) == ' ') {
    FUN_010256dc(0x70, 999);
    return;
  }
  bVar2 = *(volatile byte *)((int)puVar8 + 0x4a);
  *(volatile undefined1 *)((int)puVar8 + 0x36) = 0;
  uVar18 = (uint)bVar2;
  *(volatile undefined1 *)((int)puVar8 + 0x4a) = 0x20;
  *(volatile undefined1 *)((int)puVar8 + 0x4b) = 0x20;
  *(volatile undefined1 *)((int)puVar8 + 0x37) = 0;
  *(volatile undefined4 *)((int)puVar8) = 0;
  uVar9 = FUN_01024650();
  bVar3 = *(volatile byte *)((int)puVar8 + 0x49);
  *(volatile undefined1 *)((int)puVar8 + 0x28) = uVar9;
  uVar17 = (uint)bVar3;
  iVar16 = (uint)bVar3 * 2;
  uVar13 = (uint)*(volatile byte *)((int)puVar8 + (uint)bVar3 * 3 + 0x30);
  if ((uVar13 != 0x20) && (*(volatile char *)((int)puVar8 + uVar13 * 0x20 + 0xea) == '\x01')) {
    sVar7 = *(volatile short *)((int)puVar8 + uVar13 * 0x20 + 0xe6);
    FUN_010244cc(sVar7, auStack_2c, &uStack_2d);
    FUN_01024644();
    FUN_010245d8();
    if (*(volatile char *)((int)puVar8 + 0x4a) == ' ') {
      lVar20 = lVar19 + 0xb;
      if ((sVar7 != 0) && (FUN_01024ad0() == 0)) {
        iVar14 = FUN_010246d8();
        if (iVar14 == 0x356) {
          lVar20 = lVar19 + 0x27;
        } else if (iVar14 == 0x5f5) {
          lVar20 = lVar19 + 0x3d;
        } else if (iVar14 == 0x18c) {
          lVar20 = lVar19 + 0x18;
        }
      }
    } else {
      uVar10 = puVar8[4] + 7;
      lVar20 = (longlong)(uint)(uVar10 + puVar8[6]) |
               ((longlong)(uint)(puVar8[5] + (uint)(0xfffffff8 < (uint)puVar8[4]) +
                                 (uint)CARRY4(uVar10, puVar8[6]))
                << 32);
    }
    uVar12 = (uint)((ulonglong)lVar20 >> 0x20);
    uVar10 = puVar8[uVar13 * 8 + 0x37];
    bVar1 = (uVar10 - uVar12) < (uint)((uint)lVar20 <= (uint)puVar8[uVar13 * 8 + 0x36]);
    if (uVar12 < uVar10 || bVar1) {
      puVar8[uVar13 * 8 + 0x36] = (uint)lVar20;
    }
    if (uVar12 < uVar10 || bVar1) {
      puVar8[uVar13 * 8 + 0x37] = uVar12;
    }
    uVar13 = (uint)*(volatile byte *)((int)puVar8 + iVar16 + uVar17 + 0x30);
  }
  iVar15 = iVar16 + uVar17;
  iVar14 = uVar17 * 0x20;
  if (uVar13 == 0x20) goto LAB_01022b66;
LAB_01022b54:
  uVar10 = FUN_01022774(uVar17);
  if (uVar10 == uVar13) goto LAB_01022b66;
LAB_01022b5e:
  do {
    uVar13 = (uint)*(volatile byte *)((int)puVar8 + iVar15 + 0x30);
    if (uVar13 != 0x20) goto LAB_01022b54;
LAB_01022b66:
    lVar20 = (longlong)FUN_01025084();
    if ((*(volatile char *)((int)puVar8 + 0x4b) == ' ') ||
        (uVar10 = (uint)((ulonglong)(lVar20 + 2) >> 0x20),
         uVar10 < (uint)puVar8[5] ||
             puVar8[5] - uVar10 < (uint)((uint)(lVar20 + 2) <= (uint)puVar8[4]))) {
      if (uVar13 == 0x20) {
        if (puVar8[0x11] != (undefined4)-1 || puVar8[0x10] != (undefined4)-1) {
          FUN_01024778();
          puVar8[0x10] = 0xffffffff;
          puVar8[0x11] = 0xffffffff;
        }
        if (*(volatile char *)((int)puVar8 + 0x48) != '\0') {
          FUN_0102524c(5);
          *(volatile undefined1 *)((int)puVar8 + 0x48) = 0;
        }
        iVar15 = 1;
        FUN_0102524c(4);
        FUN_01025344();
        *(volatile undefined1 *)((int)puVar8 + 0x4b) = 0x20;
        *(volatile undefined4 *)puVar8[0x4d4 / 4] = 0;
        iVar11 = (int)puVar8 + (iVar14 + uVar18) * 2;
        cVar4 = *(volatile char *)(iVar11 + 0x50);
      } else {
        iVar11 = FUN_01021ee0((int)lVar20, (int)((ulonglong)lVar20 >> 0x20), 1, uVar13);
        if (iVar11 == 0) {
          bVar3 = *(volatile byte *)((int)puVar8 + iVar15 + 0x30);
          *(volatile undefined1 *)((int)puVar8 + iVar15 + 0x30) =
              *(volatile undefined1 *)((int)puVar8 + (iVar14 + uVar13) * 2 + 0x51);
          bVar6 = bVar3;
          do {
            bVar5 = bVar6;
            uVar10 = (uint)bVar5;
            *(volatile undefined1 *)((int)puVar8 + (iVar14 + uVar10) * 2 + 0x50) = 4;
            bVar6 = *(volatile byte *)((int)puVar8 + (iVar14 + uVar10) * 2 + 0x51);
          } while (uVar10 != uVar13);
          bVar6 = *(volatile byte *)((int)puVar8 + iVar15 + 0x32);
          if (bVar6 == 0x20) {
            *(volatile byte *)((int)puVar8 + iVar15 + 0x31) = bVar3;
          } else {
            *(volatile byte *)((int)puVar8 + ((uint)bVar6 + iVar14) * 2 + 0x51) = bVar3;
          }
          *(volatile byte *)((int)puVar8 + iVar15 + 0x32) = bVar5;
          *(volatile undefined1 *)((int)puVar8 + (uVar10 + iVar14) * 2 + 0x51) = 0x20;
          goto LAB_01022b5e;
        }
        iVar15 = 2;
        *(volatile char *)((int)puVar8 + 0x4b) = (char)uVar13;
        iVar11 = (int)puVar8 + (iVar14 + uVar18) * 2;
        cVar4 = *(volatile char *)(iVar11 + 0x50);
      }
      if (cVar4 == '\x02') {
        *(volatile undefined1 *)(iVar11 + 0x50) = 6;
        bVar3 = *(volatile byte *)((int)puVar8 + iVar16 + uVar17 + 0x32);
        if (bVar3 == 0x20) {
          *(volatile byte *)((int)puVar8 + iVar16 + uVar17 + 0x31) = bVar2;
        } else {
          *(volatile byte *)((int)puVar8 + ((uint)bVar3 + iVar14) * 2 + 0x51) = bVar2;
        }
        *(volatile byte *)((int)puVar8 + iVar16 + uVar17 + 0x32) = bVar2;
        *(volatile undefined1 *)((int)puVar8 + (iVar14 + uVar18) * 2 + 0x51) = 0x20;
      }
      *(volatile undefined1 *)((int)puVar8 + 0x39) = 0xff;
      if (*(volatile char *)((int)puVar8 + iVar16 + uVar17 + 0x31) != ' ') {
        FUN_0102583c(*(volatile unsigned char *)((int)puVar8 + 0x4d9));
      }
      if (*(volatile char *)((int)puVar8 + 0x28) != '\0') {
        FUN_0102460c();
        *(volatile undefined2 *)((int)puVar8 + 0x28) = 0;
      }
      if (iVar15 == 2) {
        FUN_01024440(puVar8[4] - (uint)lVar19);
        if (*(volatile undefined4 *)((int)puVar8 + 0x4d0) != 0) {
          fnptr_t f = (fnptr_t) * (volatile undefined4 *)((int)puVar8 + 0x4d0);
          f();
          return;
        }
      } else if (*(volatile undefined4 *)((int)puVar8 + 0x4d0) != 0) {
        void (*f2)(unsigned int) = (void (*)(unsigned int)) * (volatile undefined4 *)((int)puVar8 + 0x4d0);
        f2(0xffffffff);
        return;
      }
      return;
    }
  } while (1);
}
