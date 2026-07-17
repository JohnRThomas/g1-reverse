/* readable reconstruction; identity: FUN_0101a2e0 @ 0x0101a2e0
 * public-name: FUN_0101a2e0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_state_get               <= FUN_01019204 @ 0x01019204
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 *   g_net_session_queue_obj                  @ 0x210010f0
 */
/* net-core FUN_0101a2e0 @ 0x101a2e0  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int);
extern void FUN_01019128(void);
extern void *controller_radio_state_get(void);
extern void FUN_01019254(void);
extern void FUN_010196e0(void);
extern void FUN_0101dd0c(unsigned int);
extern void FUN_0101de60(void *);
extern int FUN_01022ebc(unsigned int);

void FUN_0101a2e0(void)
{
  volatile unsigned char * const pcVar2 = (volatile unsigned char *)0x210010a0;
  volatile unsigned char *puVar3;
  unsigned char r2;

  if (pcVar2[0] == 0) {
    sdc_assertion_fail(0x21, 0x17b);
    for (;;) { sdc_assertion_fail(0x21, 0x17b); }
  }

  if (pcVar2[0x2c] != 0) {
    goto L_332;
  }

  if (pcVar2[0] == 5) {
    goto L_34e;
  }
  goto L_2f6;

L_332:
  if (pcVar2[0] != 5) {
    sdc_assertion_fail(0x21, 0x25b);
    for (;;) { sdc_assertion_fail(0x21, 0x25b); }
  }
  if (*(volatile unsigned int *)(pcVar2 + 0x70) == 0) {
    goto L_2f6;
  }
  FUN_0101de60((void *)(pcVar2 + 0x50));
  goto L_2fc;

L_34e:
  if (*(volatile unsigned int *)(pcVar2 + 0x70) != 0) {
    goto L_2f6;
  }
  {
    unsigned int off = *(volatile unsigned int *)(pcVar2 + 0x28);
    FUN_0101dd0c(off + 0x2d8);
  }

L_2f6:
  FUN_0101dd0c(0x210010f0);

L_2fc:
  if (pcVar2[2] == 0) goto L_306;
  if (pcVar2[0x2c] == 0) goto L_360;
  goto L_306;

L_360:
  FUN_01019128();
  goto L_306;

L_306:
  FUN_01019254();
  pcVar2[0x2c] = 0;
  r2 = pcVar2[0];
  pcVar2[2] = 0;
  *(volatile unsigned int *)(pcVar2 + 0x28) = 0;
  if (r2 == 4) {
    FUN_010196e0();
  }
  pcVar2[0] = 0;
  puVar3 = (volatile unsigned char *)controller_radio_state_get();
  {
    unsigned int r0b = puVar3[0];
    int iVar4 = FUN_01022ebc(r0b);
    if (iVar4 == 0) {
      sdc_assertion_fail(0x21, 0x396);
      for (;;) { sdc_assertion_fail(0x21, 0x396); }
    }
  }
  puVar3[0] = 0x20;
}
