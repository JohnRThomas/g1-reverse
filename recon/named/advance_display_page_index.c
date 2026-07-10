/* named: advance_display_page_index */
/* globals referenced:
//   0x2001b810  g_display_page_index         
//   0x2001b811  g_display_page_dirty_flag    
*/
/* Reconstructed advance_display_page_index @ 0x369f8  (parity: 300/300 trials, PROVEN) */

void advance_display_page_index(void)
{
    *(volatile unsigned char*)0x2001b811UL = 1;
    unsigned char bVar1 = (unsigned char)(*(volatile unsigned char*)0x2001b810UL + 1);
    if (bVar1 >= 5) {
        bVar1 = 0;
    }
    *(volatile unsigned char*)0x2001b810UL = bVar1;
}

