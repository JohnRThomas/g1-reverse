/* readable reconstruction; identity: FUN_00080c46 @ 0x00080c46
 * public-name: FUN_00080c46
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_le_param_update                  <= FUN_0008157a @ 0x0008157a
 */
/* Reconstructed FUN_00080c46 @ 0x80c46  (parity: 300/300 trials, PROVEN) */

extern int FUN_000527dc(void);
extern long long bt_conn_le_param_update(unsigned int);
extern void FUN_0007350c(int, int, unsigned int, unsigned int);
extern void FUN_00073518(int);

void FUN_00080c46(unsigned int param_1)
{
  int iVar1;
  long long uVar2;
  iVar1 = FUN_000527dc();
  if (iVar1 == 0) return;
  uVar2 = bt_conn_le_param_update(param_1);
  if ((int)uVar2 != 0 && (int)uVar2 != -0x78) {
    FUN_0007350c(iVar1 + 0x38, (int)(uVar2 >> 32), 0x8000, 0);
    return;
  }
  FUN_00073518(iVar1 + 0x38);
}
