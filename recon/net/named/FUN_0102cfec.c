/* readable reconstruction; identity: FUN_0102cfec @ 0x0102cfec
 * public-name: FUN_0102cfec
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102cfec @ 0x102cfec  (parity 300 trials PROVEN) */

void FUN_0102cfec(void)
{
  volatile unsigned int *p1 = (volatile unsigned int *)0x41012000;
  volatile unsigned int *p2 = (volatile unsigned int *)0x41016000;
  *(volatile unsigned int *)((char*)p1 + 0x1ac) = *(volatile unsigned int *)((char*)p1 + 0x1ac) & 0x7fffffff;
  *(volatile unsigned int *)((char*)p2 + 0x14c) = 0;
  (void)*(volatile unsigned int *)((char*)p2 + 0x14c);
}
