/* readable reconstruction; identity: FUN_010215a8 @ 0x010215a8
 * public-name: FUN_010215a8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41004500                             @ 0x41004500
 *   REG_4100850c                             @ 0x4100850c
 */
/* net-core FUN_010215a8 @ 0x10215a8  (parity 300 trials PROVEN) */

void FUN_010215a8(unsigned int param_1)
{
  volatile unsigned int *a = (volatile unsigned int*)0x41004500;
  volatile unsigned int *b = (volatile unsigned int*)0x4100850c;

  if ((int)param_1 > 0) {
    *a = 1;
    *b = (param_1 - 3) & 0xff;
  } else {
    *a = 0;
    *b = param_1 & 0xff;
  }
}
