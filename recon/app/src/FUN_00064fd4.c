/* Reconstructed g1_recon_nrfx_gppi_task_endpoint_clear @ 0x64fd4.
 * Raw identity/back-map: FUN_00064fd4.  Parity: 300/300 trials, PROVEN.
 */

extern unsigned long long FUN_0007e2ec(unsigned int,unsigned int);
extern void FUN_0007e2fa(unsigned int,unsigned int,unsigned int,unsigned int);
void g1_recon_nrfx_gppi_task_endpoint_clear(
    unsigned int channel, int task_endpoint,
    unsigned int param_3, unsigned int param_4)
{
  if (task_endpoint == 0) {
    FUN_0007e2fa(0x00099cbdUL,0x000f6a4aUL,0x000f6a09UL,99);
    task_endpoint = (int)(FUN_0007e2ec(0x000f6a09UL,99) >> 32);
  }
  *(unsigned int *)(task_endpoint + 0x80) = 0;
  return;
}
