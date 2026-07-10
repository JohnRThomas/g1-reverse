/* named: FUN_00047a84 */
/* globals referenced:
//   0x2001b811  g_display_page_dirty_flag    
*/
/* Reconstructed FUN_00047a84 @ 0x47a84  (parity: 300/300 trials, PROVEN) */

int FUN_00047a84(int param_1, int *param_2, int *param_3)
{
    *param_3 = 200;
    if (*(volatile unsigned char*)0x2001b811UL != 0) {
        *param_2 = 0x27e;
        *param_3 = 199;
        return 0;
    }
    *param_2 = 0x240;
    *param_3 = 0x88;
    return *(volatile int*)(0x0008ac20UL + param_1 * 4);
}

