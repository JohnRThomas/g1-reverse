/* readable reconstruction; identity: FUN_01011d14 @ 0x01011d14
 * public-name: FUN_01011d14
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_packet_airtime_compute        <= FUN_010109ec @ 0x010109ec
 *   controller_descriptor_octet_product      <= FUN_01012b24 @ 0x01012b24
 * address symbols (name @ address):
 *   rodata_103c1bc                           @ 0x0103c1bc
 */
/* net-core FUN_01011d14 @ 0x1011d14  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int a, unsigned int b) __attribute__((noreturn));
extern int controller_descriptor_octet_product(void);
extern int controller_packet_airtime_compute(unsigned int a, int b, int c, int d, int e);

typedef unsigned char BOOL;

BOOL FUN_01011d14(unsigned int param_1, int *param_2)
{
  int iVar1, iVar2, iVar5;
  unsigned int cVar3;
  unsigned int uVar4, uVar6;

  if (*param_2 == 0) {
    sdc_assertion_fail(0x2d, 0x3fc);
  }
  iVar1 = controller_descriptor_octet_product();
  uVar6 = *(volatile unsigned char *)((char *)param_2 + 0xc);
  cVar3 = *(volatile unsigned char *)((char *)param_2 + 0xd);
  if (uVar6 == 4) {
    if (cVar3 == 4) {
      uVar4 = 0x2c;
      iVar5 = (iVar1 + -1) * 0x80;
      cVar3 = 8;
      iVar2 = 0x690;
    } else {
      iVar5 = (iVar1 + -1) * 0x80;
      uVar4 = 0x2c;
      iVar2 = 0x690;
    }
  } else {
    uVar4 = *(volatile unsigned short *)(0x0103c1bc + uVar6 * 2) + 999;
    uVar4 = (unsigned int)(((unsigned long long)0x10624dd3ULL * (unsigned long long)uVar4) >> 32);
    if (cVar3 == 4) {
      cVar3 = 8;
    }
    iVar5 = (iVar1 + -1) * 0x80;
    uVar4 = uVar4 >> 6;
    if (uVar6 == 8) {
      iVar2 = 0x690;
    } else if (uVar6 == 2) {
      iVar2 = 0x60;
    } else {
      iVar2 = 0xf0;
    }
  }
  iVar1 = controller_packet_airtime_compute(param_1, iVar2 * iVar1 + iVar5 + uVar4, cVar3, 0, (short)param_2[1]);
  return (unsigned int)(iVar1 + 0x131) <= (unsigned int)param_2[2];
}
