/* readable reconstruction; identity: FUN_0008688e @ 0x0008688e
 * public-name: z_handle_obj_poll_events
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_handle_obj_poll_events                 <= FUN_0008688e @ 0x0008688e
 */
/* Reconstructed FUN_0008688e @ 0x8688e  (parity: 300/300 trials, PROVEN) */

extern void FUN_000867da(void);
void z_handle_obj_poll_events(int *param_1)
{
  int *piVar1 = (int *)*(volatile int *)param_1;
  if (param_1 != piVar1) {
    int iVar3 = *(volatile int *)piVar1;
    int *piVar2 = (int *)*(volatile int *)(piVar1 + 1);
    *(volatile int *)piVar2 = iVar3;
    *(volatile int *)(iVar3 + 4) = (int)piVar2;
    *(volatile int *)piVar1 = 0;
    *(volatile int *)(piVar1 + 1) = 0;
    FUN_000867da();
  }
}
