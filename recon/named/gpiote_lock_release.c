/* named: gpiote_lock_release */
/* globals referenced:
//   0x20002c30  g_gpiote_lock                
*/
/* Reconstructed gpiote_lock_release @ 0x659cc  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_free(unsigned int, unsigned int);
void gpiote_lock_release(unsigned int param_1)
{
    nrfx_flag32_free(0x20002c30UL, param_1);
}

