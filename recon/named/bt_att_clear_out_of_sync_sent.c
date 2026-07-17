/* readable reconstruction; identity: FUN_00082572 @ 0x00082572
 * public-name: bt_att_clear_out_of_sync_sent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_get                                  <= FUN_0005858c @ 0x0005858c
 *   atomic_clear_bit_0                       <= FUN_00081e14 @ 0x00081e14
 *   bt_att_clear_out_of_sync_sent            <= FUN_00082572 @ 0x00082572
 */
/* Reconstructed FUN_00082572 @ 0x82572  (parity: 300/300 trials, PROVEN) */

extern int att_get(void);
extern void atomic_clear_bit_0(int *a, int b);
void bt_att_clear_out_of_sync_sent(void)
{
  int iVar1;
  int *piVar2;

  iVar1 = att_get();
  if (iVar1 != 0) {
    for (piVar2 = *(volatile int **)(iVar1 + 0x30); piVar2 != (int *)0; piVar2 = (int *)*(volatile int *)piVar2) {
      atomic_clear_bit_0(piVar2 + -0x1c, 5);
    }
  }
}
