/* readable reconstruction; identity: FUN_000844e0 @ 0x000844e0
 * public-name: transport_send_type2_via_ops
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_send_type2_via_ops             <= FUN_000844e0 @ 0x000844e0
 */
/* Reconstructed FUN_000844e0 @ 0x844e0  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(int, void *, int, short);

void transport_send_type2_via_ops(int *param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char local_29 = param_2;
  unsigned char *local_28 = &local_29;
  unsigned int local_24 = 1;
  unsigned char local_20 = 0;
  unsigned int local_1c = param_3;
  unsigned int uStack_18 = param_4;
  unsigned char local_14 = 2;
  int base = *param_1;
  int fieldVal = *(int *)(base + 8);
  fnptr fp = *(fnptr *)(fieldVal + 8);
  (void)local_24; (void)local_20; (void)local_1c; (void)uStack_18; (void)local_14;
  fp(base, &local_28, 2, (short)param_1[1]);
}
