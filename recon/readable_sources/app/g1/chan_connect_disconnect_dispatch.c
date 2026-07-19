#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083cfc @ 0x00083cfc
 * public-name: chan_connect_disconnect_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_twim_enable                         <= FUN_00067884 @ 0x00067884
 *   nrfx_twim_disable                        <= FUN_000678d0 @ 0x000678d0
 *   pinctrl_configure_state                  <= FUN_00083cde @ 0x00083cde
 *   chan_connect_disconnect_dispatch         <= FUN_00083cfc @ 0x00083cfc
 */
/* Reconstructed FUN_00083cfc @ 0x83cfc  (parity: 300/300 trials, PROVEN) */

extern void nrfx_twim_enable(int a);
extern void nrfx_twim_disable(int a);
extern int pinctrl_configure_state(unsigned int a, int b, unsigned int c, unsigned int d);

int chan_connect_disconnect_dispatch(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 4);
    if (param_2 != 0) {
        if (param_2 == 1) {
            iVar1 = pinctrl_configure_state(*(unsigned int *)(iVar2 + 0x20), 0,
                                 param_3, param_4);
            if (-1 < iVar1) {
                nrfx_twim_enable(iVar2);
            }
        } else {
            iVar1 = -0x86;
        }
        return iVar1;
    }
    nrfx_twim_disable(iVar2);
    iVar2 = pinctrl_configure_state(*(unsigned int *)(iVar2 + 0x20), 1, param_3, param_4);
    return iVar2;
}
