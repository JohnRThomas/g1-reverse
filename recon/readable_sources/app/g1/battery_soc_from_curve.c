#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_battery_soc_curve_point__param_0003    [param_0003; G1-original]
 * Raw function identity: 0x0000e340.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0000e340 @ 0x0000e340
 * public-name: battery_soc_from_curve
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   battery_model_state_update               <= FUN_0000c358 @ 0x0000c358
 *   battery_soc_from_curve                   <= FUN_0000e340 @ 0x0000e340
 * address symbols (name @ address):
 *   g_batt_soc_curve_charge_lo               @ 0x20002d14
 *   g_batt_soc_curve_charge_hi               @ 0x20002d18
 *   g_batt_soc_curve_interp_buf              @ 0x2000b4a4
 *   g_batt_soc_curve_val_hi                  @ 0x2000b4ec
 *   g_batt_soc_curve_val_lo                  @ 0x2000b4f0
 */
/* Reconstructed FUN_0000e340 @ 0xe340  (parity: 300/300 trials, PROVEN) */

extern void battery_model_state_update(void*, void*, void*, void*);

float battery_soc_from_curve(unsigned int *out_struct, float unused_s0, float cmpval)
{
  unsigned char stk[0x18];
  float *p_local_20 = (float*)(stk+0);
  unsigned int *p_local_18 = (unsigned int*)(stk+8);
  unsigned int *p_local_14 = (unsigned int*)(stk+0xc);
  unsigned int *p_local_c  = (unsigned int*)(stk+0x14);
  void *p_aux = (void*)(stk+4);
  unsigned int selA, selB, val1, val2;

  /* 0xe340: vmov r3,s1; cmp r3,#0; itete lt -- the selector is a SIGN-BIT
   * test on the raw bits, not a float comparison.  `cmpval < 0.0f` differs
   * for -0.0 and for negative NaNs, which selects the wrong curve pair. */
  union { float f; int i; } sel;
  sel.f = cmpval;
  if (sel.i < 0) {
    selA = 0x20002d0cUL;
    selB = 0x20002d10UL;
  } else {
    selA = ((unsigned long)&g_batt_soc_curve_charge_lo) /*=0x20002d14*/;
    selB = ((unsigned long)&g_batt_soc_curve_charge_hi) /*=0x20002d18*/;
  }
  val1 = *(volatile unsigned int*)selA;
  val2 = *(volatile unsigned int*)selB;
  *(volatile unsigned int*)((unsigned long)&g_batt_soc_curve_val_lo) /*=0x2000b4f0*/ = val1;
  *(volatile unsigned int*)((unsigned long)&g_batt_soc_curve_val_hi) /*=0x2000b4ec*/ = val2;

  battery_model_state_update((void*)((unsigned long)&g_batt_soc_curve_interp_buf) /*=0x2000b4a4*/, p_local_20, p_aux, p_local_18);

  *p_local_20 = *p_local_20 * 100.0f;

  if (out_struct != 0) {
    out_struct[0] = *p_local_18;
    out_struct[1] = *p_local_14;
    out_struct[2] = *p_local_c;
  }
  return *p_local_20;
}
