/* readable reconstruction; identity: FUN_01019128 @ 0x01019128
 * public-name: FUN_01019128
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 * address symbols (name @ address):
 *   rodata_1017579                           @ 0x01017579
 */
/* net-core FUN_01019128 @ 0x1019128  (parity 300 trials PROVEN) */

extern void sdc_work_submit(unsigned int a0, unsigned int a1, unsigned int a2);

void FUN_01019128(void)
{
  unsigned int iVar1 = 0x21000f90u;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned short uVar4;
  unsigned char bVar5;

  bVar5 = (*(volatile unsigned char *)(iVar1 + 0x54)) == 3;
  if (bVar5) {
    uVar4 = **(volatile unsigned short **)(iVar1 + 0x50);
  } else {
    uVar4 = 0;
  }
  *(volatile unsigned short *)(iVar1 + 0x40) = uVar4;
  uVar3 = 0x21000fc6u;
  uVar2 = 0x01017579u;
  *(volatile unsigned char *)(iVar1 + 0x3f) = bVar5;
  sdc_work_submit(uVar3, uVar2, 2);
  return;
}
