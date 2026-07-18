/* readable reconstruction; identity: FUN_00024d40 @ 0x00024d40
 * public-name: set_time_mark
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_time_mark                            <= FUN_00024d40 @ 0x00024d40
 * address symbols (name @ address):
 *   g_elapsed_time_mark                      @ 0x20007a28
 */
/* Reconstructed FUN_00024d40 @ 0x24d40  (parity: 300/300 trials, PROVEN) */

extern unsigned int thunk_FUN_00074f68(void);
void set_time_mark(void)
{
  unsigned int uVar1 = thunk_FUN_00074f68();
  *(volatile unsigned int *)0x20007a28UL = uVar1;
}
