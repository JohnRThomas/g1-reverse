/* readable reconstruction; identity: FUN_010294a2 @ 0x010294a2
 * public-name: FUN_010294a2
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010294a2 @ 0x10294a2 — true CFG extent 12 bytes (ends 0x10294ae) */

extern unsigned int FUN_0102946c(unsigned short, unsigned char,
                                 unsigned int, unsigned short);

unsigned int FUN_010294a2(volatile unsigned short *param_1,
                          volatile unsigned short *param_2,
                          unsigned int param_3)
{
  unsigned short uVar2 = *param_1;
  *param_2 = uVar2;
  unsigned char cVar1 = *((volatile unsigned char *)param_1 + 2);
  /* The tail wrapper carries its untouched opaque r2 context and the copied
     halfword in r3 into the shared worker. */
  return FUN_0102946c(uVar2, cVar1, param_3, uVar2);
}
