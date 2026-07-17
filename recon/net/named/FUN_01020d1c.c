/* readable reconstruction; identity: FUN_01020d1c @ 0x01020d1c
 * public-name: FUN_01020d1c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   thunk_FUN_01025028                       <= FUN_01023de8 @ 0x01023de8
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020d1c @ 0x1020d1c
 * Missing first-class radio state-transition routine recovered from the case-4
 * tail target formerly absorbed into FUN_01013650. Physical ownership extends
 * through 0x1021107 and includes embedded literal islands. All state/MMIO
 * accesses remain volatile so repeated reset writes and their order match the
 * hardware transaction stream. Authoritative CFG parity: PASS. */
#include <stdint.h>
typedef uint8_t undefined1,byte; typedef uint16_t undefined2,ushort; typedef uint32_t undefined4,uint;
extern uint32_t thunk_FUN_01025028(uint32_t,uint32_t); extern int FUN_010218d8(void); extern int FUN_010218e4(void); extern int FUN_01025cf0(void*); extern int FUN_01021614(uint16_t); extern int FUN_010215d8(void); extern int FUN_010215f4(void); extern int FUN_01021634(void); extern int FUN_01020a6c(int); extern void FUN_01008d00(uint32_t,uint32_t); extern void FUN_01020500(void); extern int FUN_01025be0(void);
#define DAT_01020fa4 0x4100c000u
#define DAT_01020fa8 0x210015f0u
#define DAT_01020fac 0x41008000u
#define DAT_01020fb0 0xfffffee2u
#define DAT_01020fb4 0x00023280u
#define DAT_01020fb8 0x8000000bu
#define DAT_01020fbc 0xe000e100u
#define DAT_01021100 0x41008000u
#define DAT_01021104 0x4100c000u
void FUN_01020d1c(uint32_t entry_r0, uint32_t entry_r1) {
 char cVar1,cVar6; byte bVar16; int iVar9=DAT_01020fa8,iVar11=DAT_01020fa4,iVar12,iVar15,iVar22; uint uVar10,uVar20,uVar21,local_24;
    *(volatile undefined4 *)(DAT_01020fa4 + 0x4c) = 1;
    iVar22 = *(volatile int *)(iVar11 + 0x54c);
    uVar10 = thunk_FUN_01025028(entry_r0, entry_r1);
    *(volatile undefined4 *)(iVar9 + 0x38) = uVar10;
    *(volatile undefined4 *)(iVar9 + 0x3c) = 0;
    *(volatile int *)(iVar9 + 0x40) = iVar22;
    if (0x95 < *(volatile ushort *)(iVar9 + 0x1c)) {
      if (*(volatile char *)(iVar9 + 9) == '\x01') {
        iVar15 = FUN_010218d8();
        if (1 < iVar15 + 1U) {
                    /* WARNING: Subroutine does not return */
          FUN_01008d00(0x3e,0x851);
        }
      }
      else if ((*(volatile char *)(iVar9 + 9) == '\x02') && (iVar15 = FUN_010218e4(), 1 < iVar15 + 1U)) {
                    /* WARNING: Subroutine does not return */
        FUN_01008d00(0x3e,0x857);
      }
    }
    uVar21 = DAT_01020fb0;
    iVar15 = DAT_01020fac;
    *(volatile undefined4 *)(DAT_01020fac + 0x80) = 0;
    *(volatile undefined4 *)(iVar15 + 0x84) = 0;
    *(volatile undefined4 *)(iVar15 + 0x88) = 0;
    *(volatile undefined4 *)(iVar15 + 0x80) = 0;
    *(volatile undefined4 *)(iVar15 + 0x84) = 0;
    *(volatile undefined1 *)(iVar9 + 0x35) = 0;
    cVar6 = *(volatile char *)(iVar9 + 0xc);
    *(volatile uint *)(iVar15 + 0x200) = uVar21 & *(volatile uint *)(iVar15 + 0x200);
    iVar11 = DAT_01020fac;
    if (cVar6 == '\0') {
      cVar6 = *(volatile char *)(iVar9 + 9);
      iVar15 = 0;
      if (cVar6 == '\x01') goto LAB_01020e60;
LAB_01020d82:
      if (cVar6 != '\x02') {
        uVar21 = 0;
        goto LAB_01020d88;
      }
      if (*(volatile int *)(DAT_01020fac + 0x10c) == 0) {
        uVar20 = 0;
        uVar21 = 4;
      }
      else {
        uVar21 = 6;
        uVar20 = 2;
      }
      if ((*(volatile uint *)(DAT_01020fac + 0x400) & 1) != 0) {
        uVar21 = uVar20;
      }
      if (iVar15 != 0) {
        uVar20 = uVar21 & 0xb | 1;
        uVar21 = uVar21 | 1;
      }
      if (uVar20 == 0) goto LAB_01020d88;
    }
    else {
      iVar15 = *(volatile int *)(iVar15 + 0x4144);
      cVar6 = *(volatile char *)(iVar9 + 9);
      if (iVar15 != 0) {
        iVar15 = 1;
      }
      if (cVar6 != '\x01') goto LAB_01020d82;
LAB_01020e60:
      uVar21 = *(volatile uint *)(DAT_01020fac + 0x10c);
      if (uVar21 == 0) {
LAB_01020d88:
        if (*(volatile int *)(DAT_01020fac + 0x110) != 0) {
          uVar21 = uVar21 & 0xff | 0x10;
        }
      }
      else {
        uVar21 = 8;
      }
    }
    iVar15 = *(volatile int *)(DAT_01020fac + 0x104);
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    local_24 = (uint8_t)iVar15;
    *(volatile undefined4 *)(DAT_01020fac + 0x100) = 0;
    *(volatile undefined4 *)(iVar11 + 0x10c) = 0;
    *(volatile undefined4 *)(iVar11 + 0x110) = 0;
    *(volatile undefined4 *)(iVar11 + 0x104) = 0;
    *(volatile undefined4 *)(iVar11 + 0x114) = 0;
    *(volatile undefined4 *)(iVar11 + 0x118) = 0;
    *(volatile undefined4 *)(iVar11 + 0x108) = 0;
    *(volatile undefined4 *)(iVar11 + 0x16c) = 0;
    iVar11 = FUN_01025cf0(&local_24);
    iVar15 = DAT_01020fa4;
    if (iVar11 != 0) {
      uVar21 = uVar21 & 0xff | 0x10;
    }
    *(volatile undefined4 *)(DAT_01020fa4 + 0x144) = 0;
    if (((uVar21 & 0x18) == 0x10) && (*(volatile char *)(iVar9 + 9) == '\x01')) {
      iVar11 = *(volatile int *)(iVar15 + 0x548);
      uVar10 = *(volatile undefined4 *)(iVar15 + 0x544);
      uVar21 = uVar21 & 0xff | 0x20;
      *(volatile int *)(iVar9 + 0x24) = iVar11;
      *(volatile undefined4 *)(iVar9 + 0x20) = uVar10;
      if (*(volatile char *)(iVar9 + 0x29) != '\x02') goto LAB_01020e02;
LAB_01020ec2:
      cVar6 = *(volatile char *)(iVar9 + 0x18);
      if ((cVar6 == '\x04') || (cVar6 == '\b')) {
        if ((*(volatile uint *)(DAT_01020fac + 0x414) & 6) == 0) {
          cVar6 = '\b';
        }
        else {
          cVar6 = '\x04';
        }
      }
    }
    else {
      iVar11 = *(volatile int *)(DAT_01020fa4 + 0x548);
      uVar10 = *(volatile undefined4 *)(DAT_01020fa4 + 0x544);
      *(volatile int *)(iVar9 + 0x24) = iVar11;
      *(volatile undefined4 *)(iVar9 + 0x20) = uVar10;
      if ((*(volatile char *)(iVar9 + 0x29) == '\x02') || (*(volatile char *)(iVar9 + 9) == '\x02'))
      goto LAB_01020ec2;
LAB_01020e02:
      cVar6 = *(volatile char *)(iVar9 + 0x18);
    }
    cVar1 = *(volatile char *)(iVar9 + 9);
    bVar16 = *(volatile byte *)(iVar9 + 8);
    uVar20 = (uint)bVar16;
    *(volatile char *)(iVar9 + 0x28) = cVar6;
    *(volatile char *)(iVar9 + 0x29) = cVar1;
    if (uVar20 == 0) {
      *(volatile ushort *)(iVar9 + 7) = (ushort)bVar16;
      *(volatile byte *)(iVar9 + 9) = bVar16;
      *(volatile byte *)(iVar9 + 0xc) = bVar16;
      uVar10 = 0;
    }
    else if ((uVar21 & 0x11) == 0) {
      iVar15 = uVar20 - 1;
      cVar6 = *(volatile char *)(iVar9 + 7);
      *(volatile undefined1 *)(iVar9 + 9) = 0;
      *(volatile undefined2 *)(iVar9 + 7) = 0;
      if (iVar15 != 0) {
        iVar15 = 1;
      }
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_01008d00(0x3e,0x804);
      }
      if (uVar20 == 1) {
        if (cVar1 == '\x01') {
          iVar12 = FUN_01021614(*(volatile undefined2 *)(iVar9 + 0x1c));
          uVar20 = iVar12 + iVar11;
        }
        else {
          iVar12 = FUN_010215d8();
          uVar20 = iVar12 + iVar11;
        }
      }
      else if (cVar1 == '\x01') {
        iVar12 = FUN_010215f4();
        uVar20 = iVar12 + iVar11;
      }
      else {
        iVar12 = FUN_01021634();
        uVar20 = iVar12 + iVar11;
      }
      if (cVar6 == '\x01') {
        if (uVar20 < iVar22 + 0x3bU) {
          *(volatile undefined4 *)(DAT_01021100 + 0x10) = 1;
          uVar10 = 1;
          goto LAB_01020ee8;
        }
        *(volatile undefined1 *)(iVar9 + 7) = 1;
      }
      iVar22 = FUN_01020a6c(iVar15);
      if (iVar22 == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_01008d00(0x3e,0xa52);
      }
      uVar10 = 0;
    }
    else {
      FUN_01020500();
      uVar10 = 0;
    }
