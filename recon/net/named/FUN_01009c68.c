/* readable reconstruction; identity: FUN_01009c68 @ 0x01009c68
 * public-name: FUN_01009c68
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01009c68 @ 0x1009c68  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern signed char FUN_0102741e(void *, unsigned int, signed char);
extern signed char FUN_01027470(void *, unsigned short);
extern unsigned int FUN_010274ea(void *, signed char);
extern unsigned int FUN_0102751a(void *, unsigned short, signed char);

unsigned int FUN_01009c68(unsigned short param_1, unsigned char param_2)
{
  volatile int * const tbl = (volatile int *)0x21000b7c;
  int iVar3 = tbl[param_2];
  if (iVar3 == 0) {
    return 0;
  }
  if (param_1 > 0xeff) {
    FUN_01008d00(0x17, 0x27e);
  }
  signed char cVar1 = FUN_01027470((void *)iVar3, param_1);
  if (cVar1 != -1) {
    return FUN_010274ea((void *)iVar3, cVar1);
  }
  signed char divv = *(volatile unsigned char *)(iVar3 + 2);
  signed char cVar1b = (signed char)param_1 - (signed char)((short)param_1 / divv) * divv;
  signed char cVar2 = FUN_0102741e((void *)iVar3, 0xfff0, cVar1b);
  if (cVar2 == -1) {
    return 0;
  }
  if (cVar2 != cVar1b) {
    *(volatile unsigned char *)(iVar3 + 3) = 0;
  }
  return FUN_0102751a((void *)iVar3, param_1, cVar2);
}
