/* readable reconstruction; identity: FUN_0002560c @ 0x0002560c
 * public-name: init_nfc_comm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_nfc_comm                            <= FUN_0002560c @ 0x0002560c
 *   process_pt_data                          <= FUN_000330ec @ 0x000330ec
 * address symbols (name @ address):
 *   rodata_9f196                             @ 0x0009f196
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_0002560c @ 0x2560c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000330a8(unsigned int a0);
extern int process_pt_data(void);
extern void log_message(unsigned int a0);

int init_nfc_comm(void)
{
  int iVar1;
  volatile unsigned int *volatile state = (volatile unsigned int *)0x20007a44UL;
  iVar1 = FUN_000330a8(*state);
  if (iVar1 == 0) {
    iVar1 = process_pt_data();
    if (iVar1 != 0) { iVar1 = -2; }
  } else {
    log_message(0x0009f196);
    iVar1 = -1;
  }
  return iVar1;
}
