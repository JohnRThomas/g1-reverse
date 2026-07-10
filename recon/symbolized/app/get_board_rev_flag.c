#include "g1_app_symbols.h"
/* named: get_board_rev_flag */
/* Reconstructed get_board_rev_flag @ 0x25284  (parity: 300/300 trials, PROVEN) */

unsigned char get_board_rev_flag(void) {
    return *(volatile unsigned char*)((uintptr_t)&g_board_rev_flag) /*=0x20018c69*/;
}

