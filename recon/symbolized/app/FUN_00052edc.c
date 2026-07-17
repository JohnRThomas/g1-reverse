#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052edc @ 0x00052edc
 * public-name: FUN_00052edc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_subsys_init                     <= FUN_0004e744 @ 0x0004e744
 * address symbols (name @ address):
 *   rodata_88178                             @ 0x00088178
 *   rodata_f2c46                             @ 0x000f2c46
 */
/* Reconstructed FUN_00052edc @ 0x52edc  (parity: 300/300 trials, PROVEN) */

extern int settings_subsys_init(void);
extern void FUN_0004d944(unsigned int a, unsigned int b, void *c, unsigned int d);

int FUN_00052edc(void)
{
    int iVar1 = settings_subsys_init();
    if (iVar1 != 0) {
        struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
        s.f0 = 3;
        s.f1 = ((unsigned long)&rodata_f2c46) /*=0xf2c46*/;
        s.f2 = iVar1;
        FUN_0004d944(((unsigned long)&rodata_88178) /*=0x88178*/, 0x1840, &s, 0);
    }
    return iVar1;
}
