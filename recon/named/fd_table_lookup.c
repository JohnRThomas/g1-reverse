/* readable reconstruction; identity: FUN_0004b01c @ 0x0004b01c
 * public-name: fd_table_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fd_table_lookup                          <= FUN_0004b01c @ 0x0004b01c
 * address symbols (name @ address):
 *   g_fd_table                               @ 0x20002550
 */
/* Reconstructed FUN_0004b01c @ 0x4b01c  (parity: 300/300 trials, PROVEN) */

extern void *thunk_FUN_00071678(void);

unsigned int fd_table_lookup(unsigned int param_1)
{
  if (param_1 < 0x10 && *(volatile int*)(param_1 * 0x28 + 0x20002550UL) != 0) {
    return 0;
  }
  unsigned int *puVar1 = (unsigned int*)thunk_FUN_00071678();
  *puVar1 = 9;
  return 0xffffffff;
}
