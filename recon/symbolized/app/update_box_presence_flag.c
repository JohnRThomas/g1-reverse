#include "g1_app_symbols.h"
/* named: update_box_presence_flag */
/* globals referenced:
//   0x20018c68  g_box_present_flag           
*/
/* Reconstructed update_box_presence_flag @ 0x254a0  (parity: 300/300 trials, PROVEN) */

extern int update_box_field_debounce(void);

void update_box_presence_flag(int param_1, unsigned char *param_2)
{
    int iVar1 = update_box_field_debounce();
    *param_2 = (iVar1 != 0);
    volatile unsigned char *flagp = (volatile unsigned char*)((uintptr_t)&g_box_present_flag) /*=0x20018c68*/;
    if (iVar1 != 0) {
        if (*flagp == 0) {
            *flagp = 1;
        }
    } else {
        if (*flagp != 0) {
            *flagp = 0;
            if (*(volatile char*)((char*)param_1+2) == 0) {
                *(volatile unsigned char*)((char*)param_1+5) = 1;
            }
        }
    }
}

