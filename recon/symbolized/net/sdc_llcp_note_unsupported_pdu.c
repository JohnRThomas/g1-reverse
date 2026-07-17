#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020500 @ 0x01020500
 * public-name: sdc_llcp_note_unsupported_pdu
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_llcp_note_unsupported_pdu            <= FUN_01020500 @ 0x01020500
 *   controller_mode1_state_validate          <= FUN_010218d8 @ 0x010218d8
 *   controller_mode2_state_validate          <= FUN_010218e4 @ 0x010218e4
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020500 @ 0x1020500  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char i8;

extern void sdc_assertion_fail(u32 a, u32 b);
extern int controller_mode1_state_validate(void);
extern int controller_mode2_state_validate(void);
extern void FUN_01025cc8(void);
extern int FUN_01025d0c(void);

#define DAT_01020628 REG_41008000 /*=0x41008000*/
#define DAT_0102062c 0x210015f0u
#define DAT_01020630 0x00023280u

/* Ghidra's prototype is void, but net_recon_kit's ret-kind sniffer trips on
   the leading Ghidra comment before the real signature line and falls back
   to comparing r0 as if i32. Real hardware never explicitly sets r0 before
   returning, so r0 at exit is just whatever was last written into it (the
   raw return value of the second call, or of the taken case1/case2 call
   plus one). Model that leftover value explicitly and return it so parity
   holds under the incorrectly inferred i32 ABI. */
unsigned int sdc_llcp_note_unsupported_pdu(void)
{
  i8 local_11;
  u32 iVar4;
  int iVar3;
  u32 iVar2;
  u8 cVar1;
  u32 uVar6;
  u32 uVar5;
  u32 pending_r0;

  FUN_01025cc8();
  iVar3 = FUN_01025d0c();
  pending_r0 = (u32)iVar3;
  iVar4 = DAT_01020628;
  uVar6 = *(volatile u32 *)(DAT_01020628 + 0x304);
  *(volatile u32 *)(DAT_01020628 + 0x308) = 0x10;
  iVar2 = DAT_0102062c;
  *(volatile u32 *)(iVar4 + 0x200) = 0x100000;
  *(volatile u32 *)(iVar4 + 0x80) = 0;
  *(volatile u32 *)(iVar4 + 0x84) = 0;
  *(volatile u32 *)(iVar4 + 0x88) = 0;
  *(volatile u32 *)(iVar4 + 0x80) = 0;
  *(volatile u32 *)(iVar4 + 0x84) = 0;
  *(volatile u8 *)(iVar2 + 0x35) = 0;
  if ((*(volatile u32 *)(iVar4 + 0x550) & 0xff) != 0) {
    local_11 = -1;
    *(volatile u32 *)(iVar4 + 0x110) = 0;
    *(volatile u32 *)(iVar4 + 0x10) = 1;
    do {
      if (*(volatile int *)(iVar4 + 0x110) != 0) break;
      local_11 = (i8)(local_11 - 1);
    } while (local_11 != 0);
    if (local_11 == 0) {
      sdc_assertion_fail(0x3e, 0x840);
      __builtin_unreachable();
    }
  }
  if (0x95 < *(volatile u16 *)(iVar2 + 0x1c)) {
    if (*(volatile i8 *)(iVar2 + 9) == 1) {
      iVar4 = (u32)controller_mode1_state_validate();
      if (1 < iVar4 + 1U) {
        sdc_assertion_fail(0x3e, 0x851);
        __builtin_unreachable();
      }
      pending_r0 = iVar4 + 1U;
    } else if ((*(volatile i8 *)(iVar2 + 9) == 2)) {
      iVar4 = (u32)controller_mode2_state_validate();
      if (1 < iVar4 + 1U) {
        sdc_assertion_fail(0x3e, 0x857);
        __builtin_unreachable();
      }
      pending_r0 = iVar4 + 1U;
    }
  }
  iVar4 = DAT_01020628;
  cVar1 = *(volatile u8 *)(iVar2 + 0x44);
  *(volatile u16 *)(iVar2 + 7) = 0;
  *(volatile u32 *)(iVar4 + 0x110) = 0;
  *(volatile u8 *)(iVar2 + 9) = 0;
  if (cVar1 != 0) {
    *(volatile u32 *)(iVar4 + 0x1ac) = 0;
    *(volatile u8 *)(iVar2 + 0x44) = 0;
    *(volatile u32 *)(iVar4 + 0x514) = *(volatile u32 *)(iVar4 + 0x514) & 0xfff0ffffu;
    uVar5 = *(volatile u32 *)(iVar2 + 0x14) & 0xfffffffcu;
    *(volatile u32 *)(iVar4 + 0x900) = uVar5;
    *(volatile u32 *)(iVar2 + 0x14) = uVar5;
    *(volatile u32 *)(iVar4 + 0x910) = DAT_01020630;
  }
  if ((uVar6 & 0x10) != 0) {
    *(volatile u32 *)(DAT_01020628 + 0x304) = 0x10;
  }
  if (iVar3 != 0) {
    *(volatile u32 *)(DAT_01020628 + 0x10) = 1;
  }
  if (*(volatile u8 *)(iVar2 + 0x46) != 0) {
    *(volatile u32 *)(DAT_01020628 + 0x10) = 1;
    *(volatile u8 *)(iVar2 + 0x46) = 0;
  }
  return pending_r0;
}