LAB_01020ee8:
    iVar22 = DAT_01020fac;
    if (*(volatile char *)(iVar9 + 0x44) != '\0') {
      *(volatile undefined4 *)(DAT_01020fac + 0x1ac) = 0;
      *(volatile undefined1 *)(iVar9 + 0x44) = 0;
      *(volatile uint *)(iVar22 + 0x514) = *(volatile uint *)(iVar22 + 0x514) & 0xfff0ffff;
      uVar20 = *(volatile uint *)(iVar9 + 0x14) & 0xfffffffc;
      *(volatile uint *)(iVar22 + 0x900) = uVar20;
      *(volatile uint *)(iVar9 + 0x14) = uVar20;
      *(volatile undefined4 *)(iVar22 + 0x910) = DAT_01020fb4;
    }
    if ((int)(uVar21 << 0x1f) < 0) {
LAB_01020ff6:
      ((void (*)(void))(uintptr_t)*(uint32_t *)(iVar9 + 0x4c))();
      uVar21 = uVar21 & 0x10;
      if (uVar21 != 0) goto LAB_01020f2e;
LAB_01021000:
      if (*(volatile char *)(iVar9 + 9) != '\x02') {
        FUN_01025be0();
        return;
      }
    }
    else {
      if ((int)(uVar21 << 0x1e) < 0) {
        uVar20 = *(volatile uint *)(DAT_01021100 + 0x450);
        if (((int)(uVar20 << 7) < 0) &&
           (((((uVar20 & 0xf00) == 0 || (uVar20 & 0xf0) == 0 || ((uVar20 & 0xf) == 0)) &&
             ((uVar20 << 8) >> 0x1d < 3)) && (*(volatile int *)(DAT_01021100 + 0x454) != 0))))
        goto LAB_01020ff6;
        if (*(volatile byte *)(iVar9 + 0x34) < *(volatile byte *)(*(volatile int *)(iVar9 + 0x30) + 1)) {
          uVar20 = 0;
          uVar21 = uVar21 & 0xff;
        }
        else {
          uVar20 = ((uVar21 ^ 4) << 0x1d) >> 0x1f;
        }
        ((void (*)(uint32_t,uint32_t))(uintptr_t)*(uint32_t *)(iVar9 + 0x50))(uVar20,uVar10);
      }
      else if ((uVar21 & 0x28) != 0) {
        ((void (*)(uint32_t,uint32_t))(uintptr_t)*(uint32_t *)(iVar9 + 0x54))(uVar10,((uVar21 ^ 0x20) << 0x1a) >> 0x1f);
      }
      uVar21 = uVar21 & 0x10;
      if (uVar21 == 0) goto LAB_01021000;
LAB_01020f2e:
      ((void (*)(void))(uintptr_t)*(uint32_t *)(iVar9 + 0x58))();
      if (*(volatile char *)(iVar9 + 9) != '\x02') goto LAB_01020f60;
    }
    cVar6 = *(volatile char *)(iVar9 + 0xc);
    if (cVar6 != '\0') {
      if (cVar6 == '\x02') {
        *(volatile int *)(DAT_01021104 + 0x544) = *(volatile int *)(iVar9 + 0x24) + *(volatile int *)(iVar9 + 0x10);
      }
      else {
        if (cVar6 != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_01008d00(0x3e,0xc15);
        }
        if (*(volatile uint *)(iVar9 + 0x10) <= *(volatile uint *)(iVar9 + 0x24)) {
                    /* WARNING: Subroutine does not return */
          FUN_01008d00(0x3e,0xc16);
        }
        *(volatile uint *)(DAT_01020fa4 + 0x544) = *(volatile uint *)(iVar9 + 0x10);
      }
      *(volatile undefined4 *)(DAT_01020fa4 + 0x1c4) = DAT_01020fb8;
    }
LAB_01020f60:
    cVar6 = FUN_01025be0();
    iVar22 = DAT_01020fbc;
    if ((uVar21 != 0) && (cVar6 != '\x01')) {
      local_24 = 0;
      do {
        local_24 = local_24 + 1;
        if (local_24 == -1) {
                    /* WARNING: Subroutine does not return */
          FUN_01008d00(0x3e,0xc34);
        }
      } while ((*(volatile uint *)(DAT_01020fac + 0x550) & 0xf7) == 4);
      *(volatile undefined4 *)(DAT_01020fac + 0x110) = 0;
      *(volatile undefined4 *)(iVar22 + 0x180) = 0x100;
    }
    return;
}
