/* Reconstructed FUN_00084774 @ 0x84774  (parity: 300/300 trials, PROVEN) */

extern int FUN_00084602(int *, int, int, unsigned short *);

/* ARGUMENT-PASSTHROUGH DEFECT, fixed in P4 iteration 15.
 * The original (0x84774) is a TAIL CALL that forwards ALL FOUR arguments to
 * 0x84602 (`flash_page_index_lookup`): it pushes {r4,r5,r6} and uses only
 * those as scratch, so r1 (min), r2 (max) and r3 (index out-pointer) reach
 * the callee untouched:
 *     84774  push {r4,r5,r6}
 *     84776  ldrh r4,[r0,#8] ; ldrh r5,[r0,#10] ; subs r5,r5,r4
 *     8477c  ldrd r4,r6,[r0] ; mla r4,r6,r5,r4 ; cmp r1,r4 ; ble 8479c
 *     84788  ldrh r4,[r0,#20]; ldrh r5,[r0,#22]; subs r5,r5,r4
 *     8478e  ldrd r4,r6,[r0,#12]; mla r4,r6,r5,r4; cmp r1,r4; bgt 847a2
 *     8479a  adds r0,#12
 *     8479c  pop {r4,r5,r6} ; b.w 0x84602
 * The previous two-parameter declaration let GCC use r2/r3 as scratch
 * (`subs r2,r2,r3` at our 0x77b82/0x77b94), so `max` arrived at
 * flash_page_index_lookup as (max_idx - min_idx) = 9 instead of 4400000 and
 * the lookup returned -EINVAL.  MEASURED in iteration 15 (g1-i15c): that
 * -EINVAL made npm1300_charger_init (panel_temp_calibration_init, 0x62644)
 * return -22, and main then skipped jdb_panel_init / pt_nfc_eeprom_link_start
 * / notification_system_init -- the E4 blocker.  This is the SIXTH member of
 * the dropped-argument class the differential harness is structurally blind
 * to (callees are order-keyed oracles; their argument registers are never
 * compared). */
int FUN_00084774(int *param_1, int param_2, int param_3,
                        unsigned short *param_4)
{
  int diff1 = *(unsigned short *)((char *)param_1 + 10) - *(unsigned short *)((char *)param_1 + 8);
  int formula1 = param_1[1] * diff1 + param_1[0];
  if (formula1 < param_2) {
    int diff2 = *(unsigned short *)((char *)param_1 + 0x16) - *(unsigned short *)((char *)param_1 + 0x14);
    int formula2 = param_1[4] * diff2 + param_1[3];
    if (formula2 < param_2) {
      return 0xffffffea;
    }
    param_1 = param_1 + 3;
  }
  return FUN_00084602(param_1, param_2, param_3, param_4);
}

