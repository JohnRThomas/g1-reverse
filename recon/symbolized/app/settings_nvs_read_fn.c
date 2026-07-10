#include "g1_app_symbols.h"
/* named: settings_nvs_read_fn */
/* Reconstructed settings_nvs_read_fn @ 0x7f210  (parity: 300/300 trials, PROVEN) */

extern int settings_nvs_read_latest(int a, int b, int c, int d);
int settings_nvs_read_fn(unsigned int *param_1, int param_2, int param_3) {
    unsigned short h = *(unsigned short*)((char*)param_1 + 4);
    int iVar1 = settings_nvs_read_latest((int)param_1[0], (int)h, param_2, param_3);
    if (param_3 <= iVar1) iVar1 = param_3;
    return iVar1;
}

