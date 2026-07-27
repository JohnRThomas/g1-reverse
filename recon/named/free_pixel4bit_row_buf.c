/* readable reconstruction; identity: FUN_00047ab8 @ 0x00047ab8
 * public-name: free_pixel4bit_row_buf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   free_pixel4bit_row_buf                   <= FUN_00047ab8 @ 0x00047ab8
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 * address symbols (name @ address):
 *   g_pixel4bit_row_buf                      @ 0x20009fcc
 */
/* Reconstructed FUN_00047ab8 @ 0x47ab8  (parity: 300/300 trials, PROVEN) */

extern void free(int);

void free_pixel4bit_row_buf(void)
{
  volatile int *piVar1 = (volatile int *)0x20009fccUL;
  int value = *piVar1;
  if (value != 0) {
    free((unsigned int)value);
    *piVar1 = 0;
  }
}
