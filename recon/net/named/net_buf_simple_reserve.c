/* readable reconstruction; identity: FUN_01030014 @ 0x01030014
 * public-name: net_buf_simple_reserve
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_reserve                   <= FUN_01030014 @ 0x01030014
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103de6b                           @ 0x0103de6b
 */
/* net-core FUN_01030014 @ 0x1030014  (parity 300 trials PROVEN) */

extern void assert_print(unsigned int a, unsigned int b, unsigned int c);
extern unsigned long long FUN_01039bb0(unsigned int a, unsigned int b);

void net_buf_simple_reserve(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned long long rv;
  unsigned int r0v, r1v;
  if (param_1 == 0) {
    assert_print(0x0103d2a7u, 0x0103de6bu, 0x2b);
    rv = FUN_01039bb0(0x0103de6bu, 0x2b);
  } else {
    if ((short)param_1[1] == 0) {
      *param_1 = param_1[2] + param_2;
      return;
    }
    assert_print(0x0103d2a7u, 0x0103de6bu, 0x2c);
    rv = FUN_01039bb0(0x0103de6bu, 0x2c);
  }
  r0v = (unsigned int)rv;
  r1v = (unsigned int)(rv >> 32);
  {
    unsigned short r3s = *(volatile unsigned short *)(r0v + 4);
    if (r3s == 0) {
      unsigned int r3vv = *(volatile unsigned int *)(r0v + 8);
      r3vv = r3vv + r1v;
      *(volatile unsigned int *)r0v = r3vv;
    }
  }
  return;
}
