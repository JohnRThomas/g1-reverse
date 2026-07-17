/* readable reconstruction; identity: FUN_00082346 @ 0x00082346
 * public-name: att_cfm_sent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_clear_bit_0                       <= FUN_00081e14 @ 0x00081e14
 *   att_cfm_sent                             <= FUN_00082346 @ 0x00082346
 */
/* Reconstructed FUN_00082346 @ 0x82346  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(void);
extern void atomic_clear_bit_0(int,unsigned int);
extern void FUN_0005833c(int*);
void att_cfm_sent(unsigned int param_1,int *param_2,int param_3)
{
  if (param_3 == 0) {
    FUN_000822ae();
  }
  atomic_clear_bit_0(*param_2 + 0x120,0);
  FUN_0005833c(param_2);
  return;
}
