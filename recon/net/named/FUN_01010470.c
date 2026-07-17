/* readable reconstruction; identity: FUN_01010470 @ 0x01010470
 * public-name: FUN_01010470
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_sdc_rssi_filter_cfg                    @ 0x21000f04
 */
/* net-core FUN_01010470 @ 0x1010470  (parity 1 trials PROVEN) */
extern signed char FUN_0101e2cc(unsigned char);
extern unsigned long long controller_time_now(void);
extern int FUN_0100cfc0(unsigned short, void *);
extern int FUN_0101e2fc(void *, int, int, int);
extern void sdc_assertion_fail(unsigned int, unsigned int);

#define DAT_01010574 0x21000f04

void FUN_01010470(int param_1)
{
  signed char cVar3;
  int iVar4;
  unsigned int uVar5;
  int iVar6;
  unsigned int uVar7;
  unsigned int *puVar8;
  unsigned int uVar9;
  int bVar10;
  unsigned long long uVar11;
  unsigned long long lVar12;
  unsigned char packet[12];
  signed char *pcVar2;
  unsigned char *controller = (unsigned char *)(long)(param_1 - 0x258);

  cVar3 = FUN_0101e2cc(controller[0x6f]);
  puVar8 = (unsigned int *)(long)(param_1 + -0x1b0);
  pcVar2 = (signed char *)DAT_01010574;
  iVar6 = *(int *)(long)(param_1 + -0x1a8) + 0x800;
  iVar4 = (iVar6 * 0x1000) >> 0x18;

  int shifted = iVar6 >> 0xc;
  signed char negShifted = (signed char)(-shifted);

  if (iVar4 < pcVar2[0]) {
    iVar4 = (int)negShifted + (int)pcVar2[1];
  } else if (iVar4 <= pcVar2[2]) {
    return;
  } else {
    iVar4 = (int)negShifted + (int)pcVar2[3];
  }

  signed char cVar4;
  if (iVar4 > 0x7f) {
    cVar4 = 0x7f;
  } else if (iVar4 < -0x80) {
    cVar4 = (signed char)0x80;
  } else {
    cVar4 = (signed char)iVar4;
  }
  if (cVar4 == 0) {
    return;
  }

  if (*(unsigned int *)(long)(param_1 + -0x1ac) != 0x7fffffff || *puVar8 != 0xffffffff) {
    uVar11 = controller_time_now();
    uVar9 = (unsigned int)(uVar11 >> 0x20);
    uVar5 = *puVar8;
    uVar7 = *(unsigned int *)(long)(param_1 + -0x1ac);
    bVar10 = uVar5 <= (unsigned int)uVar11;
    if (uVar7 < uVar9 || uVar9 - uVar7 < (unsigned int)bVar10) {
      iVar6 = FUN_0100cfc0(*(unsigned short *)(long)(param_1 + -600), packet);
      if (iVar6 != 0) {
        sdc_assertion_fail(0x7a, 0x85);
        return;
      }
      iVar4 = FUN_0101e2fc(packet, cVar3 + 1, cVar4, 2);
      if (iVar4 == 0) {
        uVar9 = (unsigned int)(unsigned char)pcVar2[4];
        lVar12 = controller_time_now();
        unsigned long long wide = (unsigned long long)uVar9 * 1000000ULL;
        *(volatile unsigned long long *)puVar8 = lVar12 + wide;
      }
    }
  }
  return;
}
