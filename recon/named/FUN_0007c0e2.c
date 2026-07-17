/* readable reconstruction; identity: FUN_0007c0e2 @ 0x0007c0e2
 * public-name: FUN_0007c0e2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   enqueue_uid                              <= FUN_00018e48 @ 0x00018e48
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 */
/* Reconstructed FUN_0007c0e2 @ 0x7c0e2  (parity: 300/300 trials, PROVEN) */

extern int ancs_get_conn_ctx(void);
extern int enqueue_uid(void *p);
extern void k_sem_give(unsigned int a);

void FUN_0007c0e2(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  struct event_record {
    unsigned int value;
    unsigned int mode;
    unsigned int context;
  } event = { param_1, (param_2 & 0xffffff00u) | 2u, param_3 };
  int iVar1 = ancs_get_conn_ctx();
  int iVar2 = enqueue_uid(&event);
  if (iVar2 == 0) {
    k_sem_give((unsigned int)iVar1 + 0x200);
  }
}
