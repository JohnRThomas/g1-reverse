#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032c28 @ 0x01032c28
 * public-name: FUN_01032c28
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_0102eb2c @ 0x0102eb2c
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   __memcpy_chk                             <= FUN_0103b53a @ 0x0103b53a
 * address symbols (name @ address):
 *   rodata_10335e5                           @ 0x010335e5
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e3e0                           @ 0x0103e3e0
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_esb_event_handler_fn                   @ 0x2100499c
 *   g_net_radio_irq_continuation_ptr         @ 0x210049a0
 *   g_esb_tx_busy_flag                       @ 0x210049a8
 *   g_esb_pipe_cfg_field                     @ 0x210049ac
 *   g_net_rf_cur_frame_ptr                   @ 0x21004a8c
 *   g_esb_state                              @ 0x21004a94
 *   g_net_rf_ack_hdr_buf                     @ 0x2100635b
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01032c28 @ 0x1032c28  (parity 300 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))

extern void arch_irq_enable(unsigned);
extern void FUN_01032860(unsigned);
extern void FUN_01032ad8(void);
extern void FUN_01033b18(unsigned,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern void assert_print(unsigned,unsigned,unsigned);
extern void __memcpy_chk(unsigned,unsigned,unsigned,unsigned);

void FUN_01032c28(void)
{
  W32(((unsigned long)&g_esb_tx_busy_flag) /*=0x210049a8*/) = 1;
  u32 pcVar4 = ((unsigned long)&g_esb_state) /*=0x21004a94*/;
  u32 idx = W32(0x21004a60u + 0x24u);
  u8 cVar1 = W8(pcVar4);
  u32 pbVar9 = W32(0x21004a60u + idx*4u);
  u32 piVar5_addr = ((unsigned long)&g_net_rf_cur_frame_ptr) /*=0x21004a8c*/;
  W32(piVar5_addr) = pbVar9;
  u32 pbVar3 = ((unsigned long)&g_net_rf_ack_hdr_buf) /*=0x2100635b*/;
  u32 uVar13;

  if (cVar1 == 0) {
    W16(pbVar3) = 0; /* pbVar3[0]=0; pbVar3[1]=0 */
    {
      void (*fn)(unsigned char) = (void (*)(unsigned char))W32(((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/);
      fn(W8(pbVar9));
    }
    u32 puVar10 = W32(piVar5_addr);
    W8(pbVar3) = (u8)((W8(pbVar3) & 0xfcu) | (W8(puVar10+4) & 3u));
    __memcpy_chk(pbVar3+2, puVar10+5, W8(puVar10), 0xfb);
    W32(REG_41008000 /*=0x41008000*/ + 0x200) = 0x11b;
    W32(REG_41008000 /*=0x41008000*/ + 0x304) = 0x10;
    W32(((unsigned long)&g_esb_pipe_cfg_field) /*=0x210049ac*/) = W16(pcVar4 + 0xe);
    W32(((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/) = 0x010338b1u;
    W8(((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/) = 2;
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
    __memcpy_chk(0x2100635du, pbVar9+5, W8(pbVar9), 0xfb);
    if (bVar14 == 0) {
      W32(REG_41008000 /*=0x41008000*/+0x200) = 0x113;
      W32(((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/) = ((unsigned long)&rodata_10335e5) /*=0x10335e5*/;
      W8(((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/) = 1;
      W32(REG_41008000 /*=0x41008000*/+0x304) = 0x10;
      uVar13 = 0;
      goto tail;
    }
    W32(REG_41008000 /*=0x41008000*/+0x200) = 0x11b;
    W32(((unsigned long)&g_esb_pipe_cfg_field) /*=0x210049ac*/) = W16(pcVar4+0xe);
    W32(((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/) = 0x010338b1u;
    W8(((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/) = 2;
    W32(REG_41008000 /*=0x41008000*/+0x304) = 0x10;
    goto set13;
  }
set13:
  uVar13 = 1;
tail:
  {
    u32 iVar12 = W32(piVar5_addr);
    W32(REG_41008000 /*=0x41008000*/+0x52c) = W8(iVar12+1);
    W32(REG_41008000 /*=0x41008000*/+0x530) = (1u << W8(iVar12+1)) & 0xffu;
    u32 sz = (u32)W8(((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/+0x13) + 0x960u;
    if (sz > 0x9c4u) {
      assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e3e0) /*=0x103e3e0*/, 0x6b7u);
      assert_post_action(((unsigned long)&rodata_103e3e0) /*=0x103e3e0*/, 0x6b7u);
      __builtin_unreachable();
    }
    W32(REG_41008000 /*=0x41008000*/+0x508) = (u32)W8(((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/+0x13);
    FUN_01032ad8();
    W32(REG_41008000 /*=0x41008000*/+0x504) = pbVar3;
    W32(0xe000e100u+0x180) = 0x100;
    arch_irq_enable(8);
    W32(REG_41008000 /*=0x41008000*/+0x104) = 0;
    W32(REG_41008000 /*=0x41008000*/+0x108) = 0;
    W32(REG_41008000 /*=0x41008000*/+0x110) = 0;
    W32(REG_41008000 /*=0x41008000*/+0x10c) = 0;
    FUN_01033b18(0, uVar13);
    FUN_01032860(uVar13);
    W32(0x41014000u+0x18) = 1;
    return;
  }
}
