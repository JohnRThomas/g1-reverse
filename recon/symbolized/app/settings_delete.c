#include "g1_app_symbols.h"
/* named: settings_delete */
/* Reconstructed settings_delete @ 0x7f198  (parity: 300/300 trials, PROVEN) */

extern void settings_save_one(unsigned int, unsigned int);
void settings_delete(unsigned int param_1)
{
    settings_save_one(param_1, 0);
}

