/* readable reconstruction; identity: FUN_010166c0 @ 0x010166c0
 * public-name: FUN_010166c0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   ble_ext_adv_header_field_get             <= FUN_0100e294 @ 0x0100e294
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   controller_work_update_or_enqueue        <= FUN_0100efc8 @ 0x0100efc8
 */
/* net-core FUN_010166c0 @ 0x10166c0  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(unsigned int, unsigned int);
extern int FUN_0100ca98(int, int);
extern void FUN_0100d5c8(unsigned int, int);
extern unsigned short FUN_0100d5d0(unsigned int);
extern void FUN_0100e018(unsigned int, void*);
extern unsigned int *ble_ext_adv_header_field_get(unsigned char*, int);
extern void sdc_work_submit(unsigned int, unsigned int, int);
extern void controller_work_update_or_enqueue(unsigned int, unsigned int, int);

#define DAT_010167e0 0x21000f90u
#define DAT_010167e4 (DAT_010167e0 + 0x14u)
#define DAT_010167e8_ADDR (DAT_010167e0 + 0x0eu)
#define DAT_010167ec (DAT_010167e0 + 0x89u)
#define DAT_010167f0 (DAT_010167e0 + 0x1au)
#define DAT_010167f4 0x010175c9u
#define DAT_010167f8 0x01016a71u
#define DAT_010167fc (DAT_010167e0 + 0x2au)

void FUN_010166c0(int param_1, unsigned char *param_2)
{
  char cVar1;
  unsigned char uVar2;
  int iVar3;
  unsigned int uVar4;
  unsigned short uVar5;
  unsigned int uVar6;
  unsigned int *puVar7;
  int iVar8;
  unsigned int *puVar9;
  unsigned int uVar10;
  unsigned int auStack_18[2];

  iVar3 = DAT_010167e0;
  puVar7 = auStack_18;
  puVar9 = (unsigned int *)(DAT_010167e0 + 0x50);
  *(volatile unsigned char *)(DAT_010167e0 + 9) = 0;
  uVar6 = *(volatile unsigned int *)((unsigned short *)(*(volatile unsigned int*)puVar9) + 10);
  *(volatile unsigned short *)(iVar3 + 10) = *(volatile unsigned short *)(*(volatile unsigned int*)puVar9);
  uVar5 = FUN_0100d5d0(uVar6);
  *(volatile unsigned short *)(iVar3 + 0x20) = uVar5;
  uVar5 = *(volatile unsigned short *)(*(volatile int *)(iVar3 + 0x50) + 0x1e);
  *(volatile unsigned short *)(iVar3 + 0x22) = *(volatile unsigned short *)(*(volatile int *)(iVar3 + 0x50) + 0x1c);
  *(volatile unsigned short *)(iVar3 + 0x26) = 0xff00;
  *(volatile unsigned short *)(iVar3 + 0x24) = uVar5;
  *(volatile unsigned short *)(iVar3 + 0x28) = 0xffff;
  if (param_1 == 0) {
    FUN_0100e018(*(volatile unsigned int *)(iVar3 + 0xc0), auStack_18);
    uVar10 = ((unsigned int)(**(volatile unsigned char **)(iVar3 + 0xc0)) << 0x19) >> 0x1f;
  } else {
    puVar7 = ble_ext_adv_header_field_get(param_2, 1);
    uVar10 = (unsigned int)(*param_2 >> 7);
  }
  iVar8 = DAT_010167e4;
  if (((*(volatile char *)(iVar3 + 0x7d) == 0) || (uVar10 == 0)) ||
      ((*(volatile unsigned char *)((int)puVar7 + 5) & 0xc0) != 0x40)) {
    cVar1 = *(volatile char *)(iVar3 + 0x79);
    *(volatile unsigned int *)(iVar3 + 0x14) = 0;
    *(volatile unsigned short *)(iVar8 + 4) = 0;
    iVar8 = DAT_010167e8_ADDR;
  } else {
    *(volatile unsigned int *)(iVar3 + 0x14) = *puVar7;
    cVar1 = *(volatile char *)(iVar3 + 0x79);
    *(volatile unsigned short *)(iVar8 + 4) = *(volatile unsigned short *)(puVar7 + 1);
    iVar8 = DAT_010167e8_ADDR;
  }
  if (cVar1 == -1) {
    uVar2 = *(volatile unsigned char *)(iVar3 + 0x90);
    *(volatile unsigned int *)(iVar3 + 0x1a) = 0;
    uVar6 = *(volatile unsigned int *)(iVar3 + 0x89);
    *(volatile unsigned short *)(iVar8 + 0x10) = 0;
    uVar5 = *(volatile unsigned short *)(iVar8 + 0x7f);
    *(volatile unsigned char *)(iVar3 + 0xd) = uVar2;
    *(volatile unsigned int *)(iVar3 + 0xe) = uVar6;
    *(volatile unsigned short *)(iVar8 + 4) = uVar5;
  } else {
    iVar8 = FUN_0100ca98(cVar1, iVar8 + -1);
    if (iVar8 == 0) {
      sdc_assertion_fail(0x32, 0x1596);
      return;
    }
    *(volatile unsigned char *)(iVar3 + 0xd) = *(volatile unsigned char *)(iVar3 + 0xd) | 2;
    puVar9 = (unsigned int *)DAT_010167ec;
    if (param_1 != 0) {
      puVar9 = ble_ext_adv_header_field_get(param_2, 0);
    }
    iVar8 = DAT_010167f0;
    *(volatile unsigned int *)(iVar3 + 0x1a) = *puVar9;
    *(volatile unsigned short *)(iVar8 + 4) = *(volatile unsigned short *)(puVar9 + 1);
  }
  FUN_0100d5c8(*(volatile unsigned int *)(iVar3 + 0x50), (int)*(volatile char *)(iVar3 + 0x59));
  sdc_work_submit(DAT_010167e0, DAT_010167f4, 2);
  uVar6 = DAT_010167f8;
  uVar2 = *(volatile unsigned char *)((int)*(volatile unsigned short **)(iVar3 + 0x50) + 0xcd);
  *(volatile unsigned short *)(iVar3 + 0x33) = **(volatile unsigned short **)(iVar3 + 0x50);
  uVar4 = DAT_010167fc;
  *(volatile unsigned char *)(iVar3 + 0x35) = uVar2;
  controller_work_update_or_enqueue(uVar4, uVar6, 2);
  return;
}
