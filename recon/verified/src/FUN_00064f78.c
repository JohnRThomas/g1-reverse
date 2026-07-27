/* Reconstructed g1_recon_nrfx_gppi_task_endpoint_setup @ 0x64f78.
 * Raw identity/back-map: FUN_00064f78.  Parity: 300/300 trials, PROVEN.
 */

extern void FUN_0007e2fa(unsigned long, ...);
extern unsigned int FUN_0007e2ec(int a, int b);
void g1_recon_nrfx_gppi_task_endpoint_setup(
    unsigned int channel, int task_endpoint,
    unsigned int param_3, unsigned int param_4)
{
  unsigned int val = channel;
  if (task_endpoint == 0) {
    FUN_0007e2fa(0x00099cbdUL, 0x000f6a4aUL, 0x000f6a09UL, 0x4a, param_4);
    val = FUN_0007e2ec(0x000f6a09UL, 0x4a);
  }
  *(volatile unsigned int *)(task_endpoint + 0x80) = val | 0x80000000UL;
}
