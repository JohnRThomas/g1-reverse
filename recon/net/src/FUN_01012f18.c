/* net-core sdc_conn_event_timing_prepare @ 0x01012f18
 *
 * Back mapping: FUN_01012f18.  The NCS 2.5.1 SDC archive contains the same
 * 0x738-byte routine as obfuscated symbol
 * sym_RGPKJ26QV7SQW5X3WYCPY4K6NKRUE6OJNP7M2PA (Thumb opcode ratio 0.997).
 * It prepares the radio timing window for one connection-event counter.  The
 * four values at context+0x31c are the initial, tracking, established and
 * recovery timing modes.  A return of one asks the caller to skip the event
 * count written through event_skip_out; zero publishes the prepared window.
 * CFG verification: five production fixtures cover every timing mode and both
 * initial-attempt values; mutating the published attempt byte is rejected.
 */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long ulonglong;

extern int sdc_assertion_fail(int, int);                        /* FUN_01008d00 */
extern int controller_timing_request_schedule(int, int);        /* FUN_0100d4d0 */
extern int sdc_phy_timing_offset_get(int, int);                  /* FUN_0100d58c */
extern int sdc_conn_recovery_window_update(uint, int, uint, void *); /* FUN_0100d6e8 */
extern int sdc_radio_context_fixed_time_get(int);                /* FUN_0100f0fc */
extern int sdc_conn_radio_overhead_set(int, int);                /* FUN_0100f48c */
extern int sdc_controller_random_get(void);                      /* FUN_0100f63c */
extern void sdc_conn_timing_fault(void);                         /* FUN_01012c08 */
extern int sdc_conn_timing_guard_enabled(void);                  /* FUN_01016160 */
extern void sdc_conn_recovery_state_restore(int);                /* FUN_0101618c */
extern void mpsl_timeslot_window_get(void *, void *);            /* FUN_010209c8 */
extern int radio_phy_airtime_tail_get(int);                      /* FUN_010209e0 */
extern int radio_phy_airtime_base_get(int);                      /* FUN_010209f0 */
extern int sdc_conn_window_admit(int, int);                      /* FUN_010231c8 */
extern int mpsl_timeslot_distance_get(uint, uint, uint, uint, uint); /* FUN_010243c0 */
extern int sdc_timing_scale(int, int);                           /* FUN_01024678 */
extern int sdc_timing_compensation_enabled(void);                /* FUN_010247cc */
extern short sdc_timing_compensation_get(void);                  /* thunk_FUN_010246cc */

#define B(o)  (*(volatile byte *)(context + (o)))
#define SC(o) (*(volatile signed char *)(context + (o)))
#define S(o)  (*(volatile short *)(context + (o)))
#define H(o)  (*(volatile ushort *)(context + (o)))
#define I(o)  (*(volatile int *)(context + (o)))
#define U(o)  (*(volatile uint *)(context + (o)))

#define G54B (*(volatile byte *)0x21000f54)
#define G58U (*(volatile uint *)0x21000f58)
#define TBL(idx) (*(short *)(0x0103c1f8 + (uint)(idx) * 2))
#define MAGIC 0x10624dd3u
#define PANIC(x) do { for(;;){ sdc_assertion_fail(0x30,(x)); } } while(0)

