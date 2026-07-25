#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032764 @ 0x01032764
 * public-name: FUN_01032764
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_op_status                    @ 0x210049a4
 *   g_net_radio_mode_state                   @ 0x21004a9c
 *   REG_41008510                             @ 0x41008510
 */
/* net-core FUN_01032764 @ 0x1032764  (CFG-directed candidate) */

/* net-core FUN_01032764 @ 0x1032764  (parity 300 trials PROVEN)
 *
 * P4 iteration 23 — SIGNATURE CORRECTION with disassembly evidence.
 * The shipped body (analysis 0x01032764..0x01032792) touches r0, r2, r3 only:
 *     ldr r3,[pc,#44] ; ldr r2,[pc,#48] ; ldrb r3,[r3,#8]
 *     str.w r3,[r2,#0x510] ; cmp r3,#4 ; bhi ; tbb [pc,r3]
 *     movs r2,#0xa0 / mov.w r2,#300 ; ldr r3,[pc,#28] ; movs r0,#1 ;
 *     str r2,[r3,#0] ; bx lr        (default: movs r0,#0 ; bx lr)
 * — it NEVER writes r1.  Its only caller, FUN_010333b4, exploits that: it
 * loads the RADIO callback-slot pointer (g_esb_event_handler_fn, 0x2100499c)
 * into r1 BEFORE the call and dereferences r1 AFTER it, i.e. GCC's
 * interprocedural register allocation kept the value live across the call.
 * FUN_010333b4's reconstruction already models the pair as one AAPCS 64-bit
 * result ("returns status in r0 and deliberately preserves its incoming r1").
 * The previous `unsigned int FUN_01032764(void)` DROPPED both arguments, so in
 * a separate translation unit GCC was free to clobber r1 — measured on
 * /private/tmp/g1-i23d-net: the CPUNET entered FUN_010333b4, called this leaf,
 * and never came back, because `callback_slot` was garbage and the indirect
 * `(*callback_slot)(saved[0x11])` went nowhere.  Declaring the live-through
 * explicitly (64-bit return = r0 low, r1 high) restores the shipped contract.
 * This is the harness blind spot the ledger names: parity cannot see a dropped
 * register argument, because it drives the ORIGINAL bytes with its own r1.
 */

unsigned long long FUN_01032764(unsigned int unused_r0, unsigned int slot)
{
  volatile unsigned char *p8  = (volatile unsigned char*)((unsigned long)&g_net_radio_mode_state) /*=0x21004a9c*/;
  volatile unsigned int  *p10 = (volatile unsigned int*)REG_41008510 /*=0x41008510*/;
  volatile unsigned int  *out = (volatile unsigned int*)((unsigned long)&g_net_radio_op_status) /*=0x210049a4*/;
  unsigned char bVar1 = *p8;

  (void)unused_r0;
  *p10 = (unsigned int)bVar1;
  switch (bVar1) {
  case 0:
  case 3:
    *out = 300;
    return ((unsigned long long)slot << 32) | 1u;
  case 1:
  case 4:
    *out = 0xa0u;
    return ((unsigned long long)slot << 32) | 1u;
  default:
    return ((unsigned long long)slot << 32);
  }
}
