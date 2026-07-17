/* readable reconstruction; identity: FUN_0100a440 @ 0x0100a440
 * public-name: FUN_0100a440
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_bufpool_slot_cnt                   @ 0x21000bb8
 *   g_net_bufpool_base_ptr                   @ 0x21000bbc
 */
/* net-core FUN_0100a440 @ 0x100a440  (parity 300 trials PROVEN) */
#define P_0100a4c8 0x21000bbc
#define P_0100a4cc 0x21000bb8

extern void sdc_assertion_fail(int, int);
extern void FUN_0100a31c(unsigned char *, int);

unsigned char *FUN_0100a440(void)
{
  unsigned char local_d;
  unsigned char *local_c;

  local_c = (unsigned char *)0;
  local_d = 0;
  for (;;) {
    if (*(volatile unsigned char *)P_0100a4cc <= local_d) break;
    if (*(unsigned char *)((unsigned int)local_d * 0x28 + *(volatile unsigned int *)P_0100a4c8) != 0) {
      local_c = (unsigned char *)((unsigned int)local_d * 0x28 + *(volatile unsigned int *)P_0100a4c8);
      break;
    }
    local_d = local_d + 1;
  }
  if (local_c == (unsigned char *)0) {
    sdc_assertion_fail(9, 0xa9);
  }
  if (local_c != (unsigned char *)0) {
    local_c[2] = 0;
    FUN_0100a31c(local_c, 1);
    *local_c = 0;
  }
  return local_c;
}
