/* readable reconstruction; identity: FUN_0102fa4c @ 0x0102fa4c
 * public-name: FUN_0102fa4c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102fa4c @ 0x102fa4c  (parity 300 trials PROVEN) */

extern void *FUN_0103b62e(void*, int, int);
extern void FUN_01039190(void*, int, int);
void FUN_0102fa4c(unsigned int param_1, unsigned int param_2, int param_3, int param_4)
{
  unsigned char buf[0x1c];
  FUN_0103b62e(buf, 0, 0x10);
  buf[2] = 2;
  *(unsigned int*)(buf+4) = 0x0103ac2f;
  *(unsigned int*)(buf+0x10) = param_1;
  *(unsigned int*)(buf+0x14) = param_2;
  FUN_01039190(buf, param_3, param_4);
}
