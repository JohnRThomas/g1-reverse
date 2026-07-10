/* named: set_display_page_index */
/* globals referenced:
//   0x2001b810  g_display_page_index         
//   0x2001b811  g_display_page_dirty_flag    
*/
/* Reconstructed set_display_page_index @ 0x369dc  (parity: 300/300 trials, PROVEN) */

void set_display_page_index(unsigned int param_1)
{
  if (param_1 > 4) {
    param_1 = 0;
  }
  *(volatile unsigned char *)0x2001b811UL = 1;
  *(volatile unsigned char *)0x2001b810UL = (unsigned char)param_1;
}

