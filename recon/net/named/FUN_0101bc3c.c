/* readable reconstruction; identity: FUN_0101bc3c @ 0x0101bc3c
 * public-name: FUN_0101bc3c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_radio_context_fixed_time_get         <= FUN_0100f0fc @ 0x0100f0fc
 *   sdc_conn_radio_overhead_set              <= FUN_0100f48c @ 0x0100f48c
 *   signed_drift_clamp                       <= FUN_0100f69c @ 0x0100f69c
 *   radio_transition_overhead_get            <= FUN_0101a0e8 @ 0x0101a0e8
 *   controller_packet_space_limit            <= FUN_0101dc50 @ 0x0101dc50
 *   schedule_node_list_is_locked             <= FUN_0101dec4 @ 0x0101dec4
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 * address symbols (name @ address):
 *   rodata_103c290                           @ 0x0103c290
 */
/* net-core FUN_0101bc3c @ 0x101bc3c  (parity 2 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))
#define S16(a) (*(volatile short*)(u32)(a))

extern void sdc_assertion_fail(unsigned,unsigned);
extern unsigned radio_transition_overhead_get(void);
extern unsigned radio_phy_airtime_base_get(unsigned);
extern void sdc_conn_radio_overhead_set(unsigned, unsigned);
extern unsigned schedule_node_list_is_locked(void);
extern unsigned signed_drift_clamp(int, unsigned);
extern unsigned controller_packet_space_limit(unsigned, unsigned, unsigned, unsigned);
extern unsigned sdc_radio_context_fixed_time_get(unsigned);
extern unsigned sdc_conn_window_admit(unsigned, void*);

void FUN_0101bc3c(unsigned param_1)
{
  if (param_1 == 0) { for(;;) sdc_assertion_fail(0x35,0x1b1); }
  if (W8(param_1+0x300) != 0) { for(;;) sdc_assertion_fail(0x35,0x1b2); }
  if (W8(param_1+0x301) == 0x20) { for(;;) sdc_assertion_fail(0x35,0x1b3); }

  u16 uVar3 = (u16)radio_transition_overhead_get();

  u32 uVar9 = 0;
  u32 uVar6;
  int local_1c;
  int skip_dec = 0;

  u8 sw = W8(param_1+0x300);
  if (sw > 3) { for(;;) sdc_assertion_fail(0x35,0x264); }

  if (sw == 0) {
    u8 bVar1 = W8(param_1+0x6f);
    u16 uVar2 = W16(0x0103c290u + (u32)W8(param_1+0x6e)*2u);
    W8(param_1+0x300) = 1;
    u32 iVar4 = radio_phy_airtime_base_get(bVar1);
    int iVar5 = ((bVar1 & 0xc) == 0) ? 0 : 0x28;
    uVar9 = 0;
    unsigned long long prod = (unsigned long long)0x10624dd3u *
                               (unsigned long long)(u32)(uVar2 + 0x79d + iVar4);
    sdc_conn_radio_overhead_set(param_1, (u32)iVar5 + (u32)(prod >> 0x26) + 199u);
    u32 iVar4b = schedule_node_list_is_locked();
    if (iVar4b != 0) {
      uVar6 = 0; local_1c = 0; skip_dec = 1;
    }
    /* else: fall directly into the "recompute uVar6" path below (LAB_0101bd1e) */
  } else {
    if (sw == 1 || sw == 3) {
      uVar9 = W32(param_1+0x14);
    } else { /* sw == 2 */
      uVar9 = W32(param_1+0x308);
      W8(param_1+0x300) = 3;
    }
  }

  if (!skip_dec) {
    u32 needRecalc;
    if (sw == 0) {
      needRecalc = 1; /* case0's else path always lands on LAB_0101bd1e */
    } else {
      u32 iVar4 = schedule_node_list_is_locked();
      needRecalc = (iVar4 == 0);
    }
    if (needRecalc) {
      uVar6 = signed_drift_clamp((int)S16(param_1+0x2fc), 2);
      local_1c = (int)uVar6 >> 31;
      S16(param_1+0x2fc) = (short)(S16(param_1+0x2fc) - (short)uVar6);
    } else {
      uVar6 = 0; local_1c = 0;
    }
  }

  {
    u32 uVar7 = W32(param_1+0x2d8);
    u32 uVar8 = uVar9 + uVar7;
    u32 local_20 = uVar8 + uVar6;
    W32(param_1+0x2d8) = local_20;
    unsigned carry1 = (uVar8 < uVar9) ? 1u : 0u;
    unsigned carry2 = (local_20 < uVar8) ? 1u : 0u;
    local_1c = local_1c + (int)W32(param_1+0x2dc) + (int)carry1 + (int)carry2;
    W32(param_1+0x2dc) = (u32)local_1c;

    (void)uVar3;
    u8 fieldc5 = W8(param_1+0xc5);
    u8 local_26;
    if (((fieldc5 & 0xfd) == 0xc) || (fieldc5 == 0x26)) {
      controller_packet_space_limit(param_1, 0, 0, fieldc5 & 0xfd);
      local_26 = 0;
    } else {
      u32 iVar4c = controller_packet_space_limit(param_1, 0, 0, fieldc5 & 0xfd);
      if (iVar4c != 0) {
        local_26 = (W8(param_1+0x300) == 1) ? 1 : 2;
      } else {
        local_26 = 0;
      }
    }
    (void)local_26;

    u32 local_2c = sdc_radio_context_fixed_time_get(param_1+0x30);
    (void)local_2c;

    struct {
      u8 b0,b1,b2,b3;
      u32 w;
      u16 h;
      u8 c1,c2;
      /* The event transport reserves three trailing words for the producer. */
      u32 reserved[3];
    } buf;
    buf.b0 = 0;
    buf.h = uVar3;
    buf.c1 = local_26;
    buf.c2 = 1;
    buf.w = local_2c;

    u32 iVar4 = sdc_conn_window_admit(W8(param_1+0x301), &buf);
    if (iVar4 != 0) {
      return;
    }
    for(;;) sdc_assertion_fail(0x35,0x1b7);
  }
}