undefined4 sdc_conn_event_timing_prepare(int context, uint event_counter,
                                        int initial_attempt,
                                        int allow_reschedule,
                                        short *event_skip_out)
{
  signed char cVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  undefined1 uVar7;
  short sVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;

  (void)uVar2; (void)uVar10; (void)local_34;
  bVar6 = B(0x6f);
  (void)bVar6;
  local_38 = 0;
  sVar8 = sdc_timing_compensation_get();
after_thunk:
  if (0xb < B(0x2d8)) {
    sdc_conn_timing_fault();
    sdc_assertion_fail(0x30,0x571);
    goto after_thunk;
  }
  cVar1 = SC(0xc6);
  sVar8 = sVar8 + TBL(B(0x2d8));
  if ((((initial_attempt == 0) && (SC(0x31c) == '\x03')) && (cVar1 == '\x0e')) &&
     (H(0x3bc) == event_counter)) {
    U(0x318) = (uint)H(0x362) + (uint)H(0x2f6);
    U(0x310) = U(0x324);
    U(0x314) = U(0x14);
    sdc_conn_recovery_state_restore(context);
    U(0x24) = U(0x3c0);
    H(0x28) = H(0x3be);
    U(0x14) = U(0x3c4);
    U(0x1c) = U(0x3c8);
    B(0x31c) = 2;
  }
  sVar4 = (short)event_counter;
  iVar22 = (int)(short)(sVar4 - S(0x360));
  iVar21 = (int)(short)(sVar4 - S(0xbc));
  if (iVar22 < 0) {
    B(0x333) = 0;
    bVar5 = G54B;
    U(0x358) = U(0x350);
    U(0x35c) = U(0x354);
    iVar22 = iVar21;
    iVar14 = 1;
  }
  else {
    bVar5 = G54B;
    iVar14 = allow_reschedule;
  }
  uVar11 = (uint)bVar5;
  if ((uVar11 != 0) && (uVar11 = sdc_timing_compensation_enabled(), uVar11 != 0)) {
    if ((H(0x308) < 2) || ((SC(0x31c) == '\x02' || (B(0x332) != '\0')))) {
      uVar11 = 0;
    }
    else if (U(0x14) < 0x1d4c) {
      uVar11 = 0;
    }
    else {
      if (0xb < B(0x2d8)) {
        sdc_conn_timing_fault();
        sdc_assertion_fail(0x30,0x571);
        goto after_thunk;
      }
      sVar8 = TBL(B(0x2d8)) + 0x640;
      if (SC(0x31c) == '\x01') {
        if (SC(0xc9) == '\x03') {
          iVar12 = I(0x314);
          iVar19 = I(0x24) + iVar12;
        }
        else {
          iVar19 = I(0x24);
          iVar12 = sdc_phy_timing_offset_get(B(0x2ef),B(0x6f));
          iVar19 = iVar19 + iVar12;
          iVar12 = I(0x314);
        }
        iVar12 = sdc_timing_scale(iVar12,sVar8);
        iVar16 = I(0x310);
        iVar20 = I(0x318);
        I(0x310) = iVar12;
        iVar19 = sdc_timing_scale(iVar19,sVar8);
        iVar17 = I(0x320);
        I(0x320) = iVar19;
        iVar13 = sdc_timing_scale(U(0x14),sVar8);
        if (U(0x14) < 0x1d4c) {
          iVar13 = iVar13 + 2;
        }
        iVar15 = I(0x324);
        I(0x324) = iVar13;
        uVar11 = (iVar13 - iVar15) *
                 ((((uint)H(0x2f6) + iVar21) - iVar22) + ~U(0x318)) +
                 (iVar12 - iVar16) * iVar20 + (iVar19 - iVar17);
      }
      else {
        iVar12 = sdc_timing_scale(U(0x14),sVar8);
        iVar19 = I(0x324);
        if (U(0x14) < 0x1d4c) {
          iVar12 = iVar12 + 2;
        }
        I(0x324) = iVar12;
        uVar11 = (iVar12 - iVar19) * (((uint)H(0x2f6) + iVar21) - iVar22);
      }
      B(0x332) = 1;
    }
  }
  switch(B(0x31c)) {
  case 0:
    iVar22 = sdc_phy_timing_offset_get(B(0x2ef),B(0x6f));
    uVar18 = MAGIC;
    uVar10 = sdc_timing_scale(I(0x24) + iVar22,sVar8);
    U(0x320) = uVar10;
    iVar21 = sdc_timing_scale(U(0x14),sVar8);
    if (U(0x14) < 0x1d4c) {
      iVar21 = iVar21 + 2;
    }
    I(0x324) = iVar21;
    mpsl_timeslot_window_get(&local_30,&local_34);
    iVar21 = mpsl_timeslot_distance_get(U(0x358),U(0x35c),local_30,uStack_2c,local_34);
    bVar6 = B(0x6f);
    iVar14 = radio_phy_airtime_base_get(bVar6);
    if ((bVar6 & 0xc) == 0) {
      iVar12 = 0;
    }
    else {
      iVar12 = 0x28;
    }
    sdc_conn_radio_overhead_set(context,iVar12 + (uint)((ulonglong)uVar18 * (ulonglong)(iVar14 + 0xdf41) >> 0x26) +
                         0xc5);
    local_38 = U(0x368);
    iVar19 = I(0x24);
    iVar14 = radio_phy_airtime_base_get(B(0x6f));
    iVar12 = I(0x320);
    uVar3 = H(0x28);
    local_38 = (((((local_38 - 0x20) + iVar19) - iVar12) + iVar22) - iVar21) -
               (uint)((ulonglong)uVar18 * (ulonglong)(iVar14 + 0xa3a1) >> 0x26);
    bVar6 = B(0x6f);
    if ((bVar6 & 0xc) == 0) {
      iVar22 = radio_phy_airtime_base_get(bVar6);
      uVar18 = (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar22 = radio_phy_airtime_tail_get(bVar6);
    uVar9 = iVar22 + (iVar12 + 0x30) * 2 + uVar3 + 0x22 + uVar18;
    G58U = uVar9;
    if (local_38 - U(0x368) < 0x244) {
      sdc_assertion_fail(0x30,0x51f); goto after_thunk;
    }
    goto LAB_010131f4;
  case 1:
    iVar14 = I(0x324);
    uVar18 = U(0x318);
    uVar2 = H(0x2f6);
    local_38 = iVar22 * (I(0x14) - iVar14);
    iVar12 = I(0x320);
    bVar6 = B(0x6f);
    iVar22 = I(0x310);
    uVar3 = H(0x28);
    if ((bVar6 & 0xc) == 0) {
      iVar19 = radio_phy_airtime_base_get(bVar6);
      uVar9 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar19 + 0xa3a1) >> 0x26);
    }
    else {
      uVar9 = 0x65;
    }
    iVar19 = radio_phy_airtime_tail_get(bVar6);
    uVar9 = iVar19 + (uint)uVar3 +
                     (iVar14 * (iVar21 + (uint)uVar2 + ~uVar18) + iVar22 * uVar18 + iVar12 + 0x30) *
                     2 + uVar9;
    G58U = uVar9;
LAB_010131f4:
    uVar18 = U(0x14);
    break;
  case 2:
    uVar10 = sdc_timing_scale(I(0x314) + I(0x24),sVar8);
    U(0x320) = uVar10;
    iVar22 = sdc_timing_scale(U(0x14),sVar8);
    uVar18 = MAGIC;
    bVar6 = B(0x6f);
    if (U(0x14) < 0x1d4c) {
      iVar22 = iVar22 + 2;
    }
    I(0x324) = iVar22;
    iVar22 = radio_phy_airtime_base_get(bVar6);
    if ((bVar6 & 0xc) == 0) {
      iVar21 = 0;
    }
    else {
      iVar21 = 0x28;
    }
    sdc_conn_radio_overhead_set(context,iVar21 + (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xdf41) >> 0x26) +
                         0xc5);
    if ((S(0x2f6) == 0) && (allow_reschedule != 0)) {
      iVar19 = I(0x314);
      iVar14 = I(0x24);
      uVar7 = B(0x6f);
      iVar22 = radio_phy_airtime_base_get(uVar7);
      iVar12 = I(0x36c);
      iVar13 = I(0x320);
      iVar21 = radio_phy_airtime_tail_get(uVar7);
      local_38 = (((iVar19 + iVar14 + -0x20 + iVar12) - iVar13) - iVar21) -
                 (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xa3a1) >> 0x26);
      iVar22 = I(0x320);
    }
    else {
      iVar22 = I(0x320);
      local_38 = (I(0x314) + I(0x24)) - iVar22;
    }
    iVar14 = I(0x310);
    iVar21 = I(0x318);
    bVar6 = B(0x6f);
    uVar3 = H(0x28);
    if ((bVar6 & 0xc) == 0) {
      iVar12 = radio_phy_airtime_base_get(bVar6);
      uVar18 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar12 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar12 = radio_phy_airtime_tail_get(bVar6);
    uVar9 = iVar12 + (uint)uVar3 + (iVar21 * iVar14 + iVar22 + 0x30) * 2 + uVar18;
    uVar18 = U(0x14);
    G58U = uVar9;
    B(0x31c) = 1;
    break;
  case 3:
    uVar18 = U(0x14);
    local_38 = uVar18 * iVar22;
    if ((allow_reschedule == 0) || (S(0x2f6) != 0)) {
      if (SC(0x333) != '\0') {
        uVar9 = G58U;
        break;
      }
      uVar18 = (uint)H(0x2f6);
    }
    else {
      B(0x333) = 0;
      uVar18 = 0;
    }
    iVar12 = I(0x324);
    uVar9 = local_38 - iVar12 * iVar22;
    if ((((SC(0xc5) == '&') || (SC(0xc6) == '&')) &&
        (-1 < (int)((event_counter - H(0x3bc)) * 0x10000))) &&
       (B(0x3bf) != 0)) {
      bVar6 = B(0x3bf);
    }
    local_38 = uVar9;
    if ((iVar14 != 0) && (uVar18 == 0)) {
      iVar22 = I(0x36c);
      if (iVar22 == 0) {
        sdc_assertion_fail(0x30,0x571); goto after_thunk;
      }
      bVar5 = B(0x6f);
      if ((bVar5 & 0xc) == 0) {
        iVar14 = radio_phy_airtime_base_get(bVar5);
        iVar22 = I(0x36c);
        bVar5 = B(0x6f);
        iVar14 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar14 + 0xa3a1) >> 0x26) + 0x10;
      }
      else {
        iVar14 = 0x75;
      }
      iVar19 = radio_phy_airtime_tail_get(bVar5);
      uVar18 = (uint)H(0x2f6);
      iVar12 = I(0x324);
      local_38 = (((uVar9 - 0x10) + iVar22) - iVar14) - iVar19;
    }
    iVar22 = (iVar12 * (uVar18 + iVar21) + 0x30) * 2;
    if ((bVar6 & 0xc) == 0) {
      iVar21 = radio_phy_airtime_base_get(bVar6);
      uVar18 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar21 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar21 = radio_phy_airtime_tail_get(bVar6);
    uVar9 = uVar18 + iVar21 + iVar22;
    uVar18 = U(0x14);
    G58U = uVar9;
    if (uVar18 < 0x1d4c) {
      uVar7 = sdc_conn_recovery_window_update(uVar18,iVar22,0x21000f58,&local_38);
      B(0x333) = uVar7;
      uVar9 = G58U;
      uVar18 = U(0x14);
    }
    break;
  default:
    sdc_assertion_fail(0x30,0x586);
    goto after_thunk;
  }
  local_38 = local_38 - uVar11;
  uVar11 = (uVar18 - I(0x324)) - 0x1d8;
  if (uVar9 <= uVar11) {
    uVar11 = uVar9;
  }
  U(0x2f0) = uVar11;
  {
    uint _a358 = U(0x358);
    U(0x348) = _a358 + local_38;
    U(0x34c) = I(0x35c) + (uint)(((ulonglong)_a358 + local_38) >> 0x20);
  }
  B(0x338) = 0;
  H(0x340) = 0x92;
  iVar22 = sdc_radio_context_fixed_time_get(context + 0x30);
  S(0x360) = sVar4;
  U(0x33c) = uVar11 + iVar22;
  U(0x358) = U(0x348);
  U(0x35c) = U(0x34c);
  iVar22 = sdc_conn_timing_guard_enabled();
  if (iVar22 != 0) {
    I(0x33c) = I(0x33c) + 0x1e;
  }
  sVar4 = S(0x2e0) - sVar4;
  B(0x342) = 0;
  if (0 < sVar4) {
    B(0x342) = 2;
  }
  if (cVar1 == '\x0e') {
    if (allow_reschedule == 0) goto LAB_010130aa;
  }
  else if (allow_reschedule == 0) {
    if ((SC(0x31c) != '\0') &&
       (sVar8 = controller_timing_request_schedule(context + 0x338,I(0x14) - I(0x324)), sVar8 != 0)) {
      if (event_skip_out == (short *)0x0) {
        return 1;
      }
      *event_skip_out = sVar8;
      return 1;
    }
    goto LAB_010130aa;
  }
  uVar3 = H(0x308);
  if (uVar3 == 0) {
    H(0x30a) = uVar3;
  }
  else if (((uint)H(0x30a) * (uint)B(0x30c) + (uint)B(0x30c) < (uint)uVar3) && (0 < sVar4)) {
    H(0x30a) = H(0x30a) + 1;
    B(0x342) = 0;
    bVar6 = sdc_controller_random_get();
    B(0x30c) = (bVar6 & 7) + 1;
  }
LAB_010130aa:
  iVar22 = sdc_conn_window_admit(B(0x364),context + 0x338);
  if (iVar22 != 0) {
    B(0x330) = (byte)initial_attempt ^ 1;
    return 0;
  }
  PANIC(0x5cf);
  return 0;
}
