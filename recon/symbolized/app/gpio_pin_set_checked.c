#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00017768 @ 0x00017768
 * public-name: gpio_pin_set_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_set_checked                     <= FUN_00017768 @ 0x00017768
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00017768 @ 0x17768  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(const char *, unsigned int);
typedef void (*jfn847)(void);
void gpio_pin_set_checked(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  jfn847 UNRECOVERED_JUMPTABLE;

  uVar1 = 1u << (param_2 & 0xff);
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 4)) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U") /*=0x99de0*/, ((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x64f);
    printk(((unsigned long)"\tUnsupported pin\n") /*=0x99e1e*/, 0, 0, 0);
    assert_post_action(((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x64f);
  }
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 0x10)) != 0) {
    param_3 = param_3 ^ 1;
  }
  /* BRING-UP WIRING FIX (P4 iteration 5) — indirect-call ABI.
   * Original bytes at 0x17768 tail-call the port op with r0 = the port device
   * and r1 = BIT(pin) (`lsl.w r1,r3,r1` at 0x1776c, then
   * `ldr r3,[r0,#8]; ldr r3,[r3,#0x10 or 0xc]; pop; bx r3`), i.e. Zephyr's
   * api->port_clear_bits_raw(port, mask) / api->port_set_bits_raw(port, mask).
   * The `(*UNRECOVERED_JUMPTABLE)()` no-argument form only worked because the
   * ORIGINAL codegen happened to leave r0/r1 correct; our codegen leaves r1 =
   * the raw pin number, so the wrong pins were driven.  Arguments are now
   * explicit.  Build/wiring TU only; recon/app/src left untouched. */
  if (param_3 == 0) {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0x10);
  } else {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0xc);
  }
  ((void (*)(int, unsigned int))UNRECOVERED_JUMPTABLE)(param_1, uVar1);
}
