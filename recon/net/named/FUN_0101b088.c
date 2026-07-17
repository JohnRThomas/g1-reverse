/* readable reconstruction; identity: FUN_0101b088 @ 0x0101b088
 * public-name: FUN_0101b088
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_state_get               <= FUN_01019204 @ 0x01019204
 *   radio_slot_margin_get                    <= FUN_0101a130 @ 0x0101a130
 *   controller_timing_snapshot_build         <= FUN_0101a38c @ 0x0101a38c
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 * address symbols (name @ address):
 *   rodata_101b321                           @ 0x0101b321
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101b088 @ 0x101b088  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int a, unsigned int b);
extern void *controller_radio_state_get(void);
extern unsigned int radio_slot_margin_get(void);
extern unsigned int FUN_01022e34(unsigned int a, unsigned int b);
extern unsigned int controller_timing_snapshot_build(void *a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int sdc_conn_window_admit(unsigned int a, void *b);

unsigned int FUN_0101b088(unsigned int param_1, int param_2)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char *)0x210010a0;
  void *puVar3;
  unsigned int uVar2 = 0x0101b321;
  int iVar4, iVar5, iVar7;
  unsigned int uVar6, uVar8;
  unsigned char auStack_30[24];

  if (param_2 != 0) {
    return 0x11;
  }
  if (*pcVar1 != 0) {
    return 0xc;
  }
  puVar3 = controller_radio_state_get();
  pcVar1[1] = 0;
  *pcVar1 = 4;
  pcVar1[0x2e] = 0;
  *(volatile unsigned short *)(pcVar1 + 0x74) = 0;
  iVar4 = radio_slot_margin_get();
  uVar6 = 0;
  iVar7 = 0;
  uVar8 = 0;
  do {
    iVar5 = uVar6 + 2;
    uVar8 = uVar8 + 1;
    uVar6 = uVar8 & 0xff;
    iVar7 = iVar7 + *(volatile int *)(pcVar1 + iVar5 * 4) + iVar4;
  } while (uVar6 <= (unsigned char)pcVar1[0x2f]);
  *(volatile int *)(pcVar1 + 0x58) = iVar7;
  iVar7 = FUN_01022e34(uVar2, 0);
  *(unsigned char *)puVar3 = (unsigned char)iVar7;
  if (iVar7 == 0x20) {
    sdc_assertion_fail(0x21, 0x366);
  }
  iVar7 = controller_timing_snapshot_build(auStack_30, 1, 0, param_1);
  if (iVar7 == 0) {
    sdc_assertion_fail(0x21, 0x368);
  }
  iVar7 = sdc_conn_window_admit(*(unsigned char *)puVar3, auStack_30);
  if (iVar7 != 0) {
    return 0;
  }
  sdc_assertion_fail(0x21, 0x369);
  return 0;
}
