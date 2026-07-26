#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002ea28 @ 0x0002ea28
 * public-name: fuel_gauge_sample_init_timestamp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   batt_soc_curve_estimate                  <= FUN_0000e2b4 @ 0x0000e2b4
 *   fuel_gauge_read_voltage_current_temp     <= FUN_0002e988 @ 0x0002e988
 *   fuel_gauge_sample_init_timestamp         <= FUN_0002ea28 @ 0x0002ea28
 *   k_uptime_get_3                           <= FUN_0007ceda @ 0x0007ceda
 *   sensor_channel_get_trampoline            <= FUN_0007cef6 @ 0x0007cef6
 * address symbols (name @ address):
 *   g_fuel_gauge_init_timestamp              @ 0x20004790
  *
 * ITERATION 39 DEFECT FIX — the request record handed to batt_soc_curve_estimate
 * is FOUR words, not three.  Shipped prologue:
 *
 *   0002ea2c  ldr  r3, [pc, #0x40]   ; literal @0x2ea70 = 0x00088a50
 *   0002ea30  str  r3, [sp, #0x14]   ; <<< request[3] = the battery curve table
 *   0002ea3a  strd r4, r4, [sp, #8]  ; request[0] = request[1] = 0
 *   0002ea3e  str  r4, [sp, #0x10]   ; request[2] = 0
 *   0002ea40  bl   #0x2e988          ; read v/i/t into sp+8 / sp+0xc / sp+0x10
 *   0002ea54  add  r0, sp, #8        ; r0 = request
 *   0002ea56  bl   #0xe2b4
 *
 * batt_soc_curve_estimate NULL-checks word 3 (`ldr r3,[r0,#0xc]` / `cbz r3` ->
 * -EINVAL) and forwards it in r1 to battery_soc_curve_model_init, which
 * memcpy's 0x1600 bytes out of it into the estimator workspace.  Omitting the
 * store left a stale stack word there (measured 0x0009d5ba), which is
 * non-NULL, so the guard passed and 5632 bytes of unrelated .rodata became the
 * battery curve: the EKF covariance went to NaN and device_info[0xfc0] stuck
 * at 0 for the whole run, which held the `> 0x1d` gate in
 * handle_box_placement_event shut and suppressed both the SAADC's third
 * per-tick conversion call site and the ST25DV NDEF/WLC record write.
*/
/* Reconstructed FUN_0002ea28 @ 0x2ea28  (parity: 300/300 trials, PROVEN) */

extern int batt_soc_curve_estimate(void*, int);
extern int fuel_gauge_read_voltage_current_temp(int, void*, void*, void*);
extern unsigned long long k_uptime_get_3(void);
extern void sensor_channel_get_trampoline(int, int, void*);

int fuel_gauge_sample_init_timestamp(int param_1)
{
    struct {
        unsigned char event[8];
        int first;
        int second;
        int third;
        const void *curve_table;
    } frame;
    int iVar1;

    frame.curve_table = (const void *)0x00088a50u;
    frame.first = 0;
    frame.second = 0;
    frame.third = 0;
    iVar1 = fuel_gauge_read_voltage_current_temp(param_1, &frame.first, &frame.second, &frame.third);
    if (iVar1 >= 0) {
        sensor_channel_get_trampoline(param_1, 0x39, frame.event);
        iVar1 = batt_soc_curve_estimate(&frame.first, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = k_uptime_get_3();
            *(volatile unsigned long long*)((unsigned long)&g_fuel_gauge_init_timestamp) /*=0x20004790*/ = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}
